
#include <algorithm>
#include <iostream>

#include "Animation.hpp"

template<class T>
Animation<T>::Animation(T *ptr, const T vend, const float duration, const bool cycle, const bool reversing) : ptr{ ptr }, vbegin{ *ptr }, vend{ vend }, duration{ duration }, t{ 0 }, is_playing{ false }, cycle{ cycle }, reversing{ reversing } {}

template<class T>
void Animation<T>::play()
{
	*ptr = vbegin;
	is_playing = true;
	t = 0;
}

template<class T>
void Animation<T>::revers()
{
	T inter = vend;
	vend = vbegin;
	vbegin = inter;
}

template<class T>
void Animation<T>::pause()
{
	is_playing = false;
}

template<class T>
void Animation<T>::progress(const float delta)
{
	if (is_playing)
	{
		t = std::min(t + delta,duration);

		*ptr = (vbegin * (duration - t) + vend * t) / duration;

		if (t == duration)
		{
			is_playing = cycle;
			if (reversing) revers();
			if (cycle) play();
			
		}
	}
	
}