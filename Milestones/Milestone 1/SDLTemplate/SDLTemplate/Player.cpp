#include "Player.h"

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

	// Query the texture to set our	width and height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
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

}

void Player::draw()
{
	blit(texture, x, y);
}


