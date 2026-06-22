add_library(lib_core
  myMain.cpp myMain.h
 "createSQL.cpp" "createXML.cpp" "createXML.h")

target_include_directories(lib_core PUBLIC ./)

target_link_libraries(lib_core PUBLIC pugixml)
if(MSVC)
  target_link_libraries(lib_core PUBLIC sqlite)
else()
  set(THREADS_PREFER_PTHREAD_FLAG ON)
  find_package(Threads REQUIRED)
  target_link_libraries(lib_core PUBLIC sqlite Threads::Threads ${CMAKE_DL_LIBS})
endif()
