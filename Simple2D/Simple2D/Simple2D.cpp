// Simple2D.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Main.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "PlayerShip.h"

using namespace std;
using namespace sf;

float MapWidth = 800;
float MapHeight = 600;
float WindowWidth = 800;
float WindowHeight = 600;

RenderWindow RENDERINGWINDOW(VideoMode(800, 600), "Simple2D");
float ScaleDownSize = 0.25;

vector<Laser*> MyLaserList;
vector<PlayerShip*> AIShips; // Two should be enough here.

PlayerShip myship;

void Render()
{
	RENDERINGWINDOW.clear();

	myship.Draw();

	for (auto laser : MyLaserList)
	{
		laser->Draw();
	}

	for (auto ship : AIShips)
	{
		ship->Draw();
	}

	RENDERINGWINDOW.display();
}

int main()
{
	// Init two ai ship trying to kill the player ship
	AIShips.push_back(new PlayerShip());
	AIShips.push_back(new PlayerShip());
	AIShips[0]->Init(10, 10, MapWidth, MapHeight);
	AIShips[1]->Init(MapWidth - 10, MapHeight - 10, MapWidth, MapHeight);

	Clock DeltaTimeClock;
	Event event;

	RENDERINGWINDOW.setFramerateLimit(60);

	myship.Init(MapWidth / 2, MapHeight / 2, MapWidth, MapHeight);

	while (RENDERINGWINDOW.isOpen())
	{
		if (RENDERINGWINDOW.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				RENDERINGWINDOW.close();
			}
		}

		if (DeltaTimeClock.getElapsedTime().asSeconds())
		{
			float deltaTime = DeltaTimeClock.restart().asSeconds();

			if (Mouse::isButtonPressed(Mouse::Left))
			{
				myship.Accelerate();

				if (myship.NextShootTimeLeft <= 0)
				{
					//myship.NextShootTimeLeft = myship.ShootRate;
					
					//Laser *laserPtr = new Laser();
					//MyLaserList.push_back(laserPtr);

					//double directionX = myship.DirectionX;
					//double directionY = myship.DirectionY;
					//float bulletDistance = myship.BulletDistance;

					//laserPtr->SetPos(myship.X + directionX * bulletDistance, myship.Y + directionY * bulletDistance);
					//laserPtr->SetDirection(directionX, directionY, myship.PI);
				}
			}

			// Get mouse pos and rotate the ship.
			Vector2i mousePos = Mouse::getPosition(RENDERINGWINDOW);
			myship.TurnToPoint(deltaTime, mousePos.x, mousePos.y);
			cout << endl << mousePos.x  << endl;
			cout << mousePos.y << endl;
			
			myship.Update(deltaTime);

			// update ai ship
			float x = myship.X;
			float y = myship.Y;
			for (auto AIShip : AIShips)
			{
				// In this case, I only need the ai turn to the player ship
				AIShip->TurnToPoint(deltaTime, x, y);

				if (AIShip->NextShootTimeLeft <= 0)
				{
					AIShip->NextShootTimeLeft = AIShip->ShootRate;

					Laser *laserPtr = new Laser();
					MyLaserList.push_back(laserPtr);

					double directionX = AIShip->DirectionX;
					double directionY = AIShip->DirectionY;
					float bulletDistance = AIShip->BulletDistance;

					laserPtr->SetPos(AIShip->X + directionX * bulletDistance, AIShip->Y + directionY * bulletDistance);
					laserPtr->SetDirection(directionX, directionY, AIShip->PI);

				}

				AIShip->Update(deltaTime);
			}


			// update laser
			float preX = myship.X + myship.DirectionX * fmax(myship.Speed, 10) * 10;
			float preY = myship.Y + myship.DirectionY * fmax(myship.Speed, 10) * 10;
			for (auto laser : MyLaserList)
			{
				laser->TurnToPoint(deltaTime, x, y);

				laser->Update(deltaTime);
			}

		}

		// Rendering here
		Render();
	}

	for (auto ship : AIShips)
		delete ship;

    return 0;
}



