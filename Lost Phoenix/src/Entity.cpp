#include "Entity.h"
#include <graphics.h>

bool judgeCollision(Entity * e1, Entity * e2)
{
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
	putimage_withalpha(NULL, model.image, getXPos( ), getYPos( ));
}