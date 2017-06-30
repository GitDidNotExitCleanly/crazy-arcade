#pragma once

enum class FontID {
	CORNERSTONE_REGULAR_14 = 0,
	FONT_UNSPECIFIED = 1
};

enum class ImageID {
	START_PAGE = 0,
	WIN_PAGE = 1,
	LOSE_PAGE = 2,
	BACKGROUND = 3,
	GEM = 4,
	SHOE = 5,
	WATER = 6,
	BRICK_RED = 7,
	BRICK_YELLOW = 8,
	BRICK_BOX = 9,
	HOUSE_BLUE = 10,
	HOUSE_RED = 11,
	HOUSE_TREE = 12,
	IMG_UNSPECIFIED = 13
};

enum class SpriteSheetID {
	TOWN_GROUND = 0,
	SPRITE_SHEET_UNSPECIFIED = 1
};

enum class ImageClipID {
	TOWN_GROUND_1 = 0,
	TOWN_GROUND_2 = 1,
	TOWN_ROAD_1 = 2,
	TOWN_ROAD_2 = 3,
	TOWN_ROAD_3 = 4,
	IMG_CLIP_UNSPECIFIED = 5
};

enum class AnimationSpriteSheetID {
	CHARACTER = 0,
	CHARACTER_LIFE = 1,
	ENEMY = 2,
	ENEMY_LIFE = 3,
	BOMB = 4,
	BOMB_EXPLOSION = 5,
	ANIMATION_SPRITE_SHEET_UNSPECIFIED = 6
};

enum class AnimationID {
	CHARACTER_BACKWARD_IDLE = 0,
	CHARACTER_FORWARD_IDLE = 1,
	CHARACTER_LEFT_IDLE = 2,
	CHARACTER_RIGHT_IDLE = 3,
	CHARACTER_BACKWARD = 4,
	CHARACTER_FORWARD = 5,
	CHARACTER_LEFT = 6,
	CHARACTER_RIGHT = 7,
	CHARACTER_DYING = 8,
	CHARACTER_RECOVER = 9,
	CHARACTER_DIE = 10,
	ENEMY_BACKWARD_IDLE = 11,
	ENEMY_FORWARD_IDLE = 12,
	ENEMY_LEFT_IDLE = 13,
	ENEMY_RIGHT_IDLE = 14,
	ENEMY_BACKWARD = 15,
	ENEMY_FORWARD = 16,
	ENEMY_LEFT = 17,
	ENEMY_RIGHT = 18,
	ENEMY_DYING = 19,
	ENEMY_RECOVER = 20,
	ENEMY_DIE = 21,
	BOMB = 22,
	BOMB_EXPLOSION = 23,
	ANIMATION_UNSPECIFIED = 24
};