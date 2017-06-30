#include "WindowManager.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "ResourceManager.h"
#include <iostream>

const char * WindowManager::WINDOW_TITLE = "My Game";
const int WindowManager::WINDOW_WIDTH = 800;
const int WindowManager::WINDOW_HEIGHT = 600;

WindowManager::WindowManager()
	:isWindowManagerInitialized_(true),
	sdl_window_(NULL),
	sdl_renderer_(NULL)
{
	sdl_window_ = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, NULL);
	sdl_renderer_ = SDL_CreateRenderer(sdl_window_, -1, SDL_RENDERER_ACCELERATED);
}

WindowManager::~WindowManager()
{
	SDL_DestroyRenderer(sdl_renderer_);
	SDL_DestroyWindow(sdl_window_);
}

void WindowManager::setWindowViewport(SDL_Rect target)
{
	SDL_RenderSetViewport(sdl_renderer_,&target);
}

void WindowManager::resetWindowViewport()
{
	SDL_RenderSetViewport(sdl_renderer_, NULL);
}

void WindowManager::setDrawColor(SDL_Color color) {
	SDL_SetRenderDrawColor(sdl_renderer_, color.r, color.g, color.b, color.a);
}

SDL_Color WindowManager::getDrawColor()
{
	SDL_Color color;
	SDL_GetRenderDrawColor(sdl_renderer_,&color.r,&color.g,&color.b,&color.a);
	return color;
}

void WindowManager::drawLine(SDL_Point p1, SDL_Point p2)
{
	SDL_RenderDrawLine(sdl_renderer_,p1.x,p1.y,p2.x,p2.y);
}

void WindowManager::drawPoint(SDL_Point point)
{
	SDL_RenderDrawPoint(sdl_renderer_, point.x, point.y);
}

void WindowManager::drawRect(SDL_Rect rect)
{
	SDL_RenderDrawRect(sdl_renderer_,&rect);
}

void WindowManager::drawFilledRect(SDL_Rect rect)
{
	SDL_RenderFillRect(sdl_renderer_, &rect);
}

void WindowManager::drawSolidString(const char * cstr, TTF_Font * font, SDL_Rect target)
{
	SDL_Color color = getDrawColor();
	SDL_Surface * surface = TTF_RenderText_Solid(font, cstr, color);
	SDL_Texture * texture = SDL_CreateTextureFromSurface(sdl_renderer_, surface);
	Image img = { texture,{0,0,surface->w,surface->h } };
	drawImage(img,target);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

void WindowManager::drawImage(const Image & img, SDL_Rect target) 
{
	SDL_RenderCopy(sdl_renderer_, img.texture, NULL, &target);
}

void WindowManager::drawImageClip(const Image & img, SDL_Rect target)
{
	SDL_RenderCopy(sdl_renderer_, img.texture, &img.clip, &target);
}

void WindowManager::clearWindow(SDL_Rect target)
{
	drawFilledRect(target);
}

void WindowManager::clearWindow()
{
	SDL_RenderClear(sdl_renderer_);
}

void WindowManager::updateWindow()
{
	SDL_RenderPresent(sdl_renderer_);
}