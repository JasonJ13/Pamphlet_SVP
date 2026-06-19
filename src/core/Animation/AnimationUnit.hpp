#pragma once

#include "Animation.h"

template<class T>
class AnimationUnit : public Animation
{
private:
	T *ptr;
	T vbegin;
	T vend;

	virtual void _play() override;
	virtual void _progress(const float delta) override;
	virtual void _revers() override;

public:
	AnimationUnit(T *ptr, T vend, const float duration, const bool cycling = false, const bool reversing = false);

};

#include "AnimationUnit.inl"