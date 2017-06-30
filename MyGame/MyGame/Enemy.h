#pragma once
#include "SDL.h"
#include "../BaseEngine/Objects/DisplayableObject.h"
#include "../BaseEngine/Scenes/Scene.h"

enum class EnemyState
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

class Enemy : public DisplayableObject
{
private:
	enum class EnemyDirection
	{
		DOWN = 0,
		UP = 1,
		LEFT = 2,
		RIGHT = 3
	};

	bool isIdle_;
	EnemyDirection direction_;
	Timer death_timer_;
	bool isDead_;
	const int SPEED;

public:
	Enemy(Scene *);
	virtual ~Enemy();

	bool isDead();
	void dying();
	void recover();
	void die();

	virtual void SetPosition(int, int);
	virtual void UpdateObject();
	virtual void DrawObject();
};

