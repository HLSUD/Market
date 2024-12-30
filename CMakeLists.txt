set(base_SRCS_ex
	demo_lev2_stock.cpp
	KsTool.cc
	main.cpp
)

include_directories(${PROJECT_SOURCE_DIR}/include)

LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib)

add_executable(main ${base_SRCS_ex})

target_link_libraries(main lev2mdapi)
target_link_libraries(main pthread rt)
set_target_properties(main PROPERTIES OUTPUT_NAME "main")
