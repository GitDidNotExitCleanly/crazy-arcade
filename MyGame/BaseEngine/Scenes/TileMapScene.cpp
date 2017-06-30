#include "TileMapScene.h"
#include "../BaseEngine.h"
#include "../../MyGame/ObjectID.h"
#include "../Objects/Object.h"
#include "../Objects/DisplayableObject.h"
#include <algorithm>

TileMapScene::TileMapScene(BaseEngine * engine)
	:Scene(engine),
	base_position_x_(0),
	base_position_y_(0),
	tile_width_(0),
	tile_height_(0),
	tile_map_width_(0),
	tile_map_height_(0),
	tile_map_left_border_x_(0),
	tile_map_right_border_x_(0),
	tile_map_top_border_y_(0),
	tile_map_bottom_border_y_(0),
	tile_map_tile_layer_(NULL),
	tile_map_tile_object_layer_(NULL)
{
}

TileMapScene::~TileMapScene()
{
	for (int i = 0; i < tile_map_width_; i++) {
		delete[] tile_map_tile_layer_[i];
	}
	delete[] tile_map_tile_layer_;

	for (int i = 0; i < tile_map_width_; i++) {
		delete[] tile_map_tile_object_layer_[i];
	}
	delete[] tile_map_tile_object_layer_;
}

void TileMapScene::sortZOrderOfTileMapObjects()
{
	std::stable_sort(tile_map_objects_.begin(),tile_map_objects_.end(),lessZOrder);
}

void TileMapScene::sortZOrderOfSceneOtherObjects()
{
	std::stable_sort(scene_other_objects_.begin(), scene_other_objects_.end(), lessZOrder);
}

void TileMapScene::setBasePosition(int screenX, int screenY)
{
	base_position_x_ = screenX;
	base_position_y_ = screenY;
}

void TileMapScene::setTileSize(int tileWidth, int tileHeight)
{
	tile_width_ = tileWidth;
	tile_height_ = tileHeight;
}

void TileMapScene::setTileMapSize(int tileMapWidth, int tileMapHeight)
{
	tile_map_width_ = tileMapWidth;
	tile_map_height_ = tileMapHeight;

	// create tile layer
	tile_map_tile_layer_ = new int *[tileMapWidth];
	for (int i = 0; i < tileMapWidth; i++) {
		tile_map_tile_layer_[i] = new int[tileMapHeight];
	}

	// create tile object layer
	tile_map_tile_object_layer_ = new TileObject **[tileMapWidth];
	for (int i = 0; i < tileMapWidth; i++) {
		tile_map_tile_object_layer_[i] = new TileObject *[tileMapHeight];
	}

	// initialize
	for (int i = 0; i < tileMapWidth; i++) {
		for (int j = 0; j < tileMapHeight; j++) {
			tile_map_tile_layer_[i][j] = 0;
			tile_map_tile_object_layer_[i][j] = NULL;
		}
	}
}

void TileMapScene::setTileMapBorders()
{
	tile_map_left_border_x_ = base_position_x_;
	tile_map_right_border_x_ = base_position_x_ + tile_map_width_ * tile_width_;
	tile_map_top_border_y_ = base_position_y_;
	tile_map_bottom_border_y_ = base_position_y_ + tile_map_height_ * tile_height_;
}

void TileMapScene::setTileLayerValue(int tileMapX, int tileMapY, int value)
{
	tile_map_tile_layer_[tileMapX][tileMapY] = value;
}

void TileMapScene::setTileObjectLayerValue(int tileMapX, int tileMapY, TileObject * obj)
{
	tile_map_tile_object_layer_[tileMapX][tileMapY] = obj;
}

void TileMapScene::addTileObject(int id, TileObject * obj)
{
	tile_map_tile_objects_.push_back(obj);
	tile_map_objects_.push_back(obj);
	addSceneObjectByID(id, obj);
}

void TileMapScene::addActiveObject(int id, DisplayableObject * obj)
{
	tile_map_active_objects_.push_back(obj);
	tile_map_objects_.push_back(obj);
	addSceneObjectByID(id, obj);
}

void TileMapScene::addSceneOtherObject(int id, DisplayableObject * obj)
{
	scene_other_objects_.push_back(obj);
	addSceneObjectByID(id, obj);
}

int TileMapScene::getBasePositionX()
{
	return base_position_x_;
}

int TileMapScene::getBasePositionY()
{
	return base_position_y_;
}

int TileMapScene::getTileWidth()
{
	return tile_width_;
}

int TileMapScene::getTileHeight()
{
	return tile_height_;
}

int TileMapScene::getTileMapWidth()
{
	return tile_map_width_;
}

int TileMapScene::getTileMapHeight()
{
	return tile_map_height_;
}

int TileMapScene::getTileMapLeftBorder()
{
	return tile_map_left_border_x_;
}

int TileMapScene::getTileMapRightBorder()
{
	return tile_map_right_border_x_;
}

int TileMapScene::getTileMapTopBorder()
{
	return tile_map_top_border_y_;
}

int TileMapScene::getTileMapBottomBorder()
{
	return tile_map_bottom_border_y_;
}

int TileMapScene::getTileMapPositionX(int screenX)
{
	return (screenX - base_position_x_) / tile_width_;
}

int TileMapScene::getTileMapPositionY(int screenY)
{
	return (screenY - base_position_y_) / tile_height_;
}

int TileMapScene::getTileTopLeftScreenPositionX(int tileMapX)
{
	return base_position_x_ + tileMapX * tile_width_;
}

int TileMapScene::getTileTopLeftScreenPositionY(int tileMapY)
{
	return base_position_y_ + tileMapY * tile_height_;
}

int TileMapScene::getTileLayerValue(int tileMapX, int tileMapY)
{
	return tile_map_tile_layer_[tileMapX][tileMapY];
}

TileObject * TileMapScene::getTileObjectLayerValue(int tileMapX, int tileMapY)
{
	return tile_map_tile_object_layer_[tileMapX][tileMapY];
}

int TileMapScene::getSizeOfTileObjects()
{
	return static_cast<int>(tile_map_tile_objects_.size());
}

TileObject * TileMapScene::getTileObjectByIndex(int index)
{
	return tile_map_tile_objects_[index];
}

int TileMapScene::getSizeOfActiveObjects()
{
	return static_cast<int>(tile_map_active_objects_.size());
}

DisplayableObject * TileMapScene::getActiveObjectByIndex(int index)
{
	return tile_map_active_objects_[index];
}

int TileMapScene::getSizeOfTileMapObjects()
{
	return static_cast<int>(tile_map_objects_.size());
}

Object * TileMapScene::getTileMapObejctByIndex(int index)
{
	return tile_map_objects_[index];
}

int TileMapScene::getSizeOfSceneOtherObjects()
{
	return static_cast<int>(scene_other_objects_.size());
}

DisplayableObject * TileMapScene::getSceneOtherObjectByIndex(int index)
{
	return scene_other_objects_[index];
}

void TileMapScene::Setup()
{
	// set what to draw
	// ...

	// draw all compoenents at the first time
	setRedraw(true);
	setRedrawAll(true);
}

void TileMapScene::Reset()
{
}

void TileMapScene::Update()
{
	// update
	// decide whether to redraw something
	// and whether to redraw them all or just redraw changing parts
	// ...
}

void TileMapScene::Draw()
{
	// mix draw all and draw changes
	// if the scene needs to redraw, then redraw
	// otherwise do nothing
	if (getRedraw()) {
		// if the scene needs to redraw all, then redraw all
		// otherwise just redraw changing parts
		if (getRedrawAll()) {
			// redraw all
			DrawAll();
			// finished redraw all
			setRedrawAll(false);
		}
		else {
			// redraw changing parts
			DrawChanges();
		}
		// finished redraw
		setRedraw(false);
	}
}