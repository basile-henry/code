#ifndef SB_IPC_MC_SOCKET_SERVER_HEADER
#define SB_IPC_MC_SOCKET_SERVER_HEADER

#include <list>
#include <string>
#include <iostream>
#include <memory>

#include <cstdint>
#include <cstdio>

#include <asio.hpp>

#include "inexor/net/MessageConnect.h"
#include "inexor/net/MCServer.h"
#include "inexor/net/MCSocket.h"
#include "inexor/compat/make_unique.h"

namespace inexor {
namespace net {

#ifdef WIN32
    #define PIPE_BUF_SIZE 50000
    class windowspipe : public MCServer 
    {
        typedef asio::io_service service;

        bool initilized = false;
        bool own_serv = false;

        service *serv;
        asio::windows::stream_handle handle;

        HANDLE pipe = INVALID_HANDLE_VALUE;
        OVERLAPPED overlapped;

      public:
        /// Default constructor with special service.
        //windowspipe(service &srv_) : serv(&srv_), handle(*serv) {}

        /// Default constructor with fresh ASIO io service
        windowspipe(std::string name) : own_serv(true), serv(new service), handle(*serv)
        {
            pipe = CreateNamedPipe(name.c_str(), 
                PIPE_ACCESS_DUPLEX
                | FILE_FLAG_FIRST_PIPE_INSTANCE
                | FILE_FLAG_OVERLAPPED,
                PIPE_TYPE_BYTE
                | PIPE_READMODE_BYTE
                | PIPE_NOWAIT, // non blocking mode -> what else needed?
                20, PIPE_BUF_SIZE, PIPE_BUF_SIZE, 0, 0);

            if(pipe != INVALID_HANDLE_VALUE)
            {
                handle.assign(pipe);
                overlapped = { 0 };
                initilized = true;
            }
        }

        ~windowspipe()
        {
            DisconnectNamedPipe(pipe);
        }

        virtual std::unique_ptr<MessageConnect> getNextStream()
        {
            overlapped.hEvent = CreateEvent(0, true, false, 0);
            if(!ConnectNamedPipe(pipe, &overlapped))
            {
                unsigned error = GetLastError();
                if(error != ERROR_PIPE_CONNECTED && error != ERROR_IO_PENDING)
                {
                    DisconnectNamedPipe(pipe);
                    return NULL;
                }
            }
            WaitForSingleObject(overlapped.hEvent, INFINITE);
            CloseHandle(overlapped.hEvent);
            return NULL; //todoo
        }

        virtual size_t read(byte *buf, size_t max)
        {
            asio::error_code er;
            //size_t n = std::min(s.available(), max); if(n>0)
            handle.read_some(asio::buffer(buf, max), er);
            if(er) throw asio::system_error(er, "Can not read from pipe");
            return max; //sizeof buffer?
        }

        virtual void write(byte *buf, size_t len)
        {
            asio::error_code er;
            handle.write_some(asio::buffer(buf, len), er); //async_write some instead??
            if(er) throw asio::system_error(er, "Can not write into pipe");
            FlushFileBuffers(pipe); //careful: this blocks! but for how long?
        }
    };
#endif // WIN32

  /**
   * Generic implementation for an ASIO based MCServer.
   *
   * This serves as basis for TCPv4/TCPv6/UNIX-SOCKET based
   * MCServers.
   */
  template <typename protocol>
  class MCSocketServer : public MCServer {
  protected:

    typedef asio::basic_socket_acceptor<protocol> acceptor;
    typedef typename protocol::endpoint endpoint;
    typedef asio::io_service service;

    typedef MCSocket<protocol> mcsoc;

    service srv;
    endpoint end;
    acceptor ack;

    virtual std::unique_ptr<MessageConnect> getNextStream() {
      asio::error_code er;
      std::unique_ptr<mcsoc> s =
          inexor::compat::make_unique<mcsoc>(srv);

      ack.accept(s->Socket(), er);

      if (er == asio::error::basic_errors::try_again)
        return NULL;
      else if (er == asio::error::basic_errors::would_block) //caused by calling in mainloop
        return NULL;
      else if (er)
        throw asio::system_error(er, "Can not accept connection");

      std::cerr << "[INFO] New connection" << std::endl;
      // TODO: Add casting functions for unique_ptr
      return std::unique_ptr<MessageConnect>(s.release());
    }

  public:
    template <typename... T>
    MCSocketServer(T... x) : end(x...), ack(srv, end) {
      ack.non_blocking(true);
    }
  };

  // TODO: This belongs somewhere else
  extern asio::ip::tcp v4();
  extern asio::ip::tcp v6();

  /**
   * MCServer that listens on TCPv4/TCPv6.
   *
   * Initialize with
   *   MCTcpServer(asio::ip::tcp protocol, unsigned short port)
   *   where protocol is one of v4() or v6().
   *
   * TODO: Support listening on specific interface.
   * TODO: Support authentification via file permissions.
   */
  typedef
    MCSocketServer< asio::ip::tcp >
    MCTcpServer;

#if defined(unix) || defined(__unix__) || defined(__unix)
  /**
   * MCServer that listens on a Unix domain socket.
   *
   * Initialize with
   *   MCUnixServer(const char *path)
   *
   * TODO: Initialize with std::string path
   * TODO: Auto delete socket file
   */
  class MCUnixServer :
    public MCSocketServer< asio::local::stream_protocol > {

      std::string path;
  public:
    /**
     * Initialize a new UnixSocket server with a path
     *
     * @param path Path of the unix socket
     */
    MCUnixServer(const char *path_)
        : MCSocketServer( (remove(path_), path_) ),
          path(path_) {}

    /**
     * Initialize a new UnixSocket server with a path
     *
     * @param path Path of the unix socket
     */
    MCUnixServer(std::string &path_)
      : MCUnixServer(path_.c_str()) {}

    /**
     * Destroy this socket server
     *
     * Just deletes the socket link
     */
    virtual ~MCUnixServer() {
      remove(path.c_str());
    }
  };


#endif
  
}
}

#endif
