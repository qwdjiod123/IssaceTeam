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
	_loading->loadImage("�����ۿ��ʾ�", "������LEFT.bmp", 28*3, 25*3, true, RGB(255, 0, 255));
	_loading->loadImage("�����ۿ����ʾ�", "�����ۿ�.bmp", 28*3, 25 * 3, true, RGB(255, 0, 255));
	_loading->loadImage("������IDLE", "������IDLE.bmp", 28 * 3, 25 * 3, true, RGB(255, 0, 255));
	_loading->loadImage("�����۵����", "�����۵����.bmp", 28 * 3, 25 * 3, true, RGB(255, 0, 255));
	_loading->loadImage("�����۸���", "����.bmp", 18 * 3, 15 * 3, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�����ۿ��ʸ���", "WALKLEFT.bmp", 180 * 3, 15 * 3, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("�����ۿ����ʸ���", "������RIGHT.bmp", 180 * 3, 15 * 3, 10,1,true, RGB(255, 0, 255));
	_loading->loadFrameImage("������UPDOWN", "������UPDOWN.bmp", 180 * 3, 15 * 3, 10, 1, true, RGB(255, 0, 255));
	_loading->loadImage("�⺻�Ѿ�", "�⺻�Ѿ�.bmp", 26, 26, true, RGB(255, 0, 255));

	//���Ϳ� ���� �̹���
	_loading->loadImage("worm_V", "wormTest_V.bmp", 20, 21, true, RGB(255, 0, 255));
	_loading->loadImage("worm_H", "wormTest_H.bmp", 30, 13, true, RGB(255, 0, 255));		

}
//�ε����� �Լ�(�̰��� ���带 ���� �־��)
void loadingScene::loadingSound(void)
{
}
