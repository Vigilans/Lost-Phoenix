#include "Plane - Bullet.h"
#include <ctime>
#include "World.h"
#include "Actions.h"

Plane::Plane(int textureID, Ally camp, Vector2D position, Vector2D velocity, int maxHP, int shootCD) :
	Entity(textureID, camp, position, velocity), 
	maxHealth(maxHP), curHealth(maxHP), shootCoolDown(shootCD), shootCheckPoint(clock( )), state(PlaneState::Alive)
{
	if (this->getAlly( ) == Ally::Enemy)
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
	if (getAlly( ) == Ally::Enemy)
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

Bullet::Bullet(int textureID, Entity * src, int atk, Vector2D velocity)
	: Entity(textureID, src->getAlly( ), Vector2D( ), velocity), attack(atk), end(false)
{ 
	setPosition(initPosBySource(src));
	world.bullets.push_back(this);
}

void Bullet::update( )
{
	Entity::update( );
}

Vector2D Bullet::initPosBySource(Entity * p)
{
	int offset_x = (p->getXHitBox( ) - this->getXHitBox( )) / 2;
	int offset_y = p->getAlly( ) == Ally::Friend ? -this->getYHitBox( ) : p->getYHitBox( );
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
