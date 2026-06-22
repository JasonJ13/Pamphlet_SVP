
#include <iostream>
#include <cassert>
#include <algorithm>

#include "AnimationGroupLinear.h"


AnimationGroupLinear::AnimationGroupLinear(const float duration, const bool cycling, const bool reversing) : AnimationGroup{ duration, cycling, reversing }, current_animation{ 0 }  {}

void AnimationGroupLinear::_play()
{
	current_animation = 0;
	if (animations.size() != 0) animations[0]->play();
}

void AnimationGroupLinear::_progress(const float delta)
{
	if (current_animation >= animations.size()) return;

	animations[current_animation]->progress(delta);

	if (!animations[current_animation]->is_playing()) 
	{
		++current_animation;
		animations[current_animation]->play();
	}
}

void AnimationGroupLinear::_revers()
{
	for (auto &animation : animations)
	{
		animation->revers();
	}

	std::reverse(animations.begin(), animations.end());
}
