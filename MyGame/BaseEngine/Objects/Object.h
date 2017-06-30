#pragma once
#include "../Scenes/Scene.h"
#include "../Utility.h"
#include "../ResourceManager.h"

class Scene;

class Object
{
private:
	Scene * environment_;
	SDL_Rect last_update_rect_;

	bool isVisible_;
	int ID_;
	int z_order_;
	int anchor_pos_x_;
	int anchor_pos_y_;
	SDL_Rect img_area_;

	// static appearance
	Image static_skin_;
	// dynamic appearance (state machine and animation)
	int current_state_;
	int num_of_states_;
	Animation ** animation_for_each_state_;
	bool isAnimationRunning_;
	int animation_current_frame_;
	Timer animation_timer_;
	
protected:
	Scene * getEnvironment();
	void saveLastUpdateRect();
	void setAnchorPosAndImageAreaPos(int, int);
	int getAnchorPosX();
	int getAnchorPosY();
	void drawStaticSkin();
	void setState(int);
	bool isAnimationRunning();
	void startAnimation();
	void stopAnimation();
	void drawAnimationFrame();

public:
	Object(Scene *);
	virtual ~Object();
	Object(const Object &) = delete;
	Object & operator=(const Object &) = delete;

	void setVisibility(bool);
	void setID(int);
	void setZOrder(int);
	void setImageAreaSize(int, int);
	void setSkin(const Image &);
	void setNumOfStates(int);
	void addStateAndAnimation(int, Animation *);
	SDL_Rect getLastUpdateRect();
	bool isVisible();
	int getID();
	int getZOrder();
	SDL_Rect getImageArea();
	int getState();

	virtual void Show() = 0;
	virtual void Hide() = 0;
	virtual void SetPosition(int, int) = 0;
	virtual int GetPositionX() = 0;
	virtual int GetPositionY() = 0;
	virtual int GetImageAreaPosXFromPosX(int) = 0;
	virtual int GetImageAreaPosYFromPosY(int) = 0;
	virtual int GetPosXFromImageAreaPosX(int) = 0;
	virtual int GetPosYFromImageAreaPosY(int) = 0;
	virtual int GetCollisionAreaPosXFromPosX(int) = 0;
	virtual int GetCollisionAreaPosYFromPosY(int) = 0;
	virtual int GetPosXFromCollisionAreaPosX(int) = 0;
	virtual int GetPosYFromCollisionAreaPosY(int) = 0;

	virtual void UpdateObject() = 0;
	virtual void DrawObject() = 0;
};


bool lessZOrder(Object *, Object *);