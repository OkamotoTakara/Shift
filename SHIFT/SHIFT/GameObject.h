#pragma once
#include "DxLib.h"
#include <cmath>

const char TITLE[] = "学籍番号名前：タイトル";

const int WIN_HEIGHT = 864;
const int WIN_WIDTH = 1536;
const int TYPE_FLONT = 0;
const int TYPE_BACK = 1;

class GameObject
{
protected:
	float posX;
	float posY;
	float oldPosX;
	float oldPosY;
	float radius;
	float velocity;
	bool isMode;
	int drawType;
	XINPUT_STATE input;
	XINPUT_STATE oldInput;
public:
	int plCollide(float x1, float y1, float radius1, float x2, float y2, float radius2);
};

