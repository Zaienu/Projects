#ifndef PLAYER__H
#define PLAYER__H

#define SCALE 0.35;

class Projectile;

struct Angle
{
	float chassis;
	float canon;
};

struct Pos
{
	sf::Vector2f chassis;
	sf::Vector2f canon;
};

struct Params
{
	int hp;
	Pos pos;
	int power = 1;
	Angle angle;
	bool isAlive = true;
	int score;
	sf::Vector2f radius;
	sf::Vector2f projPos;
	Direction dir;
	int speed;
	PlayerStates state;
	sf::Keyboard::Key keys[3];
	int shots = 1;
	int slope[2];
	bool controls = true;
	bool right = true;
	bool left = true;
};

class Player
{
	friend class GameplayManager;
private:

	std::vector <ObjectAnimParam*> m_animsParam;
	std::vector <std::string> m_chassis;
	std::string m_canon;
	std::string m_ammo;
	sf::Vector2f m_corners[2];
	Projectile* m_proj;
	Params m_pr;
	sf::RectangleShape m_frame;
	sf::RectangleShape m_charge;
	float m_timer;
	bool m_canShoot;

public:

	Player(int _id);
	void Load(int _id);

	//Setters + Getters
	sf::Vector2f Get_TankPos();
	void Set_TankPos(sf::Vector2f _pos);

	int Get_Health();
	void Add_Health(int _damages);

	int Get_Power();
	void Add_Power(int _pow);

	float Get_TankAngle();
	void Set_TankAngle(float _angle);

	bool Get_Status();
	void Set_Status(bool _status);

	int Get_Score();
	void Add_Score(int _score);

	void Activate_Controls();
	void Deactivate_Controls();
	void Can_MoveLR(int _dir, int _slope = 0);

	sf::Vector2f Get_Corners(int _choice);

	void MousePressed();
	void MouseMoved();
	void KeyPressed();
	void Update();
	void Display();
	~Player();

};

#endif