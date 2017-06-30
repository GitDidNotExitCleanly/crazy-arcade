#include "MyGame.h"
#include "../BaseEngine/BaseEngine.h"
#include "../BaseEngine/ResourceManager.h"
#include "../BaseEngine/SceneManager.h"
#include "ResourceID.h"
#include "SceneID.h"
#include "CoverScene.h"
#include "MainScene.h"
#include "YouWin.h"
#include "YouLose.h"
#include <iostream>

MyGame::MyGame()
	:BaseEngine()
{
}

MyGame::~MyGame()
{
}

void MyGame::LoadResource()
{
	ResourceManager * resource = getResourceManager();
	
	// load font
	resource->setMaxFonts(static_cast<int>(FontID::FONT_UNSPECIFIED));
	resource->loadFont(static_cast<int>(FontID::CORNERSTONE_REGULAR_14), "Cornerstone_Regular", 14);

	// load image
	resource->setMaxImages(static_cast<int>(ImageID::IMG_UNSPECIFIED));
	resource->loadImage(static_cast<int>(ImageID::START_PAGE), "start_page.jpg");
	resource->loadImage(static_cast<int>(ImageID::WIN_PAGE), "win_page.png");
	resource->loadImage(static_cast<int>(ImageID::LOSE_PAGE), "lose_page.png");
	resource->loadImage(static_cast<int>(ImageID::BACKGROUND),"background.png");
	resource->loadImage(static_cast<int>(ImageID::GEM), "gem.png");
	resource->loadImage(static_cast<int>(ImageID::SHOE), "shoe.png");
	resource->loadImage(static_cast<int>(ImageID::WATER), "water.png");
	resource->loadImage(static_cast<int>(ImageID::BRICK_RED), "brick_red.png");
	resource->loadImage(static_cast<int>(ImageID::BRICK_YELLOW), "brick_yellow.png");
	resource->loadImage(static_cast<int>(ImageID::BRICK_BOX), "brick_box.png");
	resource->loadImage(static_cast<int>(ImageID::HOUSE_BLUE), "house_blue.png");
	resource->loadImage(static_cast<int>(ImageID::HOUSE_RED), "house_red.png");
	resource->loadImage(static_cast<int>(ImageID::HOUSE_TREE), "house_tree.png");

	// load spritesheet
	resource->setMaxSpriteSheet(static_cast<int>(SpriteSheetID::SPRITE_SHEET_UNSPECIFIED));
	resource->setMaxImageClips(static_cast<int>(ImageClipID::IMG_CLIP_UNSPECIFIED));

	resource->loadSpriteSheet(static_cast<int>(SpriteSheetID::TOWN_GROUND),"town_ground.png");
	resource->loadImageClip(static_cast<int>(SpriteSheetID::TOWN_GROUND), static_cast<int>(ImageClipID::TOWN_GROUND_1),
		0, 0, 40, 40);
	resource->loadImageClip(static_cast<int>(SpriteSheetID::TOWN_GROUND), static_cast<int>(ImageClipID::TOWN_GROUND_2),
		40, 0, 40, 40);
	resource->loadImageClip(static_cast<int>(SpriteSheetID::TOWN_GROUND), static_cast<int>(ImageClipID::TOWN_ROAD_1),
		80, 0, 40, 40);
	resource->loadImageClip(static_cast<int>(SpriteSheetID::TOWN_GROUND), static_cast<int>(ImageClipID::TOWN_ROAD_2),
		120, 0, 40, 40);
	resource->loadImageClip(static_cast<int>(SpriteSheetID::TOWN_GROUND), static_cast<int>(ImageClipID::TOWN_ROAD_3),
		200, 0, 40, 40);

	// load animation
	resource->setMaxAnimationSpriteSheet(static_cast<int>(AnimationSpriteSheetID::ANIMATION_SPRITE_SHEET_UNSPECIFIED));
	resource->setMaxAnimations(static_cast<int>(AnimationID::ANIMATION_UNSPECIFIED));

	resource->loadAnimationSpriteSheet(static_cast<int>(AnimationSpriteSheetID::CHARACTER), "character.png");
	resource->loadAnimation(static_cast<int>(AnimationSpriteSheetID::CHARACTER), static_cast<int>(AnimationID::CHARACTER_FORWARD_IDLE),
		false, 200, 1, 0, 0, 64, 64);
	resource->loadAnimation(static_cast<int>(AnimationSpriteSheetID::CHARACTER), static_cast<int>(AnimationID::CHARACTER_BACKWARD_IDLE),
		false, 200, 1, 0, 64, 64, 64);
	resource->loadAnimation(static_cast<int>(AnimationSpriteSheetID::CHARACTER),static_cast<int>(AnimationID::CHARACTER_LEFT_IDLE),
		false, 200, 1, 0, 128, 64, 64);
	resource->loadAnimation(static_cast<int>(AnimationSpriteSheetID::CHARACTER),static_cast<int>(AnimationID::CHARACTER_RIGHT_IDLE),
		false, 200, 1, 0, 192, 64, 64);
	resource->loadAnimation(static_cast<int>(AnimationSpriteSheetID::CHARACTER), static_cast<int>(AnimationID::CHARACTER_FORWARD),
		true, 50, 6, 0, 256, 64, 64);
	resource->loadAnimation(static_cast<int>(AnimationSpriteSheetID::CHARACTER),static_cast<int>(AnimationID::CHARACTER_BACKWARD),
		true, 50, 6, 0, 320, 64, 64);
	resource->loadAnimation(static_cast<int>(AnimationSpriteSheetID::CHARACTER),static_cast<int>(AnimationID::CHARACTER_LEFT),
		true, 50, 6, 0, 384, 64, 64);
	resource->loadAnimation(static_cast<int>(AnimationSpriteSheetID::CHARACTER),static_cast<int>(AnimationID::CHARACTER_RIGHT),
		true, 50, 6, 0, 448, 64, 64);

	resource->loadAnimationSpriteSheet(static_cast<int>(AnimationSpriteSheetID::CHARACTER_LIFE), "character_life.png");
	resource->loadAnimation(static_cast<int>(AnimationSpriteSheetID::CHARACTER_LIFE), static_cast<int>(AnimationID::CHARACTER_DYING),
		false, 100, 4, 0, 0, 70, 70);
	resource->loadAnimation(static_cast<int>(AnimationSpriteSheetID::CHARACTER_LIFE), static_cast<int>(AnimationID::CHARACTER_RECOVER),
		false, 150, 2, 0, 70, 70, 70);
	resource->loadAnimation(static_cast<int>(AnimationSpriteSheetID::CHARACTER_LIFE), static_cast<int>(AnimationID::CHARACTER_DIE),
		false, 150, 3, 0, 140, 70, 70);

	resource->loadAnimationSpriteSheet(static_cast<int>(AnimationSpriteSheetID::ENEMY), "enemy.png");
	resource->loadAnimation(static_cast<int>(AnimationSpriteSheetID::ENEMY), static_cast<int>(AnimationID::ENEMY_FORWARD_IDLE),
		false, 200, 1, 0, 0, 67, 67);
	resource->loadAnimation(static_cast<int>(AnimationSpriteSheetID::ENEMY), static_cast<int>(AnimationID::ENEMY_BACKWARD_IDLE),
		false, 200, 1, 0, 67, 67, 67);
	resource->loadAnimation(static_cast<int>(AnimationSpriteSheetID::ENEMY), static_cast<int>(AnimationID::ENEMY_LEFT_IDLE),
		false, 200, 1, 0, 134, 67, 67);
	resource->loadAnimation(static_cast<int>(AnimationSpriteSheetID::ENEMY), static_cast<int>(AnimationID::ENEMY_RIGHT_IDLE),
		false, 200, 1, 0, 201, 67, 67);
	resource->loadAnimation(static_cast<int>(AnimationSpriteSheetID::ENEMY), static_cast<int>(AnimationID::ENEMY_FORWARD),
		true, 75, 6, 0, 268, 67, 67);
	resource->loadAnimation(static_cast<int>(AnimationSpriteSheetID::ENEMY), static_cast<int>(AnimationID::ENEMY_BACKWARD),
		true, 75, 6, 0, 335, 67, 67);
	resource->loadAnimation(static_cast<int>(AnimationSpriteSheetID::ENEMY), static_cast<int>(AnimationID::ENEMY_LEFT),
		true, 75, 6, 0, 402, 67, 67);
	resource->loadAnimation(static_cast<int>(AnimationSpriteSheetID::ENEMY), static_cast<int>(AnimationID::ENEMY_RIGHT),
		true, 75, 6, 0, 469, 67, 67);

	resource->loadAnimationSpriteSheet(static_cast<int>(AnimationSpriteSheetID::ENEMY_LIFE), "enemy_life.png");
	resource->loadAnimation(static_cast<int>(AnimationSpriteSheetID::ENEMY_LIFE), static_cast<int>(AnimationID::ENEMY_DYING),
		false, 100, 4, 0, 0, 72, 72);
	resource->loadAnimation(static_cast<int>(AnimationSpriteSheetID::ENEMY_LIFE), static_cast<int>(AnimationID::ENEMY_RECOVER),
		false, 150, 2, 0, 72, 72, 72);
	resource->loadAnimation(static_cast<int>(AnimationSpriteSheetID::ENEMY_LIFE), static_cast<int>(AnimationID::ENEMY_DIE),
		false, 150, 3, 0, 144, 72, 72);

	resource->loadAnimationSpriteSheet(static_cast<int>(AnimationSpriteSheetID::BOMB),"bomb.png");
	resource->loadAnimation(static_cast<int>(AnimationSpriteSheetID::BOMB), static_cast<int>(AnimationID::BOMB),
		true, 200, 3, 0, 0, 40, 40);

	resource->loadAnimationSpriteSheet(static_cast<int>(AnimationSpriteSheetID::BOMB_EXPLOSION), "bomb_explosion.png");
	resource->loadAnimation(static_cast<int>(AnimationSpriteSheetID::BOMB_EXPLOSION), static_cast<int>(AnimationID::BOMB_EXPLOSION),
		false, 100, 3, 0, 0, 40, 40);
}

void MyGame::SetupScenes()
{
	SceneManager * scenes = getSceneManager();
	scenes->setNumOfScenes(4);

	// start scene
	CoverScene * coverScene = new CoverScene(this);
	coverScene->Setup();
	scenes->addScene(static_cast<int>(SceneID::START_PAGE), coverScene);
	scenes->setCurrentScene(static_cast<int>(SceneID::START_PAGE));

	// main scene
	MainScene * mainScene = new MainScene(this);
	mainScene->Setup();
	scenes->addScene(static_cast<int>(SceneID::MAIN), mainScene);

	// result scene
	YouWin * winScene = new YouWin(this);
	winScene->Setup();
	scenes->addScene(static_cast<int>(SceneID::WIN_PAGE), winScene);
	YouLose * loseScene = new YouLose(this);
	loseScene->Setup();
	scenes->addScene(static_cast<int>(SceneID::LOSE_PAGE), loseScene);
}

void MyGame::GameAction()
{
	SceneManager * scenes = getSceneManager();
	Scene * currentScene = scenes->getCurrentScene();
	currentScene->Update();
}

void MyGame::GameRender()
{
	SceneManager * scenes = getSceneManager();
	Scene * currentScene = scenes->getCurrentScene();
	currentScene->Draw();
}