#include "ResourceManager.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include <iostream>

const std::string ResourceManager::RESOURCE_FONT_DIR = "Resource/Font/";
const std::string ResourceManager::RESOURCE_IMAGE_DIR = "Resource/Image/";
const std::string ResourceManager::RESOURCE_SPRITE_SHEET_DIR = "Resource/SpriteSheet/";
const std::string ResourceManager::RESOURCE_ANIMATION_SPRITE_SHEET_DIR = "Resource/Animation/";

ResourceManager::ResourceManager(SDL_Renderer * sdl_renderer)
	:sdl_renderer_(sdl_renderer),
	isResourceManagerInitialized_(true)
{
}

ResourceManager::~ResourceManager()
{
	unloadFonts();
	unloadImages();
	unloadSpriteSheets();
	unloadAnimationSpriteSheets();
}

void ResourceManager::setMaxFonts(int num)
{
	font_table_.resize(num);
}

void ResourceManager::loadFont(int fontID, std::string fontName, int fontSize)
{
	std::string file_path = RESOURCE_FONT_DIR + fontName +".ttf";
	TTF_Font * font = TTF_OpenFont(file_path.c_str(),fontSize);
	font_table_[fontID] = { font };

	if (font == NULL) {
		isResourceManagerInitialized_ = false;
	}
}

void ResourceManager::unloadFonts()
{
	for (unsigned int i = 0; i < font_table_.size(); i++) {
		TTF_CloseFont(font_table_[i].font);
	}
}

Font ResourceManager::getFont(int fontID) 
{
	return font_table_[fontID];
}

void ResourceManager::setMaxImages(int num)
{
	image_table_.resize(num);
}

void ResourceManager::loadImage(int imageID, std::string imageFileName)
{
	std::string file_path = RESOURCE_IMAGE_DIR + imageFileName;
	SDL_Surface * surface = IMG_Load(file_path.c_str());
	SDL_Texture * texture = SDL_CreateTextureFromSurface(sdl_renderer_, surface);
	image_table_[imageID] = { texture,{ 0,0,surface->w,surface->h } };
	SDL_FreeSurface(surface);

	if (texture == NULL) {
		isResourceManagerInitialized_ = false;
	}
}

void ResourceManager::unloadImages()
{
	for (unsigned int i = 0; i < image_table_.size(); i++) {
		SDL_DestroyTexture(image_table_[i].texture);
	}
}

Image ResourceManager::getImage(int imageID)
{
	return image_table_[imageID];
}

void ResourceManager::setMaxSpriteSheet(int num)
{
	sprite_sheet_table_.resize(num);
}

void ResourceManager::loadSpriteSheet(int spriteSheetID, std::string imageFileName)
{
	std::string file_path = RESOURCE_SPRITE_SHEET_DIR + imageFileName;
	SDL_Surface * surface = IMG_Load(file_path.c_str());
	SDL_Texture * texture = SDL_CreateTextureFromSurface(sdl_renderer_, surface);
	sprite_sheet_table_[spriteSheetID] = { texture,{ 0,0,surface->w,surface->h } };
	SDL_FreeSurface(surface);

	if (texture == NULL) {
		isResourceManagerInitialized_ = false;
	}
}

void ResourceManager::setMaxImageClips(int num)
{
	image_clip_table_.resize(num);
}

void ResourceManager::loadImageClip(int spriteSheetID, int imageClipID, int x, int y, int w, int h)
{
	Image spriteSheet = sprite_sheet_table_[spriteSheetID];
	spriteSheet.clip = { x,y,w,h };
	image_clip_table_[imageClipID] = spriteSheet;
}

void ResourceManager::unloadSpriteSheets()
{
	for (unsigned int i = 0; i < sprite_sheet_table_.size(); i++) {
		SDL_DestroyTexture(sprite_sheet_table_[i].texture);
	}
}

Image ResourceManager::getImageClip(int imageClipID)
{
	return image_clip_table_[imageClipID];
}

void ResourceManager::setMaxAnimationSpriteSheet(int num)
{
	animation_sprite_sheet_table_.resize(num);
}

void ResourceManager::loadAnimationSpriteSheet(int spriteSheetID, std::string imageFileName)
{
	std::string file_path = RESOURCE_ANIMATION_SPRITE_SHEET_DIR + imageFileName;
	SDL_Surface * surface = IMG_Load(file_path.c_str());
	SDL_Texture * texture = SDL_CreateTextureFromSurface(sdl_renderer_, surface);
	animation_sprite_sheet_table_[spriteSheetID] = { texture,{ 0,0,surface->w,surface->h } };
	SDL_FreeSurface(surface);

	if (texture == NULL) {
		isResourceManagerInitialized_ = false;
	}
}

void ResourceManager::setMaxAnimations(int num)
{
	animation_table_.resize(num);
}

void ResourceManager::loadAnimation(int spriteSheetID, int animationID, bool isLoop, Uint32 frequency, int frames, int x, int y, int w, int h)
{
	Image spriteSheet = animation_sprite_sheet_table_[spriteSheetID];
	std::vector<SDL_Rect> spriteSheetClips(frames);
	for (int i = 0; i < frames; i++) {
		spriteSheetClips[i] = { x + i*w,y,w,h };
	}
	animation_table_[animationID] = { isLoop,frequency,frames,spriteSheet,spriteSheetClips };
}

void ResourceManager::unloadAnimationSpriteSheets()
{
	for (unsigned int i = 0; i < animation_sprite_sheet_table_.size(); i++) {
		SDL_DestroyTexture(animation_sprite_sheet_table_[i].texture);
	}
}

Animation * ResourceManager::getAnimation(int animationID)
{
	return &(animation_table_[animationID]);
}