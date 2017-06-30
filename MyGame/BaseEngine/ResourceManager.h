#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include <vector>
#include <string>
#include <unordered_map>

struct Font
{
	TTF_Font * font;
};

struct Image 
{
	SDL_Texture * texture;
	SDL_Rect clip;
};

struct Animation
{
	bool isLoop;
	Uint32 frequency;
	int frames;
	Image sprite_sheet;
	std::vector<SDL_Rect> sprite_sheet_clips;
};

class ResourceManager
{
private:
	SDL_Renderer * sdl_renderer_;

	// fonts
	static const std::string RESOURCE_FONT_DIR;
	std::vector<Font> font_table_;
	void unloadFonts();
	
	// single images
	static const std::string RESOURCE_IMAGE_DIR;
	std::vector<Image> image_table_;
	void unloadImages();

	// sprite sheets
	static const std::string RESOURCE_SPRITE_SHEET_DIR;
	std::vector<Image> sprite_sheet_table_;
	std::vector<Image> image_clip_table_;
	void unloadSpriteSheets();

	// animations
	static const std::string RESOURCE_ANIMATION_SPRITE_SHEET_DIR;
	std::vector<Image> animation_sprite_sheet_table_;
	std::vector<Animation> animation_table_;
	void unloadAnimationSpriteSheets();

	bool isResourceManagerInitialized_;

	// only allow BaseEngine class to create instance
	ResourceManager(SDL_Renderer *);
	friend class BaseEngine;

public:
	~ResourceManager();
	ResourceManager(const ResourceManager &) = delete;
	ResourceManager & operator=(const ResourceManager &) = delete;
	
	void setMaxFonts(int);
	void loadFont(int, std::string, int);
	
	void setMaxImages(int);
	void loadImage(int, std::string);
	
	void setMaxSpriteSheet(int);
	void loadSpriteSheet(int, std::string);
	void setMaxImageClips(int);
	void loadImageClip(int,int,int,int,int,int);
	
	void setMaxAnimationSpriteSheet(int);
	void loadAnimationSpriteSheet(int, std::string);
	void setMaxAnimations(int);
	void loadAnimation(int, int, bool, Uint32, int, int, int, int, int);
	
	Font getFont(int);
	Image getImage(int);
	Image getImageClip(int);
	Animation * getAnimation(int);
};