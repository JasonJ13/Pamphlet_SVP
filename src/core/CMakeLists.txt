add_library(lib_core
  Game.cpp Game.h
  TextureGestioner.cpp TextureGestioner.h

  Object/GameObject.cpp Object/GameObject.h
  Object/FixObject.cpp Object/FixObject.h
  Object/InteractibleObject.cpp Object/InteractibleObject.h
  Object/Parchemin.cpp Object/Parchemin.h
  Object/ParcheminBig.cpp Object/ParcheminBig.h
  Object/ParcheminLittle.cpp Object/ParcheminLittle.h
  Object/Character.cpp Object/Character.h

  Object/Interface/Interface.cpp Object/Interface/Interface.h
  Object/Interface/InterfaceSprite.cpp Object/Interface/InterfaceSprite.h
  Object/Interface/InterfaceRectangle.cpp Object/Interface/InterfaceRectangle.h
  Object/Interface/InterfaceText.cpp Object/Interface/InterfaceText.h

  Animation/Animation.cpp Animation/Animation.h
  Animation/AnimationUnit.inl Animation/AnimationUnit.hpp
  Animation/AnimationGroup.cpp Animation/AnimationGroup.h
  Animation/AnimationGroupLinear.cpp Animation/AnimationGroupLinear.h
  Animation/AnimationGroupParallel.cpp Animation/AnimationGroupParallel.h

  pretreatment/myMainPretreatment.cpp pretreatment/myMainPretreatment.h
  pretreatment/createSQL.cpp pretreatment/createSQL.h
  pretreatment/createXML.cpp pretreatment/createXML.h

)
target_include_directories(lib_core PUBLIC ./)

target_link_libraries(lib_core PUBLIC pugixml sfml-graphics)
if(MSVC)
  target_link_libraries(lib_core PUBLIC sqlite)
else()
  set(THREADS_PREFER_PTHREAD_FLAG ON)
  find_package(Threads REQUIRED)
  target_link_libraries(lib_core PUBLIC sqlite Threads::Threads ${CMAKE_DL_LIBS})
endif()
