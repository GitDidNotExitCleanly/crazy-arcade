#include "Scene.h"
#include "../BaseEngine.h"
#include <algorithm>

Scene::Scene(BaseEngine * base_engine)
	:base_engine_(base_engine),
	needRedraw_(true),
	needRedrawAll_(true)
{
}

Scene::~Scene()
{
	for (unsigned int i = 0; i < scene_objects_.size(); i++) {
		delete scene_objects_[i];
	}
}

void Scene::setRedraw(bool needRedraw)
{
	needRedraw_ = needRedraw;
}

void Scene::setRedrawAll(bool needRedrawAll)
{
	needRedrawAll_ = needRedrawAll;
}

bool Scene::getRedraw()
{
	return needRedraw_;
}

bool Scene::getRedrawAll()
{
	return needRedrawAll_;
}

void Scene::setSizeOfSceneObjects(int size)
{
	scene_objects_.resize(size);
}

int Scene::getSizeOfSceneObjects()
{
	return static_cast<int>(scene_objects_.size());
}

void Scene::addSceneObjectByID(int id, Object * obj)
{
	scene_objects_[id] = obj;
}

void Scene::removeSceneObjectByID(int id)
{
	delete scene_objects_[id];
	scene_objects_[id] = NULL;
}

Object * Scene::getSceneObjectByID(int id)
{
	return scene_objects_[id];
}

BaseEngine * Scene::getBaseEngine()
{
	return base_engine_;
}

void Scene::DrawAll()
{
}

void Scene::DrawChanges()
{
}