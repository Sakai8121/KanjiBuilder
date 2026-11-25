#include "Core/Renderer/ShapeRendererComponent.h"
#include "Core/GameObject.h"
#include "Core/TransformComponent.h"
#include <DxLib.h>

void ShapeRendererComponent::Render()
{
	const TransformComponent* transform = GetGameObject()->GetTransform();
	if (transform == nullptr) return;

	// 透明なら描画スキップ
	if (_color.a == 0) return;

	const Vector2 position = transform->GetWorldPosition();
	const Vector2 scale = transform->GetWorldScale();
	const unsigned int dxColor = _color.ToDxColor();

	// 半透明の場合のみアルファブレンドを有効化
	const bool isTranslucent = (_color.a < 255);
	if (isTranslucent)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, _color.a);
	}

	switch (_shapeType)
	{
	case RenderShapeType::Box:
	{
		const float halfW = (_width * scale.x) * 0.5f;
		const float halfH = (_height * scale.y) * 0.5f;

		const int left = static_cast<int>(position.x - halfW);
		const int top = static_cast<int>(position.y - halfH);
		const int right = static_cast<int>(position.x + halfW);
		const int bottom = static_cast<int>(position.y + halfH);

		DrawBox(left, top, right, bottom, dxColor, _isFilled ? TRUE : FALSE);
		break;
	}
	case RenderShapeType::Circle:
	{
		const float maxScale = (scale.x > scale.y) ? scale.x : scale.y;
		const int centerX = static_cast<int>(position.x);
		const int centerY = static_cast<int>(position.y);
		const int r = static_cast<int>(_radius * maxScale);

		DrawCircle(centerX, centerY, r, dxColor, _isFilled ? TRUE : FALSE);
		break;
	}
	}

	// 後続の描画に影響しないよう必ずブレンドモードを元に戻す
	if (isTranslucent)
	{
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}
