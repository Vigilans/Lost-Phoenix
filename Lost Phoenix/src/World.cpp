#include "World.h"
#include <typeinfo>
#include <ctime>
#include <graphics.h>
#include <ege/fps.h>
#include "Actions.h"

bool World::initialize()
{
	running = true;
	score = 0;
	difficultyLevel = 1;

	initgraph(windowWidth(), windowHeight());
	setbkmode(TRANSPARENT);
	setrendermode(RENDER_MANUAL);
	srand(time(nullptr));
	HWND hWnd = getHWnd(); // 获得窗口句柄
	SetWindowText(hWnd, Settings::general().UI.title);// 使用 API 函数修改窗口名称

	player_plane = new Plane_Player(Settings::player());
	return true;
}

bool World::is_running()
{
	return running && is_run();
}

void World::renderMenu()
{
	putimage(0, 0, Settings::bgTextures().menu.image);
	setbkmode(TRANSPARENT);
	setcolor(LIGHTGRAY);
	settextjustify(LEFT_TEXT, TOP_TEXT);
	setfont(-80, 0, "Arial");
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	outtextxy(windowWidth() / 2, windowHeight() / 5, "Lost Phoenix");
	settextjustify(LEFT_TEXT, TOP_TEXT);
	setfont(0, 0, "Arial");
	outtextxy(300, 250, "W S A D —— move");
	outtextxy(300, 300, "SPACE —— shoot");
	outtextxy(280, 400, "Press any key to continue");
	getch();
}

void World::update()
{
	if (!running)
		return;

	/*------------HANDLE KEYBOARD INPUT------------*/
	this->inputCtrl.updateInput();
	/*------------HANDLE KEYBOARD INPUT------------*/

	/*------------HANDLE ENEMY PLANE SPAWN------------*/
	this->newEnemyWave();
	/*------------HANDLE ENEMY PLANE SPAWN------------*/

	/*------------HANDLE MOVEMENT------------*/
	player_plane->update();
	for (auto& elem : enemy_planes)
		elem->update();
	for (auto& elem : bullets)
		elem->update();
	/*------------HANDLE MOVEMENT------------*/

}

void World::updateCollision()
{
	if (!running)
		return;

	// ----- PLAYER COLLISION WITH BACKGROUND
	if (checkBackgroundCollision(player_plane, true, false))
	{
		player_plane->setXPos(player_plane->getXPos() > 0 ? windowWidth() - player_plane->getXHitBox() : 0);
		player_plane->setXVel(0);
	}
	if (checkBackgroundCollision(player_plane, false, true))
	{
		player_plane->setYPos(player_plane->getYPos() > 0 ? windowHeight() - player_plane->getYHitBox() : 0);
		player_plane->setYVel(0);
	}

	// ----- ENEMY COLLISION WITH BACKGROUND
	for (auto plane : enemy_planes)
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
				plane->setXPos(plane->getXPos() - plane->getXVel());
				plane->setXVel(-plane->getXVel());
			}
			if (checkBackgroundCollision(plane, false, true))
			{
				plane->setYPos(plane->getYPos() - plane->getYVel());
				plane->setYVel(-plane->getYVel());
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
	for (auto plane : enemy_planes)
	{
		for (auto bullet : bullets)
		{
			if (plane->getCamp() != bullet->getCamp() && plane->getState() == PlaneState::Alive && Entity::judgeCollision(plane, bullet))
			{
				focused_enemy = plane;
				dealDamage(plane, bullet);
			}
		}
	}

	// ----- PLAYER COLLISION WITH BULLET
	for (auto bullet : bullets)
	{
		if (Entity::judgeCollision(player_plane, bullet) && player_plane->getState() == PlaneState::Alive && bullet->getCamp() == Camp::Enemy)
		{
			dealDamage(player_plane, bullet);
			new Action_Plane_Explode(player_plane, false);
		}
	}

	// ----- PLAYER COLLISION WITH ENMEY
	for (auto enemy : enemy_planes)
	{
		if (Entity::judgeCollision(player_plane, enemy) && player_plane->getState() == PlaneState::Alive)
		{
			dealDamage(player_plane, enemy);
		}
	}
}

