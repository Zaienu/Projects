#include "definitions.h"
#include "GameData.h"
#include "Vector.h"
#include "Player.h"
#include "Projectile.h"
#include "GameplayManager.h"

#include "SpriteManager.h"
#include "AnimationManager.h"
#include "SoundManager.h"
#include "TextManager.h"

GameplayManager::GameplayManager()
{
	GameData* GD = GameData::Get_Instance();
	GD->m_playerNb > 4 ? GD->m_playerNb = 4 : NULL;
	Load(GD->m_playerNb);
	GD->m_scores.clear();
	GD->m_scores.resize(GD->m_playerNb);
	m_proj.clear();
	m_proj.resize(GD->m_playerNb);
	for (int i = 0; i < GD->m_playerNb; i++)
	{
		GD->m_scores[i] = 0;
	}
}

void Load_GameTheme()
{
	GameData* GD = GameData::Get_Instance();
	SoundManager* Sound = SoundManager::Get_Instance();
	Sound->FillVectors(MUSIC, "GameMusic");
	Sound->ManageMusic("GameMusic", true);
	Sound->SetMusicLoop("GameMusic", true);
	Sound->ApplyVolume(MUSIC);
}

void Load_Explosion()
{
	GameData* GD = GameData::Get_Instance();
	SoundManager* Sound = SoundManager::Get_Instance();
	Sound->FillVectors(EFFECT, "Explosion");
	Sound->ApplyVolume(EFFECT);
}

void Load_Background(std::string* _BG)
{
	GameData* GD = GameData::Get_Instance();
	SpriteManager* Sprite = SpriteManager::Get_Instance();
	SpriteSettings bgSettings =
	{
		"GameStates/Game/Background",
		"Game_Background",
		false,
		{1,1}
	};
	*_BG = bgSettings.name;
	Sprite->FillVectors(bgSettings);
}

void Load_Map(sf::Image* _im, sf::Texture* _tex, sf::Sprite* _spr)
{
	GameData* GD = GameData::Get_Instance();

	_im->loadFromFile("../Assets/Images/GameStates/Game/Map1.png");
	_tex->create(_im->getSize().x, _im->getSize().y);
	_tex->update(*_im);
	_spr->setTexture(*_tex);
}

void Load_Players(int _amount, std::vector <Player*>* _players)
{
	for (int i = 0; i < _amount; i++)
	{
		Player* player = new Player(i);
		_players->push_back(player);
	}
}

void Load_Text(std::string* _timer, std::string* _player, std::string* _wind)
{
	GameData* GD = GameData::Get_Instance();
	TextManager* Text = TextManager::Get_Instance();
	for (int i = 0; i < 3; i++)
	{
		std::string name;
		switch (i)
		{
		case 0: name = "Game_Timer"; *_timer = name; break;
		case 1: name = "Game_Players"; *_player = name; break;
		case 2: name = "Game_Wind"; *_wind = name; break;
		}
		TextSettings textSettings =
		{
			"Poggers-Bold",
			name,
			sf::Color::Red,
			30
		};
		Text->FillVectors(textSettings);
	}
}

void GameplayManager::Load(int _amount)
{
	Load_Background(&m_background);
	Load_Map(&m_mapImage, &m_mapTex, &m_mapSprite);
	Load_Players(_amount, &m_players);
	Load_Text(&m_timerValue, &m_playerTurn, &m_windValue);
	m_vector.create = create;
	m_vector.create(&m_vector);
	Load_GameTheme();
	Load_Explosion();
}

void GameplayManager::MousePressed(sf::Event _event)
{

}

void GameplayManager::MouseMoved(sf::Event _event)
{

}

void GameplayManager::KeyPressed(sf::Event _event)
{

}

