
#include <iostream>

#include "AnimationGroupParallel.h"


AnimationGroupParallel::AnimationGroupParallel(const float duration, const bool cycling, const bool reversing) : AnimationGroup{ duration, cycling, reversing } {}

void AnimationGroupParallel::_play()
{
	for (auto &animation : animations)
	{
		animation->play();
	}
}

void AnimationGroupParallel::_progress(const float delta)
{
	for (auto &animation : animations)
	{
		animation->progress(delta);
	}
}

void AnimationGroupParallel::_revers()
{
	for (auto &animation : animations)
	{
		animation->revers();
	}
}