#include "Core/GameEngine.h"
#include "Game/TestDrawComponent.h"
#include "Core/EventBus.h"
#include <Dxlib.h>
#include <algorithm>
#include "Core/Logger.h"
#include "Core/Time.h"

GameEngine::GameEngine()
{
    SceneManager::GetInstance().Init();
}

void GameEngine::Loop()
{
    LONGLONG prev = GetNowHiPerformanceCount();

    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		Time::GetInstance().Update();

        ClearDrawScreen();

        // --- ゲーム更新・描画処理 ---
        SceneManager::GetInstance().Update(Time::GetInstance().GetDeltaTime());
        EventBus::GetInstance().Flush(); // シーンの更新が終わってから
        SceneManager::GetInstance().ProcessGC(); // Update内でGameObjectの破棄は行わない。ProcessGCで遅延破棄する
        SceneManager::GetInstance().Draw(); // 新しい状態での描画

        ScreenFlip();
    }
}