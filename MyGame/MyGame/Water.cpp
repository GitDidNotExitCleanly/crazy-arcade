#include "Water.h"
#include "SDL.h"
#include "../BaseEngine/Objects/DisplayableObject.h"
#include "../BaseEngine/ResourceManager.h"
#include "MainScene.h"
#include "ResourceID.h"

Water::Water(TileMapScene * scene)
	:Gift(scene)
{
}

Water::~Water()
{
}

void Water::SetPosition(int tileMapPosX, int tileMapPosY)
{
	int anchorPosX = GetPosXFromCollisionAreaPosX(dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionX(tileMapPosX));
	int anchorPosY = GetPosYFromCollisionAreaPosY(dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionY(tileMapPosY));
	setAnchorPosAndImageAreaPos(anchorPosX, anchorPosY);
	setCollisionAreaPos(tileMapPosX, tileMapPosY);
	setZOrder(tileMapPosY * 3);
}

int Water::GetImageAreaPosXFromPosX(int posX)
{
	return posX - getImageArea().w / 2;
}

int Water::GetImageAreaPosYFromPosY(int posY)
{
	return posY - (getImageArea().h - 15);
}

int Water::GetPosXFromImageAreaPosX(int imgAreaPosX)
{
	return imgAreaPosX + getImageArea().w / 2;
}

int Water::GetPosYFromImageAreaPosY(int imgAreaPosY)
{
	return imgAreaPosY + (getImageArea().h - 15);
}

void Water::UpdateObject()
{
}

void Water::DrawObject()
{
	drawStaticSkin();
}