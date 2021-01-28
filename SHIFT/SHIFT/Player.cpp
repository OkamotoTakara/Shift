#include "Player.h"

const float GRAVITY = 9.8;

Player::Player(float posX, float posY, unsigned char buttonNum, bool nowMode, int drawType)
{
	input = { buttonNum };
	this->posX = posX;
	this->posY = posY;
	this->isMode = nowMode;
	this->drawType = drawType;
	this->iscatch = false;
	this->velocity = 4.0f;
	this->shootVelY = 0.0f;
	this->shootVelX = 4.0f;
	this->radius = 16.0f;
	this->jumpCounter = 0;
	this->isGround = true;
	this->goLeft = false;
	this->flont = LoadGraph("resource/flontplayer.png");
	this->back = LoadGraph("resource/backplayer.png");
}

void Player::update(float posX, float posY, float radius, bool nowMode, Stage* stage, Block* block)
{
	//1ループ(フレーム)前のコントローラー情報
	oldInput = input;

	//
	oldPosX = this->posX;
	oldPosY = this->posY;
	//ジョイパッドのXInputから取得できる情報を得る
	GetJoypadXInputState(DX_INPUT_PAD1, &input);

	if (this->isMode == true && (input.ThumbLX < -32768 * 0.35f ||
		input.ThumbLX > 32767 * 0.35f))
	{
		this->posX += (float)input.ThumbLX / 32768 * velocity;
	}

	//左右どちらを向いてるかの判定
	if (this->isMode == true)
	{
		if ((float)input.ThumbLX / 32768 > 0)
		{
			this->goLeft = false;
		}

		else if ((float)input.ThumbLX / 32768 < 0)
		{
			this->goLeft = true;
		}
	}

	if (block->getIsShoot() == false)
	{
		//動いてるプレイヤーとブロックの当たり判定
		if (plCollide(this->posX, this->posY, this->radius, block->getPosX(), block->getPosY(), block->getRadius()) == 1)
		{
			//ブロックの上に乗った場合の処理
			if (this->posY < block->getPosY() && jumpVel <= 0 && (this->posY - block->getPosY()) <= (block->getPosX() - this->posX) && this->posX > block->getPosX()
				|| this->posY < block->getPosY() && jumpVel < 0 && (this->posY - block->getPosY()) <= (this->posX - block->getPosX()) && this->posX < block->getPosX())
			{
				this->posY = block->getPosY() - 32;
				jumpVel = 0;
				isGround = true;
			}
			//下から当たる処理
			else if (this->posY > block->getPosY() && jumpVel > 0 && (block->getPosY() - this->posY) <= (block->getPosX() - this->posX) && this->posX > block->getPosX()
				|| this->posY > block->getPosY() && jumpVel > 0 && (block->getPosY() - this->posY) <= (this->posX - block->getPosX()) && this->posX < block->getPosX())
			{
				this->posY = block->getPosY() + 32;
				jumpVel = 0;
			}
			//動いているプレイヤーがブロックより座標が低い場合
			else
			{
				if (this->posY > block->getPosY() - block->getRadius())
				{
					//左から当たる処理
					if (this->posX < block->getPosX())
					{
						this->posX = block->getPosX() - block->getRadius() * 2;
					}

					//右から当たる処理
					if (this->posX > block->getPosX())
					{
						this->posX = block->getPosX() + block->getRadius() * 2;
					}
				}
			}
		}
	}

	//プレイヤー同士の当たり判定
	if (plCollide(this->posX, this->posY, this->radius, posX, posY, radius) == 1)
	{
		if (nowMode == false)
		{
			//プレイヤーの上に乗った場合の処理
			if (this->posY < posY && jumpVel < 0 && (this->posY - posY) <= (posX - this->posX) && this->posX > posX
				|| this->posY < posY && jumpVel < 0 && (this->posY - posY) <= (this->posX - posX) && this->posX < posX)
			{
				this->posY = posY - 32;
				jumpVel = 0;
				isGround = true;
			}

			//下からの当たり判定
			else if (this->posY > posY && jumpVel > 0 && (posY - this->posY) <= (posX - this->posX) && this->posX > posX
				|| this->posY > posY && jumpVel > 0 && (posY - this->posY) <= (this->posX - posX) && this->posX < posX)
			{
				this->posY = posY + 32;
				jumpVel = 0;
			}

			else
			{
				//動いているプレイヤーがブロックより座標が低い場合
				if (this->posY > posY - radius * 2 && this->isMode == true)
				{
					//左からの当たり判定
					if (this->posX < posX)
					{
						this->posX = posX - 32;
					}

					//右からの当たり判定
					if (this->posX > posX)
					{
						this->posX = posX + 32;
					}
				}
			}
		}
	}

	//プレイヤーの下にマップチップのブロックが無い時
	if (stage->getMapNum((int)(this->posX + this->radius - 1) / CHIPSIZE, (int)(this->posY + this->radius) / CHIPSIZE) < 2
		&& stage->getMapNum((int)(this->posX - this->radius) / CHIPSIZE, (int)(this->posY + this->radius) / CHIPSIZE) < 2)
	{
		//上に乗った状態で横に落ちる(プレイヤー)
		if (this->posX + this->radius > posX - radius
			&& this->posX - this->radius < posX + radius
			|| this->posX + this->radius > block->getPosX() - block->getRadius()
			&& this->posX - this->radius < block->getPosX() + block->getRadius()
			&& iscatch == false)
		{

		}
		else
		{
			isGround = false;
		}

		//空中で止まってしまうバグ解消
		if (isGround == true && this->posY + this->radius < posY - radius
			&& this->posY + this->radius < block->getPosY() - block->getRadius())
		{
			isGround = false;
		}
	}

	plModeChange();
	jump();
	stageCollide(stage);
	catches(stage, block);
	shoot(stage, block);
}

