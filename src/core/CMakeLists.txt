add_library(lib_core
  myMain.cpp myMain.h
  Game.cpp Game.h
  TextureGestioner.cpp TextureGestioner.h
  GameObject.cpp GameObject.h
  InteractibleObject.cpp InteractibleObject.h
  Animation.inl Animation.hpp
)
target_include_directories(lib_core PUBLIC ./)
target_link_libraries(lib_core PUBLIC sfml-graphics)