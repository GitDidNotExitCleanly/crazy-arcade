#include "Character.h"
#include "SDL.h"
#include "../BaseEngine/Objects/DisplayableObject.h"
#include "../BaseEngine/ResourceManager.h"
#include "MainScene.h"
#include "ObjectID.h"
#include "ResourceID.h"
#include <iostream>

Character::Character(Scene * scene)
	:DisplayableObject(scene),
	isIdle_(true),
	direction_(CharacterDirection::DOWN),
	isDead_(false),
	MAX_SPEED(10),
	speed_(5),
	MAX_POWER(5),
	power_(1),
	MAX_BOMBS(3),
	bombs_(1)
{
	setState(static_cast<int>(CharacterState::DOWN_IDLE));
}

Character::~Character()
{
}

int Character::getMaxBombs()
{
	return MAX_BOMBS;
}

void Character::addBomb(Bomb * bomb)
{
	bomb_array_.push_back(bomb);
}

bool Character::isDead()
{
	return isDead_;
}

void Character::dying()
{
	stopAnimation();
	setState(static_cast<int>(CharacterState::DYING));
	startAnimation();
	death_timer_.start();
}

void Character::recover()
{
	stopAnimation();
	setState(static_cast<int>(CharacterState::RECOVER));
	startAnimation();
	death_timer_.start();
}

void Character::die()
{
	stopAnimation();
	setState(static_cast<int>(CharacterState::DIE));
	startAnimation();
	death_timer_.start();
}

void Character::SetPosition(int x, int y)
{
	setAnchorPosAndImageAreaPos(x, y);
	setCollisionAreaPos(x, y);
	setZOrder(dynamic_cast<TileMapScene *>(getEnvironment())->getTileMapPositionY(y) * 3 + 2);
}

