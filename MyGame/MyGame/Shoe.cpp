#include "Shoe.h"
#include "SDL.h"
#include "../BaseEngine/Objects/DisplayableObject.h"
#include "../BaseEngine/ResourceManager.h"
#include "MainScene.h"
#include "ResourceID.h"

Shoe::Shoe(TileMapScene * scene)
	:Gift(scene)
{
}

Shoe::~Shoe()
{
}

void Shoe::SetPosition(int tileMapPosX, int tileMapPosY)
{
	int anchorPosX = GetPosXFromCollisionAreaPosX(dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionX(tileMapPosX));
	int anchorPosY = GetPosYFromCollisionAreaPosY(dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionY(tileMapPosY));
	setAnchorPosAndImageAreaPos(anchorPosX, anchorPosY);
	setCollisionAreaPos(tileMapPosX, tileMapPosY);
	setZOrder(tileMapPosY * 3);
}

int Shoe::GetImageAreaPosXFromPosX(int posX)
{
	return posX - getImageArea().w / 2;
}

int Shoe::GetImageAreaPosYFromPosY(int posY)
{
	return posY - (getImageArea().h - 15);
}

int Shoe::GetPosXFromImageAreaPosX(int imgAreaPosX)
{
	return imgAreaPosX + getImageArea().w / 2;
}

int Shoe::GetPosYFromImageAreaPosY(int imgAreaPosY)
{
	return imgAreaPosY + (getImageArea().h - 15);
}

void Shoe::UpdateObject()
{
}

void Shoe::DrawObject()
{
	drawStaticSkin();
}