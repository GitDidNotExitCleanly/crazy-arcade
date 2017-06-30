#include "Enemy.h"
#include "MainScene.h"
#include "ObjectID.h"

Enemy::Enemy(Scene * scene)
	:DisplayableObject(scene),
	isIdle_(true),
	direction_(EnemyDirection::DOWN),
	isDead_(false),
	SPEED(1)
{
	setState(static_cast<int>(EnemyState::DOWN_IDLE));
}

Enemy::~Enemy()
{
}

bool Enemy::isDead()
{
	return isDead_;
}

void Enemy::dying()
{
	stopAnimation();
	setState(static_cast<int>(EnemyState::DYING));
	startAnimation();
	death_timer_.start();
}

void Enemy::recover()
{
	stopAnimation();
	setState(static_cast<int>(EnemyState::RECOVER));
	startAnimation();
	death_timer_.start();
}

void Enemy::die()
{
	stopAnimation();
	setState(static_cast<int>(EnemyState::DIE));
	startAnimation();
	death_timer_.start();
}

void Enemy::SetPosition(int x, int y)
{
	setAnchorPosAndImageAreaPos(x, y);
	setCollisionAreaPos(x, y);
	setZOrder(dynamic_cast<TileMapScene *>(getEnvironment())->getTileMapPositionY(y) * 3 + 1);
}

