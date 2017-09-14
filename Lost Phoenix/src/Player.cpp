#include "Player.h"
#include "World.h"
#include "Actions.h"
#include <graphics.h>

Plane_Player::Plane_Player( ) 
	: Plane(PLAYER_PLANE_ID, 
		Ally::Friend, 
		getTexture(BACKGROUND_ID).hitBox - getTexture(PLAYER_PLANE_ID).hitBox, 
		Vector2D( ), 
		HEALTH_PLAYER_PLANE, 
		COOLDOWN_PLAYER_BULLET)
{
	this->setXPos(this->getXPos( ) / 2);
};

void Plane_Player::update( )
{
	if (getState( ) != PlaneState::Alive)
		return;
	handleInput( );
	Plane::update( );
}

void Plane_Player::shoot( )
{
	if(checkShootCoolDown( ))
		new Bullet_Player(this, Vector2D(0, SPEED_PLAYER_BULLET));
}

void Plane_Player::takeDamage(int damage)
{
	Plane::takeDamage(damage);
	if (getState( ) != PlaneState::Dead)
		new Action_Plane_Explode(this, false);
}

void Plane_Player::handleInput( )
{
	// -------- HANDLE X AXIS MOVE
	if (world.inputCtrl.isKeyDown(Key::A) && !world.inputCtrl.isKeyDown(Key::D))
	{
		velocity.x = -SPEED_PLAYER_PLANE;
	}
	else if (world.inputCtrl.isKeyDown(Key::D) && !world.inputCtrl.isKeyDown(Key::A))
	{
		velocity.x = SPEED_PLAYER_PLANE;
	}
	else
	{
		velocity.x = 0;
	}

	// -------- HANDLE Y AXIS MOVE
	if (world.inputCtrl.isKeyDown(Key::W) && !world.inputCtrl.isKeyDown(Key::S))
	{
		velocity.y = -SPEED_PLAYER_PLANE;
	}
	else if (world.inputCtrl.isKeyDown(Key::S) && !world.inputCtrl.isKeyDown(Key::W))
	{
		velocity.y = SPEED_PLAYER_PLANE;
	}
	else
	{
		velocity.y = 0;
	}

	if (world.inputCtrl.isKeyDown(Key::Space))
	{
		shoot( );
	}
}
