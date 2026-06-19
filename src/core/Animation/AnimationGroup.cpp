#include "AnimationGroup.h"


AnimationGroup::AnimationGroup(const float duration, const bool cycling, const bool reversing) : Animation{ duration, cycling, reversing } {}

void AnimationGroup::add_Animation(std::unique_ptr<Animation> animation)
{
	animations.push_back(std::move(animation));
}