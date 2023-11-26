#include "GameData.h"
#include "definitions.h"
#include "Player.h"
#include "Projectile.h"
#include "AnimationManager.h"
#include "SpriteManager.h"
#include "SoundManager.h"

#define TANKWIDTH 40

Player::Player(int _id)
{
	Load(_id);
}

void Player::Load(int _id)
{
	AnimationManager* Anim = AnimationManager::Get_Instance();
	SpriteManager* Sprite = SpriteManager::Get_Instance();

	//Keybinds depending on the player.
	switch (_id)
	{
	case 0:
		m_pr.keys[0] = sf::Keyboard::Key::D;
		m_pr.keys[1] = sf::Keyboard::Key::Q;
		m_pr.keys[2] = sf::Keyboard::Key::S;
		break;
	case 1:
		m_pr.keys[0] = sf::Keyboard::Key::K;
		m_pr.keys[1] = sf::Keyboard::Key::H;
		m_pr.keys[2] = sf::Keyboard::Key::J;
		break;
	case 2:
		m_pr.keys[0] = sf::Keyboard::Key::Right;
		m_pr.keys[1] = sf::Keyboard::Key::Left;
		m_pr.keys[2] = sf::Keyboard::Key::Down;
		break;
	case 3:
		m_pr.keys[0] = sf::Keyboard::Key::Numpad3;
		m_pr.keys[1] = sf::Keyboard::Key::Numpad1;
		m_pr.keys[2] = sf::Keyboard::Key::Numpad2;
		break;
	default:
		std::cout << "Error in the Player's Keybinding Switch" << '\n';
		break;
	}

	//Loads the 3 animations Left, Right & Idle.

	for (int i = 0; i < 3; i++)
	{

		//Tests the direction we need to load at which iteration.
		std::string state;
		i == 0 ? state = "Right" : state = "Left";
		if (i == 2)
		{
			state = "Idle";
		}

		//Loads Animation.
		AnimSettings chassisSettings =
		{
			"GameStates/Game/Tanks/Tank" + std::to_string(_id) + "/" + state + "/" + state,
			"Tank" + std::to_string(_id) + state,
			true,
			{0.35f,0.35f},
			{0, 4, 0.50f, 0}
		};

		//Sends the animation to its manager.
		Anim->FillVectors(chassisSettings);
		Anim->SetOrigin(chassisSettings.name, 3);

		//Saving the crucial data in the designated containers.
		ObjectAnimParam* objectParam = new ObjectAnimParam{ 0, 0.0f, 0, true, false };
		m_animsParam.push_back(objectParam);
		m_chassis.push_back(chassisSettings.name);
	}

	//Loads the canon.
	SpriteSettings canonSettings =
	{
		"GameStates/Game/Canons/Canon" + std::to_string(_id),
		"Canon" + std::to_string(_id),
		true,
		{0.35f,0.35f}
	};

	//Sends the Sprite to its manager.
	Sprite->FillVectors(canonSettings);
	Sprite->SetOrigin(canonSettings.name, 2);
	m_canon = canonSettings.name;

	//Power Bar
	m_frame.setFillColor(sf::Color::Black);
	m_frame.setSize({ 9, 24 });
	m_charge.setFillColor(sf::Color::Red);

	//Loads important parameters.
	m_pr.pos.chassis = sf::Vector2f((TANKWIDTH+2) + rand()%SWIDTH - 2*(TANKWIDTH+2), 0);
	m_pr.radius = { 31.5, 0 };
	m_pr.hp = 100;
	m_pr.isAlive = true;
	m_pr.power = 0;
	m_pr.angle.chassis = 0;
	m_pr.score = 0;
	m_pr.speed = 150;
	m_pr.state = IDLE;
	m_pr.dir = RIGHT;
}

//Setters + Getters
sf::Vector2f Player::Get_TankPos()
{
	return m_pr.pos.chassis;
}
void Player::Set_TankPos(sf::Vector2f _pos)
{
	m_pr.pos.chassis = _pos;
}

int Player::Get_Health()
{
	return m_pr.hp;
}
void Player::Add_Health(int _damages)
{
	m_pr.hp -= _damages;
}

int Player::Get_Power()
{
	return m_pr.power;
}
void Player::Add_Power(int _pow)
{
	m_pr.power += _pow;
}

float Player::Get_TankAngle()
{
	return m_pr.angle.chassis;
}
void Player::Set_TankAngle(float _angle)
{
	m_pr.angle.chassis = _angle;
}

bool Player::Get_Status()
{
	return m_pr.isAlive;
}
void Player::Set_Status(bool _status)
{
	m_pr.isAlive = _status;
}

int Player::Get_Score()
{
	return m_pr.score;
}
void Player::Add_Score(int _score)
{
	m_pr.score += _score;
}

void Player::Activate_Controls()
{
	m_pr.controls = true;
	m_pr.shots = 1;
}

void Player::Deactivate_Controls()
{
	m_pr.controls = false;
	m_pr.state = IDLE;
	m_pr.power = 0;
}

