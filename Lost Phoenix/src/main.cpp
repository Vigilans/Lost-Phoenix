#include <ctime>
#include <fstream>
#include <graphics.h>
#include <ege/fps.h>
#include "World.h"

using namespace std;

World world;
ostream& getCurrentTime(ostream&);

int main(int argc, const char* argv[ ])
{
	//try
	//{
		mainProcess:
		if (world.initialize("All Hail Finxin!", GAME_FPS, WINDOW_WIDTH, WINDOW_HEIGHT))
		{
			world.renderMenu( );
			for (fps ui_fps; world.is_running( ); delay_fps(world.get_fps( )))
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
	//}
	//catch (exception& e)
	//{
	//	ofstream ferr("error log.txt");
	//	ferr << "Exception occured: " << e.what( ) << '\t' << getCurrentTime << '\n';
	//	ferr.close( );
	//	return 1;
	//}

	return 0;
}

ostream& getCurrentTime(ostream& os)
{
	const time_t timeSec = time(NULL);
	tm time;
	localtime_s(&time, &timeSec);
	return os << time.tm_year + 1900 << "-" << time.tm_mon + 1 << "-" << time.tm_mday << " " << time.tm_hour << ":" << time.tm_min << ":" << time.tm_sec;
}