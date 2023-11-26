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
	tempFont->loadFromFile("../Assets/Fonts/" + _settings.fontName + ".otf");
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
		m_TextVec[i].text.setPosition(_pos);
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
			_parameters.window->draw(m_TextVec[i].text, tempState);
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