#ifndef DEFINITIONS__H
#define DEFINITIONS__H

#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL/freeglut.h>
#include "SFML/OpenGL.hpp"

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <time.h>
#include <cstring>
#include <vector>
#include <cmath>
#include <bitset>
#include <fstream>
#define NOMINMAX 1
#include <algorithm>
#include <windows.h>
#include <functional>

#define SWIDTH 1024
#define SHEIGHT 768
#define PI 3.14159265359
void BlitSpriteRT(sf::Sprite _sprite, int _x, int _y, float _angle, sf::RenderTexture* _rt);
float Distance(float _x1, float _y1, float _x2, float _y2);
float SqDistance(float _x1, float _y1, float _x2, float _y2);

enum Direction
{
	RIGHT,
	LEFT,
};

enum PlayerStates
{
	IDLE,
	ROLL,
	SHOOT,
	DEAD,
};

enum States
{
	MENU,
	SETTINGS,
	HIGHSCORES,
	GAME,
	GAMEOVER,
};

enum SoundType
{
	MUSIC,
	EFFECT,
};

struct Sound
{
	sf::Sound sound;
	std::string name;
};

struct Sprite
{
	sf::Sprite sprite;
	std::string name;
};


struct Text
{
	sf::Text text;
	std::string name;
};

struct Shader
{
	sf::Shader* shader;
	std::string name;
};

struct InputBox
{
	sf::RectangleShape rectangle;
	bool edit;
	std::string currentWord;
};

struct ParticlesSettings
{
	sf::Vector2f m_pos;
	float m_timer;
	std::string m_sprite;
	int speed;
};

#include "StructParameters.h"

#endif