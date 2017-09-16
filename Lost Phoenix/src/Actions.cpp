#include "Actions.h"
#include "World.h"

void updateNewAction(Action * newAction)
{
	world.actions.push_back(newAction);
}

/* -----------Action_Plane_Explode类实现----------- */
Texture Action_Plane_Explode::models[4] = { };

void Action_Plane_Explode::initializeModels( )
{
	models[0] = splitTexture(PLANE_EXPLOSION_ID, 0, 0, 128, 128);
	models[1] = splitTexture(PLANE_EXPLOSION_ID, 128, 0, 128, 128);
	models[2] = splitTexture(PLANE_EXPLOSION_ID, 0, 128, 128, 128);
	models[3] = splitTexture(PLANE_EXPLOSION_ID, 128, 128, 128, 128);
}

Action_Plane_Explode::Action_Plane_Explode(Plane* src, bool destroy, int time, void(*endCallbackFunc)())
	:Action(endCallbackFunc), curIndex(0), srcPlane(src), boomTime(time), toDestroy(destroy) { }

Action_Plane_Explode::~Action_Plane_Explode( ) 
{
	if (toDestroy)
		delete srcPlane;
}

int Action_Plane_Explode::onUpdate( )
{
	++curIndex;
	if (curIndex == 4 * boomTime)
		this->end = true;
	return 0;
}

void Action_Plane_Explode::onDraw(PIMAGE pimg) const
{
	if (curIndex < 4 * boomTime)
	{
		Vector2D boomPos = srcPlane->getPosition( ) + (srcPlane->getHitBox( ) - models[0].hitBox) / 2; // 设置爆炸贴图与飞机贴图矩形的重心重合
		putimage_withalpha(pimg, models[curIndex / boomTime].image, boomPos.x, boomPos.y);
	}
}
/* -----------Action_Plane_Explode类实现----------- */
