#pragma once
#include "GameObject.h"
#include "Stage.h"
#include "Block.h"

class Player : public GameObject
{
private:
	float jumpVel;
	float shootVelY;
	float shootVelX;
	bool isGround;
	bool goLeft;
	int jumpCounter;
	int flont;
	int back;
	bool iscatch;
public:
	Player(float posX,float posY,unsigned char buttonNum,bool nowMode,int drawType);

	void update(float posX, float posY, float radius, bool nowMode, Stage* stage, Block* block);
	void draw();
	void plModeChange();
	void jump();
	float distance(float x1, float y1, float x2, float y2);
	void catches(Stage* stage, Block* block);
	void shoot(Stage* stage, Block* block);
	void stageCollide(Stage* stage);
	void blockCollide(Block* block,float posX,float posY,float radius);

	bool getIsMode();
	float getPosX();
	float getPosY();
	float getRadius();
	
	void setIsMode(bool isMode);
	void setPosX(float posX);
	void setPosY(float posY);
	void setVelocity(float velocity);
};

