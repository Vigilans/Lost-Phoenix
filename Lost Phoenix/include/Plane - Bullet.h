/*! \file "Plane - Bullet.h"
	\brief 定义飞机及子弹的基类，以及两个"dealDamage"（子弹->飞机，自机->敌机）全局函数。
*/

#pragma once
#include "Entity.h"

/// <summary>
/// 飞机的基类。
/// </summary>
/// <seealso cref="T:Entity"/>
class Plane : public Entity
{
public:
	enum class State
	{
		Alive,
		Dead,
		Vanished,
		Invincible
	};

	Plane(Settings::Plane setting, Vector2D position, Vector2D velocity);
	~Plane( );

	virtual void update( );
	virtual void draw( );
	virtual void shoot( ) = 0;
	virtual void takeDamage(int damage);

	Plane::State getState( ) { return state; }
	void setState(Plane::State new_state) { state = new_state; }

	int getHealth( ) { return curHealth; }
	void setHealth(int hp) { curHealth = hp; }

	int speed;
	int maxHealth;
	int curHealth;
	time_t shootCoolDown;

protected:
	bool checkShootCoolDown( );

	time_t shootCheckPoint;
	Plane::State state;
};

/// <summary>
/// 子弹的基类。
/// </summary>
/// <seealso cref="T:Entity"/>
class Bullet : public Entity
{
public:
	/// <summary>
	/// 唯一构造函数。
	/// </summary>
	/// <param name="src">	    子弹的产生源。可以是飞机（射击），也可以是子弹（集束、分裂之类） </param>
	/// <param name="setting">  子弹的数据设置。 </param>
	/// <param name="velocity"> (可选)子弹的速度。可置零是方便需要在别处初始化的情况。 </param>
	Bullet(Entity* src, Settings::Bullet setting, Vector2D velocity = Vector2D( ));

	virtual void update( ); ///< 更新子弹状态。
	
	int speed; ///< 子弹的移动速率。
	int attack; ///< 子弹的伤害。
	bool end; ///< 表征子弹是否已达到结束状态。 TODO: 用Bullet::State取代bool，可以区分Not Hit, Hit与Vanished状态。

private:
	Vector2D initPosBySource(Entity* p); ///< 将子弹的位置设置为源飞机正上方。
};

class Plane_Player;

void dealDamage(Plane* plane, Bullet* bullet); ///< 子弹与飞机相碰时的伤害处理。
void dealDamage(Plane_Player* player, Plane* enemy); ///< 自机与敌机相碰时的伤害处理。
