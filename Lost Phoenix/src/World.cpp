#include "World.h"
#include <typeinfo>
#include <ctime>
#include <graphics.h>
#include <ege/fps.h>
#include "Actions.h"

bool World::initialize(const char* Title, int fps, int w, int h)
{
	game_fps = fps;
	windowWidth = w;
	windowHeight = h;
	running = true;
	score = 0;
	difficultyLevel = 1;

	initgraph(windowWidth, windowHeight);
	setbkmode(TRANSPARENT);
	setrendermode(RENDER_MANUAL);
	srand(time(NULL));
	HWND hWnd = getHWnd( ); // 获得窗口句柄
	SetWindowText(hWnd, Title);// 使用 API 函数修改窗口名称

	player_plane = new Plane_Player;
	focused_enemy = NULL;
	Action_Plane_Explode::initializeModels( );

	return true;
}

bool World::is_running( )
{
	return running && is_run( );
}

void World::renderMenu( )
{
	putimage(0, 0, getTexture(MENU_ID).image);
	setbkmode(TRANSPARENT);
	setcolor(LIGHTGRAY);
	settextjustify(LEFT_TEXT, TOP_TEXT);
	setfont(-80, 0, "Arial");
	outtextxy(220, 150, "Plane War");
	setfont(0, 0, "Arial");
	outtextxy(300, 250, "W S A D —— move");
	outtextxy(300, 300, "SPACE —— shoot");
	outtextxy(280, 400, "press any key to continue");
	getch( );
}

void World::update( )
{
	if (!running)
		return;

	/*------------HANDLE KEYBOARD INPUT------------*/
	this->inputCtrl.updateInput( );
	/*------------HANDLE KEYBOARD INPUT------------*/
	
	/*------------HANDLE ENEMY PLANE SPAWN------------*/
	this->newEnemyWave( );
	/*------------HANDLE ENEMY PLANE SPAWN------------*/

	/*------------HANDLE MOVEMENT------------*/
	player_plane->update( );
	for (auto& elem : enemy_planes)
		elem->update( );
	for (auto& elem : bullets)
		elem->update( );
	/*------------HANDLE MOVEMENT------------*/

}

void World::updateCollision( )
{
	if (!running)
		return;

	// ----- PLAYER COLLISION WITH BACKGROUND
	if (checkBackgroundCollision(player_plane, true, false))
	{
		player_plane->setXPos(player_plane->getXPos( ) > 0 ? windowWidth - player_plane->getXHitBox( ) : 0);
		player_plane->setXVel(0);
	}
	if (checkBackgroundCollision(player_plane, false, true))
	{
		player_plane->setYPos(player_plane->getYPos( ) > 0 ? windowHeight - player_plane->getYHitBox( ) : 0);
		player_plane->setYVel(0);
	}

	// ----- ENEMY COLLISION WITH BACKGROUND
	for (auto plane: enemy_planes)
	{
		if (typeid(*plane) == typeid(Plane_Enemy_Junior))
		{
			if (checkBackgroundCollision(plane, true, true, true))
			{
				plane->setState(PlaneState::Vanished);
			}
			continue;
		}

		if (typeid(*plane) == typeid(Plane_Enemy_AutoTarget))
		{
			if (checkBackgroundCollision(plane, true, false))
			{
				plane->setXPos(plane->getXPos( ) - plane->getXVel( ));
				plane->setXVel(-plane->getXVel( ));
			}
			if (checkBackgroundCollision(plane, false, true))
			{
				plane->setYPos(plane->getYPos( ) - plane->getYVel( ));
				plane->setYVel(-plane->getYVel( ));
			}
			continue;
		}
	}

	// ----- BULLET COLLISION WITH BACKGROUND
	for (auto bullet : bullets)
	{
		if (checkBackgroundCollision(bullet, true, true, true))
		{
			bullet->end = true;
		}
	}

	// ----- ENEMY COLLISION WITH BULLET
	for (auto plane :enemy_planes)
	{
		for (auto bullet :bullets)
		{
			if (plane->getAlly( ) != bullet->getAlly( ) && plane->getState( ) == PlaneState::Alive && judgeCollision(plane, bullet))
			{
				focused_enemy = plane;
				dealDamage(plane, bullet);
			}
		}
	}

	// ----- PLAYER COLLISION WITH BULLET
	for (auto bullet: bullets)
	{
		if (judgeCollision(player_plane, bullet) && player_plane->getState( ) == PlaneState::Alive && bullet->getAlly( ) == Ally::Enemy)
		{
			dealDamage(player_plane, bullet);
			new Action_Plane_Explode(player_plane, false);
		}
	}

	// ----- PLAYER COLLISION WITH ENMEY
	for (auto enemy : enemy_planes)
	{
		if (judgeCollision(player_plane, enemy) && player_plane->getState( ) == PlaneState::Alive)
		{
			dealDamage(player_plane, enemy);
		}
	}
}

