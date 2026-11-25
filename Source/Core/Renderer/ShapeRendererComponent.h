#pragma once
#include "Core/RendererComponent.h"
#include "Core/Color.h"

enum class RenderShapeType
{
	Box,
	Circle,
};

class ShapeRendererComponent final : public RendererComponent
{
public:
	// 矩形用コンストラクタ
	ShapeRendererComponent(
		float width,
		float height,
		Color color = Color::White(),
		bool isFilled = true,
		RenderLayer renderLayer = RenderLayer::Unit,
		int orderInLayer = 0)
		: RendererComponent(renderLayer, orderInLayer)
		, _shapeType(RenderShapeType::Box)
		, _width(width)
		, _height(height)
		, _color(color)
		, _isFilled(isFilled)
	{
	}

	// 円用コンストラクタ
	ShapeRendererComponent(
		float radius,
		Color color = Color::White(),
		bool isFilled = true,
		RenderLayer renderLayer = RenderLayer::Unit,
		int orderInLayer = 0)
		: RendererComponent(renderLayer, orderInLayer)
		, _shapeType(RenderShapeType::Circle)
		, _radius(radius)
		, _color(color)
		, _isFilled(isFilled)
	{
	}
	
	// RendererComponent
	void Render() override;

	// 実行時の動的変更用セッター
	void SetColor(Color color) { _color = color; }
	void SetFilled(bool isFilled) { _isFilled = isFilled; }
	void SetBoxSize(float width, float height)
	{
		_shapeType = RenderShapeType::Box;
		_width = width;
		_height = height;
	}
	void SetRadius(float radius)
	{
		_shapeType = RenderShapeType::Circle;
		_radius = radius;
	}

private:
	RenderShapeType _shapeType = RenderShapeType::Box;
	float _width = 32.0f;
	float _height = 32.0f;
	float _radius = 16.0f;
	Color _color = Color::White();
	bool _isFilled = true;
};

