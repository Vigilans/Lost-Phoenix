/*! \file Enemy_AutoTarget.h
	\brief 定义自机狙敌机的飞机类及子弹类。
*/

#pragma once
#include "Plane - Bullet.h"

/// <summary>
/// 自机狙敌机。特点是血厚，不会飞出屏幕，子弹追踪玩家飞机，伤害高；但子弹速度较慢，射击间隔长。
/// </summary>
/// <seealso cref="T:Plane"/>
class Plane_Enemy_AutoTarget : public Plane
{
public:
	Plane_Enemy_AutoTarget(Settings::Plane setting, Vector2D position, Vector2D velocity = Vector2D()); ///< 基础构造函数。

	virtual void update() override; ///< 更新状态，主要为调用射击函数。
	
	/// <summary>
	/// 进行一次射击，并改变自身速度。高等级时飞机移动速度出现变化。
	/// </summary>
	/// <remarks>
	/// 自机狙飞机在射击后，自身的速度会改变。具体机制为：
	/// * y方向速度在-2.4 ~ 2.4之间随机一个值, 取整数。  
	/// * 若y方向速度绝对值大于2，则飞机的x方向速度反向。  
	/// * 若飞机在屏幕下半区，则飞机更容易向后退。且可能具有非常大的后退速度。
	/// 
	/// 随着<see cref="difficultyLevel"/>升高，开始表现出不同的特性：
	/// * 难度等级到3以上后，每次射击时，x轴方向速度都会相对于默认速度，按一定倍数变大。难度越高，倍数越大。
	/// </remarks>
	virtual void shoot() override;
	
	/// <summary>
	/// 承受伤害。高等级时出现复仇机制。
	/// </summary>
	/// <param name="damage"> 受到的伤害。 </param>
	/// <remarks>
	/// 随着<see cref="difficultyLevel"/>升高，开始表现出不同的特性：
	/// * 难度等级到5以上后，若受到伤害且未坠毁，则立即进行一次复仇射击。该次射击不影响之前的射击冷却。
	/// </remarks>
	virtual void takeDamage(int damage) override;

};

/// <summary>
/// 自机狙敌机的追踪子弹。
/// </summary>
/// <seealso cref="T:Bullet"/>
class Bullet_Enemy_AutoTarget : public Bullet
{
public:
	/// <summary>
	/// 构造函数。
	/// </summary>
	/// <param name="src"> 射击源 </param>
	/// <param name="des"> 被追踪的飞机。一般为玩家飞机。 </param>
	/// <param name="setting"> 子弹设置。 </param>
	Bullet_Enemy_AutoTarget(Entity* src, Plane* des, Settings::Bullet setting);
};