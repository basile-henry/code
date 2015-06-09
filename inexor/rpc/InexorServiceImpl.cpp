#if defined(__MINGW32__) && (defined(__X86__) || defined(_X86_) || defined(i386))
// Work around a mingw bug: Both intrin.h (included by
// SDL.h) and x86intrin.h (included by the stdlib) declare
// intrinsics. However the former one uses "extern C", while
// the latter one does not. Hence g++ complains about
// conflicting declarations
// The linkage for intrinsics doesn't matter, but at that
// stage the compiler doesn't know; so, to avoid compile
// errors we ensure that x86intrin.h is included with an
// `extern C` declaration.
//
// See:
// * https://sourceforge.net/tracker/index.php?func=detail&aid=3018394&group_id=202880&atid=983354
// * http://eigen.tuxfamily.org/bz/attachment.cgi?id=48&action=diff#a/Eigen/Core_sec2
// * http://eigen.tuxfamily.org/bz/show_bug.cgi?id=125
extern "C" {
#include <x86intrin.h>
}
#endif

#include <iostream>
#include "inexor/rpc/InexorServiceImpl.h"

#include "inexor/rpc/SharedVar.h"
#include "inexor/rpc/SharedVar_declarations.h"

// Legacy
#include "inexor/shared/cube.h"

using namespace google::protobuf;

namespace inexor {
namespace rpc {


  void InexorServiceImpl::EvalCubescript(RpcController* ctrl,
      const Cubescript* req, CubescriptResult* res,
      Closure* done) {

#ifndef STANDALONE
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
#endif
  
    if (done)
      done->Run();
  }

void InexorServiceImpl::VarSet(RpcController* ctrl,
  const VarSetP* req, VarSetR* res, Closure* done) {
    const varMap &values = req.values()
    const Reflection ref = values.GetReflection();
    // TODO: This seems pretty inefficient; we need a very
    // simple iterator only!
    vector<const FieldDescriptor*> fields;
    ref->ListFields(values, &fields);

    for (auto field : fields) {
        auto id = field->getIndex();
        switch (id) {

#define SV(pid, ptype, pname, cpptype, cppname, include, deprecated) \
          case pid :                                       \
            if (deprecated)                                \
                res.problems().add_deprecated(id);         \
            else if (!include)                             \
                res.problems().add_unused(id);             \
            else                                           \
                cppname = values.pname();                  \
            break;
#include "inexor/rpc/vars.pp"
#undef SV

          default:
            res.problems().add_unsupported(id);
            break;
        }
    }

    if (done) done->Run();
}

void InexorServiceImpl::VarGet(RpcController* ctrl,
  const VarGetP* req, VarGetR* res, Closure* done) {
    varList &vars = req.variables();
    varMap  &values = res.values();
    for (auto i=0; i< vars.id_size(); i++) {
        auto id = vars.id(i);
        switch (id) {

#define SV(pid, ptype, pname, cpptype, cppname, include, deprecated) \
          case pid :                                       \
            if (deprecated)                                \
                res.problems().add_deprecated(id);         \
            else if (!include)                             \
                res.problems().add_unused(id);             \
            else                                           \
                values.set_ ## pname (cppname);            \
            break;
#include "inexor/rpc/vars.pp"
#undef SV

          default:
            res.problems().add_unsupported(id);
            break;
        }
    }
    if (done) done->Run();
}

void InexorServiceImpl::VarSubscribe(RpcController* ctrl,
    const VarSubscribeP* req, VarSubscribeR* res,
    Closure* done);
void InexorServiceImpl::VarUnsubscribe(RpcController* ctrl,
    const VarUnsubscribeP* req, VarUnsubscribeR* res,
    Closure* done);
void InexorServiceImpl::VarGetSubscriptions(RpcController* ctrl,
    const VarGetSubscriptionsP* req,
    VarGetSubscriptionsR* res, Closure* done);

}
}
