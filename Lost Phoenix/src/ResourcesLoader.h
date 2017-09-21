#pragma once
#include "Resources.h"
#include <map>
#include <memory>

namespace Settings
{
	struct TextureInfo
	{
		std::wstring path;
		Vector2D hitbox;
		Vector2D expectHitBox = Vector2D();
	};
}

class ResourcesLoader
{
public:
	// Used to load texture at the beginning of program
	ResourcesLoader();
	~ResourcesLoader();

	Texture loadTexture(const wchar_t* imagePath, int w_raw, int h_raw, int w_to = 0, int h_to = 0);
	Texture loadTexture(Settings::TextureInfo setting)
	{ // TODO: use forwarding for this overload
		return loadTexture(setting.path.c_str(), setting.hitbox.x, setting.hitbox.y, setting.expectHitBox.x, setting.expectHitBox.y);
	}

	void loadTextureSettings();
	void loadGeneralSettings();
	void loadBgTextures();
	void loadAnimeTextures();
	void loadPlaneSettings();
	const std::map<int, Texture>& loadAllTextures();

	// settings loaded
	struct
	{
		std::unique_ptr<Settings::General> pGeneral;
		std::unique_ptr<Settings::BgTextures> pBgTextures;
		std::unique_ptr<Settings::AnimeTextures> pAnimeTextures;
		std::unique_ptr<Settings::Plane> pPlayer;
		std::unique_ptr<Settings::Plane> pEnemyJunior;
		std::unique_ptr<Settings::Plane> pEnemyAutoTarget;
		std::map<int, Settings::TextureInfo> mTextureInfos;
	} settings;

	// textures loaded
	std::map<int, Texture> textures;
};