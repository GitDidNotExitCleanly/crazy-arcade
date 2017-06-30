#include "Gem.h"
#include "SDL.h"
#include "../BaseEngine/Objects/DisplayableObject.h"
#include "../BaseEngine/ResourceManager.h"
#include "MainScene.h"
#include "ResourceID.h"

Gem::Gem(TileMapScene * scene)
	:Gift(scene)
{
}

Gem::~Gem()
{
}

void Gem::SetPosition(int tileMapPosX, int tileMapPosY)
{
	int anchorPosX = GetPosXFromCollisionAreaPosX(dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionX(tileMapPosX));
	int anchorPosY = GetPosYFromCollisionAreaPosY(dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionY(tileMapPosY));
	setAnchorPosAndImageAreaPos(anchorPosX, anchorPosY);
	setCollisionAreaPos(tileMapPosX, tileMapPosY);
	setZOrder(tileMapPosY * 3);
}

int Gem::GetImageAreaPosXFromPosX(int posX)
{
	return posX - getImageArea().w / 2;
}

int Gem::GetImageAreaPosYFromPosY(int posY)
{
	return posY - (getImageArea().h - 15);
}

int Gem::GetPosXFromImageAreaPosX(int imgAreaPosX)
{
	return imgAreaPosX + getImageArea().w / 2;
}

int Gem::GetPosYFromImageAreaPosY(int imgAreaPosY)
{
	return imgAreaPosY + (getImageArea().h - 15);
}

void Gem::UpdateObject()
{
}

void Gem::DrawObject()
{
	drawStaticSkin();
}
