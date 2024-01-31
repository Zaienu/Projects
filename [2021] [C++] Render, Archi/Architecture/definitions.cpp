#include "definitions.h"

void BlitSpriteRT(sf::Sprite _sprite, int _x, int _y, float _angle, sf::RenderTexture* _rt)
{
    _sprite.setPosition(sf::Vector2f(_x, _y));
    _sprite.setRotation(_angle);
    _rt->draw(_sprite);
}

float Distance(float _x1, float _y1, float _x2, float _y2)
{
    float ecartX = _x1 - _x2;
    float ecartY = _y1 - _y2;
    return sqrtf(powf(ecartX, 2) + powf(ecartY, 2));
}

float SqDistance(float _x1, float _y1, float _x2, float _y2)
{
    float ecartX = _x1 - _x2;
    float ecartY = _y1 - _y2;
    return powf(ecartX, 2) + powf(ecartY, 2);
}