#include "Libraries.h"

//For Sprite FillVector
//{  (std::string)path,
//   (std::string)name,
//   (bool)isCentered,
//   (int)scale }
struct SpriteSettings
{
	std::string path;
	std::string name;
	bool isCentered;
	sf::Vector2f scale;
};

//To Setup a new Shader
// (std::string) path,
// (std::string) name,
// (std::string) type }
struct ShaderSettings
{
	std::string path;
	std::string name;
	std::string type;
};

//For AnimSettings
//{ (int)endFrame,
//   (int)frames,
//   (float)maxTime,
//   (int)maxLoop, }
struct AnimParameters
{
	int endFrame;
	int frames;
	float maxTime;
	int maxLoop;
};

//For each object
//{ (int)currentFrame,
//   (float) currentTime,
//   (int) loopPlayed,
//   (bool) loop,
//   (bool) stop }
struct ObjectAnimParam
{
	int currentFrame;
	float currentTime;
	int loopPlayed;
	bool loop;
	bool stop;
};

//For Animation Constructor
//{ (std::string)path,
//	   (std::string)name,
//   (bool)isCentered,
//   (sf::Vector2f)scale
//   (AnimParameters) param }
struct AnimSettings
{
	std::string path;
	std::string name;
	bool isCentered;
	sf::Vector2f scale;
	AnimParameters param;
};

struct Animation
{
	std::vector <std::string> spriteVector;
	std::string name;
	AnimParameters param;
};
//For Text Constructor 
//{  (std::string)fontName,
//   (std::string)name,
//   (sf::Color)color,
//   (int)size }
struct TextSettings
{
	std::string fontName;
	std::string name;
	sf::Color color;
	int size;
};

//For Sprite BlitSprite
//{ (std::string)name,
//   (float) angle,
//   (sf::Vector2f) pos,
//   (sf::RenderWindow*)window;
//   (sf::RenderTexture*)texture;
//   (sf::BlendMode) blend,
//   (std::string) shader }
struct SpriteDrawParameters
{
	std::string name;
	float angle;
	sf::Vector2f pos;
	sf::RenderWindow* window;
	sf::RenderTexture* texture;
	sf::BlendMode blend;
	std::string shader;
};

//For Text BlitText
//{ (std::string)name,
//   (float) angle,
//   (sf::Vector2f) pos,
//   (sf::RenderWindow*)window 
//   (sf::RenderTexture*)texture;
//   (sf::BlendMode) blend,
//   (std::string) shader }
struct TextDrawParameters
{
	std::string name;
	float angle;
	sf::Vector2f pos;
	sf::RenderWindow* window;
	sf::RenderTexture* texture;
	sf::BlendMode blend;
	std::string shader;
};

//For Anim DrawAnim
//{ (std::string)name,
//   (float) angle,
//   (sf::Vector2f) pos,
//   (sf::RenderWindow*)window 
//   (sf::RenderTexture*)texture;
//   (sf::BlendMode) blend,
//   (std::string) shader }
struct AnimDrawParameters
{
	std::string name;
	float angle;
	sf::Vector2f pos;
	sf::RenderWindow* window;
	sf::RenderTexture* texture;
	sf::BlendMode blend;
	std::string shader;
};

//For Button Constructor
//{ (std::string)spritePaths[2],
//   (std::string)spriteNames[2],
//   (std::string)soundNames[2],
//   (sf::Vector2f)pos }
struct ButtonSettings
{
	std::string spritePaths[2];
	std::string spriteNames[2];
	std::string soundName[2];
	sf::Vector2f pos;
};

//For Inventory Constructor
//{ (WEAPON) weapon,
//	(ARMOR) armor,
//	(RessourcesStock) ressourcesStock}
struct InventorySettings
{
	WEAPON weapon;
	ARMOR armor;
	std::vector<int> ressourcesStock;
};

//For Weapon Constructor
//{ (std::string)category,
//   (int)type,
//   (float)damage,
//   (float)attackSpeed,
//   (float)range,
//   (float)effectDuration}
struct WeaponSettings
{
	std::string category;
	int type;
	float damage;
	float attackSpeed;
	float range;
	float effectDuration;
	bool inPossession;
};

//For Armor Constructor
//{ (std::string)category,
//   (int)type,
//   (float)resistancePhysique,
//   (float)resistanceMagic,
//   (float)speed}
struct ArmorSettings
{
	std::string category;
	int type;
	float resistancePhysique;
	float resistanceMagic;
	float speed;
};

//For Tower Constructor
//{ (enum Attribute)category,
//  (enum TowerType)type,
//  (std::string)name,
//  (int)cost[9],
//  (int)lvl,
//  (int)pv,
//  (int)max_Pv,
//  (int)attack,
//  (int)range,
//  (float)reloading,
//  (int)width,
//  (int)height,
//  (enum NbPrjectile)nbP,
//  (int)speedProjectile,
//  (int)lifeProjectile,
//}
struct TowerParameters
{
	Attribute category;
	TowerType type;
	std::string name;
	int cost[9];
	int lvl;
	float pv;
	float max_Pv;
	float attack;
	float range;
	float reloading;
	int width;
	int height;
	NbPrjectile nbP;
	float speedProjectile;
	float lifeProjectile;
	int nb_Frame;
	std::string animName;
	std::string animNameReverse;
	ObjectAnimParam animPar;
	bool activated;
};

