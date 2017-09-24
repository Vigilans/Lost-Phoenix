/*! \mainpage Main Page
*
* \section intro_sec 简介
*
* 这是一个由EGE图形库编写的简易飞机对战游戏。
*
* \section build_sec 构建
*
* 将项目Clone/Download到本地后，请先运行restore_dependencies.ps1，获取EGE图形库与json库到本地项目中。
* * EGE图形库外链来自http://pan.seu.edu.cn，为VS2017版，因此最好使用Visual Studio 2017进行生成。
*
* 
* --------
* 关于项目的更多细节与结构介绍，请参见实践报告。
*/

#include <graphics.h>
#include <ege/fps.h>
#include "World.h"

World& world = *new World;

int main(int argc, const char* argv[ ])
{
	mainProcess:
	if (world.initialize())
	{
		world.renderMenu( );
		for (fps ui_fps; world.is_running( ); delay_fps(world.fps( )))
		{
			world.update( );
			world.updateCollision( );
			world.updateState( );
			world.render( );
		}
		world.clearWorld( );
		world.renderOverInterface( );
	}
	if(world.get_running( ))
		goto mainProcess;

	return 0;
}