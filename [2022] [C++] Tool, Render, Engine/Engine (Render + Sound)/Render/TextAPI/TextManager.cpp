#include "Definitions.h"
#include "TextManager.h"
#include "ShaderManager.h"

TextManager::TextManager()
{
}

TextManager* TextManager::Get_Instance()
{
	static TextManager instance;
	return &instance;
}

sf::Text TextManager::LoadText(TextSettings _settings)
{
	sf::Text tempText;
	sf::Font* tempFont = new sf::Font();
	tempFont->loadFromFile("../Assets/Fonts/" + _settings.fontName + ".ttf");
	tempText.setFont(*tempFont);
	tempText.setFillColor(_settings.color);
	tempText.setCharacterSize(_settings.size);
	return tempText;
}

bool TextManager::CheckName(std::string _name)
{
	if (m_TextVec.empty())
	{
		return 1;
	}
	else
	{
		for (int i = 0; i < m_TextVec.size(); i++)
		{
			if (m_TextVec[i].name == _name)
			{
				return 0;
			}
		}
		return 1;
	}
}

void TextManager::FillVectors(TextSettings _settings)
{
	if (CheckName(_settings.name))
	{
		sf::Text tempText = TextManager::LoadText(_settings);
		Text text = { tempText, _settings.name };

		//Fills the corresponding array.
		m_TextVec.push_back(text);
	}
}

void TextManager::SetPos(std::string _name, sf::Vector2f _pos)
{
	for (int i = 0; i < m_TextVec.size(); i++)
	{
		if (m_TextVec[i].name == _name)
		{
			m_TextVec[i].text.setPosition(_pos);
		}
	}
}

sf::Vector2f TextManager::GetPos(std::string _name)
{
	for (int i = 0; i < m_TextVec.size(); i++)
	{
		if (m_TextVec[i].name == _name)
		{
			return m_TextVec[i].text.getPosition();
		}
	}
}

sf::Vector2f TextManager::GetSize(std::string _name)
{
	for (int i = 0; i < m_TextVec.size(); i++)
	{
		if (m_TextVec[i].name == _name)
		{
			sf::Vector2f result =
			{
				m_TextVec[i].text.getLocalBounds().width,
				m_TextVec[i].text.getLocalBounds().height
			};
			return result;
		}
	}
}

void TextManager::SetScale(std::string _name, sf::Vector2f _scale)
{
	for (int i = 0; i < m_TextVec.size(); i++)
	{
		if (m_TextVec[i].name == _name)
		{
			m_TextVec[i].text.setScale(_scale);
		}
	}
}

sf::Vector2f TextManager::GetScale(std::string _name)
{
	for (int i = 0; i < m_TextVec.size(); i++)
	{
		if (m_TextVec[i].name == _name)
		{
			return m_TextVec[i].text.getScale();
		}
	}
}

void TextManager::SetOrigin(std::string _name, int _choice)
{
	sf::Vector2f center;
	for (int i = 0; i < m_TextVec.size(); i++)
	{
		if (m_TextVec[i].name == _name)
		{
			sf::Vector2u temp;
			temp.x = m_TextVec[i].text.getGlobalBounds().width + m_TextVec[i].text.getLocalBounds().left * 2;
			temp.y = m_TextVec[i].text.getGlobalBounds().height + m_TextVec[i].text.getLocalBounds().top * 2;
			switch ((Centering)_choice)
			{
			case CENTER: center = sf::Vector2f(temp.x / 2, temp.y / 2); break;
			case CENTER_RIGHT: center = sf::Vector2f(temp.x, temp.y / 2); break;
			case CENTER_LEFT: center = sf::Vector2f(0, temp.y / 2); break;
			case BOTTOM_CENTER: center = sf::Vector2f(temp.x / 2, temp.y); break;
			case BOTTOM_RIGHT: center = sf::Vector2f(temp.x, temp.y); break;
			case BOTTOM_LEFT: center = sf::Vector2f(0, temp.y); break;
			case TOP_CENTER: center = sf::Vector2f(temp.x / 2, 0); break;
			case TOP_RIGHT: center = sf::Vector2f(temp.x, 0); break;
			case TOP_LEFT: center = sf::Vector2f(0, 0); break;
			default: std::cout << "Error in the Sprite SetOrigin function" << '\n';  break;
			}
			m_TextVec[i].text.setOrigin(center);
		}
	}
}

sf::Vector2f TextManager::GetOrigin(std::string _name)
{
	for (int i = 0; i < m_TextVec.size(); i++)
	{
		if (m_TextVec[i].name == _name)
		{
			return m_TextVec[i].text.getOrigin();
		}
	}
}

void TextManager::SetString(std::string _name, std::string _string)
{
	for (int i = 0; i < m_TextVec.size(); i++)
	{
		if (m_TextVec[i].name == _name)
		{
			m_TextVec[i].text.setString(_string);
		}
	}
}

void TextManager::BlitText(TextDrawParameters _parameters)
{
	ShaderManager* Shader = ShaderManager::Get_Instance();
	for (int i = 0; i < m_TextVec.size(); i++)
	{
		if (m_TextVec[i].name == _parameters.name)
		{
			m_TextVec[i].text.setPosition(_parameters.pos);
			m_TextVec[i].text.setRotation(_parameters.angle);
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
			if (_parameters.window != NULL)
			{
				_parameters.window->draw(m_TextVec[i].text, tempState);
			}
			else
			{
				_parameters.texture->draw(m_TextVec[i].text, tempState);
			}
		}
	}
}
void TextManager::DeleteText(std::string _name)
{
	for (int i = 0; i < m_TextVec.size(); i++)
	{
		if (m_TextVec[i].name == _name)
		{
			delete m_TextVec[i].text.getFont();
			m_TextVec.erase(m_TextVec.begin() + i);
		}
	}
}
void TextManager::DeleteVector()
{
	for (int i = 0; i < m_TextVec.size(); i++)
	{
		delete m_TextVec[i].text.getFont();
	}
	m_TextVec.clear();
}

TextManager::~TextManager()
{
		for (int i = 0; i < m_TextVec.size(); i++)
		{
			delete m_TextVec[i].text.getFont();
		}
		m_TextVec.clear();
}