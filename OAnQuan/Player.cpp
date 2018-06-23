#include "Player.h"

int Player::Count = 0;

Player::Player()
{
	Order = Count;
	Status = NEUTR;
	Money = 0;
	Count++;
}


Player::~Player()
{
	Count--;
}

int Player::getStatus() const
{
	return Status;
}

void Player::setStatus(Player_Status player_status)
{
	Status = player_status;
}

int Player::getMoney() const
{
	return Money;
}

void Player::setMoney(int money)
{
	Money = money;
}

int Player::getOrder() const
{
	return Order;
}

void Player::Eat(int money)
{
	Money += money;
}
