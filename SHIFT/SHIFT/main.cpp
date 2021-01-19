#include "Player.h"
#include "DxLib.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	ChangeWindowMode(TRUE);						//�E�B���h�E���[�h�ɐݒ�
	//�E�B���h�E�T�C�Y���蓮�ł͕ύX�ł����A���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	SetMainWindowText(TITLE);					// �^�C�g����ύX
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);		//��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�i���j�^�[�̉𑜓x�ɍ��킹��j
	SetWindowSizeExtendRate(1.0);				//��ʃT�C�Y��ݒ�i�𑜓x�Ƃ̔䗦�Őݒ�j
	SetBackgroundColor(0xA6, 0xA6, 0xFF);		// ��ʂ̔w�i�F��ݒ肷��
	SetDrawScreen(DX_SCREEN_BACK);

	if (DxLib_Init() == -1)	return -1;

	Player flontplayer(WIN_WIDTH/2, WIN_HEIGHT - 16, 0, true,TYPE_FLONT);
	Player backplayer(WIN_WIDTH/2-64, WIN_HEIGHT - 16, 0, false,TYPE_BACK);
	GameObject gameobject;

	// �Q�[�����[�v
	while (1)
	{
		ClearDrawScreen();

		flontplayer.update(backplayer.getPosX(),backplayer.getPosY(),backplayer.getRadius(),backplayer.getIsMode());
		backplayer.update(flontplayer.getPosX(), flontplayer.getPosY(), flontplayer.getRadius(),flontplayer.getIsMode());
		
		flontplayer.draw();
		backplayer.draw();
		
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