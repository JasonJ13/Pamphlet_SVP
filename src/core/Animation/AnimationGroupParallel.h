
#include "AnimationGroup.h"

class AnimationGroupParallel : public AnimationGroup
{
private:
	virtual void _play() override;
	virtual void _progress(const float delta) override;
	virtual void _revers() override;


public:
	AnimationGroupParallel(const float duration, const bool cycling = false, const bool reversing = false);
};