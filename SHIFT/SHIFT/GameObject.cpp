#include "GameObject.h"


int GameObject::modeChange(int whatType)
{
    //1ループ(フレーム)前のコントローラー情報
    oldInput = input;

    //ジョイパッドのXInputから取得できる情報を得る
    GetJoypadXInputState(DX_INPUT_PAD1, &input);

    //スティック
    /*GetJoypadAnalogInput(&AX, &AY, DX_INPUT_PAD1);
    GetJoypadAnalogInputRight(&ARX, &ARY, DX_INPUT_PAD1);*/
    if (input.Buttons[XINPUT_BUTTON_RIGHT_SHOULDER] && !oldInput.Buttons[XINPUT_BUTTON_RIGHT_SHOULDER])
    {
        if (whatType == TYPE_FLONT)
        {
            return TYPE_BACK;
        }
        if (whatType == TYPE_BACK)
        {
            return TYPE_FLONT;
        }
    }
    else 
    {
        return whatType;
    }
}

int GameObject::plCollide(float x1, float y1, float radius1, float x2, float y2, float radius2)
{
    float LEFT1 = x1;
    float RIGHT1 = x1 + radius1 * 2;
    float LEFT2 = x2;
    float RIGHT2 = x2 + radius2 * 2;

    if (RIGHT1 <= LEFT2)
    {
        return 0;
    }
    if (RIGHT2 <= LEFT1)
    {
        return 0;
    }

    float UP1 = y1;
    float DOUWN1 = y1 + radius1 * 2;
    float UP2 = y2;
    float DOUWN2 = y2 + radius2 * 2;

    if (DOUWN1 <= UP2)
    {
        return 0;
    }
    if (DOUWN2 <= UP1)
    {
        return 0;
    }
    // それ以外の場合は当たっている
    return 1;
}
