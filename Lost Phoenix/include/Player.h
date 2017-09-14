#pragma once
#include "Plane - Bullet.h"

class Plane_Player : public Plane
{
public:
	Plane_Player();

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
	Bullet_Player(Entity* src, Vector2D velocity) : Bullet(PLAYER_BULLET_ID, src, ATTACK_PLAYER_BULLET, velocity) {  }

};