#include <iostream>
#include <algorithm>

#include "Animation.h"


Animation::Animation(const float duration, const bool cycling, const bool reversing) : duration{ duration }, t{ 0 }, playing{ false }, cycling { cycling }, reversing{ reversing } {}


float Animation::get_duration() const
{
	return duration;
}

bool Animation::is_playing() const
{
	return playing;
}


void Animation::play()
{
	t = 0;
	playing = true;
	_play();
}

void Animation::pause()
{
	playing = false;
}

void Animation::resume()
{
	playing = true;
}

void Animation::progress(const float delta)
{
	if (playing)
	{
		t = std::min(delta + t, duration);

		_progress(delta);

		if (t == duration)
		{
			t = 0;
			playing = reversing || cycling;

			if (reversing) _revers();

			reversing = cycling;
		}
	}
}

void Animation::revers()
{
	_revers();
}