void Player::Can_MoveLR(int _dir, int _slope)
{
	if (_dir == 0)
	{
		m_pr.right = true;
		m_pr.slope[0] = _slope;
	}
	else if (_dir == 1)
	{
		m_pr.left = true;
		m_pr.slope[1] = _slope;
	}
	else
	{
		std::cout << "Error Can_MoveLR" << '\n';
	}
}

sf::Vector2f Player::Get_Corners(int _choice)
{
	if (_choice == 0)
	{
		return m_corners[0];
	}
	else if (_choice == 1)
	{
		return m_corners[1];
	}
	else
	{
		std::cout << "Error Get_Corners" << '\n';
	}
}

void Player::MousePressed()
{

}

void Player::MouseMoved()
{
	//Singletons.
	GameData* GD = GameData::Get_Instance();
	AnimationManager* Anim = AnimationManager::Get_Instance();
	SpriteManager* Sprite = SpriteManager::Get_Instance();

	//Vectors.
	sf::Vector2i mousePos = sf::Mouse::getPosition(GD->m_window);
	sf::Vector2f tempScale = Anim->GetScale(m_chassis[m_chassis.size() - 1]);
	sf::Vector2f vect1;

	//Updates the scale to have an interactive idle.
	if (mousePos.x > m_pr.pos.chassis.x)
	{
		m_pr.dir = RIGHT;
		Anim->SetScale(m_chassis[m_chassis.size() - 1], { abs(tempScale.x), abs(tempScale.y) });
	}
	else if (mousePos.x <= m_pr.pos.chassis.x)
	{
		m_pr.dir = LEFT;
		Anim->SetScale(m_chassis[m_chassis.size() - 1], { -abs(tempScale.x), abs(tempScale.y) });
	}

	//Aims the canon toward the mouse.
	m_pr.angle.canon = atan2(mousePos.y - m_pr.pos.canon.y, mousePos.x - m_pr.pos.canon.x);

	//Locks the canon in a semi-circle.
	float chassis = m_pr.angle.chassis;
	float canon = m_pr.angle.canon *= 180 / PI;
	float agl = canon - chassis;
	if (agl > -90 && agl < 90)
	{
		m_pr.angle.canon = std::min(chassis, canon);
	}
	else
	{
		if (chassis < 0)
		{
			if (agl < 180 && agl > 90)
			{
				m_pr.angle.canon = chassis + 180;
			}
		}
		else
		{
			if (agl < -180 || agl > 0)
			{
				m_pr.angle.canon = chassis + 180;
			}
		}
	}
	//Put the canon's angle in radians to calculate the projectile's depart point
	m_pr.angle.canon = (m_pr.angle.canon * PI / 180);

	//Calculates the projectile's depart point.
	vect1.x = m_pr.radius.x * cos(m_pr.angle.canon) - m_pr.radius.y * sin(m_pr.angle.canon);
	vect1.y = m_pr.radius.x * sin(m_pr.angle.canon) + m_pr.radius.y * cos(m_pr.angle.canon);
	m_pr.projPos = sf::Vector2f(m_pr.pos.canon.x + vect1.x, m_pr.pos.canon.y + vect1.y);

	//Converts the angle to degrees for the rest of the calculus.
	m_pr.angle.canon *= 180 / PI;


	//Failed attempt to lock the canon
	//if (m_pr.angle.canon > 0 + angle && m_pr.angle.canon  < (PI / 2 + angle))
	//{
	//	m_pr.angle.canon = 0 + angle;
	//}
	//else if (m_pr.angle.canon < (PI + angle) && m_pr.angle.canon > (PI/2 + angle))
	//{
	//	m_pr.angle.canon = PI + angle;
	//}
	////Converts the angle to degrees.
	//m_pr.angle.canon *= 180 / PI;

}

void Player::KeyPressed()
{
	//Singletons.
	GameData* GD = GameData::Get_Instance();
	SoundManager* Sound = SoundManager::Get_Instance();

	//Coefficient to lower speed when going backward.
	float coef = 0.0f;

	//Movements when a key is pressed and 
	//we are authorized to go toward the desired direction.
	if (sf::Keyboard::isKeyPressed(m_pr.keys[0]) && m_pr.right)
	{
		m_pr.dir == RIGHT ? coef = 1.0f : coef = 0.60f;
		m_pr.pos.chassis.x += m_pr.speed * coef * GD->m_frameTime;
		m_pr.pos.chassis.y -= m_pr.slope[0];
		m_pr.state = ROLL;
		m_pr.right = false;
	}
	else if (sf::Keyboard::isKeyPressed(m_pr.keys[1]) && m_pr.left)
	{
		m_pr.dir == LEFT ? coef = 1.0f : coef = 0.60f;
		m_pr.pos.chassis.x -= m_pr.speed * coef * GD->m_frameTime;
		m_pr.pos.chassis.y -= m_pr.slope[1];
		m_pr.state = ROLL;
		m_pr.left = false;
	}
	else
	{
		m_pr.state = IDLE;
	}
	//Setting Up the power
	if (sf::Keyboard::isKeyPressed(m_pr.keys[2]) && m_pr.shots != 0)
	{
		m_timer += GD->m_frameTime;
		m_pr.power = round(m_timer * 10);
		m_canShoot = true;
	}
	else if (!sf::Keyboard::isKeyPressed(m_pr.keys[2]) && m_pr.shots != 0 && m_canShoot)
	{
		m_canShoot = false;
		Projectile* projectile = new Projectile(m_pr.projPos, m_pr.angle.canon, m_pr.power);
		Sound->ManageEffect("Explosion", true);
		m_proj = projectile;
		m_pr.power = 0;
		m_timer = 0;
		m_pr.shots = 0;
	}
	//if the key is released then launch the projectile with the power given put the number of shots to 0, reset the timer and the power.
}

