#include "Player.h"
#include "Scene.h"

Player::~Player()
{
	// Memory manage our bullets. Delete all bullets on player deletion/death
	for (int i = 0; i < bullets.size(); i++)
	{
		delete bullets[i];
	}
	bullets.clear(); 
}

void Player::start()
{
	// Load Texture 
	texture = loadTexture("gfx/player.png");

	// Initialize to avoid garbage values
	x = 100;
	y = 100;
	width = 0;
	height = 0;
	speed = 2;
	reloadtime = 8; // Reload time of 8 frames, or 0.13 seconds since we're running in 60 frames/sec
	currentReloadTime = 0;

	// Query the texture to set our	width and height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	// Load sound
	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
}

void Player::update()
{
	if (app.keyboard[SDL_SCANCODE_W]) {
		y -= speed;
	}

	if (app.keyboard[SDL_SCANCODE_S]) {
		y += speed;
	}

	if (app.keyboard[SDL_SCANCODE_A]) {
		x -= speed;
	}

	if (app.keyboard[SDL_SCANCODE_D]) {
		x += speed;
	}

	// Decrement the player's reload timer
	if (currentReloadTime > 0)
		currentReloadTime--;

	if (app.keyboard[SDL_SCANCODE_F] && currentReloadTime == 0) {
		SoundManager::playSound(sound);
		Bullet* bullet = new Bullet(x + width, y - 2 + height / 2, 1, 0, 10);
		bullets.push_back(bullet);
		getScene()->addGameObject(bullet);
		bullet->start();

		// After firing, reset our reload timer
		currentReloadTime = reloadtime; 
	}

	// Memory manage our bullets. When they go off screen, delete them
	for (int i = 0; i < bullets.size(); i++) 
	{
		if (bullets[i]->getPositionX() > SCREEN_WIDTH)
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

void Player::draw()
{
	blit(texture, x, y);
}


