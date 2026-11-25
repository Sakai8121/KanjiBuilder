#include "Game/Scene/GameScene.h"
#include "Core/Renderer/ShapeRendererComponent.h"
#include "Core/GameObject.h"

void GameScene::OnStart()
{
	// レンダリングのテスト
	
	// Order10：赤くて小さな矩形
	auto* frontObj = SpawnGameObject();
	frontObj->GetTransform()->SetLocalPosition({ 300.0f, 300.0f });
	frontObj->AddComponent<ShapeRendererComponent>(50.0f, 50.0f, Color::Red(), true, RenderLayer::Unit, 10);

	// Order0: 青い大きな矩形
	auto* backObj = SpawnGameObject();
	backObj->GetTransform()->SetLocalPosition({ 300.0f, 300.0f });
	backObj->AddComponent<ShapeRendererComponent>(120.0f, 120.0f, Color::Blue(), true, RenderLayer::Unit, 0);

	// 背景レイヤー：白い大きな円
	auto* rangeObj = SpawnGameObject();
	rangeObj->GetTransform()->SetLocalPosition({ 300.0f, 300.0f });
	rangeObj->AddComponent<ShapeRendererComponent>(150.0f, Color::White(), false, RenderLayer::Background, 0);
}