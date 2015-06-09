message(STATUS "Detecting Protobuf...")

find_libs(PROTOBUF_LIBRARIES protobuf)
find_path(PROTOBUF_INCLUDE_DIRS google/protobuf/service.h)

# PROTOBUF COMPILER #######

if (NOT DEFINED PROTOC_EXE)
  find_program(PROTOC_EXE protoc)
endif()

# GENERATE VARIABLES MAP

set(RPC_FILE_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "")

set(varmap_out_dir "${CMAKE_BINARY_DIR}/inexor/rpc/proto/")
set(varmap_in  "${RPC_FILE_DIR}/proto/variables_map.proto.pp")
set(varmap_out_dir "${varmap_out_dir}/variables_map.proto")
add_custom_command(
  OUTPUT "${varmap_out}"
  COMMAND ${CMAKE_CXX_COMPILER} -E -I${MAINDIR}
      ${varmap_in} -o ${varmap_out}
  DEPENDS ${varmap_in})
set_source_files_properties(${varmap_out} PROPERTIES GENERATED TRUE)

# RPC PROTOCOL FILE TARGET

set(protoc_in ${RPC_FILE_DIR}/inexor_service.proto)
set(protoc_out_dir "${CMAKE_BINARY_DIR}/inexor/rpc/inexor/rpc/")
set(protoc_out_cc ${protoc_out_dir}/inexor_service.pb.cc)
set(protoc_out
  ${protoc_out_cc}
  ${protoc_out_dir}/inexor_service.pb.h)

add_custom_command(
  OUTPUT ${protoc_out}
  COMMAND ${PROTOC_EXE}
      --proto_path=${MAINDIR}
      --cpp_out=${CMAKE_BINARY_DIR}/inexor/rpc/ ${protoc_in}
  DEPENDS ${protoc_in} ${varmap_out})
set_source_files_properties(${protoc_out} PROPERTIES GENERATED TRUE)
add_custom_target(run_protoc DEPENDS ${protoc_out})

set(RPC_INCLUDE_DIRS "${CMAKE_BINARY_DIR}/inexor/rpc/" CACHE INTERNAL "")

set_source_files_properties(
  ${protoc_out_cc} PROPERTIES GENERATED TRUE)

# MODULE ###############

add_definitions(-DGOOGLE_PROTOBUF_NO_RTTI)
include_directories(${PROTOBUF_INCLUDE_DIRS} ${RPC_INCLUDE_DIRS})

declare_module(rpc .)
set(RPC_MODULE_SOURCES ${RPC_MODULE_SOURCES} ${protoc_out_cc}
  CACHE INTERNAL "")

add_lib(rpc)
config_net(module_rpc NOLINK)

function(config_rpc targ)
  message(STATUS "Configuring ${targ} with rpc")

  add_definitions(-DGOOGLE_PROTOBUF_NO_RTTI)
  add_dependencies(${targ} run_protoc)
  include_directories(${PROTOBUF_INCLUDE_DIRS} ${RPC_INCLUDE_DIRS})
  target_link_libs(${targ}
    module_rpc module_net ${PROTOBUF_LIBRARIES} module_util)
  config_net(${targ})
endfunction()

