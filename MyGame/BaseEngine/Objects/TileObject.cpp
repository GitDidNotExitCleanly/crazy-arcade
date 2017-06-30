#include "TileObject.h"
#include "../Scenes/TileMapScene.h"

TileObject::TileObject(TileMapScene * scene)
	:Object(scene),
	tile_map_pos_x_(0),
	tile_map_pos_y_(0)
{
	Hide();
}

TileObject::~TileObject()
{
}

void TileObject::setCollisionAreaPos(int tileMapPosX, int tileMapPosY)
{
	tile_map_pos_x_ = tileMapPosX;
	tile_map_pos_y_ = tileMapPosY;
}

void TileObject::Show()
{
	setVisibility(true);
	dynamic_cast<TileMapScene *>(getEnvironment())->setTileObjectLayerValue(tile_map_pos_x_, tile_map_pos_y_, this);
}

void TileObject::Hide()
{
	setVisibility(false);
	dynamic_cast<TileMapScene *>(getEnvironment())->setTileObjectLayerValue(tile_map_pos_x_, tile_map_pos_y_, NULL);
}

void TileObject::SetPosition(int tileMapPosX, int tileMapPosY)
{
	int anchorPosX = GetPosXFromCollisionAreaPosX(dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionX(tileMapPosX));
	int anchorPosY = GetPosYFromCollisionAreaPosY(dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionY(tileMapPosY));
	setAnchorPosAndImageAreaPos(anchorPosX, anchorPosY);
	setCollisionAreaPos(tileMapPosX, tileMapPosY);
}

int TileObject::GetPositionX()
{
	return tile_map_pos_x_;
}

int TileObject::GetPositionY()
{
	return tile_map_pos_y_;
}

int TileObject::GetImageAreaPosXFromPosX(int posX)
{
	return posX - getImageArea().w / 2;
}

int TileObject::GetImageAreaPosYFromPosY(int posY)
{
	return posY - getImageArea().h / 2;
}

int TileObject::GetPosXFromImageAreaPosX(int imgAreaPosX)
{
	return imgAreaPosX + getImageArea().w / 2;
}

int TileObject::GetPosYFromImageAreaPosY(int imgAreaPosY)
{
	return imgAreaPosY + getImageArea().h / 2;
}

int TileObject::GetCollisionAreaPosXFromPosX(int posX)
{
	int tileMapPosX = dynamic_cast<TileMapScene *>(getEnvironment())->getTileMapPositionX(posX);
	int collisionAreaPosX = dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionX(tileMapPosX);
	return collisionAreaPosX;
}

int TileObject::GetCollisionAreaPosYFromPosY(int posY)
{
	int tileMapPosY = dynamic_cast<TileMapScene *>(getEnvironment())->getTileMapPositionY(posY);
	int collisionAreaPosY = dynamic_cast<TileMapScene *>(getEnvironment())->getTileTopLeftScreenPositionY(tileMapPosY);
	return collisionAreaPosY;
}

int TileObject::GetPosXFromCollisionAreaPosX(int collisionAreaPosX)
{
	return collisionAreaPosX + dynamic_cast<TileMapScene *>(getEnvironment())->getTileWidth() / 2;
}

int TileObject::GetPosYFromCollisionAreaPosY(int collisionAreaPosY)
{
	return collisionAreaPosY + dynamic_cast<TileMapScene *>(getEnvironment())->getTileHeight() / 2;
}