#include "Bomb.h"
#include "SDL.h"
#include "../BaseEngine/Objects/DisplayableObject.h"
#include "../BaseEngine/ResourceManager.h"
#include "MainScene.h"
#include "ObjectID.h"
#include "Character.h"
#include "Enemy.h"
#include "House.h"
#include "Brick.h"
#include "Gem.h"
#include "Shoe.h"
#include "Water.h"
#include <iostream>

Bomb::Bomb(TileMapScene * scene)
	:TileObject(scene),
	power_(1)
{
	setState(static_cast<int>(BombState::DISAPPEAR));
}

Bomb::~Bomb()
{
}

void Bomb::destroy()
{
	// collide with tile objects
	// up
	int up_length = 0;
	for (int i = 1; i <= power_; i++) {
		int tileMapPosY = GetPositionY() - i;
		if (tileMapPosY >= 0) {
			TileObject * tileObj = dynamic_cast<TileMapScene *>(getEnvironment())->getTileObjectLayerValue(GetPositionX(), tileMapPosY);
			if (!destroyTileObject(tileObj)) {
				break;
			}
			else {
				up_length++;
			}
		}
	}

	// down
	int down_length = 0;
	for (int i = 1; i <= power_; i++) {
		int tileMapPosY = GetPositionY() + i;
		if (tileMapPosY < dynamic_cast<TileMapScene *>(getEnvironment())->getTileMapHeight()) {
			TileObject * tileObj = dynamic_cast<TileMapScene *>(getEnvironment())->getTileObjectLayerValue(GetPositionX(), tileMapPosY);
			if (!destroyTileObject(tileObj)) {
				break;
			}
			else {
				down_length++;
			}
		}
	}

	// left
	int left_length = 0;
	for (int i = 1; i <= power_; i++) {
		int tileMapPosX = GetPositionX() - i;
		if (tileMapPosX >= 0) {
			TileObject * tileObj = dynamic_cast<TileMapScene *>(getEnvironment())->getTileObjectLayerValue(tileMapPosX, GetPositionY());
			if (!destroyTileObject(tileObj)) {
				break;
			}
			else {
				left_length++;
			}
		}
	}

	// right
	int right_length = 0;
	for (int i = 1; i <= power_; i++) {
		int tileMapPosX = GetPositionX() + i;
		if (tileMapPosX < dynamic_cast<TileMapScene *>(getEnvironment())->getTileMapWidth()) {
			TileObject * tileObj = dynamic_cast<TileMapScene *>(getEnvironment())->getTileObjectLayerValue(tileMapPosX, GetPositionY());
			if (!destroyTileObject(tileObj)) {
				break;
			}
			else {
				right_length++;
			}
		}
	}

	// collide with active objects
	for (int i = 0; i < dynamic_cast<TileMapScene *>(getEnvironment())->getSizeOfActiveObjects(); i++) {
		DisplayableObject * obj = dynamic_cast<TileMapScene *>(getEnvironment())->getActiveObjectByIndex(i);
		if (obj->getState() != static_cast<int>(CharacterState::DYING) 
			&& obj->getState() != static_cast<int>(CharacterState::RECOVER) 
			&& obj->getState() != static_cast<int>(CharacterState::DIE)) {
			int tileMapX = dynamic_cast<TileMapScene *>(getEnvironment())->getTileMapPositionX(obj->GetPositionX());
			int tileMapY = dynamic_cast<TileMapScene *>(getEnvironment())->getTileMapPositionY(obj->GetPositionY());
			if ((tileMapX == GetPositionX() && tileMapY >= GetPositionY() - up_length && tileMapY <= GetPositionY() + down_length)
				|| (tileMapY == GetPositionY() && tileMapX >= GetPositionX() - left_length && tileMapX <= GetPositionX() + right_length)) {
				destroyActiveObject(obj);
			}
		}
	}
}

bool Bomb::destroyTileObject(TileObject * tileObj)
{
	bool isContinued = true;
	if (tileObj != NULL) {
		if (tileObj->getID() == static_cast<int>(ObjectID::HOUSE)) {
			isContinued = false;
		}
		else if (tileObj->getID() == static_cast<int>(ObjectID::BRICK)) {
			dynamic_cast<Brick *>(tileObj)->exlode();
			isContinued = false;
		}
		else if (tileObj->getID() == static_cast<int>(ObjectID::BOMB)) {
			if (tileObj->getState() == static_cast<int>(BombState::APPEAR)) {
				dynamic_cast<Bomb *>(tileObj)->explode();
			}
		}
		else {
			tileObj->Hide();
		}
	}
	return isContinued;
}

void Bomb::destroyActiveObject(DisplayableObject * obj)
{
	if (obj->getID() == static_cast<int>(ObjectID::CHARACTER)) {
		dynamic_cast<Character *>(obj)->dying();
	}
	else {
		dynamic_cast<Enemy *>(obj)->dying();
	}
}

void Bomb::setPower(int power)
{
	power_ = power;
}

void Bomb::appear(int tileMapX, int tileMapY)
{
	SetPosition(tileMapX, tileMapY);
	Show();
	setState(static_cast<int>(BombState::APPEAR));
	startAnimation();
	timer_.start();
}

void Bomb::explode()
{
	setState(static_cast<int>(BombState::EXPLODE));
	startAnimation();
	timer_.stop();
	destroy();
}

void Bomb::SetPosition(int tileMapPosX, int tileMapPosY)
{
	int anchorPosX = GetPosXFromCollisionAreaPosX(dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionX(tileMapPosX));
	int anchorPosY = GetPosYFromCollisionAreaPosY(dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionY(tileMapPosY));
	setAnchorPosAndImageAreaPos(anchorPosX, anchorPosY);
	setCollisionAreaPos(tileMapPosX, tileMapPosY);
	setZOrder(tileMapPosY * 3);
}

void Bomb::UpdateObject()
{
	switch (getState())
	{
	case static_cast<int>(BombState::APPEAR) :
		if (timer_.getTotalTicks() >= 3000) {
			stopAnimation();
			setState(static_cast<int>(BombState::EXPLODE));
			startAnimation();
			timer_.stop();
			destroy();
		}
		break;
	case static_cast<int>(BombState::EXPLODE) :
		if (!isAnimationRunning()) {
			setState(static_cast<int>(BombState::DISAPPEAR));
			Hide();
		}
		break;
	case static_cast<int>(BombState::DISAPPEAR) :
		break;
	default:
		break;
	}
}

void Bomb::DrawObject()
{
	drawAnimationFrame();
}
