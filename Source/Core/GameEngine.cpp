#include "Core/GameEngine.h"
#include "Game/TestDrawComponent.h"
#include <Dxlib.h>
#include <algorithm>

GameEngine::GameEngine()
{
	// テスト用　あとで消す
	auto gameObject = std::make_unique<GameObject>(Handle());
	gameObject->AddComponent<TestDrawComponent>();
	_gameObjects.push_back(std::move(gameObject));
}

void GameEngine::Loop()
{
    LONGLONG prev = GetNowHiPerformanceCount();

    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
        // dtの計測とクランプ
        LONGLONG now = GetNowHiPerformanceCount();
        float frameDt = std::min((now - prev) / 1'000'000.0f, 0.1f);
        prev = now;

        ClearDrawScreen();

        // --- ゲーム更新・描画処理 ---
		for (auto& gameObject : _gameObjects) {
			gameObject->Update(frameDt);
			gameObject->Draw();
		}

        ScreenFlip();
    }
}