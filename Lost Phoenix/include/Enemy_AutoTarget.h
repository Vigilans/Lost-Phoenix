#pragma once
#include "Plane - Bullet.h"

class Plane_Enemy_AutoTarget : public Plane
{
public:
	Plane_Enemy_AutoTarget(Settings::Plane setting, Vector2D position, Vector2D velocity = Vector2D());

	virtual void update() override;
	virtual void shoot() override;
	virtual void takeDamage(int damage) override;

};

class Bullet_Enemy_AutoTarget : public Bullet
{
public:
	Bullet_Enemy_AutoTarget(Entity* src, Plane* des, Settings::Bullet setting);

};