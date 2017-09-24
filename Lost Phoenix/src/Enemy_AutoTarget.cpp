#include "Enemy_AutoTarget.h"
#include "World.h"
#include <cmath>
#include <ctime>

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
		double newYVel = 3 * (1.0*(rand() % 160 - 80) / 100); // -2.4 ~ 2.4
		if (curPos.y >= world.windowHeight() / 2)
			newYVel -= 1.2;

		int xVelFactor = world.difficultyLevel > 2 ? rand() % (world.difficultyLevel - 1) : 0;
		double newXVel = xVelFactor + Settings::enemy_autoTarget().speed;
		
		velocity.set(newXVel, newYVel);
		if (abs(newYVel) > 2.0)
			velocity.x *= -1;
		new Bullet_Enemy_AutoTarget(this, world.player_plane, Settings::enemy_autoTarget().bulletSetting);
	}
}

void Plane_Enemy_AutoTarget::takeDamage(int damage)
{
	Plane::takeDamage(damage);
	if (world.difficultyLevel >= 5 && getState() == State::Alive)
	{ // revenge
		auto tmp = shootCheckPoint;
		shootCheckPoint = 0;
		shoot();
		shootCheckPoint = tmp;
	}
		
}

Bullet_Enemy_AutoTarget::Bullet_Enemy_AutoTarget(Entity * src, Plane * des, Settings::Bullet setting)
	: Bullet(src, setting)
{
	this->setVelocity(Vector2D(this->getPosition(), des->getPosition() + des->getHitBox() / 2) * speed);
}
