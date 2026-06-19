#pragma once

class Animation
{
private:
	bool playing;
	const bool cycling;
	bool reversing;

	virtual void _play() = 0;
	virtual void _progress(const float delta) = 0;
	virtual void _revers() = 0;

protected:
	float duration;
	float t;

public:
	Animation(const float duration, const bool cycling = false, const bool reversing = false);
	~Animation() = default;

	float get_duration() const;
	bool is_playing() const;

	void play();
	void pause();
	void resume();
	void progress(const float delta);
	void revers();
};