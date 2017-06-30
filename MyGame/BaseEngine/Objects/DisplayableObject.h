#pragma once
#include "Object.h"

class DisplayableObject : public Object
{
private:
	SDL_Rect collision_area_;

protected:
	void setCollisionAreaPos(int, int);

public:
	DisplayableObject(Scene *);
	virtual ~DisplayableObject();

	void setCollisionAreaSize(int, int);
	SDL_Rect getCollisionArea();

	virtual void Show();
	virtual void Hide();
	virtual void SetPosition(int, int);
	virtual int GetPositionX();
	virtual int GetPositionY();
	virtual int GetImageAreaPosXFromPosX(int);
	virtual int GetImageAreaPosYFromPosY(int);
	virtual int GetPosXFromImageAreaPosX(int);
	virtual int GetPosYFromImageAreaPosY(int);
	virtual int GetCollisionAreaPosXFromPosX(int);
	virtual int GetCollisionAreaPosYFromPosY(int);
	virtual int GetPosXFromCollisionAreaPosX(int);
	virtual int GetPosYFromCollisionAreaPosY(int);

	virtual void UpdateObject() = 0;
	virtual void DrawObject() = 0;
};

