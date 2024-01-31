#ifndef CAMERA__H
#define CAMERA__H

class Camera
{
private:
	sf::View m_camera;
	sf::Vector2f pos;
	float m_zoom;
public:
	Camera(sf::Vector2f _pos);
	void SetCenter();
	void Zoom();
	void Activate();
	~Camera();
};

#endif