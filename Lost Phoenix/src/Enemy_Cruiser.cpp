#include "Enemy_Cruiser.h"
#include <graphics.h>

class Action_Enemy_Cruiser : public egeControlBase
{
public:
	Action_Enemy_Cruiser( )
	{
		delete this;
	}
	
};

Bullet_Enemy_Cruiser_Bomb::~Bullet_Enemy_Cruiser_Bomb( )
{
	new Action_Enemy_Cruiser;
}

void Bullet_Enemy_Cruiser_Bomb::update( )
{
	if ((getPosition( ) - initPosition).length( ) >= splitDistance)
	{
		delete this;
	}
}
