#pragma once
#include <list>
#include "InputController.h"
#include "Player.h"	
#include "Enemy_Junior.h"
#include "Enemy_AutoTarget.h"

class Action;

class World
{
public:
	bool initialize(const char* Title, int fps, int w, int h);
	bool is_running( );
	void renderMenu( );
	void update( );
	void updateCollision( );
	void updateState( );
	void render( );
	void clearWorld( );
	void renderOverInterface( );

	/* ------------- get & set --------------*/
	int get_fps( ) { return game_fps; }
	bool get_running( ) { return running; }

	/* ------------- public data members --------------*/
	int score;
	size_t difficultyLevel;
	InputController inputCtrl;
	Plane_Player* player_plane;
	Plane* focused_enemy;
	std::list<Plane*> enemy_planes; // newly "new"ed enemy planes will be automatically pushed back in this list
	std::list<Bullet*> bullets; // newly "new"ed bullets will be automatically pushed back in this list
	std::list<Action*> actions; // only for end check

	
private:
	void renderBackground( );
	void renderUI( );
	bool checkBackgroundCollision(Entity* e, bool leftRight = true, bool upDown = true, bool isOuter = false); // collide if return true
	void newEnemyWave( );
	void gameOver( );

private:
	int windowWidth;
	int windowHeight;
	int game_fps;
	bool running;
};

extern World world;