#pragma once
#include <list>
#include "InputController.h"
#include "Player.h"	
#include "Enemy_Junior.h"
#include "Enemy_AutoTarget.h"

class Action;

/// <summary>
/// 承载整个游戏运行逻辑的总类。有一个extern声明的实例。
/// </summary>
/// <remarks>
/// 具体承载内容有：
/// 1. 游戏界面；  
/// 2. 所有物体的存储；    
/// 3. 程序输入与输出；  
/// 4. 游戏整体逻辑流程。
/// </remarks>
class World
{
public:
	/// <summary>
	/// 初始化游戏世界。
	/// </summary>
	/// <remarks>
	/// 目前初始化内容有：
	/// 1. 重置运行状态、分数、难度等级；  
	/// 2. 初始化游戏窗口；  
	/// 3. 初始化玩家飞机。
	/// </remarks>
	/// <returns>
	/// 返回是否初始化成功。
	/// </returns>
	bool initialize();
	
	/// <summary>
	/// 获取程序整体运行状态。
	/// </summary>
	/// <returns>
	/// 返回程序运行状态。
	/// </returns>
	bool is_running();
	
	/// <summary>
	/// 渲染游戏初始菜单。
	/// </summary>
	/// <remarks>
	/// 目前只有一个画面，按任意键后进入游戏。
	/// 
	/// TODO: 为目录添加按钮设置，可以开始游戏、设置选项或退出。
	/// </remarks>
	void renderMenu();
	
	/// <summary>
	/// 主逻辑更新函数。
	/// </summary>
	/// <remarks>
	/// 此方法开始更新下一帧画面逻辑。
	/// 具体步骤为：
	/// 1. 更新键盘输入；  
	/// 2. 判断-更新新一波敌军；  
	/// 3. 更新所有Entity的行动。如所有飞机、子弹根据当前速度进行下一次移动。
	/// </remarks>
	void update();

	/// <summary>
	/// 碰撞逻辑更新函数。
	/// </summary>
	/// <remarks>
	/// 此方法在所有Entity位置更新后，判断碰撞状态并执行对应动作。
	/// 具体步骤为：
	/// 1. 判断并处理`自机、敌机、子弹`与`边界`的碰撞：  
	///   * 自机与自机狙敌机作出速度改变；  
	///   * 新兵敌机与子弹被删除（方法不一定相同）。  
	/// 2. 判断并处理`自机、敌机`与`子弹`的碰撞：  
	///   * 通过判断子弹所属的Camp与源飞机来处理伤害；  
	///   * 处理玩家得分。  
	/// 3. 判断并处理`自机`与`敌机`的碰撞：  
	///   * 敌机坠毁，获得对应得分；  
	///   * 玩家受到敌机剩余生命值的伤害。
	/// </remarks>
	void updateCollision();

	/// <summary>
	/// 状态逻辑更新函数。
	/// </summary>
	/// <remarks>
	/// 此方法在处理主逻辑与碰撞后，判断当前状态（State）并执行对应动作。
	/// 具体步骤为：
	/// 1. 处理敌机状态：  
	///   * 判断飞机状态(Alive, Dead, Vanished)；  
	///   * 若为非存活状态，判断是否产生爆炸动画。  
	/// 2. 处理子弹状态：  
	///   * 判断子弹是否为"End"状态并决定是否销毁。  
	///   * 子弹在被销毁时，可能会通过析构函数调用<see cref="Action"/>。  
	/// 3. 判断自机是否坠毁：  
	///   * 坠毁后，调用<see cref="Action_Plane_Explode"/>动画，传入gameover函数作为回调函数；  
	/// 4. 处理所有<see cref="actions"/>：  
	///   * 由于EGE图形库的BUG限制，只能在这里通过遍历所有Actions，处理他们是否达到"End"状态。  
	///   * 对于"End"状态的Action,将其销毁，并调用对应的回调函数。  
	/// </remarks>
	void updateState();
	
	/// <summary>
	/// 渲染主入口函数。
	/// </summary>
	/// <remarks>
	/// 此方法调用各子部件对应的渲染函数，渲染出完整的一帧画面。
	/// </remarks>
	void render();
	
