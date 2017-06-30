#include "Object.h"
#include "../BaseEngine.h"

Object::Object(Scene * scene)
	:environment_(scene),
	last_update_rect_({ 0,0,0,0 }),
	isVisible_(true),
	ID_(0),
	z_order_(0),
	anchor_pos_x_(0),
	anchor_pos_y_(0),
	img_area_({ 0,0,0,0 }),
	static_skin_({ NULL,{0,0,0,0} }),
	current_state_(0),
	num_of_states_(0),
	animation_for_each_state_(NULL),
	isAnimationRunning_(false),
	animation_current_frame_(0)
{
}

Object::~Object()
{
	delete[] animation_for_each_state_;
}

Scene * Object::getEnvironment()
{
	return environment_;
}

void Object::saveLastUpdateRect()
{
	last_update_rect_ = img_area_;
}

void Object::setState(int state)
{
	current_state_ = state;
}

int Object::getState()
{
	return current_state_;
}

bool Object::isAnimationRunning()
{
	return isAnimationRunning_;
}

void Object::startAnimation()
{
	isAnimationRunning_ = true;
	animation_current_frame_ = 0;
	animation_timer_.start();
}

void Object::stopAnimation()
{
	isAnimationRunning_ = false;
	animation_timer_.stop();
}

void Object::drawAnimationFrame()
{
	Animation * currentAnimation = animation_for_each_state_[current_state_];
	if (currentAnimation != NULL) {
		if (isVisible_) {
			// draw current frame
			Image sprite_sheet = currentAnimation->sprite_sheet;
			SDL_Rect sprite_sheet_clip = (currentAnimation->sprite_sheet_clips)[animation_current_frame_];
			WindowManager * window = getEnvironment()->getBaseEngine()->getWindowManager();
			window->drawImageClip({ sprite_sheet.texture,sprite_sheet_clip }, getImageArea());
			saveLastUpdateRect();
		}

		// play next frame
		bool isLoop = currentAnimation->isLoop;
		Uint32 frequency = currentAnimation->frequency;
		int frames = currentAnimation->frames;
		if (isAnimationRunning_) {
			if (isLoop) {
				if (animation_timer_.getDeltaTicks() >= frequency) {
					animation_timer_.pause();
					animation_current_frame_++;
					animation_current_frame_ %= frames;
					animation_timer_.unpause();
				}
			}
			else {
				if (animation_current_frame_ < frames - 1) {
					if (animation_timer_.getDeltaTicks() >= frequency) {
						animation_timer_.pause();
						animation_current_frame_++;
						animation_timer_.unpause();
					}
				}
				else {
					stopAnimation();
				}
			}
		}
	}
}

void Object::setAnchorPosAndImageAreaPos(int x, int y)
{
	anchor_pos_x_ = x;
	anchor_pos_y_ = y;
	img_area_.x = GetImageAreaPosXFromPosX(x);
	img_area_.y = GetImageAreaPosYFromPosY(y);
}

int Object::getAnchorPosX()
{
	return anchor_pos_x_;
}

int Object::getAnchorPosY()
{
	return anchor_pos_y_;
}

void Object::drawStaticSkin()
{
	if (isVisible_) {
		WindowManager * window = getEnvironment()->getBaseEngine()->getWindowManager();
		window->drawImageClip(static_skin_, getImageArea());
		saveLastUpdateRect();
	}
}

void Object::setID(int id)
{
	ID_ = id;
}

void Object::setZOrder(int z_order)
{
	z_order_ = z_order;
}

void Object::setVisibility(bool isVisible)
{
	isVisible_ = isVisible;
}

void Object::setImageAreaSize(int width, int height)
{
	img_area_.w = width;
	img_area_.h = height;
	img_area_.x = GetImageAreaPosXFromPosX(anchor_pos_x_);
	img_area_.y = GetImageAreaPosYFromPosY(anchor_pos_y_);
}

void Object::setSkin(const Image & img)
{
	static_skin_ = img;
}

void Object::setNumOfStates(int num)
{
	num_of_states_ = num;
	animation_for_each_state_ = new Animation *[num];
}

void Object::addStateAndAnimation(int state, Animation * animation)
{
	animation_for_each_state_[state] = animation;
}

SDL_Rect Object::getLastUpdateRect()
{
	return last_update_rect_;
}

int Object::getID()
{
	return ID_;
}

int Object::getZOrder()
{
	return z_order_;
}

bool Object::isVisible()
{
	return isVisible_;
}

SDL_Rect Object::getImageArea()
{
	return img_area_;
}


bool lessZOrder(Object * obj1, Object * obj2)
{
	return obj1->getZOrder() < obj2->getZOrder();
}