
#include <iostream>

template<class T>
AnimationUnit<T>::AnimationUnit(T *ptr, const T vend, const float duration, const bool cycling, const bool reversing) : ptr{ ptr }, vbegin{ *ptr }, vend{ vend }, Animation{duration,cycling,reversing} {}


template<class T>
void AnimationUnit<T>::_play()
{
	*ptr = vbegin;
}

template<class T>
void AnimationUnit<T>::_progress(const float delta)
{
	*ptr = (vbegin * (duration - t) + vend * t) / duration;

}

template<class T>
void AnimationUnit<T>::_revers()
{
	T inter = vend;
	vend = vbegin;
	vbegin = inter;
}