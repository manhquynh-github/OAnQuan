#pragma once
#include "O.h"
#include "List.h"
#include <iostream>
#include "Player.h"

class OAnQuan
{
private:
	List<O> Os;
	Player A, B;
	int Turn;
	
	void switchTurn();
	bool getPos(int &pos);
	Node<O> *getpNext(Node<O> *p, int direction);
	Player& getCurrentPlayer();
	Player& getPlayerA();
	Player& getPlayerB();
	enum OAnQuan_Direction { TRAI, PHAI };
public:
	OAnQuan();
	~OAnQuan();

	int getTurn() const;
	Player getCurrentPlayer() const;
	Player gettPlayerA() const;
	Player gettPlayerB() const;
	int getCurrentPlayerField() const;
	bool IsGameOver();
	bool IsCurrentPlayerPlayable();
	void Play(int pos, int direction);
	void Begin();
	void Xuat();
};

