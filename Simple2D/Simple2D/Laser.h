#pragma once
#include <sfml/Graphics.hpp>

using namespace sf;

extern RenderWindow RENDERINGWINDOW;
extern float ScaleDownSize;

class Laser
{
public:
	const double PI = std::atan(1.0) * 4;

	float X;
	float Y;

	float Speed = 0;
	float MaxSpeed = 200;
	float AddSpead = 10;

	float ImpactHalfLength = 20;

	float DirectionX;
	float DirectionY;

	float ExpireTime = 1; // Seconds
	float lifeTimeLeft = ExpireTime;
	float chaseTimeLeft = 1;

	double RotateRadianUnit = 2;

	int Damage = 2;

	void Update(float deltaTime);
	void Draw();

	void SetDirection(float DirectionX, float DirectionY, double pi);
	void SetPos(float X, float Y);
	void TurnToPoint(float deltaTime, float x, float y);

	Texture LaserTexture;
	Sprite LaserSprite;

	Laser();
	~Laser();
};

