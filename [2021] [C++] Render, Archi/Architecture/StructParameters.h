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
	int maxLoop = 1;
};

//For each object
//{ (int)currentFrame,
//   (float) currentTime,
//   (int) loopPlayed,
//   (bool) loop,
//   (bool) stop }
struct ObjectAnimParam
{
	int currentFrame = 0;
	float currentTime = 0;
	int loopPlayed = 0;
	bool loop = true;
	bool stop = false;
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
//   (sf::BlendMode) blend,
//   (std::string) shader }
struct SpriteDrawParameters
{
	std::string name;
	float angle;
	sf::Vector2f pos;
	sf::RenderWindow* window;
	sf::BlendMode blend;
	std::string shader;
};

//For Text BlitText
//{ (std::string)name,
//   (float) angle,
//   (sf::Vector2f) pos,
//   (sf::RenderWindow*)window 
//   (sf::BlendMode) blend,
//   (std::string) shader }
struct TextDrawParameters
{
	std::string name;
	float angle;
	sf::Vector2f pos;
	sf::RenderWindow* window;
	sf::BlendMode blend;
	std::string shader;
};

//For Anim DrawAnim
//{ (std::string)name,
//   (float) angle,
//   (sf::Vector2f) pos,
//   (sf::RenderWindow*)window 
//   (sf::BlendMode) blend,
//   (std::string) shader }
struct AnimDrawParameters
{
	std::string name;
	float angle;
	sf::Vector2f pos;
	sf::RenderWindow* window;
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

struct Element
{
	int x;
	int y;
	float timer;
	Element* ptrSuivant;
};
