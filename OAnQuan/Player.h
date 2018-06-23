#pragma once
class Player
{
private:
	int Status, Money, Order;
public:
	static int Count;
	enum Player_Status { WIN, LOSE, NEUTR};

	Player();
	~Player();

	int getStatus() const;
	void setStatus(Player_Status player_status);
	int getMoney() const;
	void setMoney(int money);
	int getOrder() const;

	void Eat(int money);
};

