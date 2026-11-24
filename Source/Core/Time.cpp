#include "Core/Time.h"
#include <algorithm>

Time& Time::GetInstance()
{
	static Time instance;
	return instance;
}

void Time::Update()
{
	LONGLONG nowCount = GetNowHiPerformanceCount();
	// すり抜けの帽子やブレークポイントで止めて再開するたびにワープする
	// 問題の回避のために0.1秒を上限にする。上限はスローになるだけで問題にならない
	_unscaledDeltaTime = std::min((nowCount - _prevCount) / 1e6f, 0.1f);
	_prevCount = nowCount;
	_totalTime += _unscaledDeltaTime * _timeScale;
}

void Time::Reset()
{
	_prevCount = GetNowHiPerformanceCount();
	_unscaledDeltaTime = 0.0f;
	_totalTime = 0.0f;
}