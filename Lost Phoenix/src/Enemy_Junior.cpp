#include "Enemy_Junior.h"

Plane_Enemy_Junior::Plane_Enemy_Junior(Vector2D position, Vector2D velocity)
	: Plane(ENEMY_PLANE_JUNIOR_ID, 
		Ally::Enemy,
		position, 
		velocity, 
		HEALTH_ENEMY_JUNIOR_PLANE,
		COOLDOWN_ENEMY_JUNIOR_BULLET) 
{

};

void Plane_Enemy_Junior::update( )
{
	shoot( );
	Plane::update( );
}

void Plane_Enemy_Junior::shoot( )
{
	if (checkShootCoolDown( ))
		new Bullet_Enemy_Junior(this, Vector2D(0, SPEED_ENEMY_JUNIOR_BULLET));
}

Bullet_Enemy_Junior::Bullet_Enemy_Junior(Entity * src, Vector2D velocity) 
	: Bullet(ENEMY_BULLET_JUNIOR_ID, src, ATTACK_ENEMY_JUNIOR_BULLET, velocity) 
{ 

}
