#include "Definitions.h"
#include "SpriteManager.h"
#include "AnimationManager.h"
#include "GameData.h"

AnimationManager::AnimationManager()
{

}

AnimationManager* AnimationManager::Get_Instance()
{
	static AnimationManager instance;
	return &instance;
}

bool AnimationManager::CheckName(std::string _name)
{
	if (m_AnimVec.empty())
	{
		return 1;
	}
	else
	{
		for (int i = 0; i < m_AnimVec.size(); i++)
		{
			if (m_AnimVec[i].name == _name)
			{
				return 0;
			}
		}
		return 1;
	}
}

void AnimationManager::FillVectors(AnimSettings _settings)
{
	if (CheckName(_settings.name))
	{
		m_AnimVec.resize(m_AnimVec.size() + 1);
		SpriteManager* Sprite = SpriteManager::Get_Instance();
		for (int i = 0; i < _settings.param.frames; i++)
		{
			SpriteSettings spriteSettings = {
																	_settings.path + std::to_string(i),
																	_settings.name + std::to_string(i),
																	_settings.isCentered,
																	_settings.scale,
			};
			Sprite->FillVectors(spriteSettings);
			m_AnimVec.back().spriteVector.push_back(spriteSettings.name);
		}
		m_AnimVec.back().name = _settings.name;
		m_AnimVec.back().param = _settings.param;
	}
}

sf::Sprite AnimationManager::GetSprite(std::string _name)
{
	SpriteManager* Sprite = SpriteManager::Get_Instance();
	for (int i = 0; i < m_AnimVec.size(); i++)
	{
		if (m_AnimVec[i].name == _name)
		{
			return Sprite->GetSprite(m_AnimVec[i].spriteVector[0]);
		}
	}
}

void AnimationManager::SetPos(std::string _name, sf::Vector2f _pos)
{
	SpriteManager* Sprite = SpriteManager::Get_Instance();
	for (int i = 0; i < m_AnimVec.size(); i++)
	{
		if (m_AnimVec[i].name == _name)
		{
			for (int j = 0; j < m_AnimVec[i].spriteVector.size(); j++)
			{
				Sprite->SetPos(m_AnimVec[i].spriteVector[j], _pos);
			}
		}
	}
}

sf::Vector2f AnimationManager::GetPos(std::string _name)
{
	SpriteManager* Sprite = SpriteManager::Get_Instance();
	for (int i = 0; i < m_AnimVec.size(); i++)
	{
		if (m_AnimVec[i].name == _name)
		{
			return Sprite->GetPos(m_AnimVec[i].spriteVector[0]);
		}
	}
}

void AnimationManager::SetOrigin(std::string _name, int _choice)
{
	SpriteManager* Sprite = SpriteManager::Get_Instance();
	for (int i = 0; i < m_AnimVec.size(); i++)
	{
		if (m_AnimVec[i].name == _name)
		{
			for (int j = 0; j < m_AnimVec[i].spriteVector.size(); j++)
			{
				Sprite->SetOrigin(m_AnimVec[i].spriteVector[j], _choice);
			}
		}
	}
}

sf::Vector2f AnimationManager::GetOrigin(std::string _name)
{
	SpriteManager* Sprite = SpriteManager::Get_Instance();
	for (int i = 0; i < m_AnimVec.size(); i++)
	{
		if (m_AnimVec[i].name == _name)
		{
			return Sprite->GetOrigin(m_AnimVec[i].spriteVector[0]);
		}
	}
}

void AnimationManager::SetScale(std::string _name, sf::Vector2f _scale)
{
	SpriteManager* Sprite = SpriteManager::Get_Instance();
	for (int i = 0; i < m_AnimVec.size(); i++)
	{
		if (m_AnimVec[i].name == _name)
		{
			for (int j = 0; j < m_AnimVec[i].spriteVector.size(); j++)
			{
				Sprite->SetScale(m_AnimVec[i].spriteVector[j], _scale);
			}
		}
	}
}

sf::Vector2f AnimationManager::GetScale(std::string _name)
{
	SpriteManager* Sprite = SpriteManager::Get_Instance();
	for (int i = 0; i < m_AnimVec.size(); i++)
	{
		if (m_AnimVec[i].name == _name)
		{
			for (int j = 0; j < m_AnimVec[i].spriteVector.size(); j++)
			{
				return Sprite->GetScale(m_AnimVec[i].spriteVector[j]);
			}
		}
	}
}

bool AnimationManager::Get_Status(std::string _name, ObjectAnimParam* _para)
{
	for (int i = 0; i < m_AnimVec.size(); i++)
	{
		if (m_AnimVec[i].name == _name)
		{
			if (_para->currentFrame + 1
				== m_AnimVec[i].param.frames)
			{
				return 1;
			}
		}
	}
	return 0;
}


