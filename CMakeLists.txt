
set(base_SRCS_ex
	api_tool_efvi_gx_ex.cc
	XMLConfigEx.h
	XMLConfigEx.cc
	DataFeed.cc
	KsTool.cc
)

include_directories(${PROJECT_SOURCE_DIR}/demo/include)
include_directories(${PROJECT_SOURCE_DIR}/demo/src/api_tool_efvi_gx)
include_directories(${PROJECT_SOURCE_DIR}/demo/src/api_tool_efvi_gx/include)



LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/demo/lib)



add_executable(api_tool_gx_ex ${base_SRCS_ex})

target_link_libraries(api_tool_gx_ex ksHsUdp)
target_link_libraries(api_tool_gx_ex tinyxml2)
target_link_libraries(api_tool_gx_ex pthread rt)

set_target_properties(api_tool_gx_ex PROPERTIES OUTPUT_NAME "gthq_demo")
