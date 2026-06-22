add_library(lib_core
  myMain.cpp myMain.h
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
  Animation/Animationunit.inl Animation/AnimationUnit.hpp
  Animation/AnimationGroup.cpp Animation/AnimationGroup.h
  Animation/AnimationGroupLinear.cpp Animation/AnimationGroupLinear.h
  Animation/AnimationGroupParallel.cpp Animation/AnimationGroupparallel.h

)
target_include_directories(lib_core PUBLIC ./)
target_link_libraries(lib_core PUBLIC sfml-graphics)