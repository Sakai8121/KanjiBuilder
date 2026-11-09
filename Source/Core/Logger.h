#pragma once
#include <string>
#include <source_location>

namespace Log
{
	// 正常な進行状況や変数の値を出力
	void Info(
		const std::string& message,
		const std::source_location& location = std::source_location::current());

	// 続行可能だが、意図しない挙動（アセットの読み込み失敗など）
	void Warning(
		const std::string& message,
		const std::source_location& location = std::source_location::current());

	// 致命的なエラー。デバッガを停止させる（Scene操作の衝突など）
	void Error(
		const std::string& message,
		const std::source_location& location = std::source_location::current());
}