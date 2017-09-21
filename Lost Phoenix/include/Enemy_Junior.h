#pragma once
#include "Plane - Bullet.h"

class Plane_Enemy_Junior : public Plane
{
public:
	Plane_Enemy_Junior(Settings::Plane setting, Vector2D position, Vector2D velocity = Vector2D());

	virtual void update();
	virtual void shoot();

};

class Bullet_Enemy_Junior : public Bullet
{
public:
	Bullet_Enemy_Junior(Entity* src, Settings::Bullet setting, Vector2D velocity = Vector2D());

};