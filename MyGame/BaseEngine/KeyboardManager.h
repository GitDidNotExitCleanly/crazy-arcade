#pragma once
#include "SDL.h"

enum class KeyCode 
{
	KEY_UP = 0,
	KEY_DOWN = 1,
	KEY_LEFT = 2,
	KEY_RIGHT = 3,
	KEY_SPACE = 4,
	KEY_UNSPECIFIED = 5
};

enum class KeyState {
	KEY_IDLE = 0,
	KEY_PRESSED = 1,
	KEY_RELEASED = 2
};

class KeyboardManager
{
private:
	KeyCode lastPressedKey;
	KeyCode lastReleasedKey;

	KeyCode findInternalKeyCode(const SDL_Keycode);
	void setKeyStatus(const KeyCode, const KeyState);
	void resetKeyStatus();

	bool isKeyboardManagerInitialized_;

	// only allow BaseEngine class to create instance
	KeyboardManager();
	friend class BaseEngine;

public:
	~KeyboardManager();
	KeyboardManager(const KeyboardManager &) = delete;
	KeyboardManager & operator=(const KeyboardManager &) = delete;
	KeyCode getLastPressedKey();
	KeyCode getLastReleasedKey();
};

