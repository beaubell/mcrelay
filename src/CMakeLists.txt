
add_executable (mcrelay
    udprelay.cpp
)

target_link_libraries(mcrelay
  PRIVATE
    Threads::Threads
    Boost::system
)

set_property(TARGET mcrelay PROPERTY
    INTERPROCEDURAL_OPTIMIZATION True
)

install(TARGETS mcrelay
    RUNTIME
        DESTINATION bin
)
