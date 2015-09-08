#include <iostream>
#include "inexor/rpc/InexorServiceImpl.h"

// Legacy
#define STANDALONE //we only need the minimal stuff from cube.h, meaning the cubescript part.
#include "inexor/shared/cube.h"

using namespace google::protobuf;

namespace inexor {
namespace rpc {


  void InexorServiceImpl::EvalCubescript(RpcController* ctrl,
      const Cubescript* req, CubescriptResult* res,
      Closure* done) {

    tagval v;
    ::executeret(req->code().c_str(), v);

    switch (v.type) {
      case VAL_STR:   res->set_s(v.getstr()); break;
      case VAL_INT:   res->set_i(v.getint()); break;
      case VAL_FLOAT: res->set_f(v.getfloat()); break;
      case VAL_NULL:   break;
      default:
        std::cerr << "[ERROR] Invalid command return value!"
                  << std::endl;
        // TODO: Proper error handling
    }
  
    if (done)
      done->Run();
  }

}
}
