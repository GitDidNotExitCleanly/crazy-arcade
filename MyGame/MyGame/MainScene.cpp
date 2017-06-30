#include "MainScene.h"
#include "../BaseEngine/ResourceManager.h"
#include "ResourceID.h"
#include "ObjectID.h"
#include "SceneID.h"
#include "Character.h"
#include "Enemy.h"
#include "Gem.h"
#include "Shoe.h"
#include "Water.h"
#include "House.h"
#include "Bomb.h"
#include "Brick.h"
#include <iostream>
#include <string>

MainScene::MainScene(BaseEngine * engine)
	:TileMapScene(engine),
	MAX_TIME(180000),
	time_area_({ 718,38,50,20 })
{
}

MainScene::~MainScene()
{
}

void MainScene::startGame()
{
	game_timer_.start();
}

void MainScene::stopGame()
{
	game_timer_.stop();
}

void MainScene::Setup()
{
	ResourceManager * resource = getBaseEngine()->getResourceManager();

	// setup background layer
	background_ = resource->getImage(static_cast<unsigned int>(ImageID::BACKGROUND));

	// setup tile map basics
	setBasePosition(20, 40);
	setTileSize(40, 40);
	setTileMapSize(15, 13);
	setTileMapBorders();

	// setup tile layer
	int k = 0;
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 13; j++) {
			if (k == 0) {
				setTileLayerValue(i, j, static_cast<int>(TileID::GROUND1));
			}
			else {
				setTileLayerValue(i, j, static_cast<int>(TileID::GROUND2));
			}
			k = (k + 1) % 2;
		}
	}
	for (int j = 0; j < 13; j++) {
		setTileLayerValue(6, j, static_cast<int>(TileID::ROAD1));
		setTileLayerValue(7, j, static_cast<int>(TileID::ROAD3));
		setTileLayerValue(8, j, static_cast<int>(TileID::ROAD1));
	}
	for (int i = 6; i <= 8; i++) {
		setTileLayerValue(i, 2, static_cast<int>(TileID::ROAD2));
		setTileLayerValue(i, 10, static_cast<int>(TileID::ROAD2));
	}

	// setup tile object layer
	// add all objects
	setSizeOfSceneObjects(84);
	
	int id = 0;
	House * house = new House(this);
	house->setID(static_cast<int>(ObjectID::HOUSE));
	house->setSkin(resource->getImage(static_cast<int>(ImageID::HOUSE_BLUE)));
	house->setImageAreaSize(40, 57);
	house->SetPosition(1, 1);
	house->Show();
	addTileObject(id, house);
	id++;
	house = new House(this);
	house->setID(static_cast<int>(ObjectID::HOUSE));
	house->setSkin(resource->getImage(static_cast<int>(ImageID::HOUSE_BLUE)));
	house->setImageAreaSize(40, 57);
	house->SetPosition(3, 1);
	house->Show();
	addTileObject(id, house);
	id++;
	house = new House(this);
	house->setID(static_cast<int>(ObjectID::HOUSE));
	house->setSkin(resource->getImage(static_cast<int>(ImageID::HOUSE_BLUE)));
	house->setImageAreaSize(40, 57);
	house->SetPosition(1, 3);
	house->Show();
	addTileObject(id, house);
	id++;
	house = new House(this);
	house->setID(static_cast<int>(ObjectID::HOUSE));
	house->setSkin(resource->getImage(static_cast<int>(ImageID::HOUSE_BLUE)));
	house->setImageAreaSize(40, 57);
	house->SetPosition(3, 3);
	house->Show();
	addTileObject(id, house);
	id++;
	house = new House(this);
	house->setID(static_cast<int>(ObjectID::HOUSE));
	house->setSkin(resource->getImage(static_cast<int>(ImageID::HOUSE_BLUE)));
	house->setImageAreaSize(40, 57);
	house->SetPosition(1, 5);
	house->Show();
	addTileObject(id, house);
	id++;
	house = new House(this);
	house->setID(static_cast<int>(ObjectID::HOUSE));
	house->setSkin(resource->getImage(static_cast<int>(ImageID::HOUSE_BLUE)));
	house->setImageAreaSize(40, 57);
	house->SetPosition(3, 5);
	house->Show();
	addTileObject(id, house);
	id++;

	house = new House(this);
	house->setID(static_cast<int>(ObjectID::HOUSE));
	house->setSkin(resource->getImage(static_cast<int>(ImageID::HOUSE_RED)));
	house->setImageAreaSize(40, 57);
	house->SetPosition(11, 7);
	house->Show();
	addTileObject(id, house);
	id++;
	house = new House(this);
	house->setID(static_cast<int>(ObjectID::HOUSE));
	house->setSkin(resource->getImage(static_cast<int>(ImageID::HOUSE_RED)));
	house->setImageAreaSize(40, 57);
	house->SetPosition(13, 7);
	house->Show();
	addTileObject(id, house);
	id++;
	house = new House(this);
	house->setID(static_cast<int>(ObjectID::HOUSE));
	house->setSkin(resource->getImage(static_cast<int>(ImageID::HOUSE_RED)));
	house->setImageAreaSize(40, 57);
	house->SetPosition(11, 9);
	house->Show();
	addTileObject(id, house);
	id++;
	house = new House(this);
	house->setID(static_cast<int>(ObjectID::HOUSE));
	house->setSkin(resource->getImage(static_cast<int>(ImageID::HOUSE_RED)));
	house->setImageAreaSize(40, 57);
	house->SetPosition(13, 9);
	house->Show();
	addTileObject(id, house);
	id++;
	house = new House(this);
	house->setID(static_cast<int>(ObjectID::HOUSE));
	house->setSkin(resource->getImage(static_cast<int>(ImageID::HOUSE_RED)));
	house->setImageAreaSize(40, 57);
	house->SetPosition(11, 11);
	house->Show();
	addTileObject(id, house);
	id++;
	house = new House(this);
	house->setID(static_cast<int>(ObjectID::HOUSE));
	house->setSkin(resource->getImage(static_cast<int>(ImageID::HOUSE_RED)));
	house->setImageAreaSize(40, 57);
	house->SetPosition(13, 11);
	house->Show();
	addTileObject(id, house);
	id++;

	house = new House(this);
	house->setID(static_cast<int>(ObjectID::HOUSE));
	house->setSkin(resource->getImage(static_cast<int>(ImageID::HOUSE_RED)));
	house->setImageAreaSize(40, 57);
	house->SetPosition(0, 8);
	house->Show();
	addTileObject(id, house);
	id++;
	house = new House(this);
	house->setID(static_cast<int>(ObjectID::HOUSE));
	house->setSkin(resource->getImage(static_cast<int>(ImageID::HOUSE_RED)));
	house->setImageAreaSize(40, 57);
	house->SetPosition(2, 8);
	house->Show();
	addTileObject(id, house);
	id++;
	house = new House(this);
	house->setID(static_cast<int>(ObjectID::HOUSE));
	house->setSkin(resource->getImage(static_cast<int>(ImageID::HOUSE_RED)));
	house->setImageAreaSize(40, 57);
	house->SetPosition(4, 8);
	house->Show();
	addTileObject(id, house);
	id++;
	house = new House(this);
	house->setID(static_cast<int>(ObjectID::HOUSE));
	house->setSkin(resource->getImage(static_cast<int>(ImageID::HOUSE_RED)));
	house->setImageAreaSize(40, 57);
	house->SetPosition(0, 10);
	house->Show();
	addTileObject(id, house);
	id++;
	house = new House(this);
	house->setID(static_cast<int>(ObjectID::HOUSE));
	house->setSkin(resource->getImage(static_cast<int>(ImageID::HOUSE_RED)));
	house->setImageAreaSize(40, 57);
	house->SetPosition(2, 10);
	house->Show();
	addTileObject(id, house);
	id++;
	house = new House(this);
	house->setID(static_cast<int>(ObjectID::HOUSE));
	house->setSkin(resource->getImage(static_cast<int>(ImageID::HOUSE_RED)));
	house->setImageAreaSize(40, 57);
	house->SetPosition(4, 10);
	house->Show();
	addTileObject(id, house);
	id++;
	house = new House(this);
	house->setID(static_cast<int>(ObjectID::HOUSE));
	house->setSkin(resource->getImage(static_cast<int>(ImageID::HOUSE_RED)));
	house->setImageAreaSize(40, 57);
	house->SetPosition(0, 12);
	house->Show();
	addTileObject(id, house);
	id++;
	house = new House(this);
	house->setID(static_cast<int>(ObjectID::HOUSE));
	house->setSkin(resource->getImage(static_cast<int>(ImageID::HOUSE_RED)));
	house->setImageAreaSize(40, 57);
	house->SetPosition(2, 12);
	house->Show();
	addTileObject(id, house);
	id++;
	house = new House(this);
	house->setID(static_cast<int>(ObjectID::HOUSE));
	house->setSkin(resource->getImage(static_cast<int>(ImageID::HOUSE_RED)));
	house->setImageAreaSize(40, 57);
	house->SetPosition(4, 12);
	house->Show();
	addTileObject(id, house);
	id++;

	house = new House(this);
	house->setID(static_cast<int>(ObjectID::HOUSE));
	house->setSkin(resource->getImage(static_cast<int>(ImageID::HOUSE_RED)));
	house->setImageAreaSize(40, 57);
	house->SetPosition(10, 0);
	house->Show();
	addTileObject(id, house);
	id++;
	house = new House(this);
	house->setID(static_cast<int>(ObjectID::HOUSE));
	house->setSkin(resource->getImage(static_cast<int>(ImageID::HOUSE_RED)));
	house->setImageAreaSize(40, 57);
	house->SetPosition(12, 0);
	house->Show();
	addTileObject(id, house);
	id++;
	house = new House(this);
	house->setID(static_cast<int>(ObjectID::HOUSE));
	house->setSkin(resource->getImage(static_cast<int>(ImageID::HOUSE_RED)));
	house->setImageAreaSize(40, 57);
	house->SetPosition(14, 0);
	house->Show();
	addTileObject(id, house);
	id++;
	house = new House(this);
	house->setID(static_cast<int>(ObjectID::HOUSE));
	house->setSkin(resource->getImage(static_cast<int>(ImageID::HOUSE_RED)));
	house->setImageAreaSize(40, 57);
	house->SetPosition(10, 2);
	house->Show();
	addTileObject(id, house);
	id++;
	house = new House(this);
	house->setID(static_cast<int>(ObjectID::HOUSE));
	house->setSkin(resource->getImage(static_cast<int>(ImageID::HOUSE_RED)));
	house->setImageAreaSize(40, 57);
	house->SetPosition(12, 2);
	house->Show();
	addTileObject(id, house);
	id++;
	house = new House(this);
	house->setID(static_cast<int>(ObjectID::HOUSE));
	house->setSkin(resource->getImage(static_cast<int>(ImageID::HOUSE_RED)));
	house->setImageAreaSize(40, 57);
	house->SetPosition(14, 2);
	house->Show();
	addTileObject(id, house);
	id++;
	house = new House(this);
	house->setID(static_cast<int>(ObjectID::HOUSE));
	house->setSkin(resource->getImage(static_cast<int>(ImageID::HOUSE_RED)));
	house->setImageAreaSize(40, 57);
	house->SetPosition(10, 4);
	house->Show();
	addTileObject(id, house);
	id++;
	house = new House(this);
	house->setID(static_cast<int>(ObjectID::HOUSE));
	house->setSkin(resource->getImage(static_cast<int>(ImageID::HOUSE_RED)));
	house->setImageAreaSize(40, 57);
	house->SetPosition(12, 4);
	house->Show();
	addTileObject(id, house);
	id++;
	house = new House(this);
	house->setID(static_cast<int>(ObjectID::HOUSE));
	house->setSkin(resource->getImage(static_cast<int>(ImageID::HOUSE_RED)));
	house->setImageAreaSize(40, 57);
	house->SetPosition(14, 4);
	house->Show();
	addTileObject(id, house);
	id++;

	house = new House(this);
	house->setID(static_cast<int>(ObjectID::HOUSE));
	house->setSkin(resource->getImage(static_cast<int>(ImageID::HOUSE_TREE)));
	house->setImageAreaSize(40, 67);
	house->SetPosition(0, 6);
	house->Show();
	addTileObject(id, house);
	id++;
	house = new House(this);
	house->setID(static_cast<int>(ObjectID::HOUSE));
	house->setSkin(resource->getImage(static_cast<int>(ImageID::HOUSE_TREE)));
	house->setImageAreaSize(40, 67);
	house->SetPosition(2, 6);
	house->Show();
	addTileObject(id, house);
	id++;
	house = new House(this);
	house->setID(static_cast<int>(ObjectID::HOUSE));
	house->setSkin(resource->getImage(static_cast<int>(ImageID::HOUSE_TREE)));
	house->setImageAreaSize(40, 67);
	house->SetPosition(4, 6);
	house->Show();
	addTileObject(id, house);
	id++;

	house = new House(this);
	house->setID(static_cast<int>(ObjectID::HOUSE));
	house->setSkin(resource->getImage(static_cast<int>(ImageID::HOUSE_TREE)));
	house->setImageAreaSize(40, 67);
	house->SetPosition(10, 6);
	house->Show();
	addTileObject(id, house);
	id++;
	house = new House(this);
	house->setID(static_cast<int>(ObjectID::HOUSE));
	house->setSkin(resource->getImage(static_cast<int>(ImageID::HOUSE_TREE)));
	house->setImageAreaSize(40, 67);
	house->SetPosition(12, 6);
	house->Show();
	addTileObject(id, house);
	id++;
	house = new House(this);
	house->setID(static_cast<int>(ObjectID::HOUSE));
	house->setSkin(resource->getImage(static_cast<int>(ImageID::HOUSE_TREE)));
	house->setImageAreaSize(40, 67);
	house->SetPosition(14, 6);
	house->Show();
	addTileObject(id, house);
	id++;

	house = new House(this);
	house->setID(static_cast<int>(ObjectID::HOUSE));
	house->setSkin(resource->getImage(static_cast<int>(ImageID::HOUSE_TREE)));
	house->setImageAreaSize(40, 67);
	house->SetPosition(5, 1);
	house->Show();
	addTileObject(id, house);
	id++;
	house = new House(this);
	house->setID(static_cast<int>(ObjectID::HOUSE));
	house->setSkin(resource->getImage(static_cast<int>(ImageID::HOUSE_TREE)));
	house->setImageAreaSize(40, 67);
	house->SetPosition(5, 3);
	house->Show();
	addTileObject(id, house);
	id++;
	house = new House(this);
	house->setID(static_cast<int>(ObjectID::HOUSE));
	house->setSkin(resource->getImage(static_cast<int>(ImageID::HOUSE_TREE)));
	house->setImageAreaSize(40, 67);
	house->SetPosition(5, 5);
	house->Show();
	addTileObject(id, house);
	id++;
	house = new House(this);
	house->setID(static_cast<int>(ObjectID::HOUSE));
	house->setSkin(resource->getImage(static_cast<int>(ImageID::HOUSE_TREE)));
	house->setImageAreaSize(40, 67);
	house->SetPosition(5, 9);
	house->Show();
	addTileObject(id, house);
	id++;
	house = new House(this);
	house->setID(static_cast<int>(ObjectID::HOUSE));
	house->setSkin(resource->getImage(static_cast<int>(ImageID::HOUSE_TREE)));
	house->setImageAreaSize(40, 67);
	house->SetPosition(5, 11);
	house->Show();
	addTileObject(id, house);
	id++;

	house = new House(this);
	house->setID(static_cast<int>(ObjectID::HOUSE));
	house->setSkin(resource->getImage(static_cast<int>(ImageID::HOUSE_TREE)));
	house->setImageAreaSize(40, 67);
	house->SetPosition(9, 1);
	house->Show();
	addTileObject(id, house);
	id++;
	house = new House(this);
	house->setID(static_cast<int>(ObjectID::HOUSE));
	house->setSkin(resource->getImage(static_cast<int>(ImageID::HOUSE_TREE)));
	house->setImageAreaSize(40, 67);
	house->SetPosition(9, 3);
	house->Show();
	addTileObject(id, house);
	id++;
	house = new House(this);
	house->setID(static_cast<int>(ObjectID::HOUSE));
	house->setSkin(resource->getImage(static_cast<int>(ImageID::HOUSE_TREE)));
	house->setImageAreaSize(40, 67);
	house->SetPosition(9, 7);
	house->Show();
	addTileObject(id, house);
	id++;
	house = new House(this);
	house->setID(static_cast<int>(ObjectID::HOUSE));
	house->setSkin(resource->getImage(static_cast<int>(ImageID::HOUSE_TREE)));
	house->setImageAreaSize(40, 67);
	house->SetPosition(9, 9);
	house->Show();
	addTileObject(id, house);
	id++;
	house = new House(this);
	house->setID(static_cast<int>(ObjectID::HOUSE));
	house->setSkin(resource->getImage(static_cast<int>(ImageID::HOUSE_TREE)));
	house->setImageAreaSize(40, 67);
	house->SetPosition(9, 11);
	house->Show();
	addTileObject(id, house);
	id++;

	Brick * brick = new Brick(this);
	brick->setID(static_cast<int>(ObjectID::BRICK));
	brick->setSkin(resource->getImage(static_cast<int>(ImageID::BRICK_RED)));
	brick->setImageAreaSize(40, 44);
	brick->SetPosition(2, 0);
	brick->Show();
	addTileObject(id, brick);
	id++;
	Gem * gem = new Gem(this);
	gem->setID(static_cast<int>(ObjectID::GEM));
	gem->setSkin(resource->getImage(static_cast<int>(ImageID::GEM)));
	gem->setImageAreaSize(42, 45);
	brick->addGift(gem);
	addTileObject(id, gem);
	id++;

	brick = new Brick(this);
	brick->setID(static_cast<int>(ObjectID::BRICK));
	brick->setSkin(resource->getImage(static_cast<int>(ImageID::BRICK_YELLOW)));
	brick->setImageAreaSize(40, 44);
	brick->SetPosition(4, 0);
	brick->Show();
	addTileObject(id, brick);
	id++;
	Shoe * shoe = new Shoe(this);
	shoe->setID(static_cast<int>(ObjectID::SHOE));
	shoe->setSkin(resource->getImage(static_cast<int>(ImageID::SHOE)));
	shoe->setImageAreaSize(42, 45);
	brick->addGift(shoe);
	addTileObject(id, shoe);
	id++;

	brick = new Brick(this);
	brick->setID(static_cast<int>(ObjectID::BRICK));
	brick->setSkin(resource->getImage(static_cast<int>(ImageID::BRICK_RED)));
	brick->setImageAreaSize(40, 44);
	brick->SetPosition(3, 2);
	brick->Show();
	addTileObject(id, brick);
	id++;
	Water * water = new Water(this);
	water->setID(static_cast<int>(ObjectID::WATER));
	water->setSkin(resource->getImage(static_cast<int>(ImageID::WATER)));
	water->setImageAreaSize(42, 45);
	brick->addGift(water);
	addTileObject(id, water);
	id++;

	brick = new Brick(this);
	brick->setID(static_cast<int>(ObjectID::BRICK));
	brick->setSkin(resource->getImage(static_cast<int>(ImageID::BRICK_RED)));
	brick->setImageAreaSize(40, 44);
	brick->SetPosition(0, 4);
	brick->Show();
	addTileObject(id, brick);
	id++;
	brick = new Brick(this);
	brick->setID(static_cast<int>(ObjectID::BRICK));
	brick->setSkin(resource->getImage(static_cast<int>(ImageID::BRICK_BOX)));
	brick->setImageAreaSize(40, 44);
	brick->SetPosition(2, 4);
	brick->Show();
	addTileObject(id, brick);
	id++;
	brick = new Brick(this);
	brick->setID(static_cast<int>(ObjectID::BRICK));
	brick->setSkin(resource->getImage(static_cast<int>(ImageID::BRICK_RED)));
	brick->setImageAreaSize(40, 44);
	brick->SetPosition(4, 4);
	brick->Show();
	addTileObject(id, brick);
	id++;
	brick = new Brick(this);
	brick->setID(static_cast<int>(ObjectID::BRICK));
	brick->setSkin(resource->getImage(static_cast<int>(ImageID::BRICK_RED)));
	brick->setImageAreaSize(40, 44);
	brick->SetPosition(11, 0);
	brick->Show();
	addTileObject(id, brick);
	id++;
	brick = new Brick(this);
	brick->setID(static_cast<int>(ObjectID::BRICK));
	brick->setSkin(resource->getImage(static_cast<int>(ImageID::BRICK_YELLOW)));
	brick->setImageAreaSize(40, 44);
	brick->SetPosition(10, 1);
	brick->Show();
	addTileObject(id, brick);
	id++;
	brick = new Brick(this);
	brick->setID(static_cast<int>(ObjectID::BRICK));
	brick->setSkin(resource->getImage(static_cast<int>(ImageID::BRICK_RED)));
	brick->setImageAreaSize(40, 44);
	brick->SetPosition(11, 3);
	brick->Show();
	addTileObject(id, brick);
	id++;
	brick = new Brick(this);
	brick->setID(static_cast<int>(ObjectID::BRICK));
	brick->setSkin(resource->getImage(static_cast<int>(ImageID::BRICK_RED)));
	brick->setImageAreaSize(40, 44);
	brick->SetPosition(13, 3);
	brick->Show();
	addTileObject(id, brick);
	id++;
	brick = new Brick(this);
	brick->setID(static_cast<int>(ObjectID::BRICK));
	brick->setSkin(resource->getImage(static_cast<int>(ImageID::BRICK_RED)));
	brick->setImageAreaSize(40, 44);
	brick->SetPosition(10, 5);
	brick->Show();
	addTileObject(id, brick);
	id++;
	brick = new Brick(this);
	brick->setID(static_cast<int>(ObjectID::BRICK));
	brick->setSkin(resource->getImage(static_cast<int>(ImageID::BRICK_RED)));
	brick->setImageAreaSize(40, 44);
	brick->SetPosition(12, 5);
	brick->Show();
	addTileObject(id, brick);
	id++;
	brick = new Brick(this);
	brick->setID(static_cast<int>(ObjectID::BRICK));
	brick->setSkin(resource->getImage(static_cast<int>(ImageID::BRICK_BOX)));
	brick->setImageAreaSize(40, 44);
	brick->SetPosition(14, 5);
	brick->Show();
	addTileObject(id, brick);
	id++;
	brick = new Brick(this);
	brick->setID(static_cast<int>(ObjectID::BRICK));
	brick->setSkin(resource->getImage(static_cast<int>(ImageID::BRICK_RED)));
	brick->setImageAreaSize(40, 44);
	brick->SetPosition(0, 7);
	brick->Show();
	addTileObject(id, brick);
	id++;
	brick = new Brick(this);
	brick->setID(static_cast<int>(ObjectID::BRICK));
	brick->setSkin(resource->getImage(static_cast<int>(ImageID::BRICK_RED)));
	brick->setImageAreaSize(40, 44);
	brick->SetPosition(2, 7);
	brick->Show();
	addTileObject(id, brick);
	id++;
	brick = new Brick(this);
	brick->setID(static_cast<int>(ObjectID::BRICK));
	brick->setSkin(resource->getImage(static_cast<int>(ImageID::BRICK_RED)));
	brick->setImageAreaSize(40, 44);
	brick->SetPosition(4, 7);
	brick->Show();
	addTileObject(id, brick);
	id++;
	brick = new Brick(this);
	brick->setID(static_cast<int>(ObjectID::BRICK));
	brick->setSkin(resource->getImage(static_cast<int>(ImageID::BRICK_RED)));
	brick->setImageAreaSize(40, 44);
	brick->SetPosition(1, 9);
	brick->Show();
	addTileObject(id, brick);
	id++;
	brick = new Brick(this);
	brick->setID(static_cast<int>(ObjectID::BRICK));
	brick->setSkin(resource->getImage(static_cast<int>(ImageID::BRICK_RED)));
	brick->setImageAreaSize(40, 44);
	brick->SetPosition(3, 9);
	brick->Show();
	addTileObject(id, brick);
	id++;
	brick = new Brick(this);
	brick->setID(static_cast<int>(ObjectID::BRICK));
	brick->setSkin(resource->getImage(static_cast<int>(ImageID::BRICK_YELLOW)));
	brick->setImageAreaSize(40, 44);
	brick->SetPosition(2, 11);
	brick->Show();
	addTileObject(id, brick);
	id++;
	brick = new Brick(this);
	brick->setID(static_cast<int>(ObjectID::BRICK));
	brick->setSkin(resource->getImage(static_cast<int>(ImageID::BRICK_RED)));
	brick->setImageAreaSize(40, 44);
	brick->SetPosition(4, 11);
	brick->Show();
	addTileObject(id, brick);
	id++;
	brick = new Brick(this);
	brick->setID(static_cast<int>(ObjectID::BRICK));
	brick->setSkin(resource->getImage(static_cast<int>(ImageID::BRICK_RED)));
	brick->setImageAreaSize(40, 44);
	brick->SetPosition(10, 7);
	brick->Show();
	addTileObject(id, brick);
	id++;
	brick = new Brick(this);
	brick->setID(static_cast<int>(ObjectID::BRICK));
	brick->setSkin(resource->getImage(static_cast<int>(ImageID::BRICK_BOX)));
	brick->setImageAreaSize(40, 44);
	brick->SetPosition(12, 7);
	brick->Show();
	addTileObject(id, brick);
	id++;
	brick = new Brick(this);
	brick->setID(static_cast<int>(ObjectID::BRICK));
	brick->setSkin(resource->getImage(static_cast<int>(ImageID::BRICK_RED)));
	brick->setImageAreaSize(40, 44);
	brick->SetPosition(14, 7);
	brick->Show();
	addTileObject(id, brick);
	id++;
	brick = new Brick(this);
	brick->setID(static_cast<int>(ObjectID::BRICK));
	brick->setSkin(resource->getImage(static_cast<int>(ImageID::BRICK_RED)));
	brick->setImageAreaSize(40, 44);
	brick->SetPosition(11, 8);
	brick->Show();
	addTileObject(id, brick);
	id++;
	brick = new Brick(this);
	brick->setID(static_cast<int>(ObjectID::BRICK));
	brick->setSkin(resource->getImage(static_cast<int>(ImageID::BRICK_RED)));
	brick->setImageAreaSize(40, 44);
	brick->SetPosition(13, 8);
	brick->Show();
	addTileObject(id, brick);
	id++;
	brick = new Brick(this);
	brick->setID(static_cast<int>(ObjectID::BRICK));
	brick->setSkin(resource->getImage(static_cast<int>(ImageID::BRICK_RED)));
	brick->setImageAreaSize(40, 44);
	brick->SetPosition(10, 10);
	brick->Show();
	addTileObject(id, brick);
	id++;
	brick = new Brick(this);
	brick->setID(static_cast<int>(ObjectID::BRICK));
	brick->setSkin(resource->getImage(static_cast<int>(ImageID::BRICK_YELLOW)));
	brick->setImageAreaSize(40, 44);
	brick->SetPosition(12, 10);
	brick->Show();
	addTileObject(id, brick);
	id++;
	brick = new Brick(this);
	brick->setID(static_cast<int>(ObjectID::BRICK));
	brick->setSkin(resource->getImage(static_cast<int>(ImageID::BRICK_RED)));
	brick->setImageAreaSize(40, 44);
	brick->SetPosition(11, 12);
	brick->Show();
	addTileObject(id, brick);
	id++;

	Character * character = new Character(this);
	int tile_top_left_pos_x = getTileTopLeftScreenPositionX(0);
	int tile_top_left_pos_y = getTileTopLeftScreenPositionY(0);
	character->SetPosition(character->GetPosXFromCollisionAreaPosX(tile_top_left_pos_x), character->GetPosYFromCollisionAreaPosY(tile_top_left_pos_y));
	character->setID(static_cast<int>(ObjectID::CHARACTER));
	character->setImageAreaSize(64, 64);
	character->setCollisionAreaSize(40, 40);
	character->setNumOfStates(11);
	character->addStateAndAnimation(static_cast<int>(CharacterState::DOWN_IDLE), resource->getAnimation(static_cast<int>(AnimationID::CHARACTER_BACKWARD_IDLE)));
	character->addStateAndAnimation(static_cast<int>(CharacterState::UP_IDLE), resource->getAnimation(static_cast<int>(AnimationID::CHARACTER_FORWARD_IDLE)));
	character->addStateAndAnimation(static_cast<int>(CharacterState::LEFT_IDLE), resource->getAnimation(static_cast<int>(AnimationID::CHARACTER_LEFT_IDLE)));
	character->addStateAndAnimation(static_cast<int>(CharacterState::RIGHT_IDLE), resource->getAnimation(static_cast<int>(AnimationID::CHARACTER_RIGHT_IDLE)));
	character->addStateAndAnimation(static_cast<int>(CharacterState::DOWN_WALK), resource->getAnimation(static_cast<int>(AnimationID::CHARACTER_BACKWARD)));
	character->addStateAndAnimation(static_cast<int>(CharacterState::UP_WALK), resource->getAnimation(static_cast<int>(AnimationID::CHARACTER_FORWARD)));
	character->addStateAndAnimation(static_cast<int>(CharacterState::LEFT_WALK), resource->getAnimation(static_cast<int>(AnimationID::CHARACTER_LEFT)));
	character->addStateAndAnimation(static_cast<int>(CharacterState::RIGHT_WALK), resource->getAnimation(static_cast<int>(AnimationID::CHARACTER_RIGHT)));
	character->addStateAndAnimation(static_cast<int>(CharacterState::DYING),resource->getAnimation(static_cast<int>(AnimationID::CHARACTER_DYING)));
	character->addStateAndAnimation(static_cast<int>(CharacterState::RECOVER), resource->getAnimation(static_cast<int>(AnimationID::CHARACTER_RECOVER)));
	character->addStateAndAnimation(static_cast<int>(CharacterState::DIE), resource->getAnimation(static_cast<int>(AnimationID::CHARACTER_DIE)));	
	for (int i = 0; i < 3; i++) {
		Bomb * bomb = new Bomb(this);
		bomb->setID(static_cast<int>(ObjectID::BOMB));
		bomb->setImageAreaSize(40, 40);
		bomb->setNumOfStates(3);
		bomb->addStateAndAnimation(static_cast<int>(BombState::APPEAR), resource->getAnimation(static_cast<int>(AnimationID::BOMB)));
		bomb->addStateAndAnimation(static_cast<int>(BombState::EXPLODE), resource->getAnimation(static_cast<int>(AnimationID::BOMB_EXPLOSION)));
		bomb->addStateAndAnimation(static_cast<int>(BombState::DISAPPEAR), NULL);
		character->addBomb(bomb);
		addTileObject(id, bomb);
		id++;
	}
	addActiveObject(id, character);
	id++;

	for (int i = 0; i < 3; i++) {
		Enemy * enemy = new Enemy(this);
		enemy->setID(static_cast<int>(ObjectID::ENEMY));
		enemy->setImageAreaSize(67, 67);
		enemy->setCollisionAreaSize(40, 40);
		enemy->setNumOfStates(11);
		enemy->addStateAndAnimation(static_cast<int>(EnemyState::DOWN_IDLE), resource->getAnimation(static_cast<int>(AnimationID::ENEMY_BACKWARD_IDLE)));
		enemy->addStateAndAnimation(static_cast<int>(EnemyState::UP_IDLE), resource->getAnimation(static_cast<int>(AnimationID::ENEMY_FORWARD_IDLE)));
		enemy->addStateAndAnimation(static_cast<int>(EnemyState::LEFT_IDLE), resource->getAnimation(static_cast<int>(AnimationID::ENEMY_LEFT_IDLE)));
		enemy->addStateAndAnimation(static_cast<int>(EnemyState::RIGHT_IDLE), resource->getAnimation(static_cast<int>(AnimationID::ENEMY_RIGHT_IDLE)));
		enemy->addStateAndAnimation(static_cast<int>(EnemyState::DOWN_WALK), resource->getAnimation(static_cast<int>(AnimationID::ENEMY_BACKWARD)));
		enemy->addStateAndAnimation(static_cast<int>(EnemyState::UP_WALK), resource->getAnimation(static_cast<int>(AnimationID::ENEMY_FORWARD)));
		enemy->addStateAndAnimation(static_cast<int>(EnemyState::LEFT_WALK), resource->getAnimation(static_cast<int>(AnimationID::ENEMY_LEFT)));
		enemy->addStateAndAnimation(static_cast<int>(EnemyState::RIGHT_WALK), resource->getAnimation(static_cast<int>(AnimationID::ENEMY_RIGHT)));
		enemy->addStateAndAnimation(static_cast<int>(EnemyState::DYING), resource->getAnimation(static_cast<int>(AnimationID::ENEMY_DYING)));
		enemy->addStateAndAnimation(static_cast<int>(EnemyState::RECOVER), resource->getAnimation(static_cast<int>(AnimationID::ENEMY_RECOVER)));
		enemy->addStateAndAnimation(static_cast<int>(EnemyState::DIE), resource->getAnimation(static_cast<int>(AnimationID::ENEMY_DIE)));
		addActiveObject(id, enemy);
		id++;
	}
	tile_top_left_pos_x = getTileTopLeftScreenPositionX(13);
	tile_top_left_pos_y = getTileTopLeftScreenPositionY(0);
	getActiveObjectByIndex(1)->SetPosition(getActiveObjectByIndex(1)->GetPosXFromCollisionAreaPosX(tile_top_left_pos_x), getActiveObjectByIndex(1)->GetPosYFromCollisionAreaPosY(tile_top_left_pos_y));
	tile_top_left_pos_x = getTileTopLeftScreenPositionX(0);
	tile_top_left_pos_y = getTileTopLeftScreenPositionY(11);
	getActiveObjectByIndex(2)->SetPosition(getActiveObjectByIndex(2)->GetPosXFromCollisionAreaPosX(tile_top_left_pos_x), getActiveObjectByIndex(2)->GetPosYFromCollisionAreaPosY(tile_top_left_pos_y));
	tile_top_left_pos_x = getTileTopLeftScreenPositionX(14);
	tile_top_left_pos_y = getTileTopLeftScreenPositionY(12);
	getActiveObjectByIndex(3)->SetPosition(getActiveObjectByIndex(3)->GetPosXFromCollisionAreaPosX(tile_top_left_pos_x), getActiveObjectByIndex(3)->GetPosYFromCollisionAreaPosY(tile_top_left_pos_y));

	sortZOrderOfTileMapObjects();
	setRedraw(true);
	setRedrawAll(true);
}