void Player::Update()
{
	//Singletons.
	GameData* GD = GameData::Get_Instance();
	AnimationManager* Anim = AnimationManager::Get_Instance();
	SpriteManager* Sprite = SpriteManager::Get_Instance();

	//Determining the index of the animation we need to update.
	int index = 0;

	//State Machine.
	if (!m_pr.state == IDLE)
	{
		//Updates the Movement Animations' pos.
		for (int i = 0; i < 2; i++)
		{
			Anim->SetPos(m_chassis[i], m_pr.pos.chassis);
		}

		//Movement animation index.
		index = m_pr.dir;
	}
	else
	{
		//Resets the animations except the idle's and start updating it.
		for (int i = 0; i < m_chassis.size() - 1; i++)
		{
			*m_animsParam[i] = { 0, 0.0f, 0,true,false };
		}

		//Idle animation index (always at the end).
		index = m_chassis.size() - 1;
	}

	//Sets the canon' origin at the center of the turret & adjust it to the chassis' angle.
	sf::Vector2f vect1;
	sf::Vector2f dist = { 0, -33 };
	float angle = (m_pr.angle.chassis * PI) / 180;
	vect1.x = dist.x * cos(angle) - dist.y * sin(angle);
	vect1.y = dist.x * sin(angle) + dist.y * cos(angle);
	m_pr.pos.canon = sf::Vector2f(m_pr.pos.chassis.x + vect1.x, m_pr.pos.chassis.y + vect1.y);
	Sprite->SetPos(m_canon, m_pr.pos.canon);

	//Sets Pos of Power Bars
	m_frame.setPosition({ m_pr.pos.canon.x, m_pr.pos.canon.y - 75 });
	m_charge.setPosition({ m_frame.getPosition().x + 2, m_frame.getPosition().y + m_frame.getSize().y - 2 });
	m_charge.setSize({ 5, -(float)(m_pr.power) });

	//Updates the Animation at the desired index.
	Anim->UpdateAnim(m_chassis[index], GD->m_frameTime, m_animsParam[index]);

	//Confines the player in the map Horizontally.
	if (m_pr.pos.chassis.x > SWIDTH - TANKWIDTH)
	{
		m_pr.pos.chassis.x = SWIDTH - TANKWIDTH;
	}
	else if (m_pr.pos.chassis.x < TANKWIDTH)
	{
		m_pr.pos.chassis.x = TANKWIDTH;
	}

	//Sprite->SetPos(m_ammo, { m_pr.projPos.x, m_pr.projPos.y });
	//Limits the power
	if (m_timer >= 2.0f)
	{
		m_timer = 0;
	}

	//Actualises Corners BL and BR
	sf::Sprite test = Anim->GetSprite(m_chassis[0]);
	int width = test.getLocalBounds().width * 0.35f;
	m_corners[0] = { m_pr.pos.chassis.x - width / 2 , m_pr.pos.chassis.y };
	m_corners[1] = { m_pr.pos.chassis.x + width / 2 , m_pr.pos.chassis.y };

	//Manages controls.
	if (m_pr.controls)
	{
		KeyPressed();
		MouseMoved();
	}
	if (m_proj != NULL)
	{
		m_proj->Update();
	}
}

void Player::Display()
{
	//Singletons.
	GameData* GD = GameData::Get_Instance();
	AnimationManager* Anim = AnimationManager::Get_Instance();
	SpriteManager* Sprite = SpriteManager::Get_Instance();

	//Draws the animation depending on the state and direction.
	int index;
	m_pr.state != IDLE ? index = m_pr.dir : index = 2;

	AnimDrawParameters chassisDraw =
	{
		m_chassis[index],
		m_pr.angle.chassis,
		{m_pr.pos.chassis},
		&GD->m_window
	};
	SpriteDrawParameters canonDraw =
	{
		m_canon,
		m_pr.angle.canon,
		m_pr.pos.canon,
		&GD->m_window
	};
	//if (m_pr.isAlive)
	//{
		Sprite->BlitSprite(canonDraw);
		Anim->DrawAnim(chassisDraw, m_animsParam[index]);
		if (m_proj != NULL)
		{
			m_proj->Display();
		}
		GD->m_window.draw(m_frame);
		GD->m_window.draw(m_charge);
	//}
}

Player::~Player()
{

}