#ifndef INEXOR_RPC_RPC_SUBSYSTEM_HEADER
#define INEXOR_RPC_RPC_SUBSYSTEM_HEADER

// Convenience Header

#include <memory>
#include <boost/make_unique.hpp>

#include "inexor/net/MCServer.h"

#include "inexor/rpc/inexor_service.pb.h"
#include "inexor/rpc/InexorServiceImpl.h"
#include "inexor/rpc/MCRpcServer.h"

#include "inexor/util/Subsystem.h"

namespace inexor {
namespace rpc {

class RpcSubsystem : public inexor::util::Subsystem {
public:

    /// The connection we maintain
    std::uniq_ptr<inexor::net::MCServer> socket(NULL);
    /// RPC Call Negotiation
    std::uniq_ptr<MCRpcServer> server(NULL);
    /// RPC Function Implementation
    std::uniq_ptr<InexorService> rpc_service =
        boost::make_unique<InexorServiceImpl>();

    RpcSubsystem();

    void tick();
};


}
}

#endif
