#pragma once
#include "Plane - Bullet.h"

class Plane_Player : public Plane
{
public:
	Plane_Player(Settings::Plane setting);

	virtual void update( );
	//virtual void draw( );
	virtual void shoot( );
	virtual void takeDamage(int damage);

private:
	void handleInput( );
};

class Bullet_Player : public Bullet
{
public:
	Bullet_Player(Entity* src, Settings::Bullet setting, Vector2D velocity = Vector2D());
};