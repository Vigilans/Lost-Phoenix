#pragma once
#pragma warning(disable:4244) // disable double->int conversion warning
#include "Vector2D.hpp"

namespace ege
{
	class IMAGE;
	typedef IMAGE* PIMAGE;
};

struct Texture
{
	ege::PIMAGE image;
	Vector2D hitBox;

	Texture() = default;
	Texture(ege::PIMAGE image, Vector2D hitBox) : image(image), hitBox(hitBox) { }
	explicit Texture(int id);
};

Texture getTexture(int id);

Texture splitTexture(Texture texture, int x, int y, int w, int h);

namespace Settings
{
	const struct General
	{
		struct
		{
			char* title;
			int fps;
			Vector2D resolution;
			int fontHeight;
		} UI;

		struct
		{
			int enemyInfoDuration;
			int enemyWaveCoolDown;
			int bgShiftSpeed;
		} times;
	}& general();

	const struct BgTextures
	{
		Texture menu;
		Texture gaming;
		Texture gameOver;
	}& bgTextures();

	const struct AnimeTextures
	{
		Texture explosion;
	}& animeTextures();

	struct Bullet
	{
		Texture texture;
		int attack;
		int speed;
		int coolDown;
	};

	struct Plane
	{
		int camp;
		Texture texture;
		int health;
		int speed;
		Bullet bulletSetting;
		int score;
	};

	const Settings::Plane& player( );
	const Settings::Plane& enemy_junior( );
	const Settings::Plane& enemy_autoTarget( );
};