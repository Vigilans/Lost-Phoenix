#include "Player.h"
#include "World.h"
#include "Actions.h"
#include <graphics.h>

Plane_Player::Plane_Player(Settings::Plane setting)
	: Plane(setting, Settings::general().UI.resolution - setting.texture.hitBox, Vector2D())
{
	this->setXPos(this->getXPos() / 2);
}

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
		new Bullet_Player(this, Settings::player().bulletSetting);
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
		velocity.x = -speed;
	}
	else if (world.inputCtrl.isKeyDown(Key::D) && !world.inputCtrl.isKeyDown(Key::A))
	{
		velocity.x = speed;
	}
	else
	{
		velocity.x = 0;
	}

	// -------- HANDLE Y AXIS MOVE
	if (world.inputCtrl.isKeyDown(Key::W) && !world.inputCtrl.isKeyDown(Key::S))
	{
		velocity.y = -speed;
	}
	else if (world.inputCtrl.isKeyDown(Key::S) && !world.inputCtrl.isKeyDown(Key::W))
	{
		velocity.y = speed;
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

Bullet_Player::Bullet_Player(Entity * src, Settings::Bullet setting, Vector2D velocity)
	: Bullet(src, setting, velocity) { }
