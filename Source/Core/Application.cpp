#include "Core/Application.h"
#include <Dxlib.h>
#include "Core/Looper.h"
#include "Core/GameConfig.h"

bool Application::Initialize()
{
	// ウィンドウやDXLibの設定
	SetAlwaysRunFlag(TRUE);						//ウィンドウがノンアクティブでも実行
	SetWindowSizeChangeEnableFlag(FALSE);		//ウィンドウサイズを自由に変更できるようにする
	SetOutApplicationLogValidFlag(FALSE);		//ログ出力しない
	SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_DESKTOP);	//フルスクリーン時にデスクトップ解像度を基準にする
	SetWindowText("Kanji Builder");				//ウィンドウタイトルを付ける
	ChangeWindowMode(TRUE);						//ウィンドウモードに変更
	SetWaitVSyncFlag(FALSE);					//垂直同期を設定
	SetWindowSizeExtendRate(1.0);				//ウィンドウサイズを変更したい時はここに倍率を指定する
	
	// ゲーム画面の設定
	const int COLOR_BIT = 32;					//色のbit数。通常32で良いが軽くするなら16にする
	SetGraphMode(GameConfig::WIN_W * GameConfig::WIN_EX, GameConfig::WIN_H * GameConfig::WIN_EX, COLOR_BIT);		//ゲーム画面の解像度を設定する
	SetWindowIconID(101);						//アイコン設定
	
	// その他の設定
	SetMouseDispFlag(TRUE);						// カーソル表示
	SetUseTransColor(false);                    // DXLibの画像読み込みなどで使用される透過色に関する設定

	// DXLib本体を初期化
	if (DxLib_Init()) {							//DXライブラリ初期化処理
		return false;							//異常終了したら即座にやめる
	}

	// 裏画面に描画する
	SetDrawScreen(DX_SCREEN_BACK);				//裏画面処理を設定する

	return true;
}

void Application::Run()
{
	Looper looper;
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		looper.Update();
	}
}

void Application::Finalize()
{
	DxLib_End();								//DXライブラリ使用の終了処理
}