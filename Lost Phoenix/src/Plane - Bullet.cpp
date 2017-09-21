#include "Plane - Bullet.h"
#include <ctime>
#include "World.h"
#include "Actions.h"

Plane::Plane(Settings::Plane setting, Vector2D position, Vector2D velocity) :
	Entity(setting.texture, Camp(setting.camp), position, velocity),
	speed(setting.speed),
	maxHealth(setting.health), curHealth(setting.health), 
	shootCoolDown(setting.bulletSetting.coolDown), shootCheckPoint(clock()), 
	state(PlaneState::Alive)
{
	if (this->getCamp() == Camp::Enemy)
		world.enemy_planes.push_back(this);
}

Plane::~Plane( )
{

}

void Plane::update( )
{
	Entity::update( );
}

void Plane::draw( )
{
	if (getState( ) == PlaneState::Alive)
		Entity::draw( );
}

void Plane::takeDamage(int damage)
{
	if (damage >= curHealth)
	{
		damage = curHealth;
		setState(PlaneState::Dead);
	}
	curHealth -= damage;
	if (getCamp( ) == Camp::Enemy)
		world.score += damage;
	else
		world.score -= damage;
}

bool Plane::checkShootCoolDown( )
{
	if(clock( ) - shootCheckPoint < shootCoolDown)
		return false;
	shootCheckPoint = clock( );
	return true;
}

Bullet::Bullet(Entity * src, Settings::Bullet setting, Vector2D velocity)
	: Entity(setting.texture, src->getCamp( ), Vector2D( ), velocity), speed(setting.speed), attack(setting.attack), end(false)
{ 
	setPosition(initPosBySource(src));
	setVelocity(velocity != Vector2D() ? velocity : Vector2D(0, speed));
	world.bullets.push_back(this);
}

void Bullet::update( )
{
	Entity::update( );
}

Vector2D Bullet::initPosBySource(Entity * p)
{
	int offset_x = (p->getXHitBox( ) - this->getXHitBox( )) / 2;
	int offset_y = p->getCamp( ) == Camp::Friend ? -this->getYHitBox( ) : p->getYHitBox( );
	return Vector2D(p->getXPos( ) + offset_x, p->getYPos( ) + offset_y);
}

void dealDamage(Plane * plane, Bullet * bullet)
{
	plane->takeDamage(bullet->attack);
	bullet->end = true;
}

void dealDamage(Plane_Player * player, Plane * enemy)
{
	player->takeDamage(enemy->curHealth);
	enemy->takeDamage(enemy->curHealth);
}
