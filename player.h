#pragma once
#include "Game.h"
#include <SFML/Graphics.hpp>
using namespace sf;

class Player
{
public:
	bool changescore;
	bool changegas;
	int refuelchance;
	int _randEventSubject, _randEventType;
	int dicePoint;
	Texture tPlane;
	Sprite spPlane;

	Player() 
	{
		_randEventSubject = -1;
		_randEventType = -1;
		pos = 1;
		score = 0;
		gas = 100;
		changegas = false;
		changescore = false;
		dicePoint = 1;
	}

	void setTex(const std::string& filename)
	{
		if (!tPlane.loadFromFile(filename))
			std::cout << filename << " not found" << std::endl;
		spPlane.setTexture(tPlane);
		spPlane.setOrigin(tPlane.getSize().x / 2, tPlane.getSize().y / 2);
	}

	void setPosition(const int _x, const int _y)
	{
		spPlane.setPosition(_x, _y);
	}

	void setRotation(const float _angle)
	{
		spPlane.setRotation(_angle);
	}

	void Init()
	{
		_randEventSubject = -1;
		_randEventType = -1;
		refuelchance = 3;
		pos = 1;
		score = 0;
		gas = 100;
		changescore = false;
	}

	void Roll() 
	{
		dicePoint = rand() % 6 + 1;
	}

	void Move(int step) 
	{
		if (step < 0)
			pos -= step;
		else
			pos += step;

		if (pos < 1)
			pos = 1;
		else if (pos > MapLength)
			pos = pos % MapLength;
	}

	int GetPos() 
	{
		return pos;
	}

	int GetScore()
	{
		return score;
	}

	void AddScore(int _score)
	{
		score = score + _score;
	}

	int GetGas()
	{
		return gas;
	}

	void SubGas(int _gas)
	{
		if (gas - _gas > 0)
			gas -= _gas;
		else
			gas = 0;
	}
	
	void AddGas(int _gas)
	{
		if (gas + _gas < 100)
			gas += _gas;
		else
			gas = 100;
	}

	void Refuel()
	{
		AddGas(rand() % 11 + 10);
		refuelchance--;
	}

	void GasChange(int type)
	{
		if (type && gas < 90)
			gas += 10;
		if (type && gas >= 90)
			gas = 100;
		if (!type && gas > 20)
			gas -= 20;
		if (!type && gas <= 20)
			gas = 0;
	}

	void ChangePos()
	{
		pos = rand() % MapLength;
	}
private:
	int pos;
	int score;
	int gas;
};