void MainScene::Reset()
{
}

void MainScene::Update()
{
	for (int i = 0; i < getSizeOfTileMapObjects(); i++) {
		getTileMapObejctByIndex(i)->UpdateObject();
	}

	Character * character = dynamic_cast<Character *>(getActiveObjectByIndex(0));
	for (int i = 1; i < getSizeOfActiveObjects(); i++) {
		Enemy * enemy = dynamic_cast<Enemy *>(getActiveObjectByIndex(i));
		if (SDL_HasIntersection(&(character->getCollisionArea()), &(enemy->getCollisionArea()))) {
			if (character->getState() == static_cast<int>(CharacterState::DYING) 
				&& enemy->getState() != static_cast<int>(EnemyState::DYING) 
				&& enemy->getState() != static_cast<int>(EnemyState::RECOVER)
				&& enemy->getState() != static_cast<int>(EnemyState::DIE)) {
				character->die();
			}
			else {
				if (enemy->getState() == static_cast<int>(EnemyState::DYING)
					&& character->getState() != static_cast<int>(CharacterState::DYING)
					&& character->getState() != static_cast<int>(CharacterState::RECOVER)
					&& character->getState() != static_cast<int>(CharacterState::DIE)) {
					enemy->die();
				}
			}
		}
	}

	for (int i = 1; i < getSizeOfActiveObjects(); i++) {
		Enemy * enemy1 = dynamic_cast<Enemy *>(getActiveObjectByIndex(i));
		for (int j = i + 1; j < getSizeOfActiveObjects(); j++) {
			Enemy * enemy2 = dynamic_cast<Enemy *>(getActiveObjectByIndex(j));
			if (SDL_HasIntersection(&(enemy1->getCollisionArea()), &(enemy2->getCollisionArea()))) {
				if (enemy1->getState() == static_cast<int>(EnemyState::DYING)
					&& enemy2->getState() != static_cast<int>(EnemyState::DYING)
					&& enemy2->getState() != static_cast<int>(EnemyState::RECOVER)
					&& enemy2->getState() != static_cast<int>(EnemyState::DIE)) {
					enemy1->recover();
				}
				else {
					if (enemy2->getState() == static_cast<int>(EnemyState::DYING)
						&& enemy1->getState() != static_cast<int>(EnemyState::DYING)
						&& enemy1->getState() != static_cast<int>(EnemyState::RECOVER)
						&& enemy1->getState() != static_cast<int>(EnemyState::DIE)) {
						enemy2->recover();
					}
				}
			}
		}
	}

	if (game_timer_.getTotalTicks() >= MAX_TIME) {
		SceneManager * scenes = getBaseEngine()->getSceneManager();
		scenes->setCurrentScene(static_cast<int>(SceneID::LOSE_PAGE));
		stopGame();
	}
	else {
		if (character->isDead()) {
			SceneManager * scenes = getBaseEngine()->getSceneManager();
			scenes->setCurrentScene(static_cast<int>(SceneID::LOSE_PAGE));
		}
		else {
			bool win = true;
			for (int i = 1; i < getSizeOfActiveObjects(); i++) {
				win &= dynamic_cast<Enemy *>(getActiveObjectByIndex(i))->isDead();
			}
			if (win) {
				SceneManager * scenes = getBaseEngine()->getSceneManager();
				scenes->setCurrentScene(static_cast<int>(SceneID::WIN_PAGE));
			}
		}
	}

	sortZOrderOfTileMapObjects();
	setRedraw(true);
}

