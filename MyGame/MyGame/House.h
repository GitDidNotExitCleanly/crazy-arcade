#pragma once
#include "../BaseEngine/Objects/TileObject.h"
#include "../BaseEngine/ResourceManager.h"

class House : public TileObject
{
public:
	House(TileMapScene *);
	virtual ~House();

	virtual void SetPosition(int, int);
	virtual int GetImageAreaPosXFromPosX(int);
	virtual int GetImageAreaPosYFromPosY(int);
	virtual int GetPosXFromImageAreaPosX(int);
	virtual int GetPosYFromImageAreaPosY(int);
	virtual void UpdateObject();
	virtual void DrawObject();
};

