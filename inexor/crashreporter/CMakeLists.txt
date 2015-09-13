
if(NOT MINGW)
declare_module(crashreporter .)
add_lib(crashreporter)
endif()

function(config_crashreporter targ)
  if(MINGW)
    return()
  endif()
  message(STATUS "Configuring ${targ} with crashreporter")
  if (";${ARGN};" MATCHES ";NOLINK;")
    set(NOLINK "NOLINK")
  endif()

  target_link_libs(${targ} module_crashreporter ${NOLINK})

endfunction()