void MainScene::Draw()
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

void MainScene::DrawAll()
{
	// draw background layer
	drawBackground();

	// draw visual layer
	drawTileMap();

	// draw tile objects and active objects
	for (int i = 0; i < getSizeOfTileMapObjects(); i++) {
		getTileMapObejctByIndex(i)->DrawObject();
	}

	// draw time
	drawTime();

	// update window
	WindowManager * window = getBaseEngine()->getWindowManager();
	window->updateWindow();
}

void MainScene::DrawChanges()
{
	for (int i = 0; i < getSizeOfTileMapObjects(); i++) {
		SDL_Rect rect = getTileMapObejctByIndex(i)->getLastUpdateRect();
		drawBackground(rect);
		drawTileMap(rect);
	}

	for (int i = 0; i < getSizeOfTileMapObjects(); i++) {
		getTileMapObejctByIndex(i)->DrawObject();
	}

	// draw time
	drawBackground(time_area_);
	drawTime();

	// update window
	WindowManager * window = getBaseEngine()->getWindowManager();
	window->updateWindow();
}

void MainScene::drawBackground()
{
	WindowManager * window = getBaseEngine()->getWindowManager();
	window->drawImage(background_, { 0,0,window->WINDOW_WIDTH,window->WINDOW_HEIGHT });
}

