#include "Enemy_AutoTarget.h"
#include "World.h" 
#include <cmath>

Plane_Enemy_AutoTarget::Plane_Enemy_AutoTarget(Settings::Plane setting, Vector2D position, Vector2D velocity)
	: Plane(setting, position, velocity)
{

};

void Plane_Enemy_AutoTarget::update()
{
	shoot();
	Plane::update();
}

void Plane_Enemy_AutoTarget::shoot()
{
	if (checkShootCoolDown())
	{
		double newYVel = 3 * (1.0*(rand() % 160 - 80) / 100);
		if (abs(newYVel) > 2)
			setXVel(-getXVel());
		setYVel(newYVel);
		new Bullet_Enemy_AutoTarget(this, world.player_plane, Settings::enemy_autoTarget().bulletSetting);
	}
}

Bullet_Enemy_AutoTarget::Bullet_Enemy_AutoTarget(Entity * src, Plane * des, Settings::Bullet setting)
	: Bullet(src, setting)
{
	this->setVelocity(Vector2D(this->getPosition(), des->getPosition() + des->getHitBox() / 2) * speed);
}
