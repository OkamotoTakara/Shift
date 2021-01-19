#pragma once
#include "GameObject.h"

class Player : public GameObject
{
private:
	float jumpVel;
	bool isground;
	int flont;
	int back;
public:
	Player(float posX,float posY,unsigned char buttonNum,bool nowMode,int drawType);

	void modeChange();
	void jump();
	void catches();
	void shoot();
	void update(float posX, float posY, float radius, bool nowMode);
	void draw();

	bool getIsMode();
	float getPosX();
	float getPosY();
	float getOldPosX();
	float getOldPosY();
	float getRadius();
	
	void setIsMode(bool isMode);
	void setPosX(float posX);
	void setPosY(float posY);
	void setVelocity(float velocity);
};

