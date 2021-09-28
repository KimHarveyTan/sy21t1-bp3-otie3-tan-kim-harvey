#include "Enemy.h"
#include "Scene.h"

Enemy::Enemy()
{

}

Enemy::~Enemy()
{

}

void Enemy::start()
{
	// Load Texture 
	texture = loadTexture("gfx/enemy.png");

	// Initialize to avoid garbage values
	directionX = -1;
	directionY = 1;
	width = 0;
	height = 0;
	speed = 2;
	reloadtime = 60; // Reload time of 60 frames, or 1 seconds since we're running in 60 frames/sec
	currentReloadTime = 0;
	directionChangeTime = (rand() % 301) + 180; // Direction change time of 3-8 seconds
	currentDirectionChangeTime = 0;

	// Query the texture to set our	width and height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	// Load sound
	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
}

void Enemy::update()
{
	x += directionX * speed;
	y += directionY * speed;

	if (currentDirectionChangeTime > 0)
		currentDirectionChangeTime--;

	if (currentDirectionChangeTime == 0)
	{
		directionY = -directionY;
		currentDirectionChangeTime = directionChangeTime;
	}

	if (currentReloadTime > 0)
		currentReloadTime--;

	if (currentReloadTime == 0) 
	{
		float dx = -1;
		float dy = 0;

		calcSlope(playerTarget->getPositionX(), playerTarget->getPositionY(), x, y, &dx, &dy);

		SoundManager::playSound(sound);
		Bullet* bullet = new Bullet(x + width, y - 2 + height / 2, dx, dy, 10);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);

		// After firing, reset our reload timer
		currentReloadTime = reloadtime;
	}

	// Memory manage our bullets. When they go off screen, delete them
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->getPositionX() < 0)
		{
			// Cache the variable so we can delete this later
			// We can't delete it after erasing from the vector (leaked pointer)
			Bullet* bulletToErase = bullets[i];
			bullets.erase(bullets.begin() + i);
			delete bulletToErase;

			// We can't mutate or change (delete) our vector while looping inside it 
			// This might crash on the next loop iteration
			// To counter that, we only delete one bullet per frame
			// We can also avoid lag this way 
			break;
		}
	}
}

void Enemy::draw()
{
	blit(texture, x, y);
}

void Enemy::setPlayerTarget(Player* player)
{
	playerTarget = player; 
}

void Enemy::setPosition(int xPos, int yPos)
{
	this->x = xPos;
	this->y = yPos;
}
