file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_executable(integration_testing ${srcs} src/sp/extractor/test_entity_extractor.cpp src/sp/test_source_processor.cpp src/qps/test_query_processing_subsystem.cpp src/test_spa.cpp)


target_link_libraries(integration_testing spa)
