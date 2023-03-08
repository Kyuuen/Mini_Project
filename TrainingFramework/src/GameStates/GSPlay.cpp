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
	m_isOver = false;
	m_isPause = false;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("map_1.1.tga");

	//Wave Spawner
	
	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	// button pause
	texture = ResourceManagers::GetInstance()->GetTexture("stop_button.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 50.0, 50.0);
	button->SetSize(50, 50);
	m_listButton.push_back(button);
	button->SetOnClick([this]() {
		m_isPause = true;
		//continue
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
		auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
		auto texture = ResourceManagers::GetInstance()->GetTexture("play_button.tga");
		std::shared_ptr<GameButton>  Continue = std::make_shared<GameButton>(model, shader, texture);
		Continue->Set2DPosition(Globals::screenWidth/2 - 50, Globals::screenWidth / 2 );
		Continue->SetSize(50, 50);
		m_listButton.push_back(Continue);
		//exit
		texture = ResourceManagers::GetInstance()->GetTexture("cancel_button.tga");
		std::shared_ptr<GameButton>  Exit = std::make_shared<GameButton>(model, shader, texture);
		Exit->Set2DPosition(Globals::screenWidth / 2 + 50, Globals::screenWidth / 2);
		Exit->SetSize(50, 50);
		Continue->SetOnClick([this]() 
		{
			m_isPause = false;
			m_listButton.pop_back();
			m_listButton.pop_back();
		});
		m_listButton.push_back(Exit);
		Exit->SetOnClick([this]() 
		{
			GameStateMachine::GetInstance()->PopState();
		});
	});


	// score
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("SuperMario256.ttf");
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
	std::shared_ptr<Sprite2D> waypoint_1 = std::make_shared<Sprite2D>(model, shader, texture);
	
	waypoint_1->Set2DPosition(470, 910);
	waypoint_1->SetSize(60, 80);
	m_listWaypoint.push_back(waypoint_1);

	// 2nd waypoint
	std::shared_ptr<Sprite2D> waypoint_2 = std::make_shared<Sprite2D>(model, shader, texture);

	waypoint_2->Set2DPosition(471, 470);
	waypoint_2->SetSize(60, 80);
	m_listWaypoint.push_back(waypoint_2);

	// 3rd waypoint
	std::shared_ptr<Sprite2D> waypoint_3 = std::make_shared<Sprite2D>(model, shader, texture);

	waypoint_3->Set2DPosition(210, 471);
	waypoint_3->SetSize(60, 80);
	m_listWaypoint.push_back(waypoint_3);

	// 4th waypoint
	std::shared_ptr<Sprite2D> waypoint_4 = std::make_shared<Sprite2D>(model, shader, texture);

	waypoint_4->Set2DPosition(211, 161);
	waypoint_4->SetSize(60, 80);
	m_listWaypoint.push_back(waypoint_4);

	// 5th waypoint
	std::shared_ptr<Sprite2D> waypoint_5 = std::make_shared<Sprite2D>(model, shader, texture);

	waypoint_5->Set2DPosition(1010, 153);
	waypoint_5->SetSize(60, 80);
	m_listWaypoint.push_back(waypoint_5);

	// 6th waypoint
	std::shared_ptr<Sprite2D> waypoint_6 = std::make_shared<Sprite2D>(model, shader, texture);

	waypoint_6->Set2DPosition(1005, 573);
	waypoint_6->SetSize(60, 80);
	m_listWaypoint.push_back(waypoint_6);
	
	// 7th waypoint
	std::shared_ptr<Sprite2D> waypoint_7 = std::make_shared<Sprite2D>(model, shader, texture);

	waypoint_7->Set2DPosition(762, 578);
	waypoint_7->SetSize(60, 80);
	m_listWaypoint.push_back(waypoint_7);

	// 8th waypoint
	std::shared_ptr<Sprite2D> waypoint_8 = std::make_shared<Sprite2D>(model, shader, texture);

	waypoint_8->Set2DPosition(765, 760);
	waypoint_8->SetSize(60, 80);
	m_listWaypoint.push_back(waypoint_8);

	// end waypoint
	std::shared_ptr<Sprite2D> waypoint_9 = std::make_shared<Sprite2D>(model, shader, texture);

	waypoint_9->Set2DPosition(1492, 765);
	waypoint_9->SetSize(60, 80);
	m_listWaypoint.push_back(waypoint_9);

	//Enemy1
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("enemy2walking_02.tga");
	std::shared_ptr<Enemy>	m_enemy = std::make_shared<Enemy>(model, shader, texture, 30, 300, m_listWaypoint);
	m_enemy->LockTarget();
	m_enemy->Set2DPosition(50, 900);
	m_enemy->SetSize(70, 70);
	m_listEnemy.push_back(m_enemy);

	std::shared_ptr<ArcherTower> archerTower = TowerPooling::GetInstance()->GetFromPool();
	if (archerTower != nullptr)
	{
		archerTower->Set2DPosition(690, 700);
		archerTower->SetSize(120, 120);
	}
	m_listTower.push_back(archerTower);

	//Node
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	texture = ResourceManagers::GetInstance()->GetTexture("BuildGround_tower.tga");
	std::shared_ptr<GameButton>  node_1 = std::make_shared<GameButton>(model, shader, texture);
	node_1->Set2DPosition(690, 700);
	node_1->SetSize(70, 70);
	m_listNode.push_back(node_1);
	node_1->SetOnClick([this]() {
		std::shared_ptr<ArcherTower> archerTower = TowerPooling::GetInstance()->GetFromPool();
		if (archerTower != nullptr)
		{
			archerTower->Set2DPosition(690, 700);
			archerTower->SetSize(120, 120);
		}
		m_listTower.push_back(archerTower);
	});

	//Node2
	std::shared_ptr<GameButton>  node_2 = std::make_shared<GameButton>(model, shader, texture);
	node_2->Set2DPosition(1060, 500);
	node_2->SetSize(70, 70);
	m_listNode.push_back(node_2);
	node_2->SetOnClick([this]() {
		std::shared_ptr<ArcherTower> archerTower = TowerPooling::GetInstance()->GetFromPool();
		if (archerTower != nullptr)
		{
			archerTower->Set2DPosition(1060, 500);
			archerTower->SetSize(120, 120);
		}
		m_listTower.push_back(archerTower);
	});

	//Node3
	std::shared_ptr<GameButton>  node_3 = std::make_shared<GameButton>(model, shader, texture);
	node_3->Set2DPosition(270, 370);
	node_3->SetSize(70, 70);
	m_listNode.push_back(node_3);
	node_3->SetOnClick([this]() {
		std::shared_ptr<ArcherTower> archerTower = TowerPooling::GetInstance()->GetFromPool();
		if (archerTower != nullptr)
		{
			archerTower->Set2DPosition(270, 370);
			archerTower->SetSize(120, 120);
		}
		m_listTower.push_back(archerTower);
	});

	//Node4
	std::shared_ptr<GameButton>  node_4 = std::make_shared<GameButton>(model, shader, texture);
	node_4->Set2DPosition(625, 230);
	node_4->SetSize(70, 70);
	m_listNode.push_back(node_4);
	node_4->SetOnClick([this]() {
		std::shared_ptr<ArcherTower> archerTower = TowerPooling::GetInstance()->GetFromPool();
		if (archerTower != nullptr)
		{
			archerTower->Set2DPosition(625, 230);
			archerTower->SetSize(120, 120);
		}
		m_listTower.push_back(archerTower);
	});

	//Node5
	std::shared_ptr<GameButton>  node_5 = std::make_shared<GameButton>(model, shader, texture);
	node_5->Set2DPosition(390, 600);
	node_5->SetSize(70, 70);
	m_listNode.push_back(node_5);
	node_5->SetOnClick([this]() {
		std::shared_ptr<ArcherTower> archerTower = TowerPooling::GetInstance()->GetFromPool();
		if (archerTower != nullptr)
		{
			archerTower->Set2DPosition(390, 600);
			archerTower->SetSize(120, 120);
		}
		m_listTower.push_back(archerTower);
	});

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

void GSPlay::GameOver()
{
	//back ground game over
	m_isPause = true;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_main_menu.tga");
	m_gameOver = std::make_shared<Sprite2D>(model, shader, texture);
	m_gameOver->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	m_gameOver->SetSize(Globals::screenWidth, Globals::screenHeight);
	//text
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	m_gameOverText = std::make_shared< Text>(shader, font, "Game Over!", TextColor::RED, 1.0);
	m_gameOverText->Set2DPosition(Vector2((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2 + 50));

	//home button
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	texture = ResourceManagers::GetInstance()->GetTexture("play_button.tga");
	std::shared_ptr<GameButton>  home = std::make_shared<GameButton>(model, shader, texture);
	home->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	home->SetSize(50, 50);
	m_exitButton.push_back(home);
	home->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
	});
	
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
	if (m_isPause == false)
	{
		for (auto it : m_listNode)
		{
			it->Update(deltaTime);
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
		for (auto it : m_listAnimation)
		{
			it->Update(deltaTime);
		}
		
	}
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	if (m_isOver)
	{
		GameOver();
		for (auto it : m_exitButton)
		{
			it->Update(deltaTime);
		}
	}
}

void GSPlay::Draw()
{
	m_background->Draw();
	m_score->Draw();
	for (auto it : m_listNode)
	{
		it->Draw();
	}
	for (auto it : m_listEnemy) 
	{
		it->Draw();
	}
	for (auto it : m_listAnimation)
	{
		it->Draw();
	}
	for (auto it : m_listTower)
	{
		it->Draw();
	}
	for (auto it : m_listArrow)
	{
		it->Draw();
	}
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	if (m_isOver)
	{
		m_gameOver->Draw();
		m_gameOverText->Draw();
		for (auto it : m_exitButton)
		{
			it->Draw();
		}
	}
}