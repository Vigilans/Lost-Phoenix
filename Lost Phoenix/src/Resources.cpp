#pragma once
#include <map>
#include <graphics.h>
#include "Resources.h"
 
inline Texture load_texture(wchar_t* imagePath, int w_raw, int h_raw, int w_to = 0, int h_to = 0)
{
	w_to = w_to ? w_to : w_raw;
	h_to = h_to ? h_to : h_raw;

	PIMAGE raw = newimage( );
	PIMAGE expect = newimage(w_to, h_to);
	getimage(raw, imagePath);
	putimage(expect, 0, 0, w_to, h_to, raw, 0, 0, w_raw, h_raw);
	delimage(raw);

	Texture tmp;
	tmp.image = expect;
	tmp.hitBox = Vector2D(w_to, h_to);
	return tmp;
}

// 专门负责材质加载的类
class TextureLoader
{
public:
	~TextureLoader( )
	{
		for (auto& elem : textureMap)
			delimage(elem.second.image);
	}

	void initialize( )
	{
		textureMap[MENU_ID] = load_texture(MENU_PATH, MENU_WIDTH_RAW, MENU_HEIGHT_RAW, WINDOW_WIDTH, WINDOW_HEIGHT);
		textureMap[BACKGROUND_ID] = load_texture(BACKGROUND_PATH, BACKGROUND_WIDTH_RAW, BACKGROUND_HEIGHT_RAW, WINDOW_WIDTH, WINDOW_HEIGHT);
		textureMap[PLAYER_PLANE_ID] = load_texture(PLAYER_PLANE_PATH, PLAYER_PLANE_WIDTH_RAW, PLAYER_PLANE_HEIGHT_RAW);
		textureMap[PLAYER_BULLET_ID] = load_texture(PLAYER_BULLET_PATH, PLAYER_BULLET_WIDTH_RAW, PLAYER_BULLET_HEIGHT_RAW);
		textureMap[ENEMY_PLANE_JUNIOR_ID] = load_texture(ENEMY_PLANE_JUNIOR_PATH, ENEMY_PLANE_JUNIOR_WIDTH_RAW, ENEMY_PLANE_JUNIOR_HEIGHT_RAW);
		textureMap[ENEMY_BULLET_JUNIOR_ID] = load_texture(ENEMY_BULLET_JUNIOR_PATH, ENEMY_BULLET_JUNIOR_WIDTH_RAW, ENEMY_BULLET_JUNIOR_HEIGHT_RAW);
		textureMap[ENEMY_PLANE_AUTOTARGET_ID] = load_texture(ENEMY_PLANE_AUTOTARGET_PATH, ENEMY_PLANE_AUTOTARGET_WIDTH_RAW, ENEMY_PLANE_AUTOTARGET_HEIGHT_RAW);
		textureMap[ENEMY_BULLET_AUTOTARGET_ID] = load_texture(ENEMY_BULLET_AUTOTARGET_PATH, ENEMY_BULLET_AUTOTARGET_WIDTH_RAW, ENEMY_BULLET_AUTOTARGET_HEIGHT_RAW);
		textureMap[PLANE_EXPLOSION_ID] = load_texture(PLANE_EXPLOSION_PATH, PLANE_EXPLOSION_WIDTH_RAW, PLANE_EXPLOSION_HEIGHT_RAW);
		textureMap[GAMEOVER_ID] = load_texture(GAMEOVER_PATH, GAMEOVER_WIDTH_RAW, GAMEOVER_HEIGHT_RAW, WINDOW_WIDTH, WINDOW_HEIGHT);
	}

	std::map<int, Texture> textureMap;
} Loader;

const Texture getTexture(int id)
{
	if (Loader.textureMap.empty( ))
		Loader.initialize( );
	return Loader.textureMap[id];
}

Texture cutOutTexture(int id, int x, int y, int w, int h)
{
	Texture tmp;
	tmp.image = newimage(w, h);
	putimage(tmp.image, 0, 0, w, h, getTexture(id).image, x, y);
	tmp.hitBox.set(w, h);
	return tmp;
}
