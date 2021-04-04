find_package(OpenCV REQUIRED)

add_library(physarumgen_lib
    src/agent_interface.cpp
    src/agent_physarum.cpp
    src/world.cpp
    src/world_sampler.cpp
    src/utils.cpp
)

target_include_directories(physarumgen_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(physarumgen_lib LINK_PUBLIC ${OpenCV_LIBS})
