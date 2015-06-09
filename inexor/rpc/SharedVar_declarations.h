#ifndef INEXOR_RPC_SHARED_VAR_DECLARATIONS_HEADER
#define INEXOR_RPC_SHARED_VAR_DECLARATIONS_HEADER

#include <boost/preprocessor.hpp>

#include "inexor/util/preprocessing.h"

// This should generate extern ... declarations for all
// available SharedVar's in the project
#define SV(pid, ptype, pname, cpptype, cpppath, include, deprecated) \
    BOOST_PP_IF(BOOST_PP_AND(include, BOOST_PP_NOT(deprecated))      \
        INEXOR_PP_NSP_DECLARE(extern cpptype, cpppath),              \
        BOOST_PP_NULL)
#include "inexor/rpc/vars.pp"
#undef SV

#endif
