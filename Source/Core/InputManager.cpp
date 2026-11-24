#include "Core/InputManager.h"
#include "Core/Logger.h"
#include <DxLib.h>

namespace
{
	// KeyCode -> DxLibのキー定数への変換テーブル
	int ToDxLibKey(KeyCode key)
	{
		switch (key)
		{
		case KeyCode::Space:  return KEY_INPUT_SPACE;
		case KeyCode::Escape: return KEY_INPUT_ESCAPE;
		case KeyCode::Enter:  return KEY_INPUT_RETURN;
		case KeyCode::Up: return KEY_INPUT_UP;
		case KeyCode::Down: return KEY_INPUT_DOWN;
		case KeyCode::Right: return KEY_INPUT_RIGHT;
		case KeyCode::Left: return KEY_INPUT_LEFT;
		default:
			Log::Error("未定義の KeyCode が指定されました。");
			return 0;
		}
	}

	// MouseButton -> DxLibのマウス定数への変換テーブル
	int ToDxLibMouseButton(MouseButton button)
	{
		switch (button)
		{
		case MouseButton::Left:   return MOUSE_INPUT_LEFT;
		case MouseButton::Right:  return MOUSE_INPUT_RIGHT;
		case MouseButton::Middle: return MOUSE_INPUT_MIDDLE;
		default:
			Log::Error("未定義の MouseButton が指定されました。");
			return 0;
		}
	}
}

InputManager& InputManager::GetInstance()
{
	static InputManager instance;
	return instance;
}

void InputManager::Init()
{
	// デフォルトのアクション割り当て（ここを変えればゲーム全体で一括変更される）
	BindAction(InputAction::Select, MouseButton::Left);
	BindAction(InputAction::Cancel, MouseButton::Right);
	BindAction(InputAction::TogglePause, KeyCode::Escape);

	// 初回フレームの巨大な MouseDelta を防ぐため初期座標を同期
	int mouseX = 0, mouseY = 0;
	GetMousePoint(&mouseX, &mouseY);
	_currentMousePosition = { static_cast<float>(mouseX), static_cast<float>(mouseY) };
	_prevMousePosition = _currentMousePosition;
}

void InputManager::Update()
{
	// 前フレームの状態を退避
	_prevKeys = _currentKeys;
	_prevMouseButtons = _currentMouseButtons;
	_prevMousePosition = _currentMousePosition;

	// キーボード全体の生データを一括取得
	char rawKeyState[256]{};
	GetHitKeyStateAll(rawKeyState);

	for (std::size_t i = 0; i < KeyCount; ++i)
	{
		const int dxKey = ToDxLibKey(static_cast<KeyCode>(i));
		_currentKeys[i] = (rawKeyState[dxKey] != 0);
	}

	// マウスボタンのビットフラグを取得
	const int mouseInput = GetMouseInput();
	for (std::size_t i = 0; i < MouseButtonCount; ++i)
	{
		const int dxButton = ToDxLibMouseButton(static_cast<MouseButton>(i));
		_currentMouseButtons[i] = ((mouseInput & dxButton) != 0);
	}

	// マウス座標の更新
	int mouseX = 0, mouseY = 0;
	GetMousePoint(&mouseX, &mouseY);
	_currentMousePosition = { static_cast<float>(mouseX), static_cast<float>(mouseY) };
}

// --- 物理キー判定 ---
bool InputManager::GetKeyDown(KeyCode key) const
{
	const auto idx = static_cast<std::size_t>(key);
	return _currentKeys[idx] && !_prevKeys[idx];
}

bool InputManager::GetKey(KeyCode key) const
{
	return _currentKeys[static_cast<std::size_t>(key)];
}

bool InputManager::GetKeyUp(KeyCode key) const
{
	const auto idx = static_cast<std::size_t>(key);
	return !_currentKeys[idx] && _prevKeys[idx];
}

// --- 物理マウスボタン判定 ---
bool InputManager::GetMouseButtonDown(MouseButton button) const
{
	const auto idx = static_cast<std::size_t>(button);
	return _currentMouseButtons[idx] && !_prevMouseButtons[idx];
}

bool InputManager::GetMouseButton(MouseButton button) const
{
	return _currentMouseButtons[static_cast<std::size_t>(button)];
}

bool InputManager::GetMouseButtonUp(MouseButton button) const
{
	const auto idx = static_cast<std::size_t>(button);
	return !_currentMouseButtons[idx] && _prevMouseButtons[idx];
}

// --- 論理アクション判定（std::variant の中身に応じて自動分岐） ---
bool InputManager::GetActionDown(InputAction action) const
{
	const auto it = _actionBindings.find(action);
	if (it == _actionBindings.end()) return false;

	return std::visit([this](const auto& arg) -> bool
		{
			// decay_t：
			// argの型から参照やconstなどの修飾を取り除いた型を取得する。
			using T = std::decay_t<decltype(arg)>;

			// if constexpr：
			// コンパイル時に条件式を評価し、条件に合わない分岐をコンパイル対象から除外する。
			// std::visitではvariantが保持する型ごとに処理がインスタンス化されるため、
			// 型に応じて適切な処理だけをコンパイルする。
			
			// argがKeyCode型なら、キーボード入力として処理する。
			if constexpr (std::is_same_v<T, KeyCode>)
				return GetKeyDown(arg);

			// argがMouseButton型なら、マウス入力として処理する。
			else if constexpr (std::is_same_v<T, MouseButton>)
				return GetMouseButtonDown(arg);

		}, it->second);
}

bool InputManager::GetAction(InputAction action) const
{
	const auto it = _actionBindings.find(action);
	if (it == _actionBindings.end()) return false;

	return std::visit([this](const auto& arg) -> bool {
		using T = std::decay_t<decltype(arg)>;
		if constexpr (std::is_same_v<T, KeyCode>)          return GetKey(arg);
		else if constexpr (std::is_same_v<T, MouseButton>) return GetMouseButton(arg);
		}, it->second);
}

bool InputManager::GetActionUp(InputAction action) const
{
	const auto it = _actionBindings.find(action);
	if (it == _actionBindings.end()) return false;

	return std::visit([this](const auto& arg) -> bool {
		using T = std::decay_t<decltype(arg)>;
		if constexpr (std::is_same_v<T, KeyCode>)          return GetKeyUp(arg);
		else if constexpr (std::is_same_v<T, MouseButton>) return GetMouseButtonUp(arg);
		}, it->second);
}


// --- バインド設定 ---
void InputManager::BindAction(InputAction action, KeyCode key)
{
	_actionBindings[action] = key;
}

void InputManager::BindAction(InputAction action, MouseButton button)
{
	_actionBindings[action] = button;
}