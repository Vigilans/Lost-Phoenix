#pragma once
#include "Resources.h"
#include <map>
#include <memory>

namespace Settings
{
	/// <summary>
	/// 材质的设置源，可以用来构造一个完整的材质。
	/// </summary>
	struct TextureInfo
	{
		std::wstring path; ///< 材质的路径，采用Unicode字符，可为相对路径（相对的根路径根据F5与Ctrl+F5变化）
		Vector2D hitbox; ///< 材质的分辨率。
		Vector2D expectHitBox = Vector2D(); ///< 材质经缩放后要达到的分辨率。为零向量时表示不缩放。
	};
}

/// <summary>
/// 资源加载器。仅在<see cref="Resources.cpp"/>中使用。在堆上一块稳定内存托管所有材质及设置资源。
/// </summary>
class ResourcesLoader
{
public:	
	/// <summary>
	/// 默认构造函数，用来在程序开始时加载所有材质设置到<see cref="TextureInfo"/>。
	/// </summary>
	ResourcesLoader();
	
	/// <summary>
	/// 析构函数，清除堆上所有材质及设置。
	/// </summary>
	~ResourcesLoader();
	
	/// <summary>
	/// 通过元信息加载材质。
	/// </summary>
	/// <remarks>
	/// 当w_to或h_to中有任意一项为0时，表示不缩放。
	/// </remarks>
	/// <param name="imagePath"> 材质的路径，采用Unicode。 </param>
	/// <param name="w_raw">	 材质的原分辨率宽度。 </param>
	/// <param name="h_raw">	 材质的原分辨率高度。 </param>
	/// <param name="w_to">  (可选) 期望缩放到的分辨率宽度。 </param>
	/// <param name="h_to">	 (可选) 期望缩放到的分辨率高度。 </param>
	/// <returns>
	/// 加载成功后，返回加载而得的材质。
	/// </returns>
	Texture loadTexture(const wchar_t* imagePath, int w_raw, int h_raw, int w_to = 0, int h_to = 0);
	
	/// <summary>
	/// 通过<see cref="TextureInfo"/>加载材质。
	/// </summary>
	/// <remarks>
	/// 封装了一个接收材质设置的更良好的接口。在类体中定义是默认inline的。
	/// 
	/// TODO: 用参数转发(forwarding)实现这个重载。
	/// </remarks>
	/// <param name="setting"> 材质的设置源。 </param>
	/// <returns>
	/// 加载成功后，返回加载而得的材质。
	/// </returns>
	Texture loadTexture(Settings::TextureInfo setting)
	{ 
		return loadTexture(setting.path.c_str(), setting.hitbox.x, setting.hitbox.y, setting.expectHitBox.x, setting.expectHitBox.y);
	}
	
	/// <summary>
	/// 加载所有材质设置。在程序开始时通过<see cref="constructor"/>调用。
	/// </summary>
	void loadTextureSettings();
	void loadGeneralSettings(); ///< 加载全局设置。通过Lazy Load机制延时调用。
	void loadBgTextures(); ///< 加载所有背景材质。通过Lazy Load机制延时调用。
	void loadAnimeTextures(); ///< 加载所有动画材质。通过Lazy Load机制延时调用。
	void loadPlaneSettings(); ///< 加载所有飞机设置。通过Lazy Load机制延时调用。
	const std::map<int, Texture>& loadAllTextures(); ///< 一次性加载所有材质。现为Depreciated。

	// settings loaded
	struct
	{
		std::unique_ptr<Settings::General> pGeneral; ///< 默认全局设置。
		std::unique_ptr<Settings::BgTextures> pBgTextures; ///< 所有背景材质。
		std::unique_ptr<Settings::AnimeTextures> pAnimeTextures; ///< 所有动画材质。
		std::unique_ptr<Settings::Plane> pPlayer; ///< 默认玩家飞机设置。
		std::unique_ptr<Settings::Plane> pEnemyJunior; ///< 默认新兵敌机设置。
		std::unique_ptr<Settings::Plane> pEnemyAutoTarget; ///< 默认自机狙敌机设置。
		std::map<int, Settings::TextureInfo> mTextureInfos; ///< 保存所有材质索引设置。
	} settings; ///< 保存所有默认设置。所有外部类通过此处保存的设置的引用来获取默认设置。
	
	std::map<int, Texture> textures; ///< 保存所有已完整加载的材质。通过材质的ID进行检索。
};