void MainScene::drawBackground(SDL_Rect rect)
{
	WindowManager * window = getBaseEngine()->getWindowManager();
	window->drawImageClip({ background_.texture,rect }, rect);
}

void MainScene::drawTileMap()
{
	for (int i = 0; i < getTileMapWidth(); i++) {
		for (int j = 0; j < getTileMapHeight(); j++) {
			drawTile(i, j);
		}
	}
}

void MainScene::drawTileMap(SDL_Rect rect)
{
	if (rect.x < getTileMapLeftBorder()) {
		rect.w = rect.x + rect.w - getTileMapLeftBorder();
		rect.x = getTileMapLeftBorder();
	}
	if (rect.y < getTileMapTopBorder()) {
		rect.h = rect.y + rect.h - getTileMapTopBorder();
		rect.y = getTileMapTopBorder();
	}
	if (rect.x + rect.w > getTileMapRightBorder()) {
		rect.w = getTileMapRightBorder() - rect.x;
	}
	if (rect.y + rect.h > getTileMapBottomBorder()) {
		rect.h = getTileMapBottomBorder() - rect.y;
	}
	int tileMapStartPosX = getTileMapPositionX(rect.x);
	int tileMapStartPosY = getTileMapPositionY(rect.y);
	int tileMapEndPosX = getTileMapPositionX(rect.x + rect.w - 1);
	int tileMapEndPosY = getTileMapPositionY(rect.y + rect.h - 1);
	for (int i = tileMapStartPosX; i <= tileMapEndPosX; i++) {
		for (int j = tileMapStartPosY; j <= tileMapEndPosY; j++) {
			drawTile(i, j);
		}
	}
}

