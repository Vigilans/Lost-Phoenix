#include "ResourcesLoader.h"
#include <fstream>
#include <json.hpp>
#include <graphics.h>

using namespace std;
using json = nlohmann::json;

void to_json(json& j, const Vector2D& v) { j = json { v.x, v.y }; }

void from_json(const json& j, Vector2D& v) { v = Vector2D(j[0].get<Vector2D::value_type_t>(), j[1].get<Vector2D::value_type_t>()); }

namespace Settings
{
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
			j["Camp"],
			getTexture(j["TextureID"]),
			j["Health"],
			j["Speed"],
			j["Bullet"],
			j.find("Score") == j.end() ? 0 : j["Score"]
		};
	}
}

ResourcesLoader::ResourcesLoader()
{
	loadTextureSettings();
}

ResourcesLoader::~ResourcesLoader()
{
	for (auto& elem : textures)
		delimage(elem.second.image);
	delete settings.pGeneral->UI.title;
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
	for (auto& elem : settings.mTextureInfos)
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
		settings.mTextureInfos[j["ID"]] = Settings::TextureInfo { std::move(str_utf16), std::move(j["HitBox"]) };
	}

	ifs.close();
}

void ResourcesLoader::loadGeneralSettings()
{
	ifstream ifs("settings/GeneralSettings.json");
	json raw;
	ifs >> raw;
	
	auto& ui = raw["UI"];
	auto& times = raw["Times"];
	auto& bgIDs = raw["BgTextureIDs"];
	auto& animeIDs = raw["AnimeTextureIDs"];
	
	settings.pGeneral = unique_ptr<Settings::General>(new Settings::General
	{
		{ // UI
			nullptr,
			ui["FPS"],
			ui["Resolution"],
			ui["FontHeight"]
		},
		{ // times
			times["EnemyInfoDuration"],
			times["EnemyWaveCoolDown"],
			times["BgShiftSpeed"]
		},
	});

	string title = ui["Title"];
	strcpy(settings.pGeneral->UI.title = new char[title.size()], title.c_str());

	// zoom the backgrounds to fit the resolution
	settings.mTextureInfos[bgIDs["Menu"]].expectHitBox = settings.pGeneral->UI.resolution;
	settings.mTextureInfos[bgIDs["Gaming"]].expectHitBox = settings.pGeneral->UI.resolution;
	settings.mTextureInfos[bgIDs["GameOver"]].expectHitBox = settings.pGeneral->UI.resolution;

	ifs.close();
}

void ResourcesLoader::loadBgTextures()
{
	ifstream ifs("settings/GeneralSettings.json");
	json raw;
	ifs >> raw;

	auto& bgIDs = raw["BgTextureIDs"];

	settings.pBgTextures = unique_ptr<Settings::BgTextures>(new Settings::BgTextures
	{
		getTexture(bgIDs["Menu"]),
		getTexture(bgIDs["Gaming"]),
		getTexture(bgIDs["GameOver"])
	});	

	ifs.close();
}

void ResourcesLoader::loadAnimeTextures()
{
	ifstream ifs("settings/GeneralSettings.json");
	json raw;
	ifs >> raw;

	auto& animeIDs = raw["AnimeTextureIDs"];

	settings.pAnimeTextures = unique_ptr<Settings::AnimeTextures>(new Settings::AnimeTextures
	{
		getTexture(animeIDs["Explosion"])
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
