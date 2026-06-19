

#include "AnimationGroup.h"

class AnimationGroupLinear : public AnimationGroup
{
private:
	int current_animation;

	virtual void _play() override;
	virtual void _progress(const float delta) override;
	virtual void _revers() override;


public:
	AnimationGroupLinear(const float duration, const bool cycling = false, const bool reversing = false);
};