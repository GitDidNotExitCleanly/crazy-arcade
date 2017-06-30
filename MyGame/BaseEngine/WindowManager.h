#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "ResourceManager.h"

class WindowManager
{
private:
	SDL_Window * sdl_window_;
	SDL_Renderer * sdl_renderer_;

	bool isWindowManagerInitialized_;

	// only allow BaseEngine class to create instance
	WindowManager();
	friend class BaseEngine;

public:
	static const char * WINDOW_TITLE;
	static const int WINDOW_WIDTH;
	static const int WINDOW_HEIGHT;

	~WindowManager();
	WindowManager(const WindowManager &) = delete;
	WindowManager & operator=(const WindowManager &) = delete;
	
	// draw related
	void setWindowViewport(SDL_Rect);
	void resetWindowViewport();
	void setDrawColor(SDL_Color);
	SDL_Color getDrawColor();
	void drawLine(SDL_Point, SDL_Point);
	void drawPoint(SDL_Point);
	void drawRect(SDL_Rect);
	void drawFilledRect(SDL_Rect);
	void drawSolidString(const char *, TTF_Font *, SDL_Rect);
	void drawImage(const Image &, SDL_Rect);
	void drawImageClip(const Image &, SDL_Rect);
	void clearWindow(SDL_Rect);
	void clearWindow();
	void updateWindow();
};

