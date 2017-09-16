#pragma once
#include "Resources.h"
#include <map>
#include <memory>

class ResourcesLoader
{
private:
	struct Settings_Texture
	{
		const wchar_t* path;
		Vector2D hitbox;
	};

public:
	~ResourcesLoader();

	void initialize();

	Texture loadTexture(const wchar_t* imagePath, int w_raw, int h_raw, int w_to = 0, int h_to = 0);
	Texture loadTexture(Settings_Texture setting, Vector2D expect_hitbox = Vector2D())
	{ // TODO: use forwarding for this overload
		return loadTexture(setting.path, setting.hitbox.x, setting.hitbox.y, expect_hitbox.x, expect_hitbox.y);
	}

	const std::map<int, Texture>& loadAllTextures();

private:
	void loadTextureSettings();
	void loadGeneralSettings();
	void loadPlaneSettings();

public:
	// settings loaded
	struct
	{
		std::unique_ptr<Settings::General> pGeneral;
		std::unique_ptr<Settings::Plane> pPlayer;
		std::unique_ptr<Settings::Plane> pEnemyJunior;
		std::unique_ptr<Settings::Plane> pEnemyAutoTarget;
		std::map<int, Settings_Texture> mTextures;
	} settings;

	// textures loaded
	std::map<int, Texture> textures;
};