void GameplayManager::CreateExplosion(int _id)
{
	for (int i = 0; i < 10; i++)
	{
		Element tempElem = { 0 };
		tempElem.x = m_proj[_id]->m_pos.x + rand()%50 - 25;
		tempElem.y = m_proj[_id]->m_pos.y + rand()%10 - 5;
		tempElem.timer = 1.0f;
		m_vector.push_back(&m_vector, tempElem);
	}
}

void Brezenheim(sf::Vector2f _pos1, sf::Vector2f _pos2, std::vector <sf::Vector2i>* _pixels)
{
	int dx, dy, p, x, y;

	round(_pos1.x);
	round(_pos1.y);
	round(_pos2.x);
	round(_pos2.y);

	dx = _pos2.x - _pos1.x;
	dy = _pos2.y - _pos1.y;

	x = _pos1.x;
	y = _pos1.y;

	p = 2 * dy - dx;

	while (x < _pos2.x)
	{
		if (p >= 0)
		{
			_pixels->push_back({ x, y });
			y = y + 1;
			p = p + 2 * dy - 2 * dx;
		}
		else
		{
			_pixels->push_back({ x, y });
			p = p + 2 * dy;
		}
		x = x + 1;
	}
}

void GameplayManager::Test_PlayersCollisions(int _id1, int _id2)
{
	SoundManager* Sound = SoundManager::Get_Instance();
	if (m_players[_id1] != NULL)
	{
		float dist = ((m_players[_id1]->m_pr.pos.chassis.x - m_proj[_id2]->m_pos.x) *
			(m_players[_id1]->m_pr.pos.chassis.x - m_proj[_id2]->m_pos.x))
			+ ((m_players[_id1]->m_pr.pos.chassis.y - m_proj[_id2]->m_pos.y) *
				(m_players[_id1]->m_pr.pos.chassis.y - m_proj[_id2]->m_pos.y));
		if (dist <= (30 * 30))
		{
			m_players[_id1]->m_pr.isAlive = false;
			delete m_players[_id2]->m_proj;
			m_players[_id2]->m_proj = NULL;
			m_players[_id2]->Add_Score(100);
		}
	}
}

void GameplayManager::Test_ProjectilesCollisions(int _id)
{
	GameData* GD = GameData::Get_Instance();
	SoundManager* Sound = SoundManager::Get_Instance();
	if (m_proj[_id] != NULL)
	{
		std::vector <sf::Vector2i> pixels;
		Brezenheim(m_proj[_id]->m_pos, m_proj[_id]->m_nextPos, &pixels);
		if (m_proj[_id]->m_pos.x >= SWIDTH - m_proj[_id]->m_radius ||
			m_proj[_id]->m_pos.x <= 0 + m_proj[_id]->m_radius ||
			m_proj[_id]->m_pos.y >= SHEIGHT - m_proj[_id]->m_radius ||
			m_proj[_id]->m_pos.y <= 0 + m_proj[_id]->m_radius)
		{
			Sound->ManageEffect("Explosion", true);
			delete m_players[_id]->m_proj;
			m_players[_id]->m_proj = NULL;
		}
		else
		{
			for (int i = 0; i < pixels.size(); i++)
			{
				if (m_mapImage.getPixel(pixels[i].x, pixels[i].y).a != 0)
				{
					Explode(_id);
					Sound->ManageEffect("Explosion", true);
					CreateExplosion(_id);
					delete m_players[_id]->m_proj;
					m_players[_id]->m_proj = NULL;
				}
			}
		}
		for (int j = 0; j < GD->m_playerNb; j++)
		{
			Test_PlayersCollisions(j, _id);
		}
	}
}

void GameplayManager::Explode(int _id)
{
	for (int i = m_proj[_id]->m_pos.y - m_proj[_id]->m_radius;
		i < m_proj[_id]->m_pos.y + m_proj[_id]->m_radius;
		i++)
	{
		for (int j = m_proj[_id]->m_pos.x - m_proj[_id]->m_radius;
			j < m_proj[_id]->m_pos.x + m_proj[_id]->m_radius;
			j++)
		{
			float dist = (
				((m_proj[_id]->m_pos.x - j) * (m_proj[_id]->m_pos.x - j)) +
				((m_proj[_id]->m_pos.y - i) * (m_proj[_id]->m_pos.y - i))
				);
			if (dist <= (m_proj[_id]->m_radius * m_proj[_id]->m_radius))
			{
				m_mapImage.setPixel(j, i, sf::Color::Transparent);
			}
		}
	}
	m_mapTex.update(m_mapImage);
}

