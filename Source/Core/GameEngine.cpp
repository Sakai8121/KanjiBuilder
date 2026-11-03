#include "Core/GameEngine.h"
#include <Dxlib.h>
#include <algorithm>

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
        

        ScreenFlip();
    }
}