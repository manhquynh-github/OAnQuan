#include "OAnQuan.h"
using namespace std;

void OAnQuan::switchTurn()
{
	Turn = 1 - Turn;
}

bool OAnQuan::getPos(int & pos)
{
	if (Turn == 0 && (pos > 5 || pos < 1))
		return false;
	if (Turn == 1 && (pos < 6 || pos > 10))
		return false;

	if (Turn == 1)
		pos = 17 - pos;

	pos -= 1;

	return true;
}

Node<O>* OAnQuan::getpNext(Node<O>* p, int direction)
{
	if (Turn == 0)
		return (direction == PHAI) ? p->getpNext() : p->getpPrev();
	if (Turn == 1)
		return (direction == PHAI) ? p->getpPrev() : p->getpNext();
	return nullptr;
}

OAnQuan::OAnQuan()
{
	Os = List<O>();
	for (int i = 1; i <= 5; i++)
		Os.Add(O(O::OTHUONG));
	Os.Add(O(O::OQUAN));
	for (int i = 1; i <= 5; i++)
		Os.Add(O(O::OTHUONG));
	Os.Add(O(O::OQUAN));

	A = Player();
	B = Player();

	Turn = 0;
}


OAnQuan::~OAnQuan()
{
	Os.Clear();
}

int OAnQuan::getTurn() const
{
	return Turn;
}

Player OAnQuan::getCurrentPlayer() const
{
	return (Turn == 0) ? A : B;
}

Player OAnQuan::gettPlayerA() const
{
	return A;
}

Player OAnQuan::gettPlayerB() const
{
	return B;
}

Player& OAnQuan::getCurrentPlayer()
{
	return (Turn == 0) ? A : B;
}

Player & OAnQuan::getPlayerA()
{
	return A;
}

Player & OAnQuan::getPlayerB()
{
	return B;
}

int OAnQuan::getCurrentPlayerField() const
{
	int s = 0;
	Node<O> *p = Os.GetNodeByIndex((Turn == 0) ? 0 : 6);
	for (int i = 1; i <= 5; i++, p = p->getpNext())
		s += p->getData2()->getValue();

	return s;
}

bool OAnQuan::IsGameOver()
{
	bool igo = ((Os[5].getValue() == 0 && Os[11].getValue() == 0) || IsCurrentPlayerPlayable() == false);
	if (igo == true)
	{
		getPlayerA().Eat(getCurrentPlayerField());
		getPlayerB().Eat(getCurrentPlayerField());;

		if (A.getMoney() > B.getMoney())
		{
			A.setStatus(Player::WIN);
			B.setStatus(Player::LOSE);
			cout << "1 WIN" << endl;
		}
		else if (A.getMoney() < B.getMoney())
		{
			A.setStatus(Player::LOSE);
			B.setStatus(Player::WIN);
			cout << "2 WIN" << endl;
		}
		//else
		//cout << endl << "Hue!" << endl;

		//cout << "Ti so: (" << A.getMoney() << "||" << B.getMoney() << ")" << endl;
	}

	return igo;
}

bool OAnQuan::IsCurrentPlayerPlayable()
{
	if (getCurrentPlayerField() == 0)
	{
		if (getCurrentPlayer().getMoney() < 5)
			return false;
		else
		{
			getCurrentPlayer().Eat(-5);
			Node<O> *p = Os.GetNodeByIndex((Turn == 0) ? 0 : 6);
			for (int i = 1; i <= 5; i++, p = p->getpNext())
				p->getData2()->AddValue(1);

			Xuat();
		}
	}

	return true;
}

void OAnQuan::Play(int pos, int direction)
{
	Node<O> *p = Os.GetNodeByIndex(pos);
	int value;

	while (true)
	{
		value = p->getData2()->getValue();
		p->getData2()->Consume();

		while (value > 0)
		{
			p = getpNext(p, direction);
			p->getData2()->AddValue(1);
			value--;
		}

		//Xuat();

		Node<O> *p1 = getpNext(p, direction), *p2 = getpNext(p1, direction);

		if (p1->getData2()->getValue() == 0 && p1->getData2()->getType() != O::OQUAN && p2->getData2()->getValue() > 0)
		{
			while (p1->getData2()->getValue() == 0 && p1->getData2()->getType() != O::OQUAN && p2->getData2()->getValue() > 0)
			{
				getCurrentPlayer().Eat(p2->getData2()->Consume());
				p1 = getpNext(p2, direction);
				p2 = getpNext(p1, direction);
				//Xuat();
			}
			break;
		}
		else if (p1->getData2()->getType() != O::OQUAN && p1->getData2()->getValue() > 0)
		{
			p = p1;
		}
		else
			break;
		//Xuat();
	}
	switchTurn();
}

void OAnQuan::Begin()
{
	int pos;
	char dir;
	while (!IsGameOver())
	{
		do
		{
			//cout << "Nguoi choi " << getTurn() + 1 << ": ";
			cin >> pos >> dir;
		} while (getPos(pos) == false || (dir != 'T' && dir != 'P') || Os[pos].getValue() == 0);
		Play(pos, (dir == 'T') ? TRAI : PHAI);
		Xuat();
	}
}

void OAnQuan::Xuat()
{
	Node<O> *p = Os.Front();
	int type = O::OQUAN;
	do
	{
		O i = p->getData();

		if (i.getType() != type)
		{
			if (i.getType() == O::OTHUONG)
				cout << "[";
			else
				cout << "\b]<";
			type = i.getType();
		}
		cout << i.getValue();

		if (i.getType() == O::OTHUONG)
			cout << ",";
		else
			cout << ">";

		p = p->getpNext();
	} while (p != Os.Front());
	cout << "(" << A.getMoney() << "||" << B.getMoney() << ")";
	cout << endl;
}