	/// <summary>
	/// 清除World的所有状态。
	/// </summary>
	/// <remarks>
	/// 此方法清除World所有相关变量的状态，为下一次初始化作准备。
	/// 
	/// 目前的实现是销毁所有相关指针托管的资源，并将容器置空。
	/// </remarks>
	void clearWorld();
	
	/// <summary>
	/// 渲染Game Over界面。
	/// </summary>
	/// <remarks>
	/// 游戏结束后调用此方法渲染结束界面。
	///
	/// 内容包括背景、当前得分、评级及下一步的按钮（Q退出 R重新开始）。
	/// 
	/// 评级由<see cref="difficultyLevel"/>决定，如下：
	/// * 1: 朝鲜飞行员  
	/// * 2: 初级飞行员  
	/// * 3: 中级飞行员    
	/// * 4: 高级飞行员
	/// * 4 or more: 王牌飞行员
	/// </remarks>
	void renderOverInterface();

	/* ------------- get & set --------------*/
	/// <summary>
	/// 返回游戏预设FPS。
	/// </summary>
	/// <returns>
	/// 当前FPS值。
	/// </returns>
	int fps();
	
	/// <summary>
	/// 获取窗口宽度。
	/// </summary>
	/// <returns>
	/// 返回当前设置分辨率对应的宽度。
	/// </returns>
	int windowWidth();

	/// <summary>
	/// 获取窗口高度。
	/// </summary>
	/// <returns>
	/// 返回当前设置分辨率对应的高度。
	/// </returns>
	int windowHeight();
	
	/// <summary>
	/// 获取游戏中字体高度。目前均设为同一高度。
	/// </summary>
	/// <returns>
	/// 返回字体的高度。
	/// </returns>
	int fontHeight();
	
	/// <summary>
	/// 返回游戏进行状态
	/// </summary>
	/// <returns>
	/// 返回游戏是否正在进行中
	/// </returns>
	bool get_running();

	/* ------------- public fields --------------*/
	/// <summary>
	/// 当前游戏分数。
	/// </summary>
	/// <remarks>
	/// 分数的获得方式有以下几种：
	/// 1. 子弹击中敌机。按敌机受到的伤害获得分数。  
	/// 2. 敌机坠毁。根据敌机种类获得一定分数。  
	/// 
	/// 但与此同时，自己飞机受到伤害时，也会根据伤害扣除相应的分数。
	/// </remarks>
	int score;

	/// <summary>
	/// 当前的难度等级。
	/// </summary>
	/// <remarks>
	/// 难度等级越高，刷新的敌机数量越多，间隔越短，同时敌机将开始表现出各种不同的行为。
	/// 
	/// 同时，根据不同的难度等级，游戏结束后将授予不同的称号。
	/// 
	/// 难度等级的计算方式为：
	/// * 当 `(等级的开方) <= (分数) / (1000 * (1 + (等级) / 5) * (等级))` 时， 难度等级 + 1。
	/// * 这样，等级的更新速度大致为 `等级^1.5` （`等级 / 5`因子的影响较小）。  
	/// * 作为对比，飞机数量的增加速度（对应涨分速度）为 `2 * 等级 + (等级 + 1) / 2`。
	/// 
	/// > 未来，可以在达到一定难度等级后，刷出BOSS。
	/// </remarks>
	size_t difficultyLevel;

	/// <summary>
	/// 键盘输入控制器。
	/// </summary>
	InputController inputCtrl;

	/// <summary>
	/// 玩家飞机实例的托管指针。
	/// </summary>
	Plane_Player* player_plane;

	/// <summary>
	/// 指向当前被追踪的敌机的指针。
	/// </summary>
	/// <remarks>
	/// 当自机子弹击中一个敌机后，对应敌机将被设为追踪状态，用此指针来进行托管。
	/// 
	/// 被追踪的敌机将会将其当前状态（HP）显示在屏幕上。一段时间后，自动取消追踪。
	/// 
	/// 若为nullptr，表示当前未追踪任何敌机。
	/// </remarks>
	Plane* focused_enemy;
	
