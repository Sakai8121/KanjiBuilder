#pragma once

// GameObjectやComponentの参照を安全に扱うためのハンドル
class Handle final
{
public:
	// 無効な状態を表現するデフォルトコンストラクタ
	// メンバーとして保持するが、何も指していないときが考えられるため
	Handle() : Index(kInvalidIndex), Generation(0) {}

	Handle(unsigned int index, unsigned int generation) : Index(index), Generation(generation){}

	bool IsValid() const { return Index != kInvalidIndex; }

	// スロット配列の何番目か
	unsigned int Index;
	// そのスロットが使われるのは何回目か
	unsigned int Generation;

private:
	// 無効なIndex（ここまで到達する前にゲームはクラッシュする）
	static constexpr unsigned int kInvalidIndex = std::numeric_limits<unsigned int>::max();
};

