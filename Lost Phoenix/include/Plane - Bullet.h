#pragma once
#include "Entity.h"

enum class PlaneState 
{
	Alive,
	Dead,
	Vanished
};

// Plane Base Class

class Plane : public Entity
{
public:
	Plane(int textureID, Ally camp, Vector2D position, Vector2D velocity, int maxHP, int shootCD);
	~Plane( );

	virtual void update( );
	virtual void draw( );
	virtual void shoot( ) = 0;
	virtual void takeDamage(int damage);

	PlaneState getState( ) { return state; }
	void setState(PlaneState new_state) { state = new_state; }

	int getHealth( ) { return curHealth; }
	void setHealth(int hp) { curHealth = hp; }

	int maxHealth;
	int curHealth;
	int shootCoolDown;

protected:
	bool checkShootCoolDown( );


	int shootCheckPoint;
	PlaneState state;
};

// bullet base class

class Bullet : public Entity
{
public:
	Bullet(int textureID, Entity* src, int atk, Vector2D velocity = Vector2D( ));

	virtual void update( );

	int attack;
	bool end;

private:
	Vector2D initPosBySource(Entity* p);

};

class Plane_Player;

void dealDamage(Plane* plane, Bullet* bullet);
void dealDamage(Plane_Player* player, Plane* enemy);