void Character::UpdateObject()
{
	KeyboardManager * keyboardManager = getEnvironment()->getBaseEngine()->getKeyboardManager();
	KeyCode key = keyboardManager->getLastPressedKey();
	int x = GetPositionX();
	int y = GetPositionY();
	if (key == KeyCode::KEY_UP || key == KeyCode::KEY_DOWN || key == KeyCode::KEY_LEFT || key == KeyCode::KEY_RIGHT) {
		if (getState() != static_cast<int>(CharacterState::DYING) && getState() != static_cast<int>(CharacterState::RECOVER) && getState() != static_cast<int>(CharacterState::DIE)) {
			if (key == KeyCode::KEY_UP) {
				y -= speed_;
				direction_ = CharacterDirection::UP;
			}
			else if (key == KeyCode::KEY_DOWN) {
				y += speed_;
				direction_ = CharacterDirection::DOWN;
			}
			else if (key == KeyCode::KEY_LEFT) {
				x -= speed_;
				direction_ = CharacterDirection::LEFT;
			}
			else {
				x += speed_;
				direction_ = CharacterDirection::RIGHT;
			}
			SetPosition(x, y);

			// check if it runs out of scope
			int leftBorder = dynamic_cast<TileMapScene *>(getEnvironment())->getTileMapLeftBorder();
			int rightBorder = dynamic_cast<TileMapScene *>(getEnvironment())->getTileMapRightBorder();
			int topBorder = dynamic_cast<TileMapScene *>(getEnvironment())->getTileMapTopBorder();
			int bottomBorder = dynamic_cast<TileMapScene *>(getEnvironment())->getTileMapBottomBorder();
			if (getCollisionArea().x < leftBorder) {
				x = GetPosXFromCollisionAreaPosX(leftBorder);
			}
			if (getCollisionArea().x + getCollisionArea().w > rightBorder) {
				x = GetPosXFromCollisionAreaPosX(rightBorder - getCollisionArea().w);
			}
			if (getCollisionArea().y < topBorder) {
				y = GetPosYFromCollisionAreaPosY(topBorder);
			}
			if (getCollisionArea().y + getCollisionArea().h > bottomBorder) {
				y = GetPosYFromCollisionAreaPosY(bottomBorder - getCollisionArea().h);
			}
			SetPosition(x, y);

			// check if it collides with tile objects
			bool canPass = true;
			int tileMapStartX = dynamic_cast<TileMapScene *>(getEnvironment())->getTileMapPositionX(getCollisionArea().x);
			int tileMapStartY = dynamic_cast<TileMapScene *>(getEnvironment())->getTileMapPositionY(getCollisionArea().y);
			int tileMapEndX = dynamic_cast<TileMapScene *>(getEnvironment())->getTileMapPositionX(getCollisionArea().x + getCollisionArea().w - 1);
			int tileMapEndY = dynamic_cast<TileMapScene *>(getEnvironment())->getTileMapPositionY(getCollisionArea().y + getCollisionArea().h - 1);
			if (direction_ == CharacterDirection::UP) {
				for (int i = tileMapStartX; i <= tileMapEndX; i++) {
					TileObject * tileObj = dynamic_cast<TileMapScene *>(getEnvironment())->getTileObjectLayerValue(i, tileMapStartY);
					if (tileObj != NULL) {
						if (tileObj->getID() == static_cast<int>(ObjectID::HOUSE)
							|| tileObj->getID() == static_cast<int>(ObjectID::BRICK)
							|| tileObj->getID() == static_cast<int>(ObjectID::BOMB)) {
							canPass = false;
							break;
						}
					}
				}
				if (!canPass) {
					int tileMapPosY = dynamic_cast<TileMapScene *>(getEnvironment())->getTileMapPositionY(getCollisionArea().y - 1);
					int screenY = dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionY(tileMapPosY);
					y = GetPosYFromCollisionAreaPosY(screenY + dynamic_cast<TileMapScene *>(getEnvironment())->getTileHeight());
					TileObject * leftTileObj = dynamic_cast<TileMapScene *>(getEnvironment())->getTileObjectLayerValue(tileMapStartX, tileMapStartY);
					if (leftTileObj == NULL
						|| leftTileObj->getID() == static_cast<int>(ObjectID::GEM)
						|| leftTileObj->getID() == static_cast<int>(ObjectID::SHOE)
						|| leftTileObj->getID() == static_cast<int>(ObjectID::WATER)) {
						x -= speed_;
						if (GetCollisionAreaPosXFromPosX(x) < dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionX(tileMapStartX)) {
							x = GetPosXFromCollisionAreaPosX(dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionX(tileMapStartX));
						}
					}
					TileObject * rightTileObj = dynamic_cast<TileMapScene *>(getEnvironment())->getTileObjectLayerValue(tileMapEndX, tileMapStartY);
					if (rightTileObj == NULL
						|| rightTileObj->getID() == static_cast<int>(ObjectID::GEM)
						|| rightTileObj->getID() == static_cast<int>(ObjectID::SHOE)
						|| rightTileObj->getID() == static_cast<int>(ObjectID::WATER)) {
						x += speed_;
						if (GetCollisionAreaPosXFromPosX(x) > dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionX(tileMapEndX)) {
							x = GetPosXFromCollisionAreaPosX(dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionX(tileMapEndX));
						}
					}
					SetPosition(x, y);
				}
			}
			else if (direction_ == CharacterDirection::LEFT) {
				for (int j = tileMapStartY; j <= tileMapEndY; j++) {
					TileObject * tileObj = dynamic_cast<TileMapScene *>(getEnvironment())->getTileObjectLayerValue(tileMapStartX, j);
					if (tileObj != NULL) {
						if (tileObj->getID() == static_cast<int>(ObjectID::HOUSE)
							|| tileObj->getID() == static_cast<int>(ObjectID::BRICK)
							|| tileObj->getID() == static_cast<int>(ObjectID::BOMB)) {
							canPass = false;
							break;
						}
					}
				}
				if (!canPass) {
					int tileMapPosX = dynamic_cast<TileMapScene *>(getEnvironment())->getTileMapPositionX(getCollisionArea().x - 1);
					int screenX = dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionX(tileMapPosX);
					x = GetPosXFromCollisionAreaPosX(screenX + dynamic_cast<TileMapScene *>(getEnvironment())->getTileWidth());
					TileObject * topTileObj = dynamic_cast<TileMapScene *>(getEnvironment())->getTileObjectLayerValue(tileMapStartX, tileMapStartY);
					if (topTileObj == NULL
						|| topTileObj->getID() == static_cast<int>(ObjectID::GEM)
						|| topTileObj->getID() == static_cast<int>(ObjectID::SHOE)
						|| topTileObj->getID() == static_cast<int>(ObjectID::WATER)) {
						y -= speed_;
						if (GetCollisionAreaPosYFromPosY(y) < dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionY(tileMapStartY)) {
							y = GetPosYFromCollisionAreaPosY(dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionY(tileMapStartY));
						}
					}
					TileObject * downTileObj = dynamic_cast<TileMapScene *>(getEnvironment())->getTileObjectLayerValue(tileMapStartX, tileMapEndY);
					if (downTileObj == NULL
						|| downTileObj->getID() == static_cast<int>(ObjectID::GEM)
						|| downTileObj->getID() == static_cast<int>(ObjectID::SHOE)
						|| downTileObj->getID() == static_cast<int>(ObjectID::WATER)) {
						y += speed_;
						if (GetCollisionAreaPosYFromPosY(y) > dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionY(tileMapEndY)) {
							y = GetPosYFromCollisionAreaPosY(dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionY(tileMapEndY));
						}
					}
					SetPosition(x, y);
				}
			}
			else if (direction_ == CharacterDirection::DOWN) {
				for (int i = tileMapStartX; i <= tileMapEndX; i++) {
					TileObject * tileObj = dynamic_cast<TileMapScene *>(getEnvironment())->getTileObjectLayerValue(i, tileMapEndY);
					if (tileObj != NULL) {
						if (tileObj->getID() == static_cast<int>(ObjectID::HOUSE)
							|| tileObj->getID() == static_cast<int>(ObjectID::BRICK)
							|| tileObj->getID() == static_cast<int>(ObjectID::BOMB)) {
							canPass = false;
							break;
						}
					}
				}
				if (!canPass) {
					int tileMapPosY = dynamic_cast<TileMapScene *>(getEnvironment())->getTileMapPositionY(getCollisionArea().y + getCollisionArea().h);
					int screenY = dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionY(tileMapPosY);
					y = GetPosYFromCollisionAreaPosY(screenY - dynamic_cast<TileMapScene *>(getEnvironment())->getTileHeight());
					TileObject * leftTileObj = dynamic_cast<TileMapScene *>(getEnvironment())->getTileObjectLayerValue(tileMapStartX, tileMapEndY);
					if (leftTileObj == NULL
						|| leftTileObj->getID() == static_cast<int>(ObjectID::GEM)
						|| leftTileObj->getID() == static_cast<int>(ObjectID::SHOE)
						|| leftTileObj->getID() == static_cast<int>(ObjectID::WATER)) {
						x -= speed_;
						if (GetCollisionAreaPosXFromPosX(x) < dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionX(tileMapStartX)) {
							x = GetPosXFromCollisionAreaPosX(dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionX(tileMapStartX));
						}
					}
					TileObject * rightTileObj = dynamic_cast<TileMapScene *>(getEnvironment())->getTileObjectLayerValue(tileMapEndX, tileMapEndY);
					if (rightTileObj == NULL
						|| rightTileObj->getID() == static_cast<int>(ObjectID::GEM)
						|| rightTileObj->getID() == static_cast<int>(ObjectID::SHOE)
						|| rightTileObj->getID() == static_cast<int>(ObjectID::WATER)) {
						x += speed_;
						if (GetCollisionAreaPosXFromPosX(x) > dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionX(tileMapEndX)) {
							x = GetPosXFromCollisionAreaPosX(dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionX(tileMapEndX));
						}
					}
					SetPosition(x, y);
				}
			}
			else {
				for (int j = tileMapStartY; j <= tileMapEndY; j++) {
					TileObject * tileObj = dynamic_cast<TileMapScene *>(getEnvironment())->getTileObjectLayerValue(tileMapEndX, j);
					if (tileObj != NULL) {
						if (tileObj->getID() == static_cast<int>(ObjectID::HOUSE)
							|| tileObj->getID() == static_cast<int>(ObjectID::BRICK)
							|| tileObj->getID() == static_cast<int>(ObjectID::BOMB)) {
							canPass = false;
							break;
						}
					}
				}
				if (!canPass) {
					int tileMapPosX = dynamic_cast<TileMapScene *>(getEnvironment())->getTileMapPositionX(getCollisionArea().x + getCollisionArea().w);
					int screenX = dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionX(tileMapPosX);
					x = GetPosXFromCollisionAreaPosX(screenX - dynamic_cast<TileMapScene *>(getEnvironment())->getTileWidth());
					TileObject * topTileObj = dynamic_cast<TileMapScene *>(getEnvironment())->getTileObjectLayerValue(tileMapEndX, tileMapStartY);
					if (topTileObj == NULL
						|| topTileObj->getID() == static_cast<int>(ObjectID::GEM)
						|| topTileObj->getID() == static_cast<int>(ObjectID::SHOE)
						|| topTileObj->getID() == static_cast<int>(ObjectID::WATER)) {
						y -= speed_;
						if (GetCollisionAreaPosYFromPosY(y) < dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionY(tileMapStartY)) {
							y = GetPosYFromCollisionAreaPosY(dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionY(tileMapStartY));
						}
					}
					TileObject * downTileObj = dynamic_cast<TileMapScene *>(getEnvironment())->getTileObjectLayerValue(tileMapEndX, tileMapEndY);
					if (downTileObj == NULL
						|| downTileObj->getID() == static_cast<int>(ObjectID::GEM)
						|| downTileObj->getID() == static_cast<int>(ObjectID::SHOE)
						|| downTileObj->getID() == static_cast<int>(ObjectID::WATER)) {
						y += speed_;
						if (GetCollisionAreaPosYFromPosY(y) > dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionY(tileMapEndY)) {
							y = GetPosYFromCollisionAreaPosY(dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionY(tileMapEndY));
						}
					}
					SetPosition(x, y);
				}
			}
			if (canPass) {
				int tileMapPosX = dynamic_cast<TileMapScene *>(getEnvironment())->getTileMapPositionX(x);
				int tileMapPosY = dynamic_cast<TileMapScene *>(getEnvironment())->getTileMapPositionY(y);
				TileObject * tileObj = dynamic_cast<TileMapScene *>(getEnvironment())->getTileObjectLayerValue(tileMapPosX, tileMapPosY);
				if (tileObj != NULL) {
					if (tileObj->getID() == static_cast<int>(ObjectID::BOMB)) {
					}
					else if (tileObj->getID() == static_cast<int>(ObjectID::GEM)) {
						dynamic_cast<TileMapScene *>(getEnvironment())->setTileObjectLayerValue(tileMapPosX, tileMapPosY, NULL);
						tileObj->setVisibility(false);
						if (bombs_ < MAX_BOMBS) {
							bombs_++;
						}
					}
					else if (tileObj->getID() == static_cast<int>(ObjectID::SHOE)) {
						dynamic_cast<TileMapScene *>(getEnvironment())->setTileObjectLayerValue(tileMapPosX, tileMapPosY, NULL);
						tileObj->setVisibility(false);
						if (speed_ < MAX_SPEED) {
							speed_++;
						}
					}
					else {
						dynamic_cast<TileMapScene *>(getEnvironment())->setTileObjectLayerValue(tileMapPosX, tileMapPosY, NULL);
						tileObj->setVisibility(false);
						if (power_ < MAX_POWER) {
							power_++;
						}
					}
				}
			}
			isIdle_ = false;
		}
	}
	else if (key == KeyCode::KEY_SPACE) {
		int tileMapPosX;
		int tileMapPosY;
		if (direction_ == CharacterDirection::UP) {
			tileMapPosX = dynamic_cast<TileMapScene *>(getEnvironment())->getTileMapPositionX(x);
			tileMapPosY = dynamic_cast<TileMapScene *>(getEnvironment())->getTileMapPositionY(getCollisionArea().y + getCollisionArea().h);
		}
		else if (direction_ == CharacterDirection::DOWN) {
			tileMapPosX = dynamic_cast<TileMapScene *>(getEnvironment())->getTileMapPositionX(x);
			tileMapPosY = dynamic_cast<TileMapScene *>(getEnvironment())->getTileMapPositionY(getCollisionArea().y);
		}
		else if (direction_ == CharacterDirection::LEFT) {
			tileMapPosX = dynamic_cast<TileMapScene *>(getEnvironment())->getTileMapPositionX(getCollisionArea().x + getCollisionArea().w);
			tileMapPosY = dynamic_cast<TileMapScene *>(getEnvironment())->getTileMapPositionY(y);
		}
		else {
			tileMapPosX = dynamic_cast<TileMapScene *>(getEnvironment())->getTileMapPositionX(getCollisionArea().x);
			tileMapPosY = dynamic_cast<TileMapScene *>(getEnvironment())->getTileMapPositionY(y);
		}
		if (dynamic_cast<TileMapScene *>(getEnvironment())->getTileObjectLayerValue(tileMapPosX, tileMapPosY) == NULL) {
			for (int i = 0; i < bombs_; i++) {
				if (bomb_array_[i]->getState() == static_cast<int>(BombState::DISAPPEAR)) {
					bomb_array_[i]->setPower(power_);
					bomb_array_[i]->appear(tileMapPosX, tileMapPosY);
					break;
				}
			}
		}
		isIdle_ = true;
	}
	else {
		// other keys are pressed
		isIdle_ = true;
	}

	// update state
	switch (getState())
	{
	case static_cast<int>(CharacterState::DOWN_IDLE) :
	case static_cast<int>(CharacterState::UP_IDLE) :
	case static_cast<int>(CharacterState::LEFT_IDLE) :
	case static_cast<int>(CharacterState::RIGHT_IDLE) :
		if (!isIdle_) {
			stopAnimation();
			if (direction_ == CharacterDirection::DOWN) {
				setState(static_cast<int>(CharacterState::DOWN_WALK));
			}
			else if (direction_ == CharacterDirection::UP) {
				setState(static_cast<int>(CharacterState::UP_WALK));
			}
			else if (direction_ == CharacterDirection::LEFT) {
				setState(static_cast<int>(CharacterState::LEFT_WALK));
			}
			else {
				setState(static_cast<int>(CharacterState::RIGHT_WALK));
			}
			startAnimation();
		}
		break;
	case static_cast<int>(CharacterState::DOWN_WALK) :
	case static_cast<int>(CharacterState::UP_WALK) :
	case static_cast<int>(CharacterState::LEFT_WALK) :
	case static_cast<int>(CharacterState::RIGHT_WALK) :
		if (!isIdle_) {
			if (direction_ == CharacterDirection::DOWN) {
				if (getState() != static_cast<int>(CharacterState::DOWN_WALK)) {
					stopAnimation();
					setState(static_cast<int>(CharacterState::DOWN_WALK));
					startAnimation();
				}
			}
			else if (direction_ == CharacterDirection::UP) {
				if (getState() != static_cast<int>(CharacterState::UP_WALK)) {
					stopAnimation();
					setState(static_cast<int>(CharacterState::UP_WALK));
					startAnimation();
				}
			}
			else if (direction_ == CharacterDirection::LEFT) {
				if (getState() != static_cast<int>(CharacterState::LEFT_WALK)) {
					stopAnimation();
					setState(static_cast<int>(CharacterState::LEFT_WALK));
					startAnimation();
				}
			}
			else {
				if (getState() != static_cast<int>(CharacterState::RIGHT_WALK)) {
					stopAnimation();
					setState(static_cast<int>(CharacterState::RIGHT_WALK));
					startAnimation();
				}
			}
		}
		else {
			stopAnimation();
			if (direction_ == CharacterDirection::DOWN) {
				setState(static_cast<int>(CharacterState::DOWN_IDLE));
			}
			else if (direction_ == CharacterDirection::UP) {
				setState(static_cast<int>(CharacterState::UP_IDLE));
			}
			else if (direction_ == CharacterDirection::LEFT) {
				setState(static_cast<int>(CharacterState::LEFT_IDLE));
			}
			else {
				setState(static_cast<int>(CharacterState::RIGHT_IDLE));
			}
			startAnimation();
		}
		break;
	case static_cast<int>(CharacterState::DYING) :
		if (death_timer_.getTotalTicks() >= 3000) {
			stopAnimation();
			setState(static_cast<int>(CharacterState::DIE));
			startAnimation();
			death_timer_.stop();
		}
		break;
	case static_cast<int>(CharacterState::RECOVER) :
		if (death_timer_.getTotalTicks() >= 500) {
			setState(static_cast<int>(CharacterState::DOWN_IDLE));
			isIdle_ = true;
			direction_ = CharacterDirection::DOWN;
			startAnimation();
			death_timer_.stop();
		}
		break;
	case static_cast<int>(CharacterState::DIE) :
		if (death_timer_.getTotalTicks() >= 1000) {
			isDead_ = true;
			Hide();
			death_timer_.stop();
		}
		break;
	default:
		break;
	}
}

void Character::DrawObject()
{
	drawAnimationFrame();
}