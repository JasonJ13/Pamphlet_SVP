#pragma once

template<class T>
class Animation
{
private :
	T *ptr;
	T vbegin;
	T vend;
	float duration;
	float t;
	bool is_playing;
	const bool cycle;
	const bool reversing;

	void revers();

public :
	Animation(T *ptr, const T vend, const float duration, const bool cycle, const bool reversing = true);

	void play();
	void pause();
	void progress(const float delta);
};

#include "Animation.inl"