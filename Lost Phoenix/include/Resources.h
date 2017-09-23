#pragma once
#pragma warning(disable:4244) // disable double->int conversion warning
#include "Vector2D.hpp"

namespace ege
{
	class IMAGE;
	typedef IMAGE* PIMAGE;
};

/// <summary>
/// 表征图像材质的结构体。
/// </summary>
struct Texture
{
	ege::PIMAGE image; ///< 保存对应图片的图像指针。
	Vector2D hitBox; ///< 保存图片长与宽的矩形矢量。
	
	/// <summary>
	/// 保证可以默认构造，声明为=default的构造函数。
	/// </summary>
	Texture() = default;
	
	/// <summary>
	/// 保证Texture结构体能继续使用Aggregate Initialization的构造函数。
	/// </summary>
	Texture(ege::PIMAGE image, Vector2D hitBox) : image(image), hitBox(hitBox) { }
	
	/// <summary>
	/// 从材质ID索引找到对应材质的显式转换构造函数。
	/// </summary>
	/// <param name="id"> 材质的唯一标识ID。 </param>
	explicit Texture(int id);
};

/// <summary>
/// 根据ID获取材质。采用Lazy Load机制。
/// </summary>
/// <param name="id"> 材质的唯一标识ID。 </param>
/// <returns>
/// 唯一标识ID对应的材质。
/// </returns>
Texture getTexture(int id);

/// <summary>
/// 切割材质。
/// </summary>
/// <remarks>
/// 从材质中切割一块矩形子材质。
/// 
/// 基准点为矩形自材质左上角坐标。
/// </remarks>
/// <param name="texture"> 待切割的材质。 </param>
/// <param name="x">	 被切割材质基准点x坐标。 </param>
/// <param name="y"> 被切割材质基准点y坐标。 </param>
/// <param name="w">	 欲切割下来的宽度。 </param>
/// <param name="h">	 欲切割下来的高度。 </param>
/// <returns>
/// 切割后的材质。
/// </returns>
Texture splitTexture(Texture texture, int x, int y, int w, int h);

/// <summary>
/// 切割材质。封装了一个接收两个Vector2D参数的更良好的接口。
/// </summary>
/// <param name="texture"> 待切割的材质。 </param>
/// <param name="refPos">  被切割材质基准点（矩形左上角）坐标。 </param>
/// <param name="hitBox">  欲切割矩形的长宽矢量。 </param>
/// <returns>
/// 切割后的材质。
/// </returns>
inline Texture splitTexture(Texture texture, Vector2D refPos, Vector2D hitBox) { return splitTexture(texture, refPos.x, refPos.y, hitBox.x, hitBox.y); }

/// <summary>
/// 封装了游戏全局与所有实体设置的名空间。 所有获取默认设置的方法采用 *Lazy Load（延时加载）* 机制。 **推荐参考详细描述来获取完整信息** 。
/// </summary>
/// <remarks>
/// 这个名空间将游戏的所有设置用几个struct进行表示，以提高可读性与扩展性。
/// 
/// 所有默认设置保存在json文件中，放置于/settings文件夹下。
/// 相比于用一个宏头文件保存设置，使用json的可读性与结构性更强，同时在修改相关设置数据时，也不需要 **全部重新编译一遍** 。
/// 
/// 运行游戏后，会陆续从json文件中读取相关设置，在堆上用一块专门的内存保存。具体机制为：
/// * 程序开始运行时，读取所有材质的索引信息到<see cref="TextureInfo"/>的std::map中，为此后设置的Lazy Load作准备。
/// * Setting名空间中提供几个获取**默认设置引用**的函数。此时尚未加载任何设置。  
/// * 当外部类调用任一Setting名空间的函数后，若未加载，则加载设置到堆上的一块稳定内存区域中，并返回引用。这有两个效果：
///   - 所有设置都采取了Lazy Load机制，这避免了在ege图形库未初始化窗口前读取材质而造成bug，同时节省内存。  
///   - 默认设置始终返回堆上一块稳定内存的引用，达到一处保存多处使用的效果，同时减少拷贝。
/// 
/// 
/// ---------
/// 
/// 对于飞机与子弹这样的实体，设置还有另一层作用：在一个实例构造函数中使用。
/// 实体可能有很多的属性，若全部放在构造函数中显得十分臃肿；同时，要新增一个属性，需要修改很多地方，容易出错。
/// 
/// 因此，飞机与子弹的构造函数设计为只需要传一个 `设置` 与其他 `非设置信息` 进去即可。
/// 在传入设置前，可以对设置的实例进行修改，达到修改飞机子弹相关数据的效果。
/// </remarks>
namespace Settings
{
	/// <summary>
	/// 游戏全局设置，主要包含UI与相关时间设置。
	/// </summary>
	struct General
	{
		struct
		{
			char* title; ///< 游戏标题。
			int fps; ///< 游戏的FPS。
			Vector2D resolution; ///< 游戏窗口的分辨率。
			int fontHeight; ///< UI的字体高度。
		} UI;

		struct
		{
			int enemyInfoDuration; ///< 被追踪敌机的追踪状态保留时间。
			int enemyWaveCoolDown; ///< 敌机每一波刷新的基础冷却时间。
			int bgShiftSpeed; ///< 背景的移动速度。
		} times;
	};
	/// <summary>
	/// 所有游戏背景材质设置。
	/// </summary>
	struct BgTextures
	{
		Texture menu; ///< 主菜单背景材质。
		Texture gaming; ///< 正式游戏期间背景材质。
		Texture gameOver; ///< 游戏结束背景材质。
	};
	
	/// <summary>
	/// 所有动画、<see cref="Action"/>相关材质设置。
	/// </summary>
	struct AnimeTextures
	{
		Texture explosion; ///< 爆炸贴图材质。
	}; 
	
	/// <summary>
	/// 子弹的设置基类。
	/// </summary>
	struct Bullet
	{
		Texture texture; ///< 子弹材质。
		int attack; ///< 子弹攻击力。
		int speed; ///< 子弹移动速率（速度的模）。
		int coolDown; ///< 飞机射击冷却。
	};
	
	/// <summary>
	/// 飞机的设置基类。
	/// </summary>
	struct Plane
	{
		int camp; ///< 飞机所属阵营，与Camp枚举一一对应。
		Texture texture; ///< 飞机材质。
		int health; ///< 飞机HP上限。
		int speed; ///< 飞机移动速率（速度的模）。
		Bullet bulletSetting; ///< 飞机默认子弹设置。
		int score; ///< 飞机坠毁分数。
	};

	const Settings::General& general(); ///< 获取默认的全局游戏设置。采取Lazy Load机制。
	const Settings::BgTextures& bgTextures(); ///< 获取默认的背景材质设置。采取Lazy Load机制。
	const Settings::AnimeTextures& animeTextures(); ///< 获取默认的动画材质设置。采取Lazy Load机制。
	const Settings::Plane& player( ); ///< 获取默认的玩家飞机设置。采取Lazy Load机制。
	const Settings::Plane& enemy_junior( ); ///< 获取默认的新兵敌机设置。采取Lazy Load机制。
	const Settings::Plane& enemy_autoTarget( ); ///< 获取默认的自机狙敌机设置。采取Lazy Load机制。
};