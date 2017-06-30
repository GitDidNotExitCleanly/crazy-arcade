#include "KeyboardManager.h"
#include "SDL.h"

KeyboardManager::KeyboardManager()
	:isKeyboardManagerInitialized_(true),
	lastPressedKey(KeyCode::KEY_UNSPECIFIED),
	lastReleasedKey(KeyCode::KEY_UNSPECIFIED)
{
}

KeyboardManager::~KeyboardManager()
{
}

KeyCode KeyboardManager::findInternalKeyCode(const SDL_Keycode keyCode)
{
	KeyCode internalKeyCode = KeyCode::KEY_UNSPECIFIED;
	switch (keyCode)
	{
	case SDLK_UP:
		internalKeyCode = KeyCode::KEY_UP;
		break;
	case SDLK_DOWN:
		internalKeyCode = KeyCode::KEY_DOWN;
		break;
	case SDLK_LEFT:
		internalKeyCode = KeyCode::KEY_LEFT;
		break;
	case SDLK_RIGHT:
		internalKeyCode = KeyCode::KEY_RIGHT;
		break;
	case SDLK_SPACE:
		internalKeyCode = KeyCode::KEY_SPACE;
		break;
	default:
		break;
	}
	return internalKeyCode;
}

void KeyboardManager::setKeyStatus(const KeyCode keyCode,const KeyState keyState) {
	if (keyCode != KeyCode::KEY_UNSPECIFIED) {
		if (keyState == KeyState::KEY_PRESSED) {
			lastPressedKey = keyCode;
		}
		else {
			lastReleasedKey = keyCode;
		}
	}
}

void KeyboardManager::resetKeyStatus()
{
	lastPressedKey = KeyCode::KEY_UNSPECIFIED;
	lastReleasedKey = KeyCode::KEY_UNSPECIFIED;
}

KeyCode KeyboardManager::getLastPressedKey()
{
	return lastPressedKey;
}

KeyCode KeyboardManager::getLastReleasedKey()
{
	return lastReleasedKey;
}