#pragma once
#include "Gift.h"

class Shoe : public Gift
{
public:
	Shoe(TileMapScene *);
	virtual ~Shoe();

	virtual void SetPosition(int, int);
	virtual int GetImageAreaPosXFromPosX(int);
	virtual int GetImageAreaPosYFromPosY(int);
	virtual int GetPosXFromImageAreaPosX(int);
	virtual int GetPosYFromImageAreaPosY(int);
	virtual void UpdateObject();
	virtual void DrawObject();
};

