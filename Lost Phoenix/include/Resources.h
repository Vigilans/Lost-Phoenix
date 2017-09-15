#pragma once
#pragma warning(disable:4244) // disable double->int conversion warning
#include "Vector2D.h"

/* ----------PARAMETERS---------- */

// General Settings
#define GAME_FPS							60
#define WINDOW_WIDTH							800
#define WINDOW_HEIGHT						600
#define UI_FONT_HEIGHT						20
#define UI_ENEMY_INFORMATION_SHOWTIME		1500
#define COOLDOWN_ENEMYWAVE_BASE				6000
#define SPEED_BACKGROUND_UPDATE				2

// Player Settings
#define SPEED_PLAYER_PLANE					7
#define HEALTH_PLAYER_PLANE					100
#define SPEED_PLAYER_BULLET					-10
#define ATTACK_PLAYER_BULLET				12
#define COOLDOWN_PLAYER_BULLET				200

// Enemy_Junior Settings
#define SPEED_ENEMY_JUNIOR_PLANE			1
#define HEALTH_ENEMY_JUNIOR_PLANE			12
#define SPEED_ENEMY_JUNIOR_BULLET			10
#define ATTACK_ENEMY_JUNIOR_BULLET			12
#define COOLDOWN_ENEMY_JUNIOR_BULLET			1100
#define SCORE_ENEMY_JUNIOR					30

// Enemy_AutoTarget Settings
#define SPEED_ENEMY_AUTOTARGET_PLANE			1
#define HEALTH_ENEMY_AUTOTARGET_PLANE		30
#define SPEED_ENEMY_AUTOTARGET_BULLET		6
#define ATTACK_ENEMY_AUTOTARGET_BULLET		20
#define COOLDOWN_ENEMY_AUTOTARGET_BULLET		1900
#define SCORE_ENEMY_AUTOTARGET				50

/* ----------PARAMETERS---------- */


/* ----------TEXTURES---------- */
namespace ege
{
	class IMAGE;
	typedef IMAGE* PIMAGE;
};

struct Texture
{
	ege::PIMAGE image;
	Vector2D hitBox;
};

const Texture getTexture(int id);

Texture cutOutTexture(int id, int x, int y, int w, int h);

#define MENU_ID								1000
#define MENU_PATH							L"assets/menu.jpg"
#define MENU_WIDTH_RAW						1024
#define MENU_HEIGHT_RAW						576

#define BACKGROUND_ID						1001
#define BACKGROUND_PATH						L"assets/bg.png"
#define BACKGROUND_WIDTH_RAW 				1280
#define BACKGROUND_HEIGHT_RAW				960

#define PLAYER_PLANE_ID						1002
#define PLAYER_PLANE_PATH					L"assets/player_plane.png"
#define PLAYER_PLANE_WIDTH_RAW				60
#define PLAYER_PLANE_HEIGHT_RAW				56

#define PLAYER_BULLET_ID						1003
#define PLAYER_BULLET_PATH					L"assets/player_bullet.png"
#define PLAYER_BULLET_WIDTH_RAW				30
#define PLAYER_BULLET_HEIGHT_RAW 			51

#define ENEMY_PLANE_JUNIOR_ID				1004
#define ENEMY_PLANE_JUNIOR_PATH				L"assets/enemy_plane_junior.png"
#define ENEMY_PLANE_JUNIOR_WIDTH_RAW			60
#define ENEMY_PLANE_JUNIOR_HEIGHT_RAW		61

#define ENEMY_BULLET_JUNIOR_ID				1005
#define ENEMY_BULLET_JUNIOR_PATH				L"assets/enemy_bullet_junior.png"
#define ENEMY_BULLET_JUNIOR_WIDTH_RAW		15
#define ENEMY_BULLET_JUNIOR_HEIGHT_RAW 		31

#define ENEMY_PLANE_AUTOTARGET_ID		 	1006
#define ENEMY_PLANE_AUTOTARGET_PATH		 	L"assets/enemy_plane_autoTarget.png"
#define ENEMY_PLANE_AUTOTARGET_WIDTH_RAW	 	80
#define ENEMY_PLANE_AUTOTARGET_HEIGHT_RAW	52

#define ENEMY_BULLET_AUTOTARGET_ID		  	1007
#define ENEMY_BULLET_AUTOTARGET_PATH		  	L"assets/enemy_bullet_autoTarget.png"
#define ENEMY_BULLET_AUTOTARGET_WIDTH_RAW 	15
#define ENEMY_BULLET_AUTOTARGET_HEIGHT_RAW	15

#define PLANE_EXPLOSION_ID		  			1008
#define PLANE_EXPLOSION_PATH		  			L"assets/plane_explosion.png"
#define PLANE_EXPLOSION_WIDTH_RAW 			256
#define PLANE_EXPLOSION_HEIGHT_RAW			256

#define GAMEOVER_ID		  					1009
#define GAMEOVER_PATH		  				L"assets/gameover.jpg"
#define GAMEOVER_WIDTH_RAW 					800
#define GAMEOVER_HEIGHT_RAW					600

/* ----------TEXTURES---------- */