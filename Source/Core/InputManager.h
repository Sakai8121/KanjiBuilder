#pragma once
#include "Core/Vector2.h"
#include <array>
#include <unordered_map>
#include <variant>

// DxLibのキーコードを調べたり覚えるのが大変なので、独自のキーコードを定義しておく
enum class KeyCode : std::size_t
{
	Up,
	Down,
	Left,
	Right,
	Enter,
	Escape,
	Space,

	Count // 要素カウント用（必ず末尾に置く）
};

// DxLibのマウスボタンコードを調べたり覚えるのが大変なので、独自のマウスボタンコードを定義しておく
enum class MouseButton
{
	Left,
	Right,
	Middle,

	Count // 要素カウント用（必ず末尾に置く）
};

// 後で一括で入力方法を変えるためにInputActionを定義しておく
// デバッグやマウス操作はInputActionではなくKeyCodeやMouseButtonで直接取得する
enum class InputAction
{
	Select,
	Cancel,
	TogglePause,
};


struct Vector2;

class InputManager
{
public:
	static InputManager& GetInstance();
	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;
	InputManager(InputManager&&) = delete;
	InputManager& operator=(InputManager&&) = delete;

	void Init();
	void Update();

	bool GetActionDown(InputAction action) const;
	bool GetAction(InputAction action) const;
	bool GetActionUp(InputAction action) const;

	bool GetKeyDown(KeyCode key) const;
	bool GetKey(KeyCode key) const;
	bool GetKeyUp(KeyCode key) const;

	bool GetMouseButtonDown(MouseButton button) const;
	bool GetMouseButton(MouseButton button) const;
	bool GetMouseButtonUp(MouseButton button) const;

	// 現在のカーソルの座標(左上を0,0としたピクセル単位のスクリーン座標)
	Vector2 GetMousePosition() const { return _currentMousePosition; }
	// 前フレームからの移動量
	Vector2 GetMouseDelta() const { return _currentMousePosition - _prevMousePosition; }
private:
	InputManager() = default;
	~InputManager() = default;

	void BindAction(InputAction, KeyCode);
	void BindAction(InputAction, MouseButton);

	static constexpr std::size_t KeyCount = static_cast<std::size_t>(KeyCode::Count);
	static constexpr std::size_t MouseButtonCount = static_cast<std::size_t>(MouseButton::Count);

	std::array<bool, KeyCount> _currentKeys{};
	std::array<bool, KeyCount> _prevKeys{};
	std::array<bool, KeyCount> _currentMouseButtons{};
	std::array<bool, KeyCount> _prevMouseButtons{};

	Vector2 _currentMousePosition = Vector2::Zero();
	Vector2 _prevMousePosition = Vector2::Zero();

	using InputBinding = std::variant<KeyCode, MouseButton>;
	std::unordered_map<InputAction, InputBinding> _actionBindings;
};

