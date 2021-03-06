#include "Player.hpp"
#include <string>

Player::Player( void ) {

}

Player::Player( const Player & srcObj ) {
	this->operator=( srcObj );
}

Player & Player::operator=( const Player & srcObj ) {
	this->x = srcObj.x;
	this->y = srcObj.y;
	return (*this);
}

Player::~Player( void ) {

}

Player::Player(int maxX, int maxY){
	this->maxX = maxX;
	this->maxY = maxY;
	this->x = 5;
	this->y = 5;
	this->chr = '>';
	this->state = 1;
}

void	Player::updatePos(int x, int y){
	if (x > 0)
	{
		if (this->x + x == maxX-2)
			return;
		else
			this->x += x;
	}
	if (x < 0)
	{
		if (this->x + x == 1)
			return;
		else
			this->x += x;
	}
	if (y > 0)
	{
		if (this->y + y == maxY-4)
			return;
		else
			this->y += y;
	}
	if (y < 0)
	{
		if (this->y + y == 1)
			return;
		else
			this->y += y;
	}
}
