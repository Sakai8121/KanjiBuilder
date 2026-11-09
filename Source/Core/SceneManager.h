#pragma once
#include <memory>
#include <stack>
#include <source_location>
#include "Core/Scene.h"
#include "Core/Subscription.h"

// 予約するアクションの種類
enum class SceneAction { None, Push, Pop, Change };

class SceneManager final
{
public:
	// シングルトン
	static SceneManager& GetInstance();

	void Init();
	void Update(float frameDt);
	void Draw();
	void ProcessGC();

	// 毎フレームの最後（GCのあと等）に呼ばれ、予約された遷移を実際に実行する
	void ApplyPendingAction();

	// 外部から呼ばれる遷移要求（即時実行せず予約だけする）
	void RequestPush(std::unique_ptr<Scene> scene, const std::source_location& location = std::source_location::current());
	void RequestPop(const std::source_location& location = std::source_location::current());
	void RequestChange(std::unique_ptr<Scene> scene, const std::source_location& location = std::source_location::current());

private:
	// シングルトンのための禁止事項
	SceneManager() = default;
	~SceneManager() = default;
	SceneManager(const SceneManager&) = delete;

	// スタックと予約状態
	std::vector<std::unique_ptr<Scene>> _stackScenes;
	SceneAction _pendingAction = SceneAction::None;
	std::unique_ptr<Scene> _pendingScene;

	// 実際のシーン遷移予約処理を全て引き受ける関数
	void RegisterPendingAction(
		SceneAction action,
		std::unique_ptr<Scene> scene,
		const std::source_location& location);
};