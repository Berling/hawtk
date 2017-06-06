project(hawtk VERSION 0.0.0 LANGUAGES CXX)

add_library(hawtk
	src/context.cpp)
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
install(TARGETS hawtk EXPORT hawtk
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib)
install(EXPORT hawtk DESTINATION lib)
install(DIRECTORY include/hawtk DESTINATION include)
export(TARGETS hawtk FILE hawtk.cmake)
