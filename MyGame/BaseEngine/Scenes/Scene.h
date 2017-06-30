#pragma once
#include "SDL.h"
#include "../ResourceManager.h"
#include "../Objects/Object.h"
#include <vector>

class BaseEngine;
class Object;

class Scene
{
private:
	BaseEngine * base_engine_;
	bool needRedraw_;
	bool needRedrawAll_;
	std::vector<Object *> scene_objects_;

protected:
	void setRedraw(bool);
	void setRedrawAll(bool);
	bool getRedraw();
	bool getRedrawAll();
	void setSizeOfSceneObjects(int);
	int getSizeOfSceneObjects();
	void addSceneObjectByID(int,Object *);
	void removeSceneObjectByID(int);
	Object * getSceneObjectByID(int);

	// overridable functions for all scene layers
	virtual void DrawAll();
	virtual void DrawChanges();

public:
	Scene(BaseEngine *);
	virtual ~Scene();
	Scene(const Scene &) = delete;
	Scene & operator=(const Scene &) = delete;

	// used by DisplayableObject
	BaseEngine * getBaseEngine();

	// overridable functions for all scene layers
	virtual void Setup() = 0;
	virtual void Reset() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
};
