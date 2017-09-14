#pragma once
#include "Plane - Bullet.h"

// BOSS, ÔÝÊ±Î´ÊµÏÖ

class Plane_Enemy_Cruiser : public Plane
{
public:
	Plane_Enemy_Cruiser(Vector2D position, Vector2D velocity = Vector2D( )) : Plane(ENEMY_PLANE_AUTOTARGET_ID, Ally::Enemy, position, velocity, 0, 1100) { };

	virtual void update( );
	virtual void shoot( );

};

class Bullet_Enemy_Cruiser_Basic : public Bullet
{
public:
	Bullet_Enemy_Cruiser_Basic(Entity* src, Plane* des, int speed)
		: Bullet(ENEMY_BULLET_AUTOTARGET_ID, src, 0)
	{
		this->setVelocity(Vector2D(this->getPosition( ), des->getPosition( ) + des->getHitBox( ) / 2) * speed);
	}

};

class Bullet_Enemy_Cruiser_Bomb : public Bullet
{
public:
	Bullet_Enemy_Cruiser_Bomb(Entity* src, Plane* des, int speed)
		: Bullet(ENEMY_BULLET_AUTOTARGET_ID, src, 0)
	{
		this->setVelocity(Vector2D(this->getPosition( ), des->getPosition( ) + des->getHitBox( ) / 2) * speed);
	}
	~Bullet_Enemy_Cruiser_Bomb( );

	virtual void update( );

private:
	Vector2D initPosition;
	int splitDistance;
};