void Player::draw()
{
	if (drawType == TYPE_FLONT)
	{
		DrawGraph(posX - radius, posY - radius, flont, TRUE);
		DrawFormatString(20, 300, GetColor(0, 0, 0), "%d", iscatch);
	}

	if (drawType == TYPE_BACK)
	{
		DrawGraph(posX - radius, posY - radius, back, TRUE);
	}
}

void Player::plModeChange()
{

	if (input.Buttons[XINPUT_BUTTON_RIGHT_SHOULDER] && !oldInput.Buttons[XINPUT_BUTTON_RIGHT_SHOULDER])
	{
		if (isMode == true)
		{
			isMode = false;
		}

		else
		{
			isMode = true;
		}
	}
}

void Player::jump()
{
	if (this->isMode == true)
	{
		if (input.Buttons[XINPUT_BUTTON_B])
		{
			if (isGround == true)
			{
				jumpCounter = 0;
				jumpVel = 8;
				isGround = false;
			}
			jumpCounter++;
		}

		if (!input.Buttons[XINPUT_BUTTON_B] || jumpCounter >= 16)
		{
			if (isGround == false)
			{
				jumpVel -= (GRAVITY / 25);
			}
		}

		if (isGround == false)
		{
			posY -= jumpVel;
		}

		else
		{
			jumpVel = 0.0f;
		}

		//地面の判定
		if (posY >= WIN_HEIGHT - 48)
		{
			posY = WIN_HEIGHT - 48;
			isGround = true;
		}
	}
}

float Player::distance(float x1, float y1, float x2, float y2)
{
	return pow(pow(x1 - x2, 2.0) + pow(y1 - y2, 2.0), 0.5);
}


void Player::catches(Stage* stage, Block* block)
{
	if (this->isMode == true)
	{
		if (block->getIsMode() == true)
		{
			if (input.Buttons[XINPUT_BUTTON_Y])
			{
			//ブロックを持てる距離に来た時
				if (distance(this->posX - this->radius, this->posY - this->radius,
					block->getPosX() - block->getRadius(), block->getPosY() - block->getRadius()) <= 48.0f)
				{
					if (block->getIsMode() == true)
					{
						iscatch = true;
						shootVelX = 4.0f;
						shootVelY = 0.0f;
						block->setPosX(this->posX);
						block->setPosY(this->posY - (radius * 2));
					}
				}
			}
			else
			{
				iscatch = false;
			}
		}
	}
}

