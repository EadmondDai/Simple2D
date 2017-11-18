#pragma once
#include <sfml/Graphics.hpp>
#include <stdio.h>
#include <math.h>

#include "Laser.h"
//#include "GamePlay.h"

using namespace sf;

extern RenderWindow RENDERINGWINDOW;
extern float ScaleDownSize;

class PlayerShip
{
public:
	const double PI = std::atan(1.0) * 4;

	//float ThrustChangeTime = 0.02;
	//float ThrustChangeLeftTime = 0;
	//bool IfShowThrust = false;

	//double RotateRadianUnitDefault = 1;
	double RotateRadianUnit = 1;
	//double RotateRadianUnitAdd = 0.01;

	bool Upgraded = false;

	float MapWidth;
	float MapHeight;
	float WindowWidth;
	float WindowHeight;

	const float WindowX = 400;
	const float WindowY = 300;
	float X = 400;
	float Y = 300;

	float ShipHalfLength = 20;

	double DirectionX = 0;
	double DirectionY = -1;

	float Speed = 10;
	float SpeedDown = 1;
	float ThrustSpeed = 10;
	float MaxSpeed = 50;

	float ShootRate = 0.75;

	float NextShootTimeLeft = 0;
	float BulletDistance = 15;

	void Init(int x, int y, int wideth, int height)
	{
		X = x;
		Y = y;
		MapWidth = wideth;
		MapHeight = height;
		WindowWidth = wideth;
		WindowHeight = height;
	}

	void TurnToPoint(float deltaTime, float x, float y);

	void Update(float deltaTime);
	void Accelerate() {
		Speed += ThrustSpeed;
		if (Speed > MaxSpeed)
			Speed = MaxSpeed;
	};
	void Draw();


	Texture ShipTexture1W;

	Sprite MyShipSprite;

	PlayerShip();
	~PlayerShip();
};

