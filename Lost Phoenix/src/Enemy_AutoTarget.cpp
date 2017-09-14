#include "Enemy_AutoTarget.h"
#include "World.h" 
#include <cmath>

Plane_Enemy_AutoTarget::Plane_Enemy_AutoTarget(Vector2D position, Vector2D velocity)
	: Plane(ENEMY_PLANE_AUTOTARGET_ID,
		Ally::Enemy,
		position,
		velocity,
		HEALTH_ENEMY_AUTOTARGET_PLANE,
		COOLDOWN_ENEMY_AUTOTARGET_BULLET)
{

};

void Plane_Enemy_AutoTarget::update( )
{
	shoot( );
	Plane::update( );
}

void Plane_Enemy_AutoTarget::shoot( )
{
	if (checkShootCoolDown( ))
	{
		double newYVel = 3 * (1.0*(rand( ) % 160 - 80) / 100);
		if (abs(newYVel) > 2)
			setXVel(-getXVel( ));
		setYVel(newYVel);
		new Bullet_Enemy_AutoTarget(this, world.player_plane, SPEED_ENEMY_AUTOTARGET_BULLET);
	}
}

Bullet_Enemy_AutoTarget::Bullet_Enemy_AutoTarget(Entity * src, Plane * des, int speed)
	: Bullet(ENEMY_BULLET_AUTOTARGET_ID, src, ATTACK_ENEMY_AUTOTARGET_BULLET)
{
	this->setVelocity(Vector2D(this->getPosition( ), des->getPosition( ) + des->getHitBox( ) / 2) * speed);
}
