#pragma once
#include "Resources.h"
#include <graphics.h>
#include "ResourcesLoader.h"

// restrict loader to this file only
static ResourcesLoader loader;

void Settings::initialize()
{
	loader.initialize();
}

Settings::General Settings::general()
{
	return *loader.settings.pGeneral;
}

Settings::Plane Settings::player()
{
	return *loader.settings.pPlayer;
}

Settings::Plane Settings::enemy_junior()
{
	return *loader.settings.pEnemyJunior;
}

Settings::Plane Settings::enemy_autoTarget()
{
	return *loader.settings.pEnemyAutoTarget;
}

Texture getTexture(int id)
{
	if (loader.textures.count(id) == 0)
	{ // throw exception if id does not exist
		loader.loadTexture(loader.settings.mTextures.at(id));
	}
	return loader.textures[id];
}

Texture splitTexture(int id, int x, int y, int w, int h)
{
	Texture tmp;
	tmp.image = newimage(w, h);
	putimage(tmp.image, 0, 0, w, h, getTexture(id).image, x, y);
	tmp.hitBox.set(w, h);
	return tmp;
}
