#include "Core/GameEngine.h"
#include "Game/TestDrawComponent.h"
#include "Core/EventBus.h"
#include <Dxlib.h>
#include <algorithm>
#include "Core/Logger.h"

GameEngine::GameEngine()
{
    SceneManager::GetInstance().Init();
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
        SceneManager::GetInstance().Update(frameDt);
        EventBus::GetInstance().Flush(); // シーンの更新が終わってから
        SceneManager::GetInstance().ProcessGC(); // Update内でGameObjectの破棄は行わない。ProcessGCで遅延破棄する
        SceneManager::GetInstance().Draw(); // 新しい状態での描画

        ScreenFlip();
    }
}