void World::updateState()
{
	if (!running)
		return;

	/*------------HANDLE ENEMIES------------*/
	for (auto iter = enemy_planes.begin(); iter != enemy_planes.end(); iter == enemy_planes.end() ? iter : ++iter)
	{
		auto plane = *iter;
		switch (plane->getState())
		{
		case PlaneState::Dead:
			if (typeid(*plane) == typeid(Plane_Enemy_Junior))
				score += Settings::enemy_junior().score;
			else if (typeid(*plane) == typeid(Plane_Enemy_AutoTarget))
				score += Settings::enemy_autoTarget().score;
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
	for (auto iter = bullets.begin(); iter != bullets.end(); iter == bullets.end() ? iter : ++iter)
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
	if (player_plane->getState() == PlaneState::Dead)
	{
		new Action_Plane_Explode(player_plane, false, 15, []() { world.gameOver(); });
		player_plane->setState(PlaneState::Vanished); // 防止重复进入这个条件
	}
	/*------------HANDLE PLAYER------------*/

	/*------------HANDLE ACTION END------------*/
	for (auto iter = actions.begin(); iter != actions.end(); iter == actions.end() ? iter : ++iter)
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

void World::render()
{
	if (!running)
		return;

	cleardevice();
	// render background
	this->renderBackground();
	// render player plane
	player_plane->draw();
	// render enemy planes
	for (auto& elem : enemy_planes)
		elem->draw();
	// render bullets
	for (auto& elem : bullets)
		elem->draw();
	// render UI
	this->renderUI();
}

void World::clearWorld()
{
	delete player_plane;
	for (auto& elem : enemy_planes)
		delete elem;
	for (auto& elem : bullets)
		delete elem;
	for (auto& elem : actions)
		delete elem;
	enemy_planes.clear();
	bullets.clear();
	actions.clear();
}

void World::renderOverInterface()
{
	setbkmode(TRANSPARENT);
	putimage(0, 0, Settings::bgTextures().gameOver.image);

	const char* grade;
	switch (difficultyLevel)
	{
	case 1: grade = "朝鲜飞行员"; break;
	case 2: grade = "初级飞行员"; break;
	case 3: grade = "中级飞行员"; break;
	default:grade = "高级飞行员"; break;
	}

	settextjustify(CENTER_TEXT, CENTER_TEXT);
	xyprintf(windowWidth() / 2, windowHeight() * 0.75, "得分: %d", score);
	xyprintf(windowWidth() / 2, windowHeight() * 0.75 + fontHeight(), "称号: %s", grade);
	outtextxy(windowWidth() / 2, windowHeight() * 0.75 + 3 * fontHeight(), "Q - 退出  R - 重新开始游戏");

	for (; ; )
	{
		switch (getch())
		{
		case 'r':
		case 'R': running = true; return;
		case 'q':
		case 'Q': return;
		}
	}
}

void World::newEnemyWave()
{
	static time_t startPoint = clock();
	static time_t cooldown = Settings::general().times.enemyWaveCoolDown;

	if (sqrt(difficultyLevel) <= 1.0*world.score / (1000 * (1 + difficultyLevel*0.2) * difficultyLevel)) // n^1.5刷新速度
	{
		++difficultyLevel;
	}

	if (clock() - startPoint >= cooldown - 200 * difficultyLevel) // 2n + (n + 1)/2的涨分速度
	{
		int xPos, yPos;
		for (size_t i = 0; i < difficultyLevel + 2; ++i)
		{
			xPos = rand() % (windowWidth() - (int)Settings::enemy_junior().texture.hitBox.x);
			yPos = -Settings::enemy_junior().texture.hitBox.y;
			new Plane_Enemy_Junior(Settings::enemy_junior(), Vector2D(xPos, yPos), Vector2D(0, Settings::enemy_junior().speed));
		}
		for (size_t i = 0; i < (difficultyLevel + 1) / 2; ++i)
		{
			int seed = rand() % 3;
			int speedSgn;
			switch (seed)
			{
			case 0:
				xPos = rand() % (windowWidth() - (int)Settings::enemy_autoTarget().texture.hitBox.x);
				yPos = 0;
				speedSgn = 2 * (rand() % 2) - 1;
				break;
			case 1: 
				xPos = 0; 
				yPos = rand() % (windowHeight() / 3);
				speedSgn = 1;
				break;
			case 2: 
				xPos = windowWidth() - (int)Settings::enemy_autoTarget().texture.hitBox.x;
				yPos = rand() % (windowHeight() / 3);
				speedSgn = -1;
				break;
			}
			new Plane_Enemy_AutoTarget(Settings::enemy_autoTarget(), Vector2D(xPos, yPos), Vector2D(speedSgn * Settings::enemy_autoTarget().speed, 0));
		}
		startPoint = clock();
	}
}

inline void World::gameOver() { running = false; }

int World::fps() { return Settings::general().UI.fps; }

bool World::get_running() { return running; }

inline int World::windowWidth()
{
	return Settings::general().UI.resolution.x;
}

inline int World::windowHeight()
{
	return Settings::general().UI.resolution.y;
}

int World::fontHeight()
{
	return Settings::general().UI.fontHeight;
}

void World::renderBackground()
{
	static int levelYPos = 0;
	putimage(0, levelYPos - windowHeight(), Settings::bgTextures().gaming.image);
	putimage(0, levelYPos, Settings::bgTextures().gaming.image);
	levelYPos >= windowHeight() ? levelYPos = 0 : levelYPos += Settings::general().times.bgShiftSpeed;
}

void World::renderUI()
{
	setfont(fontHeight(), 0, "黑体");
	setbkmode(TRANSPARENT);

	// render player health
	xyprintf(0, windowHeight() - 2 * fontHeight(), "HP: %d / %d", player_plane->curHealth, player_plane->maxHealth);

	// render score
	xyprintf(0, windowHeight() - fontHeight(), "Score: %d", score);

	// render difficulty level
	settextjustify(RIGHT_TEXT, TOP_TEXT);
	xyprintf(windowWidth(), windowHeight() - fontHeight(), "Level: %d", difficultyLevel);
	settextjustify(LEFT_TEXT, TOP_TEXT);

	// render focused enemy health
	static const char* enemy_name;
	static int enemy_curHP;
	static int enemy_maxHP;
	static time_t showTimeStart = clock();
	static bool begin = false;
	if (focused_enemy)
	{
		enemy_curHP = focused_enemy->curHealth;
		enemy_maxHP = focused_enemy->maxHealth;
		enemy_name = typeid(*focused_enemy).name() + 12; /* +12是为了去掉typeid生成的类名字前的"class Plane_" */
		begin = true;
		focused_enemy = nullptr;
		showTimeStart = clock();
	}
	if (begin && clock() - showTimeStart < Settings::general().times.enemyInfoDuration)
	{
		settextjustify(CENTER_TEXT, CENTER_TEXT);
		xyprintf(windowWidth() / 2, windowHeight() / 18, "%s: %d / %d", enemy_name, enemy_curHP, enemy_maxHP);
		settextjustify(LEFT_TEXT, TOP_TEXT);
	}
}

bool World::checkBackgroundCollision(Entity * e, bool leftRight, bool upDown, bool isOuter)
{ 
	return isOuter ?
		leftRight && (e->getXPos( ) + e->getXHitBox( ) < 0 || e->getXPos( ) > windowWidth()) ||
		upDown && (e->getYPos( ) + e->getYHitBox( ) < 0 || e->getYPos( ) > windowHeight())
		:
		leftRight && (e->getXPos( ) < 0 || e->getXPos( ) + e->getXHitBox( ) > windowWidth()) ||
		upDown && (e->getYPos( ) < 0 || e->getYPos( ) + e->getYHitBox( ) > windowHeight());
}
