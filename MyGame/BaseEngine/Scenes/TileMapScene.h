#pragma once
#include "SDL.h"
#include "Scene.h"
#include "../ResourceManager.h"
#include "../Objects/Object.h"
#include "../Objects/TileObject.h"
#include "../BaseEngine.h"
#include <vector>

class TileObject;

class TileMapScene : public Scene
{
private:
	int base_position_x_;
	int base_position_y_;
	int tile_width_;
	int tile_height_;
	int tile_map_width_;
	int tile_map_height_;
	int tile_map_left_border_x_;
	int tile_map_right_border_x_;
	int tile_map_top_border_y_;
	int tile_map_bottom_border_y_;
	// tile layer
	int ** tile_map_tile_layer_;
	// tile object layer
	TileObject *** tile_map_tile_object_layer_;
	// objects
	std::vector<TileObject *> tile_map_tile_objects_;
	std::vector<DisplayableObject *> tile_map_active_objects_;
	std::vector<Object *> tile_map_objects_;
	std::vector<DisplayableObject *> scene_other_objects_;

protected:
	void sortZOrderOfTileMapObjects();
	void sortZOrderOfSceneOtherObjects();

public:
	TileMapScene(BaseEngine *);
	virtual ~TileMapScene();

	void setBasePosition(int, int);
	void setTileSize(int, int);
	void setTileMapSize(int, int);
	void setTileMapBorders();
	void setTileLayerValue(int, int, int);
	void setTileObjectLayerValue(int, int, TileObject *);
	void addTileObject(int, TileObject *);
	void addActiveObject(int, DisplayableObject *);
	void addSceneOtherObject(int, DisplayableObject *);
	int getBasePositionX();
	int getBasePositionY();
	int getTileWidth();
	int getTileHeight();
	int getTileMapWidth();
	int getTileMapHeight();
	int getTileMapLeftBorder();
	int getTileMapRightBorder();
	int getTileMapTopBorder();
	int getTileMapBottomBorder();
	int getTileMapPositionX(int);
	int getTileMapPositionY(int);
	int getTileTopLeftScreenPositionX(int);
	int getTileTopLeftScreenPositionY(int);
	int getTileLayerValue(int, int);
	TileObject * getTileObjectLayerValue(int, int);
	int getSizeOfTileObjects();
	TileObject * getTileObjectByIndex(int);
	int getSizeOfActiveObjects();
	DisplayableObject * getActiveObjectByIndex(int);
	int getSizeOfTileMapObjects();
	Object * getTileMapObejctByIndex(int);
	int getSizeOfSceneOtherObjects();
	DisplayableObject * getSceneOtherObjectByIndex(int);

	// overridable functions for all scene layers
	virtual void Setup() = 0;
	virtual void Reset() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
};

