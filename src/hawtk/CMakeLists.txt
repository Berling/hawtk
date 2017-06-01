project(hawtk VERSION 0.0.0 LANGUAGES CXX)

add_library(hawtk)
target_include_directories(hawtk
	PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
	PRIVATE
	src)
target_compile_options(hawtk
	PUBLIC
	$<$<OR:$<CXX_COMPILER_ID:GNU>,$<CXX_COMPILER_ID:Clang>>:-std=c++14 -Wall -Wextra -Werror>
	$<$<CXX_COMPILER_ID:Clang>:-stdlib=libc++>)
target_link_libraries(hawtk
	PUBLIC
	$<$<CXX_COMPILER_ID:Clang>:c++>
	freetype2)
export(TARGETS hawtk FILE hawtk.cmake)
