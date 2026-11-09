#include "Core/Logger.h"
#include <Windows.h>
#include <intrin.h> // __debugbreak()用

namespace Log
{
	// 共通のログフォーマットを作成する内部ヘルパー関数
	// ※ Visual Studio が認識できるように "file(line): level: message" の形式にする
	static std::string FormatLog(
		const std::string& level,
		const std::string& message,
		const std::source_location& location)
	{
		return std::string(location.file_name()) +
			"(" + std::to_string(location.line()) + "): " +
			level + ": " + message + "\n";
	}

	void Info(const std::string& message, const std::source_location& location)
	{
		// Visual Studioの出力ウィンドウに流す
		OutputDebugStringA(FormatLog("info", message, location).c_str());
	}

	void Warning(const std::string& message, const std::source_location& location)
	{
		OutputDebugStringA(FormatLog("warning", message, location).c_str());
	}

	void Error(const std::string& message, const std::source_location& location)
	{
		OutputDebugStringA(FormatLog("error", message, location).c_str());

		// デバッグビルド時のみ、ここでブレークポイントを強制発動させる
#ifdef _DEBUG
		__debugbreak();
#endif
	}
}