void GameplayManager::Update()
{
	GameData* GD = GameData::Get_Instance();
	TextManager* Text = TextManager::Get_Instance();

	for (int i = 0; i < m_players.size(); i++)
	{
		if (m_players[i] != NULL)
		{
			m_players[i]->Update();
			m_proj[i] = m_players[i]->m_proj;
			sf::Vector2f pos = m_players[i]->m_pr.pos.chassis;
			if (m_mapImage.getPixel(pos.x, pos.y + 1).a == 0)
			{
				m_players[i]->m_pr.pos.chassis.y += 0.2f;
			}

			if (m_mapImage.getPixel(pos.x + 1, pos.y).a != 0)
			{
				int tempY = pos.y;
				int count = 0;
				int currPixelAlpha;
				do
				{
					currPixelAlpha = m_mapImage.getPixel(pos.x + 1, tempY).a;
					tempY -= 1;
					count++;
				} while (currPixelAlpha != 0);
				if (count <= m_slopeLimit)
				{
					m_players[i]->Can_MoveLR(0, count);
				}
			}
			else if (m_mapImage.getPixel(pos.x + 1, pos.y).a == 0)
			{
				m_players[i]->Can_MoveLR(0);
			}

			if (m_mapImage.getPixel(pos.x - 1, pos.y).a != 0)
			{
				int tempY = pos.y;
				int count = 0;
				int currPixelAlpha;
				do
				{
					currPixelAlpha = m_mapImage.getPixel(pos.x - 1, tempY).a;
					tempY -= 1;
					count++;
				} while (currPixelAlpha != 0);
				if (count <= m_slopeLimit)
				{
					m_players[i]->Can_MoveLR(1, count);
				}
			}
			else if (m_mapImage.getPixel(pos.x - 1, pos.y).a == 0)
			{
				m_players[i]->Can_MoveLR(1);
			}

			//Angulate the player
			sf::Vector2f corners[2];
			for (int j = 0; j < 2; j++)
			{
				sf::Vector2f corner = m_players[i]->m_corners[j];
				int width = abs(m_players[i]->m_corners[1].x - m_players[i]->m_corners[0].x);
				while (m_mapImage.getPixel(corner.x, corner.y + 1).a == 0
					&& abs(corner.y - m_players[i]->m_pr.pos.chassis.y) <= 40) // <= width/2.0f
				{
					corner.y++;
				}
				while (m_mapImage.getPixel(corner.x, corner.y).a != 0
					&& abs(corner.y - m_players[i]->m_pr.pos.chassis.y) <= 40) // <= width/2.0f
				{
					corner.y--;
				}
				corners[j] = corner;
			}
			float angle = atan2f(corners[1].y - corners[0].y, corners[1].x - corners[0].x) * 180 / PI;
			m_players[i]->m_pr.angle.chassis = angle;

			GD->m_scores[i] = m_players[i]->Get_Score();
			Test_ProjectilesCollisions(i);
		}
		for (int k = 0; k < GD->m_playerNb; k++)
		{
			if (m_players[k] != NULL && !m_players[k]->m_pr.isAlive)
			{
				delete m_players[k];
				m_players[k] = NULL;
			}
		}
	}
	for (int i = 1; i < m_vector.size + 1; i++)
	{
		m_vector.modify_element(&m_vector, i, 2, GD->m_frameTime);
		m_vector.modify_element(&m_vector, i, 1, GD->m_frameTime/110);
		if (m_vector.get_element(&m_vector, i).timer <= 0)
		{
			m_vector.erase(&m_vector, i);
		}
	}
	m_timer -= GD->m_frameTime;
	if (m_timer <= 0)
	{
		do
		{
			m_currentPlayer++;
			m_currentPlayer = m_currentPlayer % GD->m_playerNb;
		} while (m_players[m_currentPlayer] == NULL);
		m_nextTurn = true;
		m_timer = 10.0f;
	}
	if (m_nextTurn)
	{
		GD->m_wind = { (float)(rand() % 20 + 1), (float)(rand() % 20 + 1) };
		m_players[m_currentPlayer]->Activate_Controls();
		for (int i = 0; i < GD->m_playerNb; i++)
		{
			if (i != m_currentPlayer && m_players[i] != NULL)
			{
				m_players[i]->Deactivate_Controls();
			}
		}
		m_nextTurn = false;
	}

	Text->SetString(m_timerValue, "Timer : " + std::to_string((int)round(m_timer)));
	Text->SetString(m_playerTurn, "Current Player : " + std::to_string(m_currentPlayer));
	Text->SetString(m_windValue, "Wind : " + 
								std::to_string((int)round(GD->m_wind.x)) +
								"x ; "+ std::to_string((int)round(GD->m_wind.x)) + "y");

	///
	int aliveCount = 0;
	for (int i = 0; i < GD->m_playerNb; i++)
	{
		if (m_players[i] == NULL)
		{
			aliveCount++;
		}
	}
	if (aliveCount >= GD->m_playerNb - 1)
	{
		GD->m_state = GAMEOVER;
	}
}

