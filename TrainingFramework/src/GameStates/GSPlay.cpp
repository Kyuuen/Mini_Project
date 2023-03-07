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
#include "Towers/ArcherTower.h"
#include "Projectiles/Projectile.h"


GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{
}


void GSPlay::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("map_1.1.tga");

	//Wave Spawner
	
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
	m_KeyPress = 0;

	// begin waypoint
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<Sprite2D> waypoint_0 = std::make_shared<Sprite2D>(model, shader, texture);

	waypoint_0->Set2DPosition(0, 905);
	waypoint_0->SetSize(60, 80);
	m_listWaypoint.push_back(waypoint_0);

	// 1st waypoint
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<Sprite2D> waypoint_1 = std::make_shared<Sprite2D>(model, shader, texture);
	
	waypoint_1->Set2DPosition(450, 910);
	waypoint_1->SetSize(60, 80);
	m_listWaypoint.push_back(waypoint_1);

	// 2nd waypoint
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<Sprite2D> waypoint_2 = std::make_shared<Sprite2D>(model, shader, texture);

	waypoint_2->Set2DPosition(451, 480);
	waypoint_2->SetSize(60, 80);
	m_listWaypoint.push_back(waypoint_2);

	// 3rd waypoint
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<Sprite2D> waypoint_3 = std::make_shared<Sprite2D>(model, shader, texture);

	waypoint_3->Set2DPosition(210, 481);
	waypoint_3->SetSize(60, 80);
	m_listWaypoint.push_back(waypoint_3);

	// 4th waypoint
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<Sprite2D> waypoint_4 = std::make_shared<Sprite2D>(model, shader, texture);

	waypoint_4->Set2DPosition(211, 161);
	waypoint_4->SetSize(60, 80);
	m_listWaypoint.push_back(waypoint_4);

	// 5th waypoint
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<Sprite2D> waypoint_5 = std::make_shared<Sprite2D>(model, shader, texture);

	waypoint_5->Set2DPosition(985, 153);
	waypoint_5->SetSize(60, 80);
	m_listWaypoint.push_back(waypoint_5);

	// 6th waypoint
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<Sprite2D> waypoint_6 = std::make_shared<Sprite2D>(model, shader, texture);

	waypoint_6->Set2DPosition(990, 603);
	waypoint_6->SetSize(60, 80);
	m_listWaypoint.push_back(waypoint_6);
	
	// 7th waypoint
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<Sprite2D> waypoint_7 = std::make_shared<Sprite2D>(model, shader, texture);

	waypoint_7->Set2DPosition(762, 605);
	waypoint_7->SetSize(60, 80);
	m_listWaypoint.push_back(waypoint_7);

	// 8th waypoint
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<Sprite2D> waypoint_8 = std::make_shared<Sprite2D>(model, shader, texture);

	waypoint_8->Set2DPosition(765, 760);
	waypoint_8->SetSize(60, 80);
	m_listWaypoint.push_back(waypoint_8);

	// end waypoint
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<Sprite2D> waypoint_9 = std::make_shared<Sprite2D>(model, shader, texture);

	waypoint_9->Set2DPosition(1492, 765);
	waypoint_9->SetSize(60, 80);
	m_listWaypoint.push_back(waypoint_9);

	//Enemy1
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("enemy2walking_02.tga");
	std::shared_ptr<Enemy>	m_enemy = std::make_shared<Enemy>(model, shader, texture, 30, 100, m_listWaypoint);
	m_enemy->LockTarget();
	m_enemy->Set2DPosition(50, 900);
	m_enemy->SetSize(100, 100);
	m_listEnemy.push_back(m_enemy);

	//Enemy2
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("enemy2walking_02.tga");
	std::shared_ptr<Enemy>	m_enemy2 = std::make_shared<Enemy>(model, shader, texture, 30, 120, m_listWaypoint);
	m_enemy2->LockTarget();
	m_enemy2->Set2DPosition(50, 900);
	m_enemy2->SetSize(200, 200);
	m_listEnemy.push_back(m_enemy2);

	//Tower
	std::shared_ptr<ArcherTower> tower = std::make_shared<ArcherTower>();
	tower->Set2DPosition(Globals::screenWidth / 2 + 400.0, Globals::screenHeight / 2 - 200);
	tower->SetSize(120, 120);
	tower->m_sprite->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
	tower->m_sprite->SetSize(120, 120);
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
		it->Update(deltaTime, m_listEnemy, m_listArrow);
	}
	for (auto it : m_listArrow) 
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
		it->m_sprite->Draw();
	}
	for (auto it : m_listEnemy) 
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
	for (auto it : m_listArrow) 
	{
		it->m_sprite->Draw();
	}
}