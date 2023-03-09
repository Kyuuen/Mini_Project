#include "GSPlay.h"

#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Text.h"
#include "GameButton.h"
#include "Enemy.h"
#include "Towers/ArcherTower.h"


GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{
}


void GSPlay::Init()
{
	m_isPlayed = false;
	m_pauseToDraw = false;
	m_isOver = false;
	m_isPause = false;
	m_Overing = false;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("map_1.1.tga");
	
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
		m_pauseToDraw = true;
		m_isPause = true;
		//continue
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
		auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
		auto texture = ResourceManagers::GetInstance()->GetTexture("play_button.tga");
		std::shared_ptr<GameButton>  Continue = std::make_shared<GameButton>(model, shader, texture);
		Continue->Set2DPosition(Globals::screenWidth/2 - 100, 400);
		Continue->SetSize(150, 150);
		m_listButton.push_back(Continue);
		//exit
		texture = ResourceManagers::GetInstance()->GetTexture("Home_Button.tga");
		std::shared_ptr<GameButton>  Exit = std::make_shared<GameButton>(model, shader, texture);
		Exit->Set2DPosition(Globals::screenWidth / 2 + 100, 400);
		Exit->SetSize(150, 150);
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

	// money
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("SuperMario256.ttf");
	m_money = std::make_shared< Text>(shader, font, "$" + std::to_string(GameMaster::GetInstance()->GetCurrentMoney()), TextColor::YELLOW, 2.0);
	m_money->Set2DPosition(Vector2(5, 150));
	m_money->m_type = 1;
	m_KeyPress = 0;

	//Wave count down timer
	m_waveCountDown = std::make_shared< Text>(shader, font, "Next wave: " + std::to_string(WaveSpawner::GetInstance()->GetWaveCountDown()), TextColor::YELLOW, 2.0);
	m_waveCountDown->Set2DPosition(Vector2(5, 1000));
	m_waveCountDown->m_type = 3;
	m_KeyPress = 0;

	//Game Pause text
	m_pauseText = std::make_shared< Text>(shader, font, "Paused", TextColor::YELLOW, 3.0);
	m_pauseText->Set2DPosition(Vector2(580, 300));

	// player health
	m_health = std::make_shared< Text>(shader, font,"Health: " + std::to_string(GameMaster::GetInstance()->GetCurrentHealth()), TextColor::YELLOW, 2.0);
	m_health->Set2DPosition(Vector2(5, 50));
	m_health->m_type = 2;
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

	//Wave Spawner
	WaveSpawner::GetInstance()->GetListWaypoints(m_listWaypoint);

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
			archerTower->Set2DPosition(690, 660);
			archerTower->SetSize(120, 120);
		}
		m_listTower.push_back(archerTower);
		GameMaster::GetInstance()->SpendToBuild();
		ResourceManagers::GetInstance()->PlaySound("towerBuilt.wav");
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
			archerTower->Set2DPosition(1060, 460);
			archerTower->SetSize(120, 120);
		}
		m_listTower.push_back(archerTower);
		GameMaster::GetInstance()->SpendToBuild();
		ResourceManagers::GetInstance()->PlaySound("towerBuilt.wav");
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
			archerTower->Set2DPosition(270, 330);
			archerTower->SetSize(120, 120);
		}
		m_listTower.push_back(archerTower);
		GameMaster::GetInstance()->SpendToBuild();
		ResourceManagers::GetInstance()->PlaySound("towerBuilt.wav");
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
			archerTower->Set2DPosition(625, 190);
			archerTower->SetSize(120, 120);
		}
		m_listTower.push_back(archerTower);
		GameMaster::GetInstance()->SpendToBuild();
		ResourceManagers::GetInstance()->PlaySound("towerBuilt.wav");
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
			archerTower->Set2DPosition(390, 560);
			archerTower->SetSize(120, 120);
		}
		m_listTower.push_back(archerTower);
		GameMaster::GetInstance()->SpendToBuild();
		ResourceManagers::GetInstance()->PlaySound("towerBuilt.wav");
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
	ResourceManagers::GetInstance()->StopSound("level.wav");
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_main_menu.tga");
	m_gameOver = std::make_shared<Sprite2D>(model, shader, texture);
	m_gameOver->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	m_gameOver->SetSize(Globals::screenWidth, Globals::screenHeight);
	//text
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("SuperMario256.ttf");
	m_gameOverText = std::make_shared< Text>(shader, font, "Game Over!", TextColor::YELLOW, 3.0);
	m_gameOverText->Set2DPosition(Vector2(500, 200));

	//Enemies killed
	m_enemiesKilled = std::make_shared< Text>(shader, font, "You've killed: " + std::to_string(GameMaster::GetInstance()->GetEnemyKilled()) + " enemies", TextColor::YELLOW, 2.5);
	m_enemiesKilled->Set2DPosition(Vector2(300, 300));
	//home button
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	texture = ResourceManagers::GetInstance()->GetTexture("Home_Button.tga");
	std::shared_ptr<GameButton>  home = std::make_shared<GameButton>(model, shader, texture);
	home->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	home->SetSize(200, 200);
	m_exitButton.push_back(home);
	home->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		ResourceManagers::GetInstance()->PlaySound("level.wav");
		ResourceManagers::GetInstance()->StopSound("gameover.wav");
	});

	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("Enemy2Taunt_01.tga");
	std::shared_ptr<SpriteAnimation> decor = std::make_shared<SpriteAnimation>(model, shader, texture, 18, 1, 0, 0.05f);
	decor->Set2DPosition(300, 500);
	decor->SetSize(300, 300);
	m_listAnimation.push_back(decor);
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
	if (GameMaster::GetInstance()->GetCurrentMoney() >= 200) {
		for (auto button : m_listNode)
		{
			if (button->HandleTouchEvents(x, y, bIsPressed))
			{
				break;
			}
		}
	}
	for (auto button : m_exitButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
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
	m_isOver = GameMaster::GetInstance()->GameIsOver();
	switch (m_KeyPress)//Handle Key event
	{
	default:
		break;
	}
	if (m_isPause == false && m_isOver == false)
	{
		m_money->Update(deltaTime);
		m_health->Update(deltaTime);
		m_waveCountDown->Update(deltaTime);
		WaveSpawner::GetInstance()->Update(deltaTime, m_listEnemy);
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
			if(it != nullptr) it->Update(deltaTime);
		}
		for (auto it : m_listEnemy)
		{
			it->Update(deltaTime);
		}	
	}
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	for (auto it : m_listAnimation)
	{
		it->Update(deltaTime);
	}
	if (m_isOver)
	{
		if (!m_Overing)
		{
			if (!m_isPlayed)
			{
				ResourceManagers::GetInstance()->PlaySound("gameover.wav");
				m_isPlayed = true;
			}
			GameOver();
			for (auto it : m_exitButton)
			{
				it->Update(deltaTime);
			}
			m_Overing = true;
		}
	}
}

void GSPlay::Draw()
{
	m_background->Draw();
	m_health->Draw();
	m_money->Draw();
	for (auto it : m_listNode)
	{
		it->Draw();
	}
	for (auto it : m_listEnemy) 
	{
		if(it->IsEnable()) it->Draw();
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
		if(it != nullptr) 
			it->Draw();
	}
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_waveCountDown->Draw();
	if (m_isOver)
	{
		m_gameOver->Draw();
		m_gameOverText->Draw();
		m_enemiesKilled->Draw();
		for (auto it : m_exitButton)
		{
			it->Draw();
		}
		for (auto it : m_listAnimation)
		{
			it->Draw();
		}
	}
	if (m_isPause) {
		if (m_pauseToDraw) m_pauseText->Draw();
	}
}