void MainScene::drawTile(int tileMapX, int tileMapY)
{
	ResourceManager * resource = getBaseEngine()->getResourceManager();
	WindowManager * window = getBaseEngine()->getWindowManager();
	Image imgClip;
	SDL_Rect target = { getTileTopLeftScreenPositionX(tileMapX),getTileTopLeftScreenPositionY(tileMapY),getTileWidth(),getTileHeight() };
	switch (getTileLayerValue(tileMapX, tileMapY)) {
	case static_cast<int>(TileID::GROUND1):
		imgClip = resource->getImageClip(static_cast<int>(ImageClipID::TOWN_GROUND_1));
		window->drawImageClip(imgClip,target);
		break;
	case static_cast<int>(TileID::GROUND2):
		imgClip = resource->getImageClip(static_cast<int>(ImageClipID::TOWN_GROUND_2));
		window->drawImageClip(imgClip, target);
		break;
	case static_cast<int>(TileID::ROAD1) :
		imgClip = resource->getImageClip(static_cast<int>(ImageClipID::TOWN_ROAD_1));
		window->drawImageClip(imgClip, target);
		break;
	case static_cast<int>(TileID::ROAD2) :
		imgClip = resource->getImageClip(static_cast<int>(ImageClipID::TOWN_ROAD_2));
		window->drawImageClip(imgClip, target);
		break;
	case static_cast<int>(TileID::ROAD3) :
		imgClip = resource->getImageClip(static_cast<int>(ImageClipID::TOWN_ROAD_3));
		window->drawImageClip(imgClip, target);
		break;
	default:
		// empty
		break;
	};
}

void MainScene::drawTime()
{
	Uint32 timeLeft = MAX_TIME - game_timer_.getTotalTicks();
	int total_seconds = timeLeft / 1000;
	int minutes = total_seconds / 60;
	int seconds = total_seconds % 60;
	std::string str = std::to_string(minutes) + " " + std::to_string(seconds);
	WindowManager * window = getBaseEngine()->getWindowManager();
	ResourceManager * resource = getBaseEngine()->getResourceManager();
	window->setDrawColor({ 255,166,0,0 });
	window->drawSolidString(str.c_str(), (resource->getFont(static_cast<int>(FontID::CORNERSTONE_REGULAR_14))).font, time_area_);
}
