#pragma once
#include <graphics.h>
#include "Resources.h"

// 前置声明
class Plane;
class Bullet;
class Action;

void updateNewAction(Action* newAction);

/// <summary>
/// 由ege控制类继承来的Action基类，仿自ege自带的fps类写成。用于表现一些动画的动作，同时通过析构 + 回调函数实现事件的连锁。
/// </summary>
/// <seealso cref="T:egeControlBase"/>
class Action : public egeControlBase
{
public:
	CTL_PREINIT(Action, egeControlBase)
	{
		// do sth. before sub objects' construct function call
	} CTL_PREINITEND;
	
	/// <summary>
	/// 基类构造函数。
	/// </summary>
	/// <param name="endCallbackFunc"> （可选）在一个动作结束后，析构时调用的回调函数指针。若传空指针则不调用。</param>
	/// <param name="parameter2"> ege用于自身进行处理的参数，可置空，不影响使用。 </param>
	Action(void(*endCallbackFunc)() = nullptr, CTL_DEFPARAM) : CTL_INITBASE(egeControlBase), end(false), callback(endCallbackFunc)
	{
		CTL_INIT; // must be the first line
		directdraw(true);
		enable(false);
		updateNewAction(this);
	}
	
	/// <summary>
	/// 析构函数。在回调函数指针不为空时，调用回调函数。
	/// </summary>
	virtual ~Action ( ) 
	{
		if (callback)
			callback( );
	}

	bool end; ///< 表征动作是否已到达结束状态。会在<see cref="World::actions"/>中被检测并处理。
	void(*callback)(); ///< 回调函数指针。
};

/// <summary>
/// Action之飞机爆炸。对于敌机，会在坠毁时出现；对于自机，会在受到伤害会坠毁时出现。
/// </summary>
/// <seealso cref="T:Action"/>
class Action_Plane_Explode : public Action
{
public:
	/// <summary>
	/// 初始化表现爆炸动画的材质组。采取Lazy Load机制。
	/// </summary>
	static void initializeModels( );
	
	/// <summary>
	/// 构造函数。
	/// </summary>
	/// <param name="src"> 爆炸源飞机。 </param>
	/// <param name="doDestroy">	 (可选) 是否销毁源飞机。默认为true。 </param>
	/// <param name="boomSpeed">	 爆炸动画每一帧展现时间。 </param>
	/// <param name="endCallbackFunc"> 回调函数指针。 </param>
	Action_Plane_Explode(Plane* src, bool doDestroy = true, int boomSpeed = 5, void(*endCallbackFunc)() = NULL);
	virtual ~Action_Plane_Explode( ); ///< 析构函数。若<see cref="toDestroy"/>为true，会销毁源飞机。

	virtual int onUpdate( ); ///< 更新爆炸状态。主要是更新爆炸帧，以及确定动作是否已结束。
	virtual void onDraw(PIMAGE pimg) const; ///< 绘制爆炸帧。会设置爆炸贴图的中心与飞机贴图的重心重合。

public:
	static Texture models[4]; ///< 用于表现爆炸动画的材质组。
	int boomTime; ///< 爆炸动画每一帧展现时间。
	int curIndex; ///< 目前所处的爆炸动画材质数组索引。
	Plane* srcPlane; ///< 爆炸源飞机。
	bool toDestroy; ///< 表示是否要销毁爆炸源飞机。
};

