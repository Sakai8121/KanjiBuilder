#pragma once
#include <cmath>

struct Vector2
{
    float x = 0.0f;
    float y = 0.0f;

    // --- コンストラクタ ---
    constexpr Vector2() = default;
    constexpr Vector2(float x, float y) : x(x), y(y) {}

    // --- 基本の四則演算 ---
    constexpr Vector2 operator+(const Vector2& rhs) const { return { x + rhs.x, y + rhs.y }; }
    constexpr Vector2 operator-(const Vector2& rhs) const { return { x - rhs.x, y - rhs.y }; }
    constexpr Vector2 operator*(float scalar) const { return { x * scalar, y * scalar }; }
    constexpr Vector2 operator/(float scalar) const { return { x / scalar, y / scalar }; }

    constexpr Vector2& operator+=(const Vector2& rhs) { x += rhs.x; y += rhs.y; return *this; }
    constexpr Vector2& operator-=(const Vector2& rhs) { x -= rhs.x; y -= rhs.y; return *this; }
    constexpr Vector2& operator*=(float scalar) { x *= scalar; y *= scalar; return *this; }

    // --- 長さ・距離 ---
    float LengthSq() const { return x * x + y * y; }
    float Length() const { return std::sqrt(LengthSq()); }

    static float DistanceSq(const Vector2& a, const Vector2& b) { return (b - a).LengthSq(); }
    static float Distance(const Vector2& a, const Vector2& b) { return (b - a).Length(); }

    // --- 正規化 ---
    Vector2 Normalized() const
    {
        float len = Length();
        if (len <= 1e-6f) return { 0.0f, 0.0f };
        return { x / len, y / len };
    }

    // --- 内積・2D外積 ---
    static constexpr float Dot(const Vector2& a, const Vector2& b) { return a.x * b.x + a.y * b.y; }
    static constexpr float Cross(const Vector2& a, const Vector2& b) { return a.x * b.y - a.y * b.x; }

    // --- 線形補間 ---
    static constexpr Vector2 Lerp(const Vector2& a, const Vector2& b, float t)
    {
        return a + (b - a) * t;
    }

    // --- よく使う定数 ---
    static constexpr Vector2 Zero() { return { 0.0f, 0.0f }; }
    static constexpr Vector2 One() { return { 1.0f, 1.0f }; }
    static constexpr Vector2 Up() { return { 0.0f, -1.0f }; } // DxLibはY軸下向きが正
    static constexpr Vector2 Down() { return { 0.0f, 1.0f }; }
    static constexpr Vector2 Left() { return { -1.0f, 0.0f }; }
    static constexpr Vector2 Right() { return { 1.0f, 0.0f }; }
};

// スカラー値を左側に書いた場合（例: 2.0f * vec）の対応
constexpr Vector2 operator*(float scalar, const Vector2& rhs) { return rhs * scalar; }