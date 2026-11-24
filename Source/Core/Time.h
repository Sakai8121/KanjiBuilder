#pragma once
#include <DxLib.h>

class Time
{
public:
	static Time& GetInstance();

	Time(const Time&) = delete;
	Time& operator=(const Time&) = delete;
	Time(Time&&) = delete;
	Time& operator=(Time&&) = delete;

	void Update();
	void Reset();
	float GetDeltaTime() const { return _unscaledDeltaTime * _timeScale; }
	float GetUnscaledDeltaTime() const { return _unscaledDeltaTime; }
	float GetTotalTime() const { return _totalTime; }

	void SetTimeScale(float timeScale) { _timeScale = timeScale; }
	float GetTimeScale() const { return _timeScale; }

private:
	Time() = default;
	~Time() = default;

	LONGLONG _prevCount = 0;
	float _unscaledDeltaTime = 0.0f;
	float _timeScale = 1.0f;
	float _totalTime = 0.0f;
};

