#pragma once

/// <summary>
/// 处理键盘输入的控制器类。
/// </summary>
class InputController
{
public:
	/// <summary>
	/// 用来与存储键位的数组一一对应的枚举。
	/// </summary>
	enum class Key
	{
		W, A, S, D, Space,
		Size /// 置于枚举的最后一位，用来代表枚举拥有的元素个数（除了Size）
	};

	/// <summary>
	/// 默认构造函数，用以初始化按键状态数组（全部置零）。
	/// </summary>
	InputController( );
	
	/// <summary>
	/// 从键盘更新输入。该函数会被<see cref="World::update"/>调用。
	/// </summary>
	/// <remarks>
	/// 此方法将遍历键盘按键消息队列，在状态数组中将对应按键状态设为true，同时将未搜索到按键的状态设为false。
	/// 
	/// 时间复杂度最差为k*n, k为按键消息队列size，n为按键枚举的size。
	/// </remarks>
	void updateInput( );
	
	/// <summary>
	/// 判断当前是否按下某个键。
	/// </summary>
	/// <param name="key"> 要检测的键位枚举值。 </param>
	/// <returns>
	/// 若按下则返回真。
	/// </returns>
	bool isKeyDown(Key key);

private:
	/// <summary>
	/// 存储某个按键对应的Virtual Key的数组。每个元素的索引号与<see cref="Key"/>枚举的对应枚举值一一对应。
	/// </summary>
	static int KeysEnum[(int)Key::Size];
	
	/// <summary>
	/// 存储按键状态的数组。Key枚举值对应元素为<see cref="Key"/>表示对应按键正被按下。
	/// </summary>
	bool m_KeyState[(int)Key::Size];
};