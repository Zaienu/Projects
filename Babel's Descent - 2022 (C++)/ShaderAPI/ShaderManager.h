#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

class ShaderManager
{
private:

	std::vector <Shader> m_ShaderVec;
	bool CheckName(std::string _name);
	ShaderManager();
	~ShaderManager();

public:

	static ShaderManager* Get_Instance();
	sf::Shader* LoadShader(ShaderSettings _settings);
	void FillVectors(ShaderSettings _settings);
	sf::Shader* GetShader(std::string _name);
};

#endif
