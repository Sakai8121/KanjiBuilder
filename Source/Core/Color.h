#pragma once
#include <cstdint>

struct Color
{
	std::uint8_t r = 255;
	std::uint8_t g = 255;
	std::uint8_t b = 255;
	std::uint8_t a = 255;

	// constexprはコンパイル時定数を定義したいからつける
	constexpr Color() = default;
	constexpr Color(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a = 255)
		: r(r), g(g), b(b), a(a) {
	}

	// DxLib用のカラーコードに変換（<DxLib.h>への依存が発生するため実装は.cppに隠蔽）
	unsigned int ToDxColor() const;

	// よく使う定数色
	static constexpr Color White() { return { 255, 255, 255 }; }
	static constexpr Color Black() { return { 0, 0, 0 }; }
	static constexpr Color Red() { return { 255, 60, 60 }; }
	static constexpr Color Green() { return { 60, 220, 100 }; }
	static constexpr Color Blue() { return { 60, 140, 255 }; }
	static constexpr Color Yellow() { return { 255, 230, 60 }; }
	static constexpr Color Gray() { return { 140, 140, 140 }; }
};