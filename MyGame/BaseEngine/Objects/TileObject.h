#pragma once
#include "Object.h"
#include "../Scenes/TileMapScene.h"

class TileMapScene;

class TileObject : public Object
{
private:
	int tile_map_pos_x_;
	int tile_map_pos_y_;

protected:
	void setCollisionAreaPos(int, int);

public:
	TileObject(TileMapScene *);
	virtual ~TileObject();

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

