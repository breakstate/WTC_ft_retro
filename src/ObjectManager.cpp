#include "ObjectManager.hpp"
#include <ncurses.h>
#include <time.h>

#define EC 5 // Enemy Count
#define MC 10 // Missile Count
#define EMC 10 // Enemy Missile Count

ObjectManager::ObjectManager( void ) {
}

ObjectManager::ObjectManager ( const ObjectManager & srcObj ) {
	this->operator=( srcObj );
}

ObjectManager & ObjectManager::operator=( const ObjectManager & srcObj ) {
	this->maxX = srcObj.maxX;
	return (*this);
}

ObjectManager::~ObjectManager( void ) {
	delete [] this->player;
	delete [] this->enemy;
	delete [] this->missile;
	delete [] this->enemy_missile;
}

ObjectManager::ObjectManager( int maxX, int maxY){
	this->ticks = 0;
	this->maxX = maxX;
	this->maxY = maxY;
	this->player = new Player( maxX, maxY );
	this->enemy = new Enemy[EC];
	this->missile = new Missile[MC];
	this->enemy_missile = new Missile[EMC];
}

void	ObjectManager::gameTickCounter() {
	if (this->ticks == 5)
		this->ticks = 0;
	else
		this->ticks += 1;
}

int		ObjectManager::getGameTick( void ) {
	return (this->ticks);
}


void	ObjectManager::playerFire( void ) {
	int i = -1;

	while (++i < 10){
		if (missile[i].isActive() == 0){
			missile[i].activate( this->player->getPosX() + 1, this->player->getPosY() );
			return;
		}
	}
}

Player *ObjectManager::getPlayer( void ) {
	return(this->player);
}

void	ObjectManager::objectCleaner( void ) {
	int i = -1;
	while ( ++i < MC ) {
		if (this->missile[i].isActive())
			if (this->missile[i].getPosX() > this->maxX - 3)
				this->missile[i].deactivate();
	}
	i = -1;
	while ( ++i < EC ) {
		if (this->enemy[i].isActive())
			if (this->enemy[i].getPosX() < 2)
				this->enemy[i].deactivate();
	}
}

void	ObjectManager::collisionManager( void ) {
	// loops through arrays of alive enemy_missiles, enemies and bullets
	int	i = -1;
	int k = -1;

	i = -1;
	while (++i < MC){ // Missile loop
		if (this->missile[i].isActive()) {
			while (++k < EC){
				if (this->enemy[k].isActive())
					if ((this->missile[i].selfCollision(this->enemy[k].getPosX(), this->enemy[k].getPosY())) ||
					(this->missile[i].selfCollision(this->enemy[k].getPosX() -1, this->enemy[k].getPosY())))
					 {
						this->missile[i].deactivate();
						this->enemy[k].deactivate();
					};
			}
		}
		k = -1;
	}
	i = -1;
	while (++i < EC){
		if (this->enemy[i].isActive())
			if ((this->enemy[i].selfCollision( this->player->getPosX(), this->player->getPosY())) ||
			(this->enemy[i].selfCollision( this->player->getPosX() + 1, this->player->getPosY()))){
				this->enemy[i].deactivate();
				this->player->deactivate();
			}
	}
}

void	ObjectManager::enemySpawner( void ) {
	int i = -1;
	if (this->ticks == 4){
		while (++i < EC){ // Enemy loop
			if (this->enemy[i].isActive() == 0){
				this->enemy[i].activate( this->maxX - 2, (rand() % (this->maxY -6)) +2);
			}
		}
	}
}

void	ObjectManager::moveManager( void ) {
	// loops through arrays of alive enemy_missiles, enemies and bullets	
	int	i = -1;
	while (++i < MC){ // Missile loop
		if (this->missile[i].isActive()){
			this->missile[i].updatePos( 1, 0 );
		}
	}
	i = -1;
	while (++i < EC){ // Enemy loop
		if (this->enemy[i].isActive() /*&& this->ticks == 4*/){
			this->enemy[i].updatePos( -1 , 0 ); //-1 to rand()
			return;
		}
	}
}

void	ObjectManager::drawManager( void ) {
	// loops through arrays of alive enemy_missiles, enemies and bullets
	int i = -1;
	this->player->drawSelf();
	while (++i < MC){ // Missile loop
		if (this->missile[i].isActive())
			this->missile[i].drawSelf();
	}
	i = -1;
	while (++i < EC){ // Enemy loop
		if (this->enemy[i].isActive()){
			this->enemy[i].drawSelf();
			return;
		}
	}
}

int     ObjectManager::getMaxX( void ) {
	return (this->maxX);
}

int     ObjectManager::getMaxY( void ) {
	return (this->maxY);
}