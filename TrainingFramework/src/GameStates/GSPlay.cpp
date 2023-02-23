#include "GSPlay.h"

#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "GameButton.h"
#include "SpriteAnimation.h"
#include "Enemy.h"
#include "Tower.h"
#include "Projectile.h"



GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{
}


void GSPlay::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_main_menu.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// button close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 50.0, 50.0);
	button->SetSize(50, 50);
	button->SetOnClick([this]() {
			GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	// score
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	m_score = std::make_shared< Text>(shader, font, "score: 10", TextColor::RED, 1.0);
	m_score->Set2DPosition(Vector2(5, 25));
	//Enemy 2
	/*shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("Enemy2Idle.tga");
	std::shared_ptr<SpriteAnimation> obj = std::make_shared<SpriteAnimation>(model, shader, texture, 12, 1, 0, 0.1f);
	
	obj->Set2DPosition(240, 400);
	obj->SetSize(240, 320);

	m_listAnimation.push_back(obj);
	m_KeyPress = 0;*/

	// First waypoint
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<Sprite2D> waypoint_1 = std::make_shared<Sprite2D>(model, shader, texture);
	
	waypoint_1->Set2DPosition(400, 500);
	waypoint_1->SetSize(60, 80);
	m_listWaypoint.push_back(waypoint_1);
	//Second waypoint
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<Sprite2D> waypoint_2 = std::make_shared<Sprite2D>(model, shader, texture);

	waypoint_2->Set2DPosition(Globals::screenWidth / 2 + 300.0, Globals::screenHeight / 2 - 200);
	waypoint_2->SetSize(60, 80);
	m_listWaypoint.push_back(waypoint_2);
	
	//Enemy
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("Enemy2Idle.tga");
	std::shared_ptr<Enemy>	m_enemy = std::make_shared<Enemy>(model, shader, texture, 30, 100, m_listWaypoint);
	m_enemy->LockTarget();
	m_enemy->Set2DPosition(100, 100);
	m_enemy->SetSize(240, 320);
	m_listEnemy.push_back(m_enemy);

	//Enemy
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("Enemy2Idle.tga");
	std::shared_ptr<Enemy>	m_enemy2 = std::make_shared<Enemy>(model, shader, texture, 30, 120, m_listWaypoint);
	m_enemy2->LockTarget();
	m_enemy2->Set2DPosition(200, 100);
	m_enemy2->SetSize(320, 320);
	m_listEnemy.push_back(m_enemy2);

	//Tower
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	texture = ResourceManagers::GetInstance()->GetTexture("Archer Tower Front.tga");
	std::shared_ptr<Tower> tower = std::make_shared<Tower>(model, shader, texture, 3000, 1, 0, 200);
	tower->Set2DPosition(Globals::screenWidth / 2 + 400.0, Globals::screenHeight / 2 - 200);
	tower->SetSize(120, 120);
	m_listTower.push_back(tower);
}

void GSPlay::Exit()
{
}


void GSPlay::Pause()
{
}

void GSPlay::Resume()
{
}


void GSPlay::HandleEvents()
{
}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	if (bIsPressed)
	{
		switch (key)
		{
		case KEY_MOVE_LEFT:
			m_KeyPress |= 1;
			break;
		case KEY_MOVE_BACKWORD:
			m_KeyPress |= 1<<1;
			break;
		case KEY_MOVE_RIGHT:
			m_KeyPress |= 1<<2;
			break;
		case KEY_MOVE_FORWORD:
			m_KeyPress |= 1<<3;
			break;
		default:
			break;
		}
	}
	else
	{
		switch (key)
		{
		case KEY_MOVE_LEFT:
			m_KeyPress ^= 1;
			break;
		case KEY_MOVE_BACKWORD:
			m_KeyPress ^= 1 << 1;
			break;
		case KEY_MOVE_RIGHT:
			m_KeyPress ^= 1 << 2;
			break;
		case KEY_MOVE_FORWORD:
			m_KeyPress ^= 1 << 3;
			break;
		default:
			break;
		}
	}
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if(button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSPlay::HandleMouseMoveEvents(int x, int y)
{
}

void GSPlay::Update(float deltaTime)
{
	switch (m_KeyPress)//Handle Key event
	{
	default:
		break;
	}
	for (auto it : m_listTower)
	{
		it->Update(deltaTime, m_listEnemy, m_listProjectile);
	}
	for (auto it : m_listProjectile) 
	{
		it->Update(deltaTime);
	}
	for (auto it : m_listEnemy) 
	{
		it->Update(deltaTime);
	}
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	for (auto it : m_listAnimation)
	{
		it->Update(deltaTime);
	}
}

void GSPlay::Draw()
{
	m_background->Draw();
	m_score->Draw();
	for (auto it : m_listTower) 
	{
		it->Draw();
	}
	for (auto it : m_listEnemy) 
	{
		it->Draw();
	}
	for (auto it : m_listWaypoint)
	{
		it->Draw();
	}
	for (auto it : m_listButton)
	{
		it->Draw();
	}

	for (auto it : m_listAnimation)
	{
		it->Draw();
	}
	for (auto it : m_listProjectile) 
	{
		it->Draw();
	}
}