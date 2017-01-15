#include "stdafx.h"
#include "loadingScene.h"

HRESULT loadingScene::init(void)
{
	//�ε�Ŭ���� ���� �� �ʱ�ȭ
	_loading = new loading;
	_loading->init();

	//�̹��� �� ���� �ε�
	this->loadingImage();
	this->loadingSound();

	return S_OK;
}

void loadingScene::release(void)
{
	//�ε�Ŭ���� ����
	SAFE_DELETE(_loading);
}

void loadingScene::update(void)
{
	//�ε�Ŭ���� ������Ʈ
	_loading->update();

	if (_loading->loadingDone())
	{		
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{			
			//�ε��� �Ϸ� ������ ������
			SCENEMANAGER->changeScene("����ȭ��");
		}		
	}
}

void loadingScene::render(void)
{
	//�ε�Ŭ���� ����
	_loading->render();
}

//�ε��̹��� �Լ�(�̰��� �̹����� ���� �־��)
void loadingScene::loadingImage(void)
{
	//_loading->loadImage();
	//_loading->loadFrameImage();

	//�ε��� �ʹ� ������ ����Ǽ� õõ�� ���ư����� �׽�Ʈ������ ����� ����
	for (int i = 0; i < 100; i++)
	{
		_loading->loadImage("�׽�Ʈ", WINSIZEX, WINSIZEY);
	}

	//��׶��� �̹���
	//_loading->loadImage("��׶���", "background.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("�Ѿ�", "ball.bmp", 10, 10);
	_loading->loadImage("map1", "inGameInfo.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("map2", "map2.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("map3", "map3.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("��ź", "bomb.bmp", 50, 50);
	_loading->loadImage("����", "key.bmp", 50, 50);
	//�÷��̾� �̹��� 
	_loading->loadImage("�����ۿ��ʾ�", "������LEFT.bmp", PLAYERHEADSIZEX, PLAYERHEADSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("�����ۿ����ʾ�", "�����ۿ�.bmp", PLAYERHEADSIZEX, PLAYERHEADSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("������IDLE", "������IDLE.bmp", PLAYERHEADSIZEX, PLAYERHEADSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("�����۵����", "�����۵����.bmp", PLAYERHEADSIZEX, PLAYERHEADSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("�����۸���", "����.bmp", PLAYERSIZEX, PLAYERSIZEY, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�����ۿ��ʸ���", "WALKLEFT.bmp", PLAYERSIZEX*10, PLAYERSIZEY, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�����ۿ����ʸ���", "������RIGHT.bmp", PLAYERSIZEX * 10, PLAYERSIZEY, 10,1,true, RGB(255, 0, 255));
	_loading->loadFrameImage("������UPDOWN", "������UPDOWN.bmp", PLAYERSIZEX * 10, PLAYERSIZEY, 10, 1, true, RGB(255, 0, 255));
	//��Ȳ�÷��̾�
	_loading->loadImage("��Ȳ���ʾ�", "��ȲLEFT.bmp", PLAYERHEADSIZEX, PLAYERHEADSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("��Ȳ�����ʾ�", "��ȲRIGHT.bmp", PLAYERHEADSIZEX, PLAYERHEADSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("��ȲIDLE", "��ȲIDLE.bmp", PLAYERHEADSIZEX+10, PLAYERHEADSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("��Ȳ�����", "��Ȳ�����.bmp", PLAYERHEADSIZEX, PLAYERHEADSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("��Ȳ����", "��Ȳ����.bmp", PLAYERSIZEX, PLAYERSIZEY, true, RGB(255, 0, 255));
	_loading->loadFrameImage("��Ȳ���ʸ���", "��������ȲLEFT.bmp", PLAYERSIZEX * 10, PLAYERSIZEY, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("��Ȳ�����ʸ���", "��������ȲRIGHT.bmp", PLAYERSIZEX * 10, PLAYERSIZEY, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("��ȲUPDOWN", "��������ȲUPDOWN.bmp", PLAYERSIZEX * 10, PLAYERSIZEY, 10, 1, true, RGB(255, 0, 255));
	//�Ѿ��̹��� 
	_loading->loadImage("�⺻�Ѿ�", "�⺻�Ѿ�.bmp", 26, 26, true, RGB(255, 0, 255));
	//���Ϳ� ���� �̹���


	_loading->loadFrameImage("wormH", "wormH.bmp", 504, 40, 12, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("wormD", "wormD.bmp", 600, 28, 24, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("wormDA", "wormDA.bmp", 27, 30, 1, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("wormHA", "wormHA.bmp", 39, 62, 1, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("wormU", "wormU.bmp", 27, 31, 1, 1, true, RGB(255, 0, 255));

	_loading->loadFrameImage("wormHR", "wormHR.bmp", 504, 40, 12, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("wormDR", "wormDR.bmp", 600, 28, 24, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("wormDAR", "wormDAR.bmp", 27, 30, 1, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("wormHAR", "wormHAR.bmp", 39, 62, 1, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("wormUR", "wormUR.bmp", 27, 31, 1, 1, true, RGB(255, 0, 255));


	_loading->loadImage("shootEnemy", "shootEnemy.bmp", 41, 36, true, RGB(255, 0, 255));
	_loading->loadFrameImage("shootEnemyAnime", "shootEnemyAnime.bmp", 368, 45, 8, 1, true, RGB(255, 0, 255));
	_loading->loadImage("shootEnemyR", "shootEnemyR.bmp", 41, 36, true, RGB(255, 0, 255));
	_loading->loadFrameImage("shootEnemyAnimeR", "shootEnemyAnimeR.bmp", 368, 45, 8, 1, true, RGB(255, 0, 255));

	_loading->loadFrameImage("fly", "fly.bmp", 84, 21, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("flyR", "flyR.bmp", 84, 21, 4, 1, true, RGB(255, 0, 255));

	_loading->loadFrameImage("enemyBullet", "enemyBullet.bmp", 45, 15, 3, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("bulletEffect", "bulletEffect.bmp", 444, 74, 6, 1, true, RGB(255, 0, 255));

	_loading->loadFrameImage("monstroAll", "monstroAll.bmp", 228, 104, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("monstroJumpMotion", "monstroJumpMotion.bmp", 816, 122, 6, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("monstroShootAnime", "monstroShootAnime.bmp", 408, 97, 3, 1, true, RGB(255, 0, 255));

	_loading->loadFrameImage("monstroAllR", "monstroAllR.bmp", 228, 104, 2, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("monstroJumpMotionR", "monstroJumpMotionR.bmp", 816, 122, 6, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("monstroShootAnimeR", "monstroShootAnimeR.bmp", 408, 97, 3, 1, true, RGB(255, 0, 255));


	_loading->loadImage("emptyHP", "emptyHP.bmp", 309, 33, true, RGB(255, 0, 255));
	_loading->loadImage("HP", "HP.bmp", 276, 18, true, RGB(255, 0, 255));


}
//�ε����� �Լ�(�̰��� ���带 ���� �־��)
void loadingScene::loadingSound(void)
{
}