	/// <summary>
	/// 存储所有敌机基类指针的链表。
	/// </summary>
	/// <remarks>
	/// 所有新构造的敌机（主要通过new）将被自动放入这个链表中。
	/// </remarks>
	std::list<Plane*> enemy_planes;
	
	/// <summary>
	/// 存储所有子弹基类指针的链表。
	/// </summary>
	/// <remarks>
	/// 链表中的子弹不分敌我，通过子弹存储的源飞机指针判定阵营。
	/// 
	/// 所有新构造的子弹（主要通过new）将被自动放入这个链表中。
	/// </remarks>
	std::list<Bullet*> bullets;

	/// <summary>
	/// 存储所有Action基类指针的链表。
	/// </summary>
	/// <remarks>
	/// 最初，想通过action在触发条件后自动`delete this`来"自杀"的方法触发回调函数。
	/// 但受限于EGE的实现机制，这样做会引起指针悬挂BUG。
	/// 
	/// 因此，换用一个链表来存储指针，此链表仅用来检查Action状态，通过<see cref="updateState"/>函数来进行销毁。
	/// </remarks>
	std::list<Action*> actions; // only for end check

private:
	/// <summary>
	/// 渲染游戏背景。
	/// </summary>
	/// <remarks>
	/// 游戏背景是滚动的，实现方式为：
	/// 
	/// 两张相同的背景图拼接在一起，拼接处的水平线的y轴坐标从上往下不断移动。到达底端后，y轴重新设为0。
	/// </remarks>
	void renderBackground();

	/// <summary>
	/// 渲染游戏UI。
	/// </summary>
	/// <remarks>
	/// UI的渲染由以下几部分组成： 
	/// 1. 当前飞机的HP数据；  
	/// 2. 当前游戏得分数据；  
	/// 3. 当前被追踪状态的敌机的HP数据。
	/// 
	/// 其中，当前被追踪的敌机由<see cref="focused_enemy"/>指针控制。当指针不为空时，追踪指针指向的飞机的数据。
	/// 同时，函数会在一段时间后自动将指针置空，避免一直显示飞机数据。
	/// </remarks>
	void renderUI();

	/// <summary>
	/// 检测一个Entity是否与边界发生碰撞。
	/// </summary>
	/// <remarks>
	/// 可以以内部碰撞和外部碰撞两种方式检测。
	/// 
	/// 当leftRight与upDown都为false时，表示不检测，返回false（没有碰撞到墙壁）。.
	/// </remarks>
	/// <param name="e">		 [in,out] 被检测的Entity的指针。. </param>
	/// <param name="leftRight"> (可选) 检测是否与左右边界碰撞。默认为真。. </param>
	/// <param name="upDown">    (可选) 检测是否与上下边界碰撞。默认为真。. </param>
	/// <param name="isOuter">   (可选) 为真时，检测Entity是否已超出边界外；为假时，检测Entity是否在内侧与边界碰撞。. </param>
	/// <returns>
	/// 返回指定条件下的碰撞检测结果。
	/// </returns>
	bool checkBackgroundCollision(Entity* e, bool leftRight = true, bool upDown = true, bool isOuter = false); // collide if return true

	/// <summary>
	/// 产生新一波敌军。
	/// </summary>
	/// <remarks>
	/// 函数中有一个计时器用来控制刷新冷却。
	///
	/// 敌军的刷新数量由当前的<see cref="difficultyLevel"/>控制。同时难度等级也会在这个函数中根据当前分数更新。
	/// 
	/// 对于新兵飞机与自机狙飞机，他们有不同的刷新机制，分别为：
	/// * 新兵飞机： 始终从屏幕最上方出现，x轴位置随机。
	/// * 自机狙飞机： 会在屏幕上方或左右随机出现。上方出现时，x轴随机；左右边出现时，y轴随机（不会超过屏幕的上1/3位置）。
	/// </remarks>
	void newEnemyWave();

	/// <summary>
	/// 设置游戏状态为“结束”。
	/// </summary>
	void gameOver();

private:
	/// <summary>
	/// 表征当前游戏状态。
	/// </summary>
	bool running;
};

extern World world;