#include "Player.h"
#include "DxLib.h"
#include "Stage.h"
#include "Block.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	ChangeWindowMode(TRUE);						//ウィンドウモードに設定
	//ウィンドウサイズを手動では変更できず、かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	SetMainWindowText(TITLE);					// タイトルを変更
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);		//画面サイズの最大サイズ、カラービット数を設定（モニターの解像度に合わせる）
	SetWindowSizeExtendRate(1.0);				//画面サイズを設定（解像度との比率で設定）
	SetBackgroundColor(0xFF, 0xFF, 0xFF);		// 画面の背景色を設定する
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
	
	// ゲームループ
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
		// 20ミリ秒待機（疑似60FPS）
		WaitTimer(20);
		// Windows システムからくる情報を処理する
		if (ProcessMessage() == -1)
		{
			break;
		}
		// ＥＳＣキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}
	//Dxライブラリ終了処理
	DxLib_End();

	return 0;
}