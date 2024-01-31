#include "definitions.h"
#include "GameData.h"
#include "Camera.h"

Camera::Camera(sf::Vector2f _pos)
{
	m_camera.setCenter(_pos);
	m_camera.setSize(SWIDTH, SHEIGHT);
}

void Camera::SetCenter()
{

}

void Camera::Zoom()
{

}

void Camera::Activate()
{

}

Camera::~Camera()
{

}