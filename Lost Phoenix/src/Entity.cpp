#include "Entity.h"
#include <graphics.h>

bool Entity::judgeCollision(const Entity * e1, const Entity * e2)
{
	if (e1 == nullptr || e2 == nullptr)
		return false;

	int zx = 2 * abs(e1->getXPos( ) + e1->getXHitBox( ) / 2 - e2->getXPos( ) - e2->getXHitBox( ) / 2);
	int zy = 2 * abs(e1->getYPos( ) + e1->getYHitBox( ) / 2 - e2->getYPos( ) - e2->getYHitBox( ) / 2);
	return zx <= e1->getXHitBox( ) + e2->getXHitBox( ) && zy <= e1->getYHitBox( ) + e2->getYHitBox( );
}

void Entity::update( )
{ 
	curPos += velocity;
}

void Entity::draw( )
{
	putimage_withalpha(nullptr, model.image, getXPos( ), getYPos( ));
}
