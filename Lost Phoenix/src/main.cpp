/*! \mainpage Lost Phoenix Main Page
*
* \section intro_sec Introduction
*
* This is the introduction.
*
* \section install_sec Installation
*
* \subsection step1 Step 1: Opening the box
*
* etc...
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