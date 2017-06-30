#include "Brick.h"
#include "SDL.h"
#include "../BaseEngine/Objects/DisplayableObject.h"
#include "../BaseEngine/ResourceManager.h"
#include "MainScene.h"

Brick::Brick(TileMapScene * scene)
	:TileObject(scene),
	gift_(NULL)
{
}

Brick::~Brick()
{
}

void Brick::addGift(Gift * gift)
{
	gift_ = gift;
}

void Brick::exlode()
{
	Hide();
	if (gift_ != NULL) {
		gift_->SetPosition(GetPositionX(), GetPositionY());
		gift_->Show();
	}
}

void Brick::SetPosition(int tileMapPosX, int tileMapPosY)
{
	int anchorPosX = GetPosXFromCollisionAreaPosX(dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionX(tileMapPosX));
	int anchorPosY = GetPosYFromCollisionAreaPosY(dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionY(tileMapPosY));
	setAnchorPosAndImageAreaPos(anchorPosX, anchorPosY);
	setCollisionAreaPos(tileMapPosX, tileMapPosY);
	setZOrder(tileMapPosY * 3);
}

int Brick::GetImageAreaPosXFromPosX(int posX)
{
	return posX - getImageArea().w / 2;
}

int Brick::GetImageAreaPosYFromPosY(int posY)
{
	return posY - (getImageArea().h - 20);
}

int Brick::GetPosXFromImageAreaPosX(int imgAreaPosX)
{
	return imgAreaPosX + getImageArea().w / 2;
}

int Brick::GetPosYFromImageAreaPosY(int imgAreaPosY)
{
	return imgAreaPosY + (getImageArea().h - 20);
}

void Brick::UpdateObject()
{
}

void Brick::DrawObject()
{
	drawStaticSkin();
}
