#include "stdafx.h"
#include "Laser.h"

void Laser::SetDirection(float directionX, float directionY, double pi) 
{
	DirectionX = directionX;
	DirectionY = directionY;

	double radian = atan2(DirectionY, DirectionX);

	LaserSprite.setRotation(radian / pi * 180 + 90);
}

void Laser::SetPos(float x, float y)
{
	X = x;
	Y = y;

	LaserSprite.setPosition(X, Y);
}

void Laser::TurnToPoint(float deltaTime, float x, float y)
{
	if (chaseTimeLeft <= 0) return;
	chaseTimeLeft -= deltaTime;

	float otherX = x - X;
	float otherY = y - Y;

	//// Check if they are in the same position.
	//if (WindowX == x && WindowY == y)
	//	return;

	// check if they are in the same direction.
	if (otherY / otherX == DirectionY / DirectionX)
		return;

	//order of magnitudes
	float mag = otherX * DirectionX + otherY * DirectionY;
	double orderA = sqrtf(DirectionX * DirectionX + DirectionY * DirectionY);
	double orderB = sqrtf(otherX * otherX + otherY * otherY);

	double cosValue = mag / (orderA * orderB);

	if (cosValue < -1)
		cosValue = -1;

	if (cosValue > 1)
		cosValue = 1;

	double radian = acos(cosValue);

	// using * to decide the direction of the rotation angle.
	if (DirectionX * otherY - otherX * DirectionY < 0) // counterclockwise
	{
		radian = -radian;
	}

	// check if the rotate unit is bigger than the radian left.
	double rotateValue = radian * deltaTime * RotateRadianUnit;

	// Then rotate my object with the radian I have.
	// Calculate the new x and y first.
	double newDirectionX = DirectionX * cos(rotateValue) - DirectionY * sin(rotateValue);
	double newDIrectionY = DirectionX * sin(rotateValue) + DirectionY * cos(rotateValue);

	// Then normalnise the direction.
	//double sumTemp = newDirectionX * newDirectionX + newDIrectionY * newDIrectionY;
	DirectionX = newDirectionX;
	DirectionY = newDIrectionY;

	LaserSprite.rotate(rotateValue / PI * 180);
}

void Laser::Update(float deltaTime)
{
	lifeTimeLeft -= deltaTime;
	Speed += AddSpead;
	Speed = fmin(Speed, MaxSpeed);

	X += deltaTime * Speed * DirectionX;
	Y += deltaTime * Speed * DirectionY;

	LaserSprite.setPosition(X, Y);
}

void Laser::Draw()
{
	RENDERINGWINDOW.draw(LaserSprite);
}

Laser::Laser()
{
	LaserTexture.loadFromFile("Pic/Bullet.png");
	LaserSprite.setTexture(LaserTexture);
	LaserSprite.setOrigin(120, 120);
	LaserSprite.setScale(0.25 * 2, 0.25 * 2);
}


Laser::~Laser()
{
}