void Enemy::UpdateObject()
{
	int x = GetPositionX();
	int y = GetPositionY();
	if (getState() != static_cast<int>(EnemyState::DYING) && getState() != static_cast<int>(EnemyState::RECOVER) && getState() != static_cast<int>(EnemyState::DIE)) {
		if (direction_ == EnemyDirection::DOWN) {
			y += SPEED;
		}
		else if (direction_ == EnemyDirection::UP) {
			y -= SPEED;
		}
		else if (direction_ == EnemyDirection::LEFT) {
			x -= SPEED;
		}
		else {
			x += SPEED;
		}
		SetPosition(x, y);

		// check if it runs out of scope
		int leftBorder = dynamic_cast<TileMapScene *>(getEnvironment())->getTileMapLeftBorder();
		int rightBorder = dynamic_cast<TileMapScene *>(getEnvironment())->getTileMapRightBorder();
		int topBorder = dynamic_cast<TileMapScene *>(getEnvironment())->getTileMapTopBorder();
		int bottomBorder = dynamic_cast<TileMapScene *>(getEnvironment())->getTileMapBottomBorder();
		if (getCollisionArea().x < leftBorder) {
			x = GetPosXFromCollisionAreaPosX(leftBorder);
			direction_ = EnemyDirection::UP;
		}
		if (getCollisionArea().x + getCollisionArea().w > rightBorder) {
			x = GetPosXFromCollisionAreaPosX(rightBorder - getCollisionArea().w);
			direction_ = EnemyDirection::DOWN;
		}
		if (getCollisionArea().y < topBorder) {
			y = GetPosYFromCollisionAreaPosY(topBorder);
			direction_ = EnemyDirection::RIGHT;
		}
		if (getCollisionArea().y + getCollisionArea().h > bottomBorder) {
			y = GetPosYFromCollisionAreaPosY(bottomBorder - getCollisionArea().h);
			direction_ = EnemyDirection::LEFT;
		}
		SetPosition(x, y);

		// check if it collides with tile objects
		bool canPass = true;
		int tileMapStartX = dynamic_cast<TileMapScene *>(getEnvironment())->getTileMapPositionX(getCollisionArea().x);
		int tileMapStartY = dynamic_cast<TileMapScene *>(getEnvironment())->getTileMapPositionY(getCollisionArea().y);
		int tileMapEndX = dynamic_cast<TileMapScene *>(getEnvironment())->getTileMapPositionX(getCollisionArea().x + getCollisionArea().w - 1);
		int tileMapEndY = dynamic_cast<TileMapScene *>(getEnvironment())->getTileMapPositionY(getCollisionArea().y + getCollisionArea().h - 1);
		if (direction_ == EnemyDirection::UP) {
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
					x -= SPEED;
					if (GetCollisionAreaPosXFromPosX(x) < dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionX(tileMapStartX)) {
						x = GetPosXFromCollisionAreaPosX(dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionX(tileMapStartX));
					}
				}
				TileObject * rightTileObj = dynamic_cast<TileMapScene *>(getEnvironment())->getTileObjectLayerValue(tileMapEndX, tileMapStartY);
				if (rightTileObj == NULL
					|| rightTileObj->getID() == static_cast<int>(ObjectID::GEM)
					|| rightTileObj->getID() == static_cast<int>(ObjectID::SHOE)
					|| rightTileObj->getID() == static_cast<int>(ObjectID::WATER)) {
					x += SPEED;
					if (GetCollisionAreaPosXFromPosX(x) > dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionX(tileMapEndX)) {
						x = GetPosXFromCollisionAreaPosX(dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionX(tileMapEndX));
					}
				}
				SetPosition(x, y);
				if (tileMapStartX == tileMapEndX) {
					direction_ = EnemyDirection::RIGHT;
				}
			}
		}
		else if (direction_ == EnemyDirection::LEFT) {
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
					y -= SPEED;
					if (GetCollisionAreaPosYFromPosY(y) < dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionY(tileMapStartY)) {
						y = GetPosYFromCollisionAreaPosY(dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionY(tileMapStartY));
					}
				}
				TileObject * downTileObj = dynamic_cast<TileMapScene *>(getEnvironment())->getTileObjectLayerValue(tileMapStartX, tileMapEndY);
				if (downTileObj == NULL
					|| downTileObj->getID() == static_cast<int>(ObjectID::GEM)
					|| downTileObj->getID() == static_cast<int>(ObjectID::SHOE)
					|| downTileObj->getID() == static_cast<int>(ObjectID::WATER)) {
					y += SPEED;
					if (GetCollisionAreaPosYFromPosY(y) > dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionY(tileMapEndY)) {
						y = GetPosYFromCollisionAreaPosY(dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionY(tileMapEndY));
					}
				}
				SetPosition(x, y);
				if (tileMapStartY == tileMapEndY) {
					direction_ = EnemyDirection::UP;
				}
			}
		}
		else if (direction_ == EnemyDirection::DOWN) {
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
					x -= SPEED;
					if (GetCollisionAreaPosXFromPosX(x) < dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionX(tileMapStartX)) {
						x = GetPosXFromCollisionAreaPosX(dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionX(tileMapStartX));
					}
				}
				TileObject * rightTileObj = dynamic_cast<TileMapScene *>(getEnvironment())->getTileObjectLayerValue(tileMapEndX, tileMapEndY);
				if (rightTileObj == NULL
					|| rightTileObj->getID() == static_cast<int>(ObjectID::GEM)
					|| rightTileObj->getID() == static_cast<int>(ObjectID::SHOE)
					|| rightTileObj->getID() == static_cast<int>(ObjectID::WATER)) {
					x += SPEED;
					if (GetCollisionAreaPosXFromPosX(x) > dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionX(tileMapEndX)) {
						x = GetPosXFromCollisionAreaPosX(dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionX(tileMapEndX));
					}
				}
				SetPosition(x, y);
				if (tileMapStartX == tileMapEndX) {
					direction_ = EnemyDirection::LEFT;
				}
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
					y -= SPEED;
					if (GetCollisionAreaPosYFromPosY(y) < dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionY(tileMapStartY)) {
						y = GetPosYFromCollisionAreaPosY(dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionY(tileMapStartY));
					}
				}
				TileObject * downTileObj = dynamic_cast<TileMapScene *>(getEnvironment())->getTileObjectLayerValue(tileMapEndX, tileMapEndY);
				if (downTileObj == NULL
					|| downTileObj->getID() == static_cast<int>(ObjectID::GEM)
					|| downTileObj->getID() == static_cast<int>(ObjectID::SHOE)
					|| downTileObj->getID() == static_cast<int>(ObjectID::WATER)) {
					y += SPEED;
					if (GetCollisionAreaPosYFromPosY(y) > dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionY(tileMapEndY)) {
						y = GetPosYFromCollisionAreaPosY(dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionY(tileMapEndY));
					}
				}
				SetPosition(x, y);
				if (tileMapStartY == tileMapEndY) {
					direction_ = EnemyDirection::DOWN;
				}
			}
		}
		isIdle_ = false;
	}

	// update state
	switch (getState())
	{
	case static_cast<int>(EnemyState::DOWN_IDLE) :
	case static_cast<int>(EnemyState::UP_IDLE) :
	case static_cast<int>(EnemyState::LEFT_IDLE) :
	case static_cast<int>(EnemyState::RIGHT_IDLE) :
		if (!isIdle_) {
			stopAnimation();
			if (direction_ == EnemyDirection::DOWN) {
				setState(static_cast<int>(EnemyState::DOWN_WALK));
			}
			else if (direction_ == EnemyDirection::UP) {
				setState(static_cast<int>(EnemyState::UP_WALK));
			}
			else if (direction_ == EnemyDirection::LEFT) {
				setState(static_cast<int>(EnemyState::LEFT_WALK));
			}
			else {
				setState(static_cast<int>(EnemyState::RIGHT_WALK));
			}
			startAnimation();
		}
		break;
	case static_cast<int>(EnemyState::DOWN_WALK) :
	case static_cast<int>(EnemyState::UP_WALK) :
	case static_cast<int>(EnemyState::LEFT_WALK) :
	case static_cast<int>(EnemyState::RIGHT_WALK) :
		if (!isIdle_) {
			if (direction_ == EnemyDirection::DOWN) {
				if (getState() != static_cast<int>(EnemyState::DOWN_WALK)) {
					stopAnimation();
					setState(static_cast<int>(EnemyState::DOWN_WALK));
					startAnimation();
				}
			}
			else if (direction_ == EnemyDirection::UP) {
				if (getState() != static_cast<int>(EnemyState::UP_WALK)) {
					stopAnimation();
					setState(static_cast<int>(EnemyState::UP_WALK));
					startAnimation();
				}
			}
			else if (direction_ == EnemyDirection::LEFT) {
				if (getState() != static_cast<int>(EnemyState::LEFT_WALK)) {
					stopAnimation();
					setState(static_cast<int>(EnemyState::LEFT_WALK));
					startAnimation();
				}
			}
			else {
				if (getState() != static_cast<int>(EnemyState::RIGHT_WALK)) {
					stopAnimation();
					setState(static_cast<int>(EnemyState::RIGHT_WALK));
					startAnimation();
				}
			}
		}
		else {
			stopAnimation();
			if (direction_ == EnemyDirection::DOWN) {
				setState(static_cast<int>(EnemyState::DOWN_IDLE));
			}
			else if (direction_ == EnemyDirection::UP) {
				setState(static_cast<int>(EnemyState::UP_IDLE));
			}
			else if (direction_ == EnemyDirection::LEFT) {
				setState(static_cast<int>(EnemyState::LEFT_IDLE));
			}
			else {
				setState(static_cast<int>(EnemyState::RIGHT_IDLE));
			}
			startAnimation();
		}
		break;
	case static_cast<int>(EnemyState::DYING) :
		if (death_timer_.getTotalTicks() >= 3000) {
			stopAnimation();
			setState(static_cast<int>(EnemyState::DIE));
			startAnimation();
			death_timer_.start();
		}
		break;
	case static_cast<int>(EnemyState::RECOVER) :
		if (death_timer_.getTotalTicks() >= 500) {
			setState(static_cast<int>(EnemyState::DOWN_IDLE));
			isIdle_ = true;
			direction_ = EnemyDirection::DOWN;
			startAnimation();
			death_timer_.stop();
		}
		break;
	case static_cast<int>(EnemyState::DIE) :
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

void Enemy::DrawObject()
{
	drawAnimationFrame();
}
