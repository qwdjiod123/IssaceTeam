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
	for (int i = 0; i < 500; i++)
	{
		_loading->loadImage("�׽�Ʈ", WINSIZEX, WINSIZEY);
	}

	//��׶��� �̹���
	//_loading->loadImage("��׶���", "background.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("�Ѿ�", "ball.bmp", 10, 10);
	_loading->loadImage("map1", "map1.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("map2", "map2.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("map3", "map3.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("��ź", "bomb.bmp", 50, 50);
	_loading->loadImage("����", "key.bmp", 50, 50);

}
//�ε����� �Լ�(�̰��� ���带 ���� �־��)
void loadingScene::loadingSound(void)
{
}
