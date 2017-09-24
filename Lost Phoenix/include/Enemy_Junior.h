/*! \file Enemy_Junior.h	
	\brief 定义新兵敌机的飞机类及子弹类。
*/

#pragma once
#include "Plane - Bullet.h"

/// <summary>
/// 新兵敌机。特点为血少，子弹伤害低，路径单一，会飞离屏幕；但子弹速度快，射击间隔短。
/// </summary>
/// <seealso cref="T:Plane"/>
class Plane_Enemy_Junior : public Plane
{
public:
	Plane_Enemy_Junior(Settings::Plane setting, Vector2D position, Vector2D velocity = Vector2D()); ///< 基础构造函数。

	virtual void update() override; ///< 更新状态，主要为调用射击函数。
	
	/// <summary>
	/// 进行一次射击。高等级时子弹移动速度出现变化。
	/// </summary>
	/// <remarks>
	/// 随着<see cref="difficultyLevel"/>升高，开始表现出不同的特性：
	/// * 难度等级到2以上后，子弹的速度将在一个区间变动，初始为0.8~1.2倍原速度。随着难度越来越高，区间将变得越来越宽。  
	/// * 这样做会使得小飞机构造出一个子弹网，使得玩家飞机难以通行。
	/// </remarks>
	virtual void shoot() override;

};

/// <summary>
/// 新兵敌机子弹。
/// </summary>
/// <seealso cref="T:Bullet"/>
class Bullet_Enemy_Junior : public Bullet
{
public:
	Bullet_Enemy_Junior(Entity* src, Settings::Bullet setting, Vector2D velocity = Vector2D()); ///< 基础构造函数，与玩家子弹构造函数相同。

};