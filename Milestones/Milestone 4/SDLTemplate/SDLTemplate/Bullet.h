#pragma once
#include "GameObject.h"
#include "draw.h"
#include "common.h"

enum class Side
{
	PLAYER_SIDE,
	ENEMY_SIDE
};

class Bullet :
    public GameObject
{
public:
	Bullet(float positionX, float positionY, float directionX, float directionY, float speed, Side side);
	virtual void start();
	virtual void update();
	virtual void draw();
	int getPositionX();
	int getPositionY();
	int getWidth();
	int getHeight();
	Side getSide();
private:
	SDL_Texture* texture;
	Side side;
	int x;
	int y;
	int width;
	int height;
	int speed;
	float directionX;
	float directionY;
};

