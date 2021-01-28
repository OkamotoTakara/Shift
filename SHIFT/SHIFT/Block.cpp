#include "Block.h"

Block::Block(float posX, float posY, bool nowMode, int drawType)
{
	this->posX = posX;
	this->posY = posY;
	this->drawType = drawType;
	this->radius = 16.0f;
	this->isShoot = false;
	this->isMode = nowMode;
	this->velocity = 4.0;
	this->isGround = false;
	this->flont = LoadGraph("resource/flontblock.png");
	this->back = LoadGraph("resource/backblock.png");
}

void Block::update(float posX, float posY, float radius, bool nowMode, Stage* stage)
{
	//�u���b�N���m�̓����蔻��
	if (plCollide(this->posX, this->posY, this->radius, posX, posY, radius) == 1)
	{
		//isCollide = true;

		if (nowMode == false)
		{
			//�u���b�N�̏�ɏ�����ꍇ�̏���
			if (this->posY < posY && (this->posY - posY) <= (posX - this->posX) && this->posX > posX
				|| this->posY < posY && (this->posY - posY) <= (this->posX - posX) && this->posX < posX)
			{
				this->posY = posY - 32;
				isGround = true;
			}
			//������̓����蔻��
			else if (this->posY > posY && (posY - this->posY) <= (posX - this->posX) && this->posX > posX
				|| this->posY > posY && (posY - this->posY) <= (this->posX - posX) && this->posX < posX)
			{
				this->posY = posY + 32;
			}
			else
			{
				//�����Ă���u���b�N�������ĂȂ��u���b�N�����W���Ⴂ�ꍇ
				if (this->posY > posY - radius * 2)
				{
					//������̓����蔻��
					if (this->posX < posX)
					{
						this->posX = posX - radius * 2;
					}

					//�E����̓����蔻��
					if (this->posX > posX)
					{
						this->posX = posX + radius * 2;
					}
				}
			}

		}
	}

	modeChange();
	stageCollide(stage);
}

void Block::draw()
{
	if (drawType == TYPE_FLONT)
	{
		DrawGraph(posX - radius, posY - radius, flont, TRUE);
		DrawFormatString(0, 100, GetColor(0, 0, 0), "%d", isMode);
	}

	if (drawType == TYPE_BACK)
	{
		DrawGraph(posX - radius, posY - radius, back, TRUE);
	}
}

void Block::modeChange()
{
	//1���[�v(�t���[��)�O�̃R���g���[���[���
	oldInput = input;
	//�W���C�p�b�h��XInput����擾�ł�����𓾂�
	GetJoypadXInputState(DX_INPUT_PAD1, &input);

	if (input.Buttons[XINPUT_BUTTON_RIGHT_SHOULDER] && !oldInput.Buttons[XINPUT_BUTTON_RIGHT_SHOULDER])
	{
		if (isMode == false)
		{
			isMode = true;
		}

		else
		{
			isMode = false;
		}
	}
}

void Block::stageCollide(Stage* stage)
{
	if (isMode == true)
	{
		//�u���b�N�̍��̓����蔻��
		if (stage->getMapNum((int)(posX - radius) / CHIPSIZE, (int)(posY - radius) / CHIPSIZE) > 1
			|| stage->getMapNum((int)(posX - radius) / CHIPSIZE, (int)(posY + radius - 1) / CHIPSIZE) > 1)
		{
			posX = ((posX - radius) / CHIPSIZE) * CHIPSIZE + radius;
		}

		//�u���b�N�̉E�̓����蔻��
		if (stage->getMapNum((int)(posX + radius - 1) / CHIPSIZE, (int)(posY + radius - 1) / CHIPSIZE) > 1
			|| stage->getMapNum((int)(posX + radius - 1) / CHIPSIZE, (int)(posY - radius) / CHIPSIZE) > 1)
		{
			posX = ((posX + radius - 1) / CHIPSIZE) * CHIPSIZE - radius;
		}

		//�u���b�N�̏�̓����蔻��
		if (stage->getMapNum((int)(posX - radius) / CHIPSIZE, (int)(posY - radius) / CHIPSIZE) > 1
			|| stage->getMapNum((int)(posX + radius - 1) / CHIPSIZE, (int)(posY - radius) / CHIPSIZE) > 1)
		{
			posY = ((posY - radius) / CHIPSIZE) * CHIPSIZE + radius;
		}

		//�u���b�N�̉��̓����蔻��
		if (stage->getMapNum((int)(posX + radius - 1) / CHIPSIZE, (int)(posY + radius - 1) / CHIPSIZE) > 1
			|| stage->getMapNum((int)(posX - radius) / CHIPSIZE, (int)(posY + radius - 1) / CHIPSIZE) > 1)
		{
			posY = ((posY + radius - 1) / CHIPSIZE) * CHIPSIZE - radius;

			//�u���b�N�𓊂��ă}�b�v�ɂ����������󒆂Ŏ~�܂�̂͋��炭���ꂪ���
			isShoot = false;
		}
	}
}


float Block::getPosX() { return posX; }
float Block::getPosY() { return posY; }
float Block::getRadius() { return radius; }
bool  Block::getIsMode() { return isMode; }
bool Block::getIsGround() { return isGround; }
bool Block::getIsCollide() { return isCollide; }
bool Block::getIsShoot() { return isShoot; }

void Block::setPosX(float posX) { this->posX = posX; }
void Block::setPosY(float posY) { this->posY = posY; }
void Block::setIsMode(bool isMode) { this->isMode = isMode; }
void Block::setIsGround(bool isGround) { this->isGround = isGround; }
void Block::setIsCollide(bool isCollide) { this->isCollide = isCollide; }
void Block::setIsShoot(bool isShoot) { this->isShoot = isShoot; }
