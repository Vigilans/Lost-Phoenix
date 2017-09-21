#pragma once
#include "Resources.h"

enum class Camp
{
	Friend,
	Enemy
};

class Entity
{
public:
	Entity(Texture texture, Camp camp, Vector2D position, Vector2D velocity = Vector2D()) :
		model(texture), camp(camp), curPos(position), velocity(velocity) { }
	virtual ~Entity() { }

	virtual void update();
	virtual void draw();

	/* -------------- get & set --------------*/
	int getXPos() { return curPos.x; }
	int getYPos() { return curPos.y; }
	void setXPos(int x) { curPos.x = x; }
	void setYPos(int y) { curPos.y = y; }

	int getXVel() { return velocity.x; }
	int getYVel() { return velocity.y; }
	void setXVel(int x) { velocity.x = x; }
	void setYVel(int y) { velocity.y = y; }

	int getXHitBox() { return model.hitBox.x; }
	int getYHitBox() { return model.hitBox.y; }

	Vector2D getPosition() { return curPos; }
	Vector2D getVelocity() { return velocity; }
	Vector2D getHitBox() { return model.hitBox; }

	void setPosition(const Vector2D& pos) { curPos = pos; }
	void setVelocity(const Vector2D& vel) { velocity = vel; }

	Camp getCamp() { return camp; }

protected:
	Texture model;
	Vector2D curPos;
	Vector2D velocity;
	Camp camp;
};

bool judgeCollision(Entity* e1, Entity* e2);