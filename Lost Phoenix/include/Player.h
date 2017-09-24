/*! \file Player.h
	\brief 定义玩家的飞机及子弹类。
*/

#pragma once
#include "Plane - Bullet.h"

/// <summary>
/// 玩家飞机。
/// </summary>
/// <seealso cref="T:Plane"/>
class Plane_Player : public Plane
{
public:
	/// <summary>
	/// 唯一构造函数。
	/// </summary>
	/// <param name="setting"> 飞机的设置。以后可改成`Settings::Player`。 </param>
	Plane_Player(Settings::Plane setting);
	
	virtual void update( ); ///< 更新状态，主要是更新键盘输入。若飞机已不属于存活状态，则无任何动作。
	//virtual void draw( );
	virtual void shoot( ); ///< 射击，产生一个<see cref="Bullet_Player"/>。
	virtual void takeDamage(int damage); ///< 承担伤害。若飞机仍存活，会产生一次<see cref="Action_Plane_Explode"/>。

private:
	void handleInput( ); ///< 处理键盘输入，更新飞机状态。
};

/// <summary>
/// 玩家飞机基础子弹。
/// </summary>
/// <seealso cref="T:Bullet"/>
class Bullet_Player : public Bullet
{
public:
	/// <summary>
	/// 唯一构造函数。
	/// </summary>
	/// <param name="src"> 射击源，一般为玩家飞机。 </param>
	/// <param name="setting">  子弹设置。 </param>
	/// <param name="velocity"> 子弹速度。 </param>
	Bullet_Player(Entity* src, Settings::Bullet setting, Vector2D velocity = Vector2D());
};