#include "Enemy_Junior.h"
#include <cstdlib>
#include "World.h"

Plane_Enemy_Junior::Plane_Enemy_Junior(Settings::Plane setting, Vector2D position, Vector2D velocity)
	: Plane(setting, position, velocity)
{

};

void Plane_Enemy_Junior::update()
{
	shoot();
	Plane::update();
}

void Plane_Enemy_Junior::shoot()
{
	if (checkShootCoolDown())
	{
		auto setting = Settings::enemy_junior().bulletSetting;
		if (world.difficultyLevel > 1)
		{
			auto speedFactor = (rand() % (400 + 100 * (world.difficultyLevel - 1)) + 800) / 1000.0;
			setting.speed *= speedFactor;
		}
		new Bullet_Enemy_Junior(this, setting);
	}
}

Bullet_Enemy_Junior::Bullet_Enemy_Junior(Entity * src, Settings::Bullet setting, Vector2D velocity)
	: Bullet(src, setting, velocity)
{

}
