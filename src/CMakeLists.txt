
add_executable (udprelay
    udprelay.cpp
)

target_link_libraries(udprelay
  PRIVATE
    Threads::Threads
    Boost::system
)

set_property(TARGET udprelay PROPERTY
    INTERPROCEDURAL_OPTIMIZATION True
)

install(TARGETS udprelay
    RUNTIME
        DESTINATION bin
)