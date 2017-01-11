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
	bulletCount = 0;
	fire = false;
	bulletFire = false; 
	//���⼭ �Ѿ����� �ΰ��� ���� ����! 
	_bullet = new bullet; 
	_bullet->init("�⺻�Ѿ�", 200);
	_��Ȳ = new bullet;
	hp = 6;
	maxHp = 6;
	return S_OK;
}

void cPlayer::release(void)
{
	_bullet->release();
	SAFE_DELETE(_bullet);

}

void cPlayer::update(void)
{
	bulletCount++;
	if (bulletCount % 10 == 0)
	{
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			if (KEYMANAGER->isStayKeyDown('A'))
			{
				_bullet->fire(x, y, (PI / 1.9), 300, 10, 5);
				//�⺻�Ѿ� �̵��Ÿ� 300, ������ 10, �̵��ӵ� 5
				
			}
			else if (KEYMANAGER->isStayKeyDown('D'))
			{
				_bullet->fire(x, y, (PI / 2.1), 300, 10, 5);
				
			}
			else
			{
				_bullet->fire(x, y, (PI / 2), 300, 10, 5);
		
			}
			fire = true;
			faceState = pUP;
		}

	////////////////////
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			if (KEYMANAGER->isStayKeyDown('A'))
			{
				_bullet->fire(x, y, -(PI / 1.5), 300, 10, 5);
				
				//�⺻�Ѿ� �̵��Ÿ� 300, ������ 10, �̵��ӵ� 5
			}
			else if (KEYMANAGER->isStayKeyDown('D'))
			{
				_bullet->fire(x, y, -(PI / 2.5), 300, 10, 5);
				
			}
			else
			{
				_bullet->fire(x, y, -(PI/2), 300, 10, 5);
				
			}
			faceState = pIDLE;
			fire = true;

		}
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			if (KEYMANAGER->isStayKeyDown('W'))
			{
				_bullet->fire(x, y, (PI / 1.5), 300, 10, 5);
				
				//�⺻�Ѿ� �̵��Ÿ� 300, ������ 10, �̵��ӵ� 5
			}
			else if (KEYMANAGER->isStayKeyDown('S'))
			{
				_bullet->fire(x, y, -(PI / 1.5), 300, 10, 5);
				
			}
			else
			{
				_bullet->fire(x, y,PI , 300, 10, 5);
				
			}
			faceState = pLEFT;
			fire = true;
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			if (KEYMANAGER->isStayKeyDown('W'))
			{
				_bullet->fire(x, y, (PI / 2.5), 300, 10, 5);
			
				//�⺻�Ѿ� �̵��Ÿ� 300, ������ 10, �̵��ӵ� 5
			}
			else if (KEYMANAGER->isStayKeyDown('S'))
			{
				_bullet->fire(x, y, -(PI / 2.5), 300, 10, 5);
				
			}
			else
			{
				_bullet->fire(x, y, (PI * 2), 300, 10, 5);
			
			}
			faceState = pRIGHT;
			fire = true;
		}
	}
	

		if (KEYMANAGER->isStayKeyDown('D'))
		{    if(fire==false)
			faceState = pIDLE;
			keyState = pRIGHT;
			x += moveSpeed;
		}
		if (KEYMANAGER->isStayKeyDown('A'))
		{
			if (fire == false)
			faceState = pIDLE;
			keyState = pLEFT;
			x -= moveSpeed;
		}
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			if (fire == false)
			faceState = pIDLE;
			keyState = pUP;
			y -= moveSpeed;
		}
		if (KEYMANAGER->isStayKeyDown('S'))
		{
			if (fire == false)
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
	_bullet->update();
	rc = RectMakeCenter(x, y, PLAYERSIZEX, PLAYERSIZEY);
	rcHead = RectMakeCenter(x, y - PLAYERSIZEY / 2 - PLAYERHEADSIZEY / 2 + 15, PLAYERHEADSIZEX, PLAYERHEADSIZEY);
}

void cPlayer::render(void)
{
	_bullet->render();
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