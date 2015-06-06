#include <string>
#include <iostream>

#include "inexor/rpc/RpcSubsystem.h"

#include "inexor/net/MCSocketServer.h"

using namespace std;
using namespace inexor::net;
using namespace inexor::util;

SUBSYSTEM_REGISTER(rpc, inexor::rpc::RpcSubsystem);

namespace inexor {
namespace rpc {

RpcSubsystem::RpcSubsystem() {
#if defined(unix) || defined(__unix__) || defined(__unix)
    string path = "/tmp/inexor.socket";
    cerr << "[INFO] Listening for IPC connections on: "
      << path << endl;

    socket = boost::make_unique<MCUnixServer>(path);

    // TODO: Windows needs a fast (more secure) IPC transport
#else
    unsigned short port = 56732;
    cerr << "[INFO] Listening for IPC connections on port "
          << port << endl;

    // TODO: This should not require ipv4
    socket = boost::make_unique<MCTcpServer>(v4(), port);
#endif

    server = boost::make_unique(
        rpc_service.get(), &socket->broadcast());
}

void RpcSubsystem::tick() {
    socket->accept_all();
    server->ProcessAllCalls();
}

}
}
