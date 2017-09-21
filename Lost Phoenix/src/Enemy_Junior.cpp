#include "Enemy_Junior.h"

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
		new Bullet_Enemy_Junior(this, Settings::enemy_junior().bulletSetting);
}

Bullet_Enemy_Junior::Bullet_Enemy_Junior(Entity * src, Settings::Bullet setting, Vector2D velocity)
	: Bullet(src, setting, velocity)
{

}
