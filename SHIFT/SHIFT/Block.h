#pragma once
#include "GameObject.h"
#include  "Stage.h"
class Block : public GameObject
{
private:
	int flont;
	int back;
	bool isMode;
	bool isGround;
	bool isCollide;
	bool isShoot;
public:
	Block(float posX, float posY, bool nowMode, int drawType);

	void update(float posX, float posY, float radius, bool nowMode, Stage* stage);
	void draw();
	void modeChange();
	void stageCollide(Stage* stage);

	float getPosX();
	float getPosY();
	float getRadius();
	bool getIsMode();
	bool getIsGround();
	bool getIsCollide();
	bool getIsShoot();

	void setPosX(float posX);
	void setPosY(float posY);
	void setIsMode(bool isMode);
	void setIsGround(bool isGround);
	void setIsCollide(bool isCollide);
	void setIsShoot(bool isShoot);
};