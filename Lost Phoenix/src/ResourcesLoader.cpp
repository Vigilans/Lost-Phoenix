#include "ResourcesLoader.h"
#include <fstream>
#include <json.hpp>
#include <graphics.h>

using namespace std;
using json = nlohmann::json;

void to_json(json& j, const Vector2D& v)
{
	j = json { v.x, v.y };
}

void from_json(const json& j, Vector2D& v)
{
	v = Vector2D(j[0].get<Vector2D::value_type_t>(), j[1].get<Vector2D::value_type_t>());
}

void from_json(const json& j, Settings::Bullet& b)
{
	b = Settings::Bullet
	{
		getTexture(j["TextureID"]),
		j["Attack"],
		j["Speed"],
		j["CoolDown"]
	};
}

void from_json(const json& j, Settings::Plane& s)
{
	s = Settings::Plane
	{
		getTexture(j["TextureID"]),
		j["Health"],
		j["Speed"],
		j["Bullet"],
		j.find("Score") == j.end() ? 0 : j["Score"]
	};
}

ResourcesLoader::~ResourcesLoader()
{
	for (auto& elem : textures)
		delimage(elem.second.image);
}

void ResourcesLoader::initialize()
{
	//loadTextureSettings();
	//loadAllTextures();
	textures[MENU_ID] = loadTexture(MENU_PATH, MENU_WIDTH_RAW, MENU_HEIGHT_RAW, WINDOW_WIDTH, WINDOW_HEIGHT);
	textures[BACKGROUND_ID] = loadTexture(BACKGROUND_PATH, BACKGROUND_WIDTH_RAW, BACKGROUND_HEIGHT_RAW, WINDOW_WIDTH, WINDOW_HEIGHT);
	textures[PLAYER_PLANE_ID] = loadTexture(PLAYER_PLANE_PATH, PLAYER_PLANE_WIDTH_RAW, PLAYER_PLANE_HEIGHT_RAW);
	textures[PLAYER_BULLET_ID] = loadTexture(PLAYER_BULLET_PATH, PLAYER_BULLET_WIDTH_RAW, PLAYER_BULLET_HEIGHT_RAW);
	textures[ENEMY_PLANE_JUNIOR_ID] = loadTexture(ENEMY_PLANE_JUNIOR_PATH, ENEMY_PLANE_JUNIOR_WIDTH_RAW, ENEMY_PLANE_JUNIOR_HEIGHT_RAW);
	textures[ENEMY_BULLET_JUNIOR_ID] = loadTexture(ENEMY_BULLET_JUNIOR_PATH, ENEMY_BULLET_JUNIOR_WIDTH_RAW, ENEMY_BULLET_JUNIOR_HEIGHT_RAW);
	textures[ENEMY_PLANE_AUTOTARGET_ID] = loadTexture(ENEMY_PLANE_AUTOTARGET_PATH, ENEMY_PLANE_AUTOTARGET_WIDTH_RAW, ENEMY_PLANE_AUTOTARGET_HEIGHT_RAW);
	textures[ENEMY_BULLET_AUTOTARGET_ID] = loadTexture(ENEMY_BULLET_AUTOTARGET_PATH, ENEMY_BULLET_AUTOTARGET_WIDTH_RAW, ENEMY_BULLET_AUTOTARGET_HEIGHT_RAW);
	textures[PLANE_EXPLOSION_ID] = loadTexture(PLANE_EXPLOSION_PATH, PLANE_EXPLOSION_WIDTH_RAW, PLANE_EXPLOSION_HEIGHT_RAW);
	textures[GAMEOVER_ID] = loadTexture(GAMEOVER_PATH, GAMEOVER_WIDTH_RAW, GAMEOVER_HEIGHT_RAW, WINDOW_WIDTH, WINDOW_HEIGHT);
	loadGeneralSettings();
	loadPlaneSettings();
}

Texture ResourcesLoader::loadTexture(const wchar_t * imagePath, int w_raw, int h_raw, int w_to, int h_to)
{
	PIMAGE raw = newimage();
	getimage(raw, imagePath);

	if (w_to != 0 && h_to != 0)
	{
		PIMAGE expect = newimage(w_to, h_to);
		putimage(expect, 0, 0, w_to, h_to, raw, 0, 0, w_raw, h_raw);
		delimage(raw);
		return Texture { expect , Vector2D(w_to, h_to) };
	}

	return Texture { raw, Vector2D(w_raw, h_raw) };
}

const std::map<int, Texture>& ResourcesLoader::loadAllTextures()
{
	for (auto& elem : settings.mTextures)
	{
		loadTexture(elem.second);
	}
	return textures;
}

void ResourcesLoader::loadTextureSettings()
{
	ifstream ifs("settings/TextureSettings.json");
	json raw;
	ifs >> raw;

	for (auto& j : raw)
	{
		string str_utf8 = j["Path"];
		wstring str_utf16 = wstring(begin(str_utf8), end(str_utf8));
		settings.mTextures[j["ID"]] = Settings_Texture { str_utf16.c_str(), j["HitBox"] };
	}

	ifs.close();
}

void ResourcesLoader::loadGeneralSettings()
{
	ifstream ifs("settings/GeneralSettings.json");
	json raw;
	ifs >> raw;
	
	auto ui = raw["UI"];
	auto times = raw["Times"];
	auto bgIDs = raw["BgTextureIDs"];
	auto animeIDs = raw["AnimeTextureIDs"];

	settings.pGeneral = unique_ptr<Settings::General>(new Settings::General
	{
		{ // UI
			ui["FPS"],
			ui["Resolution"],
			ui["FontHeight"]
		},
		{ // times
			times["EnemyInfoDuration"],
			times["EnemyWaveCoolDown"],
			times["BgShiftSpeed"]
		},
		{ // bgTextures
			getTexture(bgIDs["Menu"]),
			getTexture(bgIDs["Gaming"]),
			getTexture(bgIDs["GameOver"])
		},
		{ // animeTextures
			getTexture(animeIDs["Explosion"])
		}
	});

	ifs.close();
}

void ResourcesLoader::loadPlaneSettings()
{
	ifstream ifs("settings/PlaneSettings.json");
	json raw;
	ifs >> raw;

	settings.pPlayer = make_unique<Settings::Plane>(raw["Player"]);
	settings.pEnemyJunior = make_unique<Settings::Plane>(raw["Enemy_Junior"]);
	settings.pEnemyAutoTarget = make_unique<Settings::Plane>(raw["Enemy_AutoTarget"]);

	ifs.close();
}