//Potentially useless function
void AnimationManager::Stop(std::string _name, ObjectAnimParam* _para)
{
	for (int i = 0; i < m_AnimVec.size(); i++)
	{
		if (m_AnimVec[i].name == _name)
		{
			_para->stop = true;
			_para->currentFrame = 0;
			_para->currentTime = 0.0f;
		}
	}
}

void AnimationManager::Resume(std::string _name, ObjectAnimParam* _para)
{
	for (int i = 0; i < m_AnimVec.size(); i++)
	{
		if (m_AnimVec[i].name == _name)
		{
			_para->stop = false;
		}
	}
}

sf::Color AnimationManager::GetColor(std::string _name)
{
	SpriteManager* Sprite = SpriteManager::Get_Instance();
	for (int i = 0; i < m_AnimVec.size(); i++)
	{
		if (m_AnimVec[i].name == _name)
		{
			for (int j = 0; j < m_AnimVec[i].spriteVector.size(); j++)
			{
				return Sprite->GetColor(m_AnimVec[i].spriteVector[j]);
			}
		}
	}
}

void AnimationManager::SetColor(std::string _name, sf::Color _color)
{
	SpriteManager* Sprite = SpriteManager::Get_Instance();
	for (int i = 0; i < m_AnimVec.size(); i++)
	{
		if (m_AnimVec[i].name == _name)
		{
			for (int j = 0; j < m_AnimVec[i].spriteVector.size(); j++)
			{
				Sprite->SetColor(m_AnimVec[i].spriteVector[j], _color);
			}
		}
	}
}

void AnimationManager::UpdateAnim(std::string _name, float _timer, ObjectAnimParam* _para)
{
	for (int i = 0; i < m_AnimVec.size(); i++)
	{
		if (m_AnimVec[i].name == _name)
		{
			if (!_para->stop)
			{
				_para->currentTime += _timer;
				if (_para->currentTime >= m_AnimVec[i].param.maxTime)
				{
					_para->currentTime = 0;
					_para->loopPlayed += 1;
				}
			}

			//currentFrame = frames * (currentTime / maxTime);
			_para->currentFrame =
				m_AnimVec[i].param.frames *
				(_para->currentTime /
					m_AnimVec[i].param.maxTime);

			if (!_para->loop)
			{
				if ((_para->loopPlayed ==
					m_AnimVec[i].param.maxLoop) &&
					(_para->currentFrame ==
						m_AnimVec[i].param.endFrame))
				{
					_para->stop = true;
					_para->loopPlayed = 0;
				}
			}
		}
	}
}


void AnimationManager::DrawAnim(AnimDrawParameters _pr, ObjectAnimParam* _para)
{
	SpriteManager* Sprite = SpriteManager::Get_Instance();
	GameData* GD = GameData::Get_Instance();
	for (int i = 0; i < m_AnimVec.size(); i++)
	{
		if (m_AnimVec[i].name == _pr.name)
		{
			SpriteDrawParameters spriteDrawParameter =
			{
				m_AnimVec[i].spriteVector[_para->currentFrame],
				_pr.angle,
				_pr.pos,
				&GD->m_window,
				_pr.texture,
				_pr.blend,
				_pr.shader
			};
			Sprite->BlitSprite(spriteDrawParameter);
		}
	}
}

void AnimationManager::ResetAnim(std::string _name, ObjectAnimParam* _para)
{
	for (int i = 0; i < m_AnimVec.size(); i++)
	{
		if (m_AnimVec[i].name == _name)
		{
			_para->currentFrame = 0;
			_para->currentTime = 0;
			_para->stop = false;
		}
	}
}

void AnimationManager::DeleteAnim(std::string _name)
{
	SpriteManager* Sprite = SpriteManager::Get_Instance();
	for (int i = 0; i < m_AnimVec.size(); i++)
	{
		if (m_AnimVec[i].name == _name)
		{
			for (int j = 0; j < m_AnimVec[i].spriteVector.size(); j++)
			{
				Sprite->DeleteSprite(m_AnimVec[i].spriteVector[j]);
			}
		}
		m_AnimVec.erase(m_AnimVec.begin() + i);
	}
}

void AnimationManager::DeleteVector()
{
	SpriteManager* Sprite = SpriteManager::Get_Instance();
	for (int i = 0; i < m_AnimVec.size(); i++)
	{
		for (int j = 0; j < m_AnimVec[i].spriteVector.size(); j++)
		{
			Sprite->DeleteSprite(m_AnimVec[i].spriteVector[j]);
		}
	}
	m_AnimVec.clear();
}

AnimationManager::~AnimationManager()
{
	SpriteManager* Sprite = SpriteManager::Get_Instance();
	for (int i = 0; i < m_AnimVec.size(); i++)
	{
		for (int j = 0; j < m_AnimVec[i].spriteVector.size(); j++)
		{
			Sprite->DeleteSprite(m_AnimVec[i].spriteVector[j]);
		}
	}
	m_AnimVec.clear();
}