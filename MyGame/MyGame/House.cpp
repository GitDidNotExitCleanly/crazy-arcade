#include "House.h"
#include "SDL.h"
#include "../BaseEngine/Objects/DisplayableObject.h"
#include "../BaseEngine/ResourceManager.h"
#include "MainScene.h"

House::House(TileMapScene * scene)
	:TileObject(scene)
{
}

House::~House()
{
}

void House::SetPosition(int tileMapPosX, int tileMapPosY)
{
	int anchorPosX = GetPosXFromCollisionAreaPosX(dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionX(tileMapPosX));
	int anchorPosY = GetPosYFromCollisionAreaPosY(dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionY(tileMapPosY));
	setAnchorPosAndImageAreaPos(anchorPosX, anchorPosY);
	setCollisionAreaPos(tileMapPosX, tileMapPosY);
	setZOrder(tileMapPosY * 3);
}

int House::GetImageAreaPosXFromPosX(int posX)
{
	return posX - getImageArea().w / 2;
}

int House::GetImageAreaPosYFromPosY(int posY)
{
	return posY - (getImageArea().h - 20);
}

int House::GetPosXFromImageAreaPosX(int imgAreaPosX)
{
	return imgAreaPosX + getImageArea().w / 2;
}

int House::GetPosYFromImageAreaPosY(int imgAreaPosY)
{
	return imgAreaPosY + (getImageArea().h - 20);
}

void House::UpdateObject()
{
}

void House::DrawObject()
{
	drawStaticSkin();
}
