set(SRC "${CMAKE_CURRENT_SOURCE_DIR}/demo.cpp")
set(HDR "")

add_executable( demo ${SRC} ${HDR} )
target_link_libraries( demo PRIVATE viewer_static )

target_compile_features( demo PUBLIC cxx_std_17 )
set_target_properties( demo PROPERTIES CXX_EXTENSIONS OFF )

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT demo)


