#include "Player.h"

const float GRAVITY = 9.8;

Player::Player(float posX, float posY, unsigned char buttonNum,bool nowMode,int drawType)
{
    input = { buttonNum };
    this->posX = posX;
    this->posY = posY;
    this->isMode = nowMode;
    this->drawType = drawType;
    this->velocity = 4.0f;
    this->radius = 16.0f;
    this->isground = true;
    this->flont = LoadGraph("resource/omotekun.png");
    this->back = LoadGraph("resource/urakun.png");
    this->oldPosX = 0.0f;
    this->oldPosY = 0.0f;
}

void Player::modeChange()
{
    //スティック
    /*GetJoypadAnalogInput(&AX, &AY, DX_INPUT_PAD1);
    GetJoypadAnalogInputRight(&ARX, &ARY, DX_INPUT_PAD1);*/
    if (input.Buttons[XINPUT_BUTTON_RIGHT_SHOULDER] && !oldInput.Buttons[XINPUT_BUTTON_RIGHT_SHOULDER])
    {
        if (isMode==true)
        {
            isMode=false;
        }
    	
        else
        {
            isMode = true;
        }
    }
}

void Player::jump()
{
    //スティック
    /*GetJoypadAnalogInput(&AX, &AY, DX_INPUT_PAD1);
    GetJoypadAnalogInputRight(&ARX, &ARY, DX_INPUT_PAD1);*/

    if (this->isMode == true)
    {
        if (input.Buttons[XINPUT_BUTTON_B] && !oldInput.Buttons[XINPUT_BUTTON_B])
        {
            if (isground == true)
            {
                jumpVel = 8;
                isground = false;
            }
        }

        if (isground == false)
        {
            posY -= jumpVel;
            jumpVel -= (GRAVITY / 50);
        }

        //地面の判定
        if (posY >= WIN_HEIGHT - 16)
        {
            posY = WIN_HEIGHT - 16;
            isground = true;
        }
    }
}

void Player::catches()
{
	
}

void Player::shoot()
{
	
}


void Player::update(float posX, float posY, float radius, bool nowMode)
{
    oldPosX = this->posX;
    oldPosY = this->posY;

    //1ループ(フレーム)前のコントローラー情報
    oldInput = input;
    //ジョイパッドのXInputから取得できる情報を得る
    GetJoypadXInputState(DX_INPUT_PAD1, &input);

    if (this->isMode == true)
    {
        this->posX += (input.Buttons[XINPUT_BUTTON_DPAD_RIGHT] - input.Buttons[XINPUT_BUTTON_DPAD_LEFT]) * velocity;
    }
    
    if (plCollide(this->posX, this->posY, this->radius, posX, posY, radius) == 1)
    {
        if (nowMode == false)
        {
            if (this->posX + radius <= posX - radius)
            {
                this->posX -= velocity;
            }

            if (this->posX - radius >= posX + radius)
            {
                this->posX += velocity;
            }

            if (this->posY < posY)
            {
                this->posY = posY - 32;
                jumpVel = 0;
            }

            if (this->posY >= posY)
            {
               
            }
        }
	}

    else
    {
       /* if (this->posY < posY)
        {
            this->posY = posY - 32;
            isground = true;
        }*/
    }

	
    modeChange();
    jump();
}

void Player::draw()
{
    if (drawType == TYPE_FLONT)
    {
        DrawGraph(posX-radius, posY-radius, flont, TRUE);
    }
	
    if (drawType == TYPE_BACK)
    {
        DrawGraph(posX-radius, posY-radius, back, TRUE);
    }

    //DrawBox(posX, posY, posX + radius * 2, posY + radius * 2, GetColor(30, 30, 30), TRUE);
}

bool Player::getIsMode(){return isMode;}

void Player::setIsMode(bool ModeOn){this->isMode = ModeOn;}

void Player::setPosX(float posX){this->posX = posX;}

void Player::setPosY(float posY){this->posY = posY;}

void Player::setVelocity(float velocity){this->velocity = velocity;}

float Player::getPosX(){return posX;}

float Player::getPosY(){return posY;}

float Player::getOldPosX(){return oldPosX;}

float Player::getOldPosY(){return oldPosY;}

float Player::getRadius(){return radius;}
