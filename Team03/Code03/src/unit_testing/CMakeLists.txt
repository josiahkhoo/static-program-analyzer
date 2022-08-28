file(GLOB srcs "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")
add_executable(unit_testing ${srcs} src/spa/common/test_token.cpp src/spa/common/test_t_node.cpp src/spa/sp/extractor/entity/test_assign_entity_node_extractor.cpp src/spa/sp/extractor/entity/test_call_entity_node_extractor.cpp src/spa/sp/extractor/entity/test_constant_entity_node_extractor.cpp src/spa/sp/extractor/entity/test_if_entity_node_extractor.cpp src/spa/sp/extractor/entity/test_print_entity_node_extractor.cpp src/spa/sp/extractor/entity/test_procedure_entity_node_extractor.cpp src/spa/sp/extractor/entity/test_read_entity_node_extractor.cpp src/spa/sp/extractor/entity/test_statement_entity_node_extractor.cpp src/spa/sp/extractor/entity/test_variable_entity_node_extractor.cpp src/spa/sp/extractor/entity/test_while_entity_node_extractor.cpp src/spa/sp/extractor/test_entity_extractor.cpp)

target_link_libraries(unit_testing spa)

