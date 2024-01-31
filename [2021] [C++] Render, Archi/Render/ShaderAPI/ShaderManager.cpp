#include "Definitions.h"
#include "ShaderManager.h"

ShaderManager::ShaderManager()
{
	sf::Shader* tempShader = new sf::Shader;
	tempShader->loadFromFile("../Assets/Shaders/Default.frag", sf::Shader::Fragment);
	Shader shader = { tempShader, "Default" };
	m_ShaderVec.push_back(shader);
}

ShaderManager* ShaderManager::Get_Instance()
{
	static ShaderManager instance;
	return &instance;
}

sf::Shader* ShaderManager::LoadShader(ShaderSettings _settings)
{
	sf::Shader* tempShader = new sf::Shader;
	if (_settings.type == "Fragment")
	{
		tempShader->loadFromFile("../Assets/Shaders/" + _settings.path + ".frag", sf::Shader::Fragment);
	}
	else if (_settings.type == "Vertex")
	{
		tempShader->loadFromFile("../Assets/Shaders/" + _settings.path + ".vert", sf::Shader::Vertex);
	}
	return tempShader;
}

bool ShaderManager::CheckName(std::string _name)
{
	if (m_ShaderVec.empty())
	{
		return 1;
	}
	else
	{
		for (int i = 0; i < m_ShaderVec.size(); i++)
		{
			if (m_ShaderVec[i].name == _name)
			{
				return 0;
			}
		}
		return 1;
	}
}

void ShaderManager::FillVectors(ShaderSettings _settings)
{
	if (CheckName(_settings.name))
	{
		std::string name = _settings.name;
		//be careful, the file must be a ".vert" or ".frag"
		sf::Shader* tempShader = ShaderManager::LoadShader(_settings);
		Shader shader = { tempShader,  name };
		//Fills the corresponding array.
		m_ShaderVec.push_back(shader);
	}
}

sf::Shader* ShaderManager::GetShader(std::string _name)
{
	for (int i = 0; i < m_ShaderVec.size(); i++)
	{
		if (m_ShaderVec[i].name == _name)
		{
			return m_ShaderVec[i].shader;
		}
	}
	return 0;
}

ShaderManager::~ShaderManager()
{

}