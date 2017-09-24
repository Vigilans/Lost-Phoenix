/*! \file Entity.h
	\brief 定义所有实体的基类，以及一个阵营的枚举。
*/

#pragma once
#include "Resources.h"

/// <summary>
/// 实体的阵营枚举。用来表征飞机与子弹的敌友关系。
/// </summary>
enum class Camp
{
	Friend, /// 友军（只有自机及射出的子弹）
	Enemy /// 敌军
};

/// <summary>
/// 游戏中所有实体的总基类。
/// </summary>
class Entity
{
public:
	/// <summary>
	/// 判断两个实体是否发生碰撞。
	/// </summary>
	/// <remarks>
	/// 本来，用代码判断两个矩形是否碰撞是一件很麻烦的事……（曾经一个项目写了很长的代码但还是有问题……）
	/// 但是后来找到了一个即简单又严格的数学方法，即**比较两个矩形重心的绝对值距离与矩形长宽的关系**。
	/// <seealso cref="http://blog.csdn.net/u011483306/article/details/45368367"/>
	/// </remarks>
	/// <param name="e1"> 一个实体的指针（非空）。</param>
	/// <param name="e2"> 另一个实体的指针（非空）。 </param>
	/// <returns>
	/// * 如果发生碰撞，则返回true；  
	/// * 如果未发生碰撞或任一参数为空，则返回false。
	/// </returns>
	static bool judgeCollision(const Entity * e1, const Entity * e2);

	/// <summary>
	/// 唯一构造函数。
	/// </summary>
	/// <param name="texture">  实体的材质。 </param>
	/// <param name="camp">	    实体的<see cref="Camp"/>（阵营）。 </param>
	/// <param name="position"> 实体在地图上的坐标。 </param>
	/// <param name="velocity"> (可选) 实体的速度矢量。默认为0。 </param>
	Entity(Texture texture, Camp camp, Vector2D position, Vector2D velocity = Vector2D()) :
		model(texture), camp(camp), curPos(position), velocity(velocity) { }
	
	/// <summary>
	/// 基类虚析构函数，保证子类能正常析构。
	/// </summary>
	virtual ~Entity() { }
	
	/// <summary>
	/// 更新实体状态。作为基类虚函数，此方法只通过速度更新当前位置。
	/// </summary>
	virtual void update();
	
	/// <summary>
	/// 在地图上绘制实体。使用了透明通道，因此可以渲染出透明材质。
	/// </summary>
	virtual void draw();

	/* -------------- get & set --------------*/
	int getXPos() const { return curPos.x; }
	int getYPos() const { return curPos.y; }
	void setXPos(int x) { curPos.x = x; }
	void setYPos(int y) { curPos.y = y; }

	int getXVel() const { return velocity.x; }
	int getYVel() const { return velocity.y; }
	void setXVel(int x) { velocity.x = x; }
	void setYVel(int y) { velocity.y = y; }

	int getXHitBox() const { return model.hitBox.x; }
	int getYHitBox() const { return model.hitBox.y; }

	Vector2D getPosition() const { return curPos; }
	Vector2D getVelocity() const { return velocity; }
	Vector2D getHitBox() const { return model.hitBox; }

	void setPosition(const Vector2D& pos) { curPos = pos; }
	void setVelocity(const Vector2D& vel) { velocity = vel; }

	Camp getCamp() const { return camp; }

protected:
	/// <summary>
	/// 实体的材质模型。通过它获取实体的HitBox属性。<seealso cref="Texture"/>
	/// </summary>
	Texture model;
	
	/// <summary>
	/// 实体当前在地图上的位置。
	/// </summary>
	Vector2D curPos;
	
	/// <summary>
	/// 实体当前的速度矢量。
	/// </summary>
	Vector2D velocity;

	/// <summary>
	/// 实体当前的<see cref="Camp"/>（阵营）。
	/// </summary>
	Camp camp;
};

