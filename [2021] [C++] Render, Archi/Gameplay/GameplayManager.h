#ifndef GAMEPLAYMANAGER__H
#define GAMEPLAYMANAGER__H

#include "Vector.h"

class Button;
class Projectile;

class GameplayManager
{
private:
	std::string m_background;
	std::string m_playerTurn;
	std::string m_windValue;
	std::string m_timerValue;
	sf::Image m_mapImage;
	sf::Texture m_mapTex;
	sf::Sprite m_mapSprite;
	std::vector <Player*> m_players;
	std::vector <Button*> m_buttons;
	std::vector <Projectile*> m_proj;
	int m_slopeLimit = 10;
	int m_currentPlayer = 0;
	bool m_nextTurn = true;
	float m_timer = 10.0f;
	Vec m_vector;

public:
	GameplayManager();
	void Load(int _amount);
	void MousePressed(sf::Event _event);
	void MouseMoved(sf::Event _event);
	void KeyPressed(sf::Event _event);
	void CreateExplosion(int _id);
	void Explode(int _id);
	void Test_PlayersCollisions(int _id1, int _id2);
	void Test_ProjectilesCollisions(int _id);
	void Update();
	void Display();
	~GameplayManager();
};

#endif