#pragma once
#include "GameObject.h"

const int XMAPMAX = 93;
const int YMAPMAX = 27;
const int MAPMAX = XMAPMAX * YMAPMAX;
const int CHIPSIZE = 32;

class Stage : public GameObject
{
private:
	int block;
	int chip[12];
	int map[YMAPMAX][XMAPMAX];
	bool isChange[MAPMAX];
	int vignette;

public:
	  Stage();

	void load();
	void update();
	void draw();
	int getMapNum(int x, int y);
};