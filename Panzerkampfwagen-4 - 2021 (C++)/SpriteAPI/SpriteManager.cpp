#include "definitions.h"
#include "SpriteManager.h"
#include "ShaderManager.h"

SpriteManager::SpriteManager()
{

}

SpriteManager* SpriteManager::Get_Instance()
{
	static SpriteManager instance;
	return &instance;
}

sf::Sprite SpriteManager::LoadSprite(SpriteSettings _settings)
{
	sf::Sprite tempSprite;
	sf::Texture* tempTexture = new sf::Texture();
	tempTexture->loadFromFile("../Assets/Images/" + _settings.path + ".png");
	tempSprite.setTexture(*tempTexture);
	sf::Vector2u tempSize = tempTexture->getSize();
	if (_settings.isCentered)
	{
		tempSprite.setOrigin(tempSize.x / 2, tempSize.y / 2);
	}
	tempSprite.setScale(_settings.scale.x, _settings.scale.y);

	return tempSprite;
}

bool SpriteManager::CheckName(std::string _name)
{
	if (m_SpriteVec.empty())
	{
		return 1;
	}
	else
	{
		for (int i = 0; i < m_SpriteVec.size(); i++)
		{
			if (m_SpriteVec[i].name == _name)
			{
				return 0;
			}
		}
		return 1;
	}
}

void SpriteManager::FillVectors(SpriteSettings _settings)
{
	if (CheckName(_settings.name))
	{
		//be careful, the file must be a ".png".
		sf::Sprite tempSprite = SpriteManager::LoadSprite(_settings);
		Sprite sprite = { tempSprite, _settings.name };

		//Fills the corresponding array.
		m_SpriteVec.push_back(sprite);
	}
}

sf::Sprite SpriteManager::GetSprite(std::string _name)
{
	for (int i = 0; i < m_SpriteVec.size(); i++)
	{
		if (m_SpriteVec[i].name == _name)
		{
			return m_SpriteVec[i].sprite;
		}
	}
}

void SpriteManager::SetPos(std::string _name, sf::Vector2f _pos)
{
	for (int i = 0; i < m_SpriteVec.size(); i++)
	{
		m_SpriteVec[i].sprite.setPosition(_pos);
	}
}

sf::Vector2f SpriteManager::GetPos(std::string _name)
{
	for (int i = 0; i < m_SpriteVec.size(); i++)
	{
		if (m_SpriteVec[i].name == _name)
		{
			return m_SpriteVec[i].sprite.getPosition();
		}
	}
}

void SpriteManager::SetOrigin(std::string _name, int _choice)
{
	sf::Vector2f center;
	for (int i = 0; i < m_SpriteVec.size(); i++)
	{
		if (m_SpriteVec[i].name == _name)
		{
			sf::Vector2u temp = m_SpriteVec[i].sprite.getTexture()->getSize();
			switch ((Centering)_choice)
			{
			case CENTER: center = sf::Vector2f( temp.x/2, temp.y/2 ); break;
			case CENTER_RIGHT: center = sf::Vector2f(temp.x, temp.y/2 ); break;
			case CENTER_LEFT: center = sf::Vector2f(0, temp.y/2 ); break;
			case BOTTOM_CENTER: center = sf::Vector2f(temp.x / 2, temp.y); break;
			case BOTTOM_RIGHT: center = sf::Vector2f(temp.x, temp.y ); break;
			case BOTTOM_LEFT: center = sf::Vector2f(0, temp.y ); break;
			case TOP_CENTER: center = sf::Vector2f(temp.x/2, 0); break;
			case TOP_RIGHT: center = sf::Vector2f(temp.x, 0 ); break;
			case TOP_LEFT: center = sf::Vector2f(0, 0 ); break;
			default: std::cout << "Error in the Sprite SetOrigin function" << '\n';  break;
			}
			m_SpriteVec[i].sprite.setOrigin(center);
		}
	}
}

sf::Vector2f SpriteManager::GetOrigin(std::string _name)
{
	for (int i = 0; i < m_SpriteVec.size(); i++)
	{
		if (m_SpriteVec[i].name == _name)
		{
			return m_SpriteVec[i].sprite.getOrigin();
		}
	}
}

void SpriteManager::SetScale(std::string _name, sf::Vector2f _scale)
{
	for (int i = 0; i < m_SpriteVec.size(); i++)
	{
		if (m_SpriteVec[i].name == _name)
		{
			m_SpriteVec[i].sprite.setScale(_scale);
		}
	}
}

sf::Vector2f SpriteManager::GetScale(std::string _name)
{
	for (int i = 0; i < m_SpriteVec.size(); i++)
	{
		if (m_SpriteVec[i].name == _name)
		{
			return m_SpriteVec[i].sprite.getScale();
		}
	}
}

void SpriteManager::BlitSprite(SpriteDrawParameters _parameters)
{
	ShaderManager* Shader = ShaderManager::Get_Instance();
	for (int i = 0; i < m_SpriteVec.size(); i++)
	{
		if (m_SpriteVec[i].name == _parameters.name)
		{
			m_SpriteVec[i].sprite.setPosition(_parameters.pos);
			m_SpriteVec[i].sprite.setRotation(_parameters.angle);
			sf::Shader* loadShader = Shader->GetShader("Default");
			if (Shader->GetShader(_parameters.shader) != NULL)
			{
				loadShader = Shader->GetShader(_parameters.shader);
			}
			sf::RenderStates tempState;
			tempState.shader = loadShader;
			tempState.blendMode = _parameters.blend;
			tempState.transform = sf::Transform::Identity;
			tempState.texture = NULL;
			_parameters.window->draw(m_SpriteVec[i].sprite, tempState);
		}
	}
}
void SpriteManager::DeleteSprite(std::string _name)
{
	for (int i = 0; i < m_SpriteVec.size(); i++)
	{
		if (m_SpriteVec[i].name == _name)
		{
			delete m_SpriteVec[i].sprite.getTexture();
			m_SpriteVec.erase(m_SpriteVec.begin() + i);
		}
	}
}
void SpriteManager::DeleteVector()
{
	for (int i = 0; i < m_SpriteVec.size(); i++)
	{
		delete m_SpriteVec[i].sprite.getTexture();
	}
	m_SpriteVec.clear();
}

SpriteManager::~SpriteManager()
{
	for (int i = 0; i < m_SpriteVec.size(); i++)
	{
		delete m_SpriteVec[i].sprite.getTexture();
	}
	m_SpriteVec.clear();
}