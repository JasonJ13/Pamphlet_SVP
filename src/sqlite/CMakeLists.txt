add_library(sqlite sqlite3.c)
target_include_directories(sqlite PUBLIC ./)

# We prevent CMake Error: CMake can not determine linker language for target: sqlite
set_target_properties(sqlite PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(sqlite)