void Player::shoot(Stage* stage, Block* block)
{
	if (block->getIsMode() == true)
	{
		//ブロックを投げられる範囲に近づいた時
		if (distance(this->posX - this->radius, this->posY - this->radius,
			block->getPosX() - block->getRadius(), block->getPosY() - block->getRadius()) <= 48.0f)
		{
			//スティックの方向に飛ばす
			if (!input.Buttons[XINPUT_BUTTON_Y] && oldInput.Buttons[XINPUT_BUTTON_Y])
			{
				block->setIsShoot(true);
				float rad = atan2((float)-input.ThumbLY, (float)input.ThumbLX);
				shootVelX = cos(rad) * velocity * 2;
				shootVelY = sin(rad) * velocity * 2;
			}
		}

		if (block->getIsShoot() == true)
		{
			shootVelY += (GRAVITY / 50);
			block->setPosX(block->getPosX() + shootVelX);
			block->setPosY(block->getPosY() + shootVelY);
		}

		else
		{
			shootVelY = 0.0f;
		}
	}
}

//マップチップとプレイヤーの当たり判定
void Player::stageCollide(Stage* stage)
{
	//プレイヤーの左の当たり判定
	if (stage->getMapNum((int)(posX - radius) / CHIPSIZE, (int)(posY - radius) / CHIPSIZE) > 1
		|| stage->getMapNum((int)(posX - radius) / CHIPSIZE, (int)(posY + radius - 1) / CHIPSIZE) > 1)
	{
		posX += velocity;
	}

	//プレイヤーの右の当たり判定
	if (stage->getMapNum((int)(posX + radius - 1) / CHIPSIZE, (int)(posY + radius - 1) / CHIPSIZE) > 1
		|| stage->getMapNum((int)(posX + radius - 1) / CHIPSIZE, (int)(posY - radius) / CHIPSIZE) > 1)
	{
		posX -= velocity;
	}

	//プレイヤーの上の当たり判定
	if (stage->getMapNum((int)(posX - radius) / CHIPSIZE, (int)(posY - radius) / CHIPSIZE) > 1 && jumpVel > 0
		|| stage->getMapNum((int)(posX + radius - 1) / CHIPSIZE, (int)(posY - radius) / CHIPSIZE) > 1 && jumpVel > 0)
	{
		posY = ((posY - radius) / CHIPSIZE) * CHIPSIZE + radius;
		jumpVel = 0;
	}

	//プレイヤーの下の当たり判定
	if (stage->getMapNum((int)(posX + radius - 1) / CHIPSIZE, (int)(posY + radius - 1) / CHIPSIZE) > 1
		|| stage->getMapNum((int)(posX - radius) / CHIPSIZE, (int)(posY + radius - 1) / CHIPSIZE) > 1)
	{
		int tmp = (int)oldPosY % CHIPSIZE;
		
		posY = oldPosY + tmp - radius;
		//posY = ((posY + radius - 1) / CHIPSIZE) * CHIPSIZE - radius;
		
		jumpVel = 0;
		isGround = true;
	}
}

//ブロックから動いた時の当たり判定
void Player::blockCollide(Block* block, float posX, float posY, float radius)
{
	if (block->getIsShoot() == true)
	{
		//ブロックからプレイヤーの当たり判定
		if (plCollide(block->getPosX(), block->getPosY(), block->getRadius(), posX, posY, radius) == 1)
		{
			//動いているブロックがプレイヤーより座標が低い場合
			if (posY - radius < block->getPosY())
			{
				//左からの当たり判定
				if (block->getPosX() < posX)
				{
					block->setPosX(posX - radius * 2);
				}

				//右からの当たり判定
				if (block->getPosX() > posX)
				{
					block->setPosX(posX + radius * 2);
				}
			}

			//プレイヤーの上に乗った場合の処理
			if (block->getPosY() < posY && shootVelY <= 0)
			{
				block->setPosY(posY - radius * 2);
				shootVelY = 0;
				block->setIsShoot(false);
			}

			//下からの当たり判定
			if (this->posY > posY && jumpVel > 0)
			{
				block->setPosY(posY + radius * 2);
				shootVelY = 0;
			}
		}
	}
}

void Player::setIsMode(bool ModeOn) { this->isMode = ModeOn; }

void Player::setPosX(float posX) { this->posX = posX; }

void Player::setPosY(float posY) { this->posY = posY; }

void Player::setVelocity(float velocity) { this->velocity = velocity; }

bool Player::getIsMode() { return isMode; }

float Player::getPosX() { return posX; }

float Player::getPosY() { return posY; }

float Player::getRadius() { return radius; }