//For Projectile Constructor
//{ (sf::Vector2f)pos,
//{ (sf::Vector2f)speed,
//  (sf::Vector2f)dest,
//  (float)angle,
//  (std::string)sprite,
//  (sf::CircleShape)hitbox,
//  (int)life,
//  (int)lvl,
//  (int)type,
//  (float)damageTimer,
//  (float)damage,
//  (enum ProjectileState)state,
//  (float)lifeTime,
//}
struct Projectile
{
	sf::Vector2f pos;
	sf::Vector2f speed;
	sf::Vector2f dest;

	float angle;
	std::string sprite;
	sf::CircleShape hitbox;

	int life;
	int lvl;
	int type;
	float damageTimer;
	float damage;
	ProjectileState state;
	float lifeTime;
};

//For Tower Function in the Update
//{ (sf::Vector2f)pos,
//  (sf::Vector2f)dest,
//  (std::string)sprite,
//  (float)speed,
//  (float)damage,
//  (int)life,
//  (int)lvl,
//  (int)type,
//  (enum ProjectileState)state,
//  (float)lifeTime,
//}
struct ProjectilePara
{
	sf::Vector2f pos;
	sf::Vector2f dest;
	std::string sprite;
	float speed;
	float damage;
	int life;
	int lvl;
	int type;
	ProjectileState state;
	float lifeTime;
};

//For Projectile Constructor
//{ (sf::Vector2f)pos,
// (sf::Vector2f)speed,
//  (enum [Direction])dir,
//  (sf::Vector2f)dest,
//  (float)range,
//  (std::string)sprite,
//  (sf::RectangleShape)hitbox,
//  (int)indice,
//  (int)life,
//  (float)damageTimer,
//  (float)damage,
//  (enum PlayerMoveState)state,
//  (enum SoldierState)target,
//}
struct Soldier
{
	sf::Vector2f pos;
	sf::Vector2f speed;
	Direction dir;
	sf::Vector2f dest;

	float range;
	std::string sprite;
	sf::RectangleShape hitbox;

	int indice;
	int life;
	float damageTimer;
	float damage;
	PlayerMoveState state;
	SoldierState target;
};

//For Tower Function in the Update
//{ (sf::Vector2f)pos,
//  (sf::Vector2f)dest,
//  (std::string)sprite,
//  (float)speed,
//  (float)damage,
//  (int)indice,
//  (int)life,
//  (enum PlayerMoveState)state,
//}
struct SoldierPara
{
	sf::Vector2f pos;
	sf::Vector2f dest;
	std::string sprite;
	float speed;
	float damage;
	int indice;
	int life;
	PlayerMoveState state;
};

//For Wave Constructor
//{	 (int)spawnerId,
//   (int)enemyType,
//   (int)nb_Enemy,
//   (float)TimeSpawn}
struct EnemySpawnSettings
{
	int spawnerId;
	int enemyType;
	int nb_Enemy;
	float timeSpawn;
	float timeInitSpawn;
};

//For Wave Constructor
//{ (int)waveNumber,
//   (float)waveTimer,
//   (std::vector<SpawnerSettings>)spawnerVector}
struct WaveSettings
{
	int waveNumber;
	float waveTimer;
	std::vector<EnemySpawnSettings> enemySpawnVector;
};

struct RectangleParameters
{
	sf::Vector2f pos;
	sf::Vector2f dim;
};

struct CircleParameters
{
	sf::Vector2f pos;
	float radius;
};

struct Enemy
{
	EnemyType type;
	float timer;
};

struct ConstructionCell
{
	sf::RectangleShape rect;
	bool inRange;
	bool occupied;
};

struct MapItem
{
	std::string name;
	bool type;
	sf::Vector2f pos;
	sf::Vector2f size;
};

struct MapRessource
{
	std::string name;
	sf::Vector2f pos;
};

struct MapSpawner
{
	std::string name;
	std::string path;
	sf::Vector2f pos;
	sf::Vector2f size;
	int id;
};

struct MapPath
{
	std::string path;
	int id;
	sf::Vector2f pos;
};

struct GridVect
{
	bool freeCell;
	sf::Vector2f pos;
	int towerId;
};

//sf::Vector2f pos
//sf::Vector2f speed
//sf::Sprite* sprite
//float lifeTime
//float angle
//float rotation
//bool gravity
//bool collision
//float alpha
//std::string type
//float scale
//bool inertia
//float inertiaCoef
//bool trail
//float trailTimerMax
//ParticleInfo* trailInfo
struct ParticleInfo
{
	sf::Vector2f pos;
	float speed;
	std::string sprite;
	float lifeTime;
	float angle;
	float rotation;
	bool gravity;
	bool collision;
	float alpha;
	std::string type;
	float scale;
	bool inertia;
	float inertiaCoef;
	bool trail;
	float trailTimerMax;
	ParticleInfo* trailInfo;
};

struct Emitter
{
	sf::Vector2f pos;
	std::string name;
	ParticleInfo particleInfo;
	float timer;
	float timerMax;
	float lifeTime;
};

//sf::Vector2f pos;
//std::string backSprite;
//std::string buttonSprite;
//std::string direction;
//std::string name;
struct SliderParam
{
	sf::Vector2f pos;
	std::string backSprite;
	std::string buttonSprite;
	std::string direction;
	std::string name;
	SettingsState settingsState;
};

//std::vector<std::string> names,
//std::vector<sf::Vector2f> pos,
//std::vector<void(*)()> ptr,
struct ButtonList
{
	std::vector <std::string> names;
	std::vector <sf::Vector2f> pos;
	std::vector <void(*)()>  pointerVec;
};

struct ChoiceBoxParam
{
	sf::Vector2f pos;
	std::vector<std::string> valueList;
	std::string name;
};

struct InputBoxParam
{
	sf::Vector2f pos;
	std::string name;
	sf::Keyboard::Key defaultInput;
};