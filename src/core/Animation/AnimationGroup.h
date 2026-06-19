#pragma once

#include <vector>
#include <memory>
#include "Animation.h"

class AnimationGroup : public Animation
{
protected:
	std::vector<std::unique_ptr<Animation>> animations;

public :
	AnimationGroup(const float duration, const bool cycling = false, const bool reversing = false);

	void add_Animation(std::unique_ptr<Animation> animation);
};