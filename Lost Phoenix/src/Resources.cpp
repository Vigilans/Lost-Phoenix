#pragma once
#include "Resources.h"
#include <graphics.h>
#include "ResourcesLoader.h"

/// <summary>
/// restrict loader to source file only.
/// </summary>
static ResourcesLoader loader;

// TODO : Create a lazy load class
// Lazy Load
const Settings::General& Settings::general()
{
	if (loader.settings.pGeneral == nullptr)
		loader.loadGeneralSettings();
	return *loader.settings.pGeneral;
}

const Settings::BgTextures& Settings::bgTextures()
{
	if (loader.settings.pBgTextures == nullptr)
		loader.loadBgTextures();
	return *loader.settings.pBgTextures;
}

const Settings::AnimeTextures& Settings::animeTextures()
{
	if (loader.settings.pAnimeTextures == nullptr)
		loader.loadAnimeTextures();
	return *loader.settings.pAnimeTextures;
}

const Settings::Plane& Settings::player()
{
	if (loader.settings.pPlayer == nullptr)
		loader.loadPlaneSettings();
	return *loader.settings.pPlayer;
}

const Settings::Plane& Settings::enemy_junior()
{
	if (loader.settings.pEnemyJunior == nullptr)
		loader.loadPlaneSettings();
	return *loader.settings.pEnemyJunior;
}

const Settings::Plane& Settings::enemy_autoTarget()
{
	if (loader.settings.pEnemyAutoTarget == nullptr)
		loader.loadPlaneSettings();
	return *loader.settings.pEnemyAutoTarget;
}

Texture getTexture(int id)
{
	if (loader.textures.count(id) == 0)
	{ // throw exception if id does not exist
		loader.textures[id] = loader.loadTexture(loader.settings.mTextureInfos.at(id));
	}
	return loader.textures[id];
}

Texture splitTexture(Texture texture, int x, int y, int w, int h)
{
	Texture tmp;
	tmp.image = newimage(w, h);
	putimage(tmp.image, 0, 0, w, h, texture.image, x, y);
	tmp.hitBox.set(w, h);
	return tmp;
}

Texture::Texture(int id)
{
	*this = getTexture(id);
}
