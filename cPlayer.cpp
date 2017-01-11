#include "stdafx.h"
#include "cPlayer.h"
#include"cItemManager.h"

HRESULT cPlayer::init(void)
{
	IsFly = false;
	key = 0;
	money = 0;
	bomb = 0;
	arrow = �⺻�Ѿ�;
	space = ����;
	x = WINSIZEX / 2;
	y = WINSIZEY / 2;
	moveSpeed = 3.0f;
	faceState = pIDLE;
	keyState = pIDLE;
	range = 500;
	damage = 1;
	tears = 10;
	bulletSpeed = 3;
	rc = RectMakeCenter(x, y, PLAYERSIZEX, PLAYERSIZEY); //�÷��̾� ����
	rcHead = RectMakeCenter(x, y - PLAYERSIZEY / 2 - PLAYERHEADSIZEY / 2 + 15, PLAYERHEADSIZEX, PLAYERHEADSIZEY);//�÷��̾� �Ӹ� 
	frameCount = 0;
	leftFrame = 0;
	rightFrame = 0;
	upDownFrame = 0;
	returnCount = 0;
	fire = false;
	return S_OK;
}

void cPlayer::release(void)
{


}

void cPlayer::update(void)
{


	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		if (faceState == pLEFT)
		{

		}
		else
			faceState = pUP;
		fire = true;

	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		faceState = pIDLE;
		fire = true;

	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		faceState = pLEFT;
		fire = true;

	}

	if (KEYMANAGER->isStayKeyDown('D'))
	{
		faceState = pIDLE;
		keyState = pRIGHT;
		x += moveSpeed;
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		faceState = pIDLE;
		keyState = pLEFT;
		x -= moveSpeed;
	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		faceState = pIDLE;
		keyState = pUP;
		y -= moveSpeed;
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		faceState = pIDLE;
		keyState = pIDLE;
		y += moveSpeed;
	}

	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		if (bomb > 0)
		{
			_im->ItemUse(��ź);
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		if (space == �ڻ���������)
		{
			_im->ItemUse(�ڻ���������);
		}
		if (space == �𷡽ð�)
		{
			_im->ItemUse(�𷡽ð�);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		if (card == ī��)
		{
			_im->ItemUse(ī��);
		}
	}

	animation();
	rc = RectMakeCenter(x, y, PLAYERSIZEX, PLAYERSIZEY);
	rcHead = RectMakeCenter(x, y - PLAYERSIZEY / 2 - PLAYERHEADSIZEY / 2 + 15, PLAYERHEADSIZEX, PLAYERHEADSIZEY);
}

void cPlayer::render(void)
{

	for (int i = 0; i < vInventory.size(); i++)
	{
		if (vInventory[i] == ��Ȳ)
		{
			//�÷��̾� �̹����ٲ�
		}
		if (vInventory[i] == ���������Ǳ���)
		{
			//�÷��̾� �̹����ٲ�
		}
	}

	//RectangleMake(getMemDC(), rc);
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		IMAGEMANAGER->frameRender("�����ۿ��ʸ���", getMemDC(), rc.left, rc.top, leftFrame, 1);
	}
	else if (KEYMANAGER->isStayKeyDown('A'))
	{
		IMAGEMANAGER->frameRender("�����ۿ����ʸ���", getMemDC(), rc.left, rc.top, rightFrame, 1);
	}
	else if (KEYMANAGER->isStayKeyDown('W'))
	{
		IMAGEMANAGER->frameRender("������UPDOWN", getMemDC(), rc.left, rc.top, upDownFrame, 1);
	}
	else if (KEYMANAGER->isStayKeyDown('S'))
	{
		IMAGEMANAGER->frameRender("������UPDOWN", getMemDC(), rc.left, rc.top, upDownFrame, 1);
	}
	else
	{
		IMAGEMANAGER->render("�����۸���", getMemDC(), rc.left, rc.top, 0, 0, PLAYERSIZEX, PLAYERSIZEY);
	}

	switch (faceState)
	{
	case pLEFT:
		IMAGEMANAGER->render("�����ۿ��ʾ�", getMemDC(), rcHead.left, rcHead.top, 0, 0, PLAYERHEADSIZEX, PLAYERHEADSIZEY);
		cout << "left" << endl;
		break;
	case pRIGHT:
		IMAGEMANAGER->render("�����ۿ����ʾ�", getMemDC(), rcHead.left, rcHead.top, 0, 0, PLAYERHEADSIZEX, PLAYERHEADSIZEY);
		break;
	case pIDLE:
		IMAGEMANAGER->render("������IDLE", getMemDC(), rcHead.left, rcHead.top, 0, 0, PLAYERHEADSIZEX, PLAYERHEADSIZEY);
		break;
	case pUP:
		IMAGEMANAGER->render("�����۵����", getMemDC(), rcHead.left, rcHead.top, 0, 0, PLAYERHEADSIZEX, PLAYERHEADSIZEY);
		break;
	default:
		break;
	}

	//==================================================================
	//		## ��ġȮ�ο� ##
	//==================================================================
	for (int i = 0; i < vInventory.size(); i++)
	{
		wsprintf(buffer, TEXT("�÷��̾��κ�:%d"), vInventory[i]);
		TextOut(getMemDC(), 100, 10 + 20 * i, buffer, lstrlen(buffer));
	}

	wsprintf(buffer, TEXT("bomb:%d,  key:%d  money:%d"), bomb, key, money);
	TextOut(getMemDC(), 10, 10, buffer, lstrlen(buffer));
}

void cPlayer::animation(void)
{
	if (fire == true)
	{
		returnCount++;
		if (returnCount > 50)
		{
			fire = false;
			returnCount = 0;
			faceState = pIDLE;

		}
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		//frameCount = 0;
		frameCount++;
		if (frameCount % 5 == 0)
			leftFrame++;
		if (leftFrame == 10)
			leftFrame = 0;
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		//	frameCount = 0;
		frameCount++;
		if (frameCount % 5 == 0)
			rightFrame++;
		if (rightFrame == 10)
			rightFrame = 0;
	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		//	frameCount = 0;
		frameCount++;
		if (frameCount % 5 == 0)
			upDownFrame++;
		if (upDownFrame == 10)
			upDownFrame = 0;
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		//		frameCount = 0;
		frameCount++;
		if (frameCount % 5 == 0)
			upDownFrame++;
		if (upDownFrame == 10)
			upDownFrame = 0;
	}
	RectangleMake(getMemDC(), rc);
}

void cPlayer::addInVentory(int _item)
{
	vInventory.push_back(_item);
}