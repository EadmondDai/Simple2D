#include "stdafx.h"
#include "PlayerShip.h"
#include <stdio.h>
#include <iostream>

using namespace std;

void PlayerShip::Update(float deltaTime)
{
	NextShootTimeLeft -= deltaTime;

	Speed -= SpeedDown;
	if (Speed < 0)
		Speed = 0;

	X += Speed * DirectionX * deltaTime;
	Y += Speed * DirectionY * deltaTime;

	// check if the ship fly too far away.
	if (X <= 0)
	{
		X = 0;
	}

	if (X >= MapWidth)
	{
		X = MapWidth;
	}

	if (Y <= 0)
	{
		Y = 0;
	}

	if (Y >= MapHeight)
	{
		Y = MapHeight;
	}

	MyShipSprite.setPosition(X, Y);
}

void PlayerShip::TurnToPoint(float deltaTime, float x, float y)
{
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

	MyShipSprite.rotate(rotateValue / PI * 180);
}

void PlayerShip::Draw() 
{
	RENDERINGWINDOW.draw(MyShipSprite);
}

PlayerShip::PlayerShip()
{
	ShipTexture1W.loadFromFile("Pic/ShipNormal.png");

	MyShipSprite.setTexture(ShipTexture1W);
	MyShipSprite.setOrigin(120, 120);
	MyShipSprite.setScale(ScaleDownSize, ScaleDownSize);
	MyShipSprite.setPosition(X, Y);

}


PlayerShip::~PlayerShip()
{
}
