#pragma once
#include "SDL.h"
#include "../BaseEngine/Objects/DisplayableObject.h"
#include "../BaseEngine/Scenes/Scene.h"
#include "Bomb.h"
#include <vector>

enum class CharacterState
{
	DOWN_IDLE = 0,
	UP_IDLE = 1,
	LEFT_IDLE = 2,
	RIGHT_IDLE = 3,
	DOWN_WALK = 4,
	UP_WALK = 5,
	LEFT_WALK = 6,
	RIGHT_WALK = 7,
	DYING = 8,
	RECOVER = 9,
	DIE = 10
};

class Character : public DisplayableObject
{
private:
	enum class CharacterDirection
	{
		DOWN = 0,
		UP = 1,
		LEFT = 2,
		RIGHT = 3
	};

	bool isIdle_;
	CharacterDirection direction_;
	Timer death_timer_;
	bool isDead_;
	const int MAX_SPEED;
	int speed_;
	const int MAX_POWER;
	int power_;
	const int MAX_BOMBS;
	int bombs_;
	std::vector<Bomb *> bomb_array_;

public:
	Character(Scene *);
	virtual ~Character();

	int getMaxBombs();
	void addBomb(Bomb *);
	bool isDead();
	void dying();
	void recover();
	void die();

	virtual void SetPosition(int, int);
	virtual void UpdateObject();
	virtual void DrawObject();
};