void World::updateState( )
{
	if (!running)
		return;

	/*------------HANDLE ENEMIES------------*/
	for (auto iter = enemy_planes.begin( ); iter != enemy_planes.end( ); iter == enemy_planes.end( ) ? iter : ++iter)
	{
		auto plane = *iter;
		switch (plane->getState( ))
		{
		case PlaneState::Dead: 
			if (typeid(*plane) == typeid(Plane_Enemy_Junior))
				score += SCORE_ENEMY_JUNIOR;
			else if (typeid(*plane) == typeid(Plane_Enemy_AutoTarget))
				score += SCORE_ENEMY_AUTOTARGET;
			new Action_Plane_Explode(plane);  // explode结束后自动delete plane 
			iter = enemy_planes.erase(iter);
			break;
		case PlaneState::Vanished: 
			delete plane;
			iter = enemy_planes.erase(iter);
			break;
		}
	}
	/*------------HANDLE ENEMIES------------*/

	/*------------HANDLE BULLETS------------*/
	for (auto iter = bullets.begin( ); iter != bullets.end( ); iter == bullets.end( ) ? iter : ++iter)
	{
		auto bullet = *iter;
		if (bullet->end)
		{
			delete bullet;
			iter = bullets.erase(iter);
		}
	}
	/*------------HANDLE BULLETS------------*/

	/*------------HANDLE PLAYER------------*/
	if (player_plane->getState( ) == PlaneState::Dead)
	{
		new Action_Plane_Explode(player_plane, false, 15, []( ) { world.gameOver( ); });
		player_plane->setState(PlaneState::Vanished); // 防止重复进入这个条件
	}
	/*------------HANDLE PLAYER------------*/

	/*------------HANDLE ACTION END------------*/
	for (auto iter = actions.begin( ); iter != actions.end( ); iter == actions.end( ) ? iter : ++iter)
	{
		auto action = *iter;
		if (action->end)
		{
			delete action;
			iter = actions.erase(iter);
		}
	}
	/*------------HANDLE ACTION END------------*/
}

void World::render( )
{
	if (!running)
		return;

	cleardevice( );
	// render background
	this->renderBackground( );
	// render player plane
	player_plane->draw( );
	// render enemy planes
	for (auto& elem : enemy_planes)
		elem->draw( );
	// render bullets
	for (auto& elem : bullets)
		elem->draw( );
	// render UI
	this->renderUI( );
}

void World::clearWorld( )
{
	delete player_plane;
	for (auto& elem : enemy_planes)
		delete elem;
	for (auto& elem : bullets)
		delete elem;
	for (auto& elem : actions)
		delete elem;
	enemy_planes.clear( );
	bullets.clear( );
	actions.clear( );
}

void World::renderOverInterface( )
{
	putimage(0, 0, getTexture(GAMEOVER_ID).image);

	const char* grade;
	switch (difficultyLevel)
	{
	case 1: grade = "朝鲜飞行员"; break;
	case 2: grade = "初级飞行员"; break;
	case 3: grade = "中级飞行员"; break;
	default:grade = "高级飞行员"; break;
	}

	settextjustify(CENTER_TEXT, CENTER_TEXT);
	xyprintf(windowWidth / 2, windowHeight * 0.75, "得分: %d", score);
	xyprintf(windowWidth / 2, windowHeight * 0.75 + UI_FONT_HEIGHT, "称号: %s", grade);
	outtextxy(windowWidth / 2, windowHeight * 0.75 + 3*UI_FONT_HEIGHT, "Q - 退出  R - 重新开始游戏");

	for ( ; ; ) 
	{
		switch (getch( ))
		{
		case 'r':
		case 'R': running = true; return;
		case 'q':
		case 'Q': return;
		}
	}
}

