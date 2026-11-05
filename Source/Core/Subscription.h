#pragma once

class Subscription final
{
public:
	// 無効な状態 (idが0) も作れるようにしておく
	Subscription() : _id(0) {}
	// Subscription sub = 5;のような暗黙な型変換を禁止
	explicit Subscription(unsigned int id) : _id(id) {}

	// 循環インクルードを防ぐためにCPPファイルに書く。
	~Subscription();

	// コピーされると破棄のタイミングがおかしくなるから禁止
	Subscription(const Subscription&) = delete;
	Subscription& operator=(const Subscription&) = delete;

	// ムーブ（所有権の移動）は許可する
	Subscription(Subscription&& other) noexcept : _id(other._id)
	{
		other._id = 0; // ムーブ元のIDを無効化（二重解除を防ぐ）
	}
	Subscription& operator=(Subscription&& other) noexcept
	{
		if (this != &other) {
			_id = other._id;
			other._id = 0;
		}
		return *this;
	}

private:
	unsigned int _id;
};