void Display_Background(std::string _BG)
{
	GameData* GD = GameData::Get_Instance();
	SpriteManager* Sprite = SpriteManager::Get_Instance();
	SpriteDrawParameters bgParameters =
	{
		_BG,
		0,
		{0, 0},
		&GD->m_window
	};
	Sprite->BlitSprite(bgParameters);
}

void Display_Map(sf::Sprite _map)
{
	GameData* GD = GameData::Get_Instance();
	GD->m_window.draw(_map);
}

void Display_Particles(Vec _vector)
{
	GameData* GD = GameData::Get_Instance();
	SpriteManager* Sprite = SpriteManager::Get_Instance();
	for (int i = 1; i < _vector.size; i++)
	{
		SpriteSettings particleSettings =
		{

			"GameStates/Game/Smoke",
			"Smoke",
			true,
			{0.5f, 0.5f}
		};
		Sprite->FillVectors(particleSettings);
		SpriteDrawParameters particleDraw =
		{
			"Smoke",
			0,
			{(float)(_vector.get_element(&_vector, i).x), (float)(_vector.get_element(&_vector, i).y)},
			&GD->m_window
		};
		Sprite->BlitSprite(particleDraw);
	}
}

void Display_Text(std::string _timer, std::string _player, std::string _wind)
{
	GameData* GD = GameData::Get_Instance();
	TextManager* Text = TextManager::Get_Instance();
	for (int i = 0; i < 3; i++)
	{
		std::string name;
		sf::Vector2f pos;
		switch (i)
		{
		case 0: name = _timer; pos = { 10, 10 }; break;
		case 1: name = _player; pos = { SWIDTH/2, 10 }; break;
		case 2: name = _wind; pos = {20, SHEIGHT - 40 }; break;
		}
		TextDrawParameters drawText =
		{
			name,
			0,
			pos,
			&GD->m_window
		};
		Text->BlitText(drawText);
	}
}

void GameplayManager::Display()
{
	Display_Background(m_background);
	Display_Map(m_mapSprite);
	for (int i = 0; i < m_players.size(); i++)
	{
		if (m_players[i] != NULL)
		{
			m_players[i]->Display();
		}
	}
	Display_Text(m_timerValue, m_playerTurn, m_windValue);
	Display_Particles(m_vector);
}

GameplayManager::~GameplayManager()
{

}