void World::newEnemyWave( )
{
	static time_t startPoint = clock( );
	static time_t cooldown = COOLDOWN_ENEMYWAVE_BASE;
	static Vector2D juniorHitBox = getTexture(ENEMY_PLANE_JUNIOR_ID).hitBox;
	static Vector2D autoTargetHitBox = getTexture(ENEMY_PLANE_AUTOTARGET_ID).hitBox;

	if (sqrt(difficultyLevel) <= 1.0*world.score / (1000 * (1 + difficultyLevel*0.2) * difficultyLevel)) // n^1.5刷新速度
	{
		++difficultyLevel;
	}

	if (clock( ) - startPoint >= cooldown - 200 *difficultyLevel) // 2n + (n + 1)/2的涨分速度
	{
		int xPos;
		for (size_t i = 0; i < difficultyLevel + 2; ++i)
		{
			xPos = rand( ) % (windowWidth - (int)juniorHitBox.x);
			new Plane_Enemy_Junior(Vector2D(xPos, -juniorHitBox.y), Vector2D(0, SPEED_ENEMY_JUNIOR_PLANE)); // 自动放入敌机vector中
		}
		for (size_t i = 0; i < (difficultyLevel + 1) / 2; ++i)
		{
			xPos = rand( ) % (windowWidth - (int)autoTargetHitBox.x);
			new Plane_Enemy_AutoTarget(Vector2D(xPos, -1), Vector2D(SPEED_ENEMY_AUTOTARGET_PLANE, 0));
		}
		startPoint = clock( );
	}
}

void World::gameOver( )
{
	running = false;
}

void World::renderBackground( )
{
	static PIMAGE tmp = getTexture(BACKGROUND_ID).image;
	static int levelYPos = 0;
	putimage(0, levelYPos - windowHeight, tmp);
	putimage(0, levelYPos, tmp);
	levelYPos >= windowHeight ? levelYPos = 0 : levelYPos += SPEED_BACKGROUND_UPDATE;
}

void World::renderUI( )
{
	setfont(UI_FONT_HEIGHT, 0, "黑体");

	// render player health
	xyprintf(0, windowHeight - 2*UI_FONT_HEIGHT, "HP: %d / %d", player_plane->curHealth, player_plane->maxHealth);

	// render score
	xyprintf(0, windowHeight - UI_FONT_HEIGHT, "Score: %d", score);

	// render focused enemy health
	static const char* enemy_name;
	static int enemy_curHP;
	static int enemy_maxHP;
	static time_t showTimeStart = clock( );
	static bool begin = false;
	if (focused_enemy)
	{
		enemy_curHP = focused_enemy->curHealth;
		enemy_maxHP = focused_enemy->maxHealth;
		enemy_name = typeid(*focused_enemy).name( ) + 12; /* +12是为了去掉typeid生成的类名字前的"class Plane_" */
		begin = true;
		focused_enemy = NULL;
		showTimeStart = clock( );
	}
	if (begin && clock( ) - showTimeStart < UI_ENEMY_INFORMATION_SHOWTIME)
	{
		settextjustify(CENTER_TEXT, CENTER_TEXT);
		xyprintf(windowWidth / 2, windowHeight / 18, "%s: %d / %d", enemy_name, enemy_curHP, enemy_maxHP);
		settextjustify(LEFT_TEXT, TOP_TEXT);
	}
}

bool World::checkBackgroundCollision(Entity * e, bool leftRight, bool upDown, bool isOuter)
{ // leftRight表示检测左右碰撞, upDown表示检测上下碰撞，当都为false时，表示不检测，返回false（没有碰撞到墙壁）
	if (isOuter)
		return leftRight && (e->getXPos( ) + e->getXHitBox( ) < 0 || e->getXPos( ) > windowWidth) ||
			   upDown && (e->getYPos( ) + e->getYHitBox( ) < 0 || e->getYPos( ) > windowHeight);
	else
		return leftRight && (e->getXPos( ) < 0 || e->getXPos( ) + e->getXHitBox( ) > windowWidth) ||
			   upDown && (e->getYPos( ) < 0 || e->getYPos( ) + e->getYHitBox( ) > windowHeight);
}
