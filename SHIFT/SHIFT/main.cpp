#include "Player.h"
#include "DxLib.h"
#include "Stage.h"
#include "Block.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	ChangeWindowMode(TRUE);						//�E�B���h�E���[�h�ɐݒ�
	//�E�B���h�E�T�C�Y���蓮�ł͕ύX�ł����A���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	SetMainWindowText(TITLE);					// �^�C�g����ύX
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);		//��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�i���j�^�[�̉𑜓x�ɍ��킹��j
	SetWindowSizeExtendRate(1.0);				//��ʃT�C�Y��ݒ�i�𑜓x�Ƃ̔䗦�Őݒ�j
	SetBackgroundColor(0xFF, 0xFF, 0xFF);		// ��ʂ̔w�i�F��ݒ肷��
	SetDrawScreen(DX_SCREEN_BACK);

	if (DxLib_Init() == -1)	return -1;

	Block* flontblock = new Block(320 - 32, WIN_HEIGHT - 224 - 16,true, TYPE_FLONT);
	Block* backblock = new Block(480 - 32, WIN_HEIGHT - 224 - 16,false, TYPE_BACK);
	Player flontplayer(320 + 32, WIN_HEIGHT - 224 - 16, 0, true, TYPE_FLONT);
	Player backplayer(480 + 32, WIN_HEIGHT - 224 - 16, 0, false, TYPE_BACK);
	GameObject gameobject;
	Stage* stage;
	stage = new Stage;
	stage->load();
	
	// �Q�[�����[�v
	while (1)
	{
		ClearDrawScreen();

		stage->update();
		flontplayer.update(backplayer.getPosX(), backplayer.getPosY(), backplayer.getRadius(), backplayer.getIsMode(), stage, flontblock);
		backplayer.update(flontplayer.getPosX(), flontplayer.getPosY(), flontplayer.getRadius(), flontplayer.getIsMode(), stage, backblock);
		flontblock->update(backblock->getPosX(), backblock->getPosY(), backblock->getRadius(),backblock->getIsMode(),stage);
		backblock->update(flontblock->getPosX(), flontblock->getPosY(), flontblock->getRadius(), flontblock->getIsMode(),stage);
		
		//SetDrawBlendMode(DX_BLENDMODE_INVSRC, 255);
		stage->draw();
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		flontplayer.draw();
		backplayer.draw();
		flontblock->draw();
		backblock->draw();
		
		DrawFormatString(0, 0, GetColor(255, 255, 255), "%f,%f", flontplayer.getPosX(), flontplayer.getPosY());
		DrawFormatString(0, 20, GetColor(255, 255, 255), "%f,%f", backplayer.getPosX(), backplayer.getPosY());
		
		ScreenFlip();
		// 20�~���b�ҋ@�i�^��60FPS�j
		WaitTimer(20);
		// Windows �V�X�e�����炭�������������
		if (ProcessMessage() == -1)
		{
			break;
		}
		// �d�r�b�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}
	//Dx���C�u�����I������
	DxLib_End();

	return 0;
}