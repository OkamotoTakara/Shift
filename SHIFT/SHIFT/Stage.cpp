#include "Stage.h"
#pragma warning(disable: 4996)


Stage::Stage()
{
    vignette = LoadGraph("resource/backcircle2.png");
    block = LoadGraph("resource/block.png"); 
    LoadDivGraph("resource/chip.png", 12, 12, 1, 32, 32, chip);
}

void Stage::load()
{
    for (auto y = 0; y < YMAPMAX; y++) {
        for (auto x = 0; x < XMAPMAX; x++) {
            map[y][x] = 0;
        }
    }


    FILE* fp;

    fopen_s(&fp, "Resource/newtuto.csv", "r");

    if (fp == NULL)DebugBreak();
    int c;
    int retu = 0;
    int gyou = 0;
    char buf[10];
    memset(buf, 0, sizeof(buf));
    bool eofFlag = false;
    while (1) {
        while (1) {
            c = fgetc(fp);//�����ǂ��c�Ɋi�[
            if (c == EOF) {
                eofFlag = true;//EndOfFile�̎��Ƀ��[�v�𔲂���
                break;
            }
            if (c != ',' && c != '\n') {
                strcat(buf, (const char*)&c);//c���Z���̋�؂肩���s�łȂ���΁Abuf�ɘA������
            }
            else {
                int num = atoi(buf);//buf��int�^�ɒ����āA���Ȃ̃��[�J���ϐ�num�ɑ��
                map[gyou][retu] = num;//num�Ԗڂ̃`�b�v�摜�̃n���h�����擾
                memset(buf, 0, sizeof(buf));//buf�����Z�b�g
                break;//��؂肩���s�Ȃ烋�[�v�𔲂���
            }
        }
        //1�Z�����̃��[�v�𔲂�����
        if (eofFlag)break;
        if (c == ',')retu++;
        if (c == '\n') {//���s��������s�𑝂₷
            gyou++;
            retu = 0;
        }
    }

    fclose(fp);
}

void Stage::update()
{
    load();
}

void Stage::draw()
{
    for (int y = 0; y < YMAPMAX; y++)
    {
        for (int x = 0; x < XMAPMAX; x++)
        {
            if (map[y][x] == 0)
            {
                DrawGraph(x * CHIPSIZE, y * CHIPSIZE, chip[0], TRUE);
            }

            if (map[y][x] == 1)
            {
                DrawGraph(x * CHIPSIZE, y * CHIPSIZE, chip[1], TRUE);
            }

            if (map[y][x] == 2)
            {
                DrawGraph(x * CHIPSIZE, y * CHIPSIZE, chip[2], TRUE);
            }

            if (map[y][x] == 3)
            {
                DrawGraph(x * CHIPSIZE, y * CHIPSIZE, chip[3], TRUE);
            }

            if (map[y][x] == 4)
            {
                DrawGraph(x * CHIPSIZE, y * CHIPSIZE, chip[4], TRUE);
            }

            if (map[y][x] == 5)
            {
                DrawGraph(x * CHIPSIZE, y * CHIPSIZE, chip[5], TRUE);
            }

            if (map[y][x] == 6)
            {
                DrawGraph(x * CHIPSIZE, y * CHIPSIZE, chip[6], TRUE);
            }

            if (map[y][x] == 7)
            {
                DrawGraph(x * CHIPSIZE, y * CHIPSIZE, chip[7], TRUE);
            }

            if (map[y][x] == 8)
            {
                DrawGraph(x * CHIPSIZE, y * CHIPSIZE, chip[8], TRUE);
            }

            if (map[y][x] == 9)
            {
                DrawGraph(x * CHIPSIZE, y * CHIPSIZE, chip[9], TRUE);
            }

            if (map[y][x] == 10)
            {
                DrawGraph(x * CHIPSIZE, y * CHIPSIZE, chip[10], TRUE);
            }

            if (map[y][x] == 11)
            {
                DrawGraph(x * CHIPSIZE, y * CHIPSIZE, chip[11], TRUE);
            }
        }
    }
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 130);
    DrawGraph(0, 0, vignette, TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

int Stage::getMapNum(int x, int y) { return map[y][x]; }
