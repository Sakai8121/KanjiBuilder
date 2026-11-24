#pragma once
#include <numbers>
#include <algorithm>

namespace Math
{
	constexpr float Pi = std::numbers::pi_v<float>;
	constexpr float Deg2Rag = Pi / 180.0f;
	constexpr float Rag2Deg = 180.0f / Pi;

	constexpr float ToRadians(float degrees) { return degrees * Deg2Rag; }
	constexpr float ToDegrees(float radians) { return radians * Rag2Deg; }
}