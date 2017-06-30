#pragma once
#include "../BaseEngine/Scenes/TileMapScene.h"
#include "../BaseEngine/BaseEngine.h"
#include "../BaseEngine/Objects/DisplayableObject.h"
#include "../BaseEngine/Objects/TileObject.h"
#include "Character.h"

class MainScene : public TileMapScene
{
private:
	const Uint32 MAX_TIME;
	Timer game_timer_;
	SDL_Rect time_area_;
	Image background_;

protected:
	// overridable functions for all scene layers
	virtual void DrawAll();
	virtual void DrawChanges();

	// functions for background layer
	void drawBackground();
	void drawBackground(SDL_Rect);

	// functions for tilemap layer
	void drawTileMap();
	void drawTileMap(SDL_Rect);
	void drawTile(int, int);

	void drawTime();

public:
	MainScene(BaseEngine *);
	virtual ~MainScene();

	void startGame();
	void stopGame();

	// overridable functions for all scene layers
	virtual void Setup();
	virtual void Reset();
	virtual void Update();
	virtual void Draw();
};