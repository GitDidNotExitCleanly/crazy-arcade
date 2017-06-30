#include "DisplayableObject.h"
#include "../BaseEngine.h"

DisplayableObject::DisplayableObject(Scene * scene)
	:Object(scene),
	collision_area_({ 0,0,40,40 })
{
	Show();
}

DisplayableObject::~DisplayableObject()
{
}

void DisplayableObject::setCollisionAreaPos(int anchorPosX, int anchorPosY)
{
	collision_area_.x = GetCollisionAreaPosXFromPosX(anchorPosX);
	collision_area_.y = GetCollisionAreaPosYFromPosY(anchorPosY);
}

void DisplayableObject::setCollisionAreaSize(int width, int height)
{
	collision_area_.w = width;
	collision_area_.h = height;
	collision_area_.x = GetCollisionAreaPosXFromPosX(GetPositionX());
	collision_area_.y = GetCollisionAreaPosYFromPosY(GetPositionY());
}

SDL_Rect DisplayableObject::getCollisionArea()
{
	return collision_area_;
}

void DisplayableObject::Show()
{
	setVisibility(true);
}

void DisplayableObject::Hide()
{
	setVisibility(false);
}

void DisplayableObject::SetPosition(int x, int y)
{
	setAnchorPosAndImageAreaPos(x, y);
	setCollisionAreaPos(x, y);
}

int DisplayableObject::GetPositionX()
{
	return getAnchorPosX();
}

int DisplayableObject::GetPositionY()
{
	return getAnchorPosY();
}

int DisplayableObject::GetImageAreaPosXFromPosX(int posX)
{
	return posX - getImageArea().w / 2;
}

int DisplayableObject::GetImageAreaPosYFromPosY(int posY)
{
	return posY - (getImageArea().h - getCollisionArea().h / 2);
}

int DisplayableObject::GetPosXFromImageAreaPosX(int imgAreaPosX)
{
	return imgAreaPosX + getImageArea().w / 2;
}

int DisplayableObject::GetPosYFromImageAreaPosY(int imgAreaPosY)
{
	return imgAreaPosY + (getImageArea().h - getCollisionArea().h / 2);
}

int DisplayableObject::GetCollisionAreaPosXFromPosX(int posX)
{
	return posX - collision_area_.w / 2;
}

int DisplayableObject::GetCollisionAreaPosYFromPosY(int posY)
{
	return posY - collision_area_.h / 2;
}

int DisplayableObject::GetPosXFromCollisionAreaPosX(int collisionAreaPosX)
{
	return collisionAreaPosX + collision_area_.w / 2;
}

int DisplayableObject::GetPosYFromCollisionAreaPosY(int collisionAreaPosY)
{
	return collisionAreaPosY + collision_area_.h / 2;
}