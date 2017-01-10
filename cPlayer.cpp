#include "stdafx.h"
#include "cPlayer.h"
#include"cItemManager.h"

HRESULT cPlayer::init(void)
{
	_bullet = new bullet();
	_bullet->init("�Ѿ�",50);

	IsFly = false;

	key = 0;
	money = 0;
	bomb = 0;
	arrow = �⺻�Ѿ�;
	space = ����;

	x = WINSIZEX / 2;
	y = WINSIZEY / 2;
	moveSpeed = 3.0f;
	range = 500;
	damage = 1;
	tears = 10;
	bulletSpeed = 3;
	rc = RectMakeCenter(x, y, PLAYERSIZE, PLAYERSIZE);

	return S_OK;
}

void cPlayer::release(void)
{
	SAFE_DELETE(_bullet);
	
}

void cPlayer::update(void)
{

//==================================================================
//		## �Ѿ� �������� ����¥���� ##
//==================================================================
	if (arrow==�⺻�Ѿ�)
	{
		int static nCount = 0;
		nCount++;
		if (nCount>1000)
		{
			nCount = 0;
		}
		if (nCount%tears == 0)
		{
			if (KEYMANAGER->isStayKeyDown(VK_UP))
			{
				_bullet->fire(x, y, PI / 2, range, damage, bulletSpeed);
			}
			if (KEYMANAGER->isStayKeyDown(VK_DOWN))
			{
				_bullet->fire(x, y, 3 * PI / 2, range, damage, bulletSpeed);
			}
			if (KEYMANAGER->isStayKeyDown(VK_LEFT))
			{
				_bullet->fire(x, y, PI, range, damage, bulletSpeed);
			}
			if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
			{
				_bullet->fire(x, y, 0, range, damage, bulletSpeed);
			}
		}
	}
	if (arrow==��Ȳ)
	{

	}

//==================================================================
//		## �÷��̾� ������ ���� ##
//==================================================================

	if (KEYMANAGER->isStayKeyDown('D'))
	{
		x += moveSpeed;
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		x -= moveSpeed;
	}
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		y -= moveSpeed;
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		y += moveSpeed;
	}

//==================================================================
//		## ��ź��� ##
//==================================================================
	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		if (bomb>0)
		{
			_im->ItemUse(��ź);
		}		
	}

//==================================================================
//		## ��Ƽ������ۻ�� ##
//==================================================================
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		if (space==�ڻ���������)
		{
			_im->ItemUse(�ڻ���������);
		}
		if (space == �𷡽ð�)
		{
			_im->ItemUse(�𷡽ð�);
		}
	}

//==================================================================
//		## ī������ۻ�� ##
//==================================================================
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		if (card==ī��)
		{
			_im->ItemUse(ī��);
		}
	}


	_bullet->update();
	rc = RectMakeCenter(x, y, PLAYERSIZE, PLAYERSIZE);
}

void cPlayer::render(void)
{

	for (int i = 0; i < vInventory.size(); i++)
	{
		if (vInventory[i]==��Ȳ)
		{
			//�÷��̾� �̹����ٲ�
		}
		if (vInventory[i]==���������Ǳ���)
		{
			//�÷��̾� �̹����ٲ�
		}
	}
	
	if (arrow==�⺻�Ѿ�)
	{
		if (damage==1)
		{
			_bullet->render();
		}
		if (damage==3) //ī������� ��2�ö�
		{
			//�Ѿ˴�ū�ɷ� �̹��� ���
		}
	}
	if (arrow==��Ȳ)
	{
		// �Ѿ˿� �̹��� �ٲ㼭 ���
	}
	



	TCHAR buffer[256];
	wsprintf(buffer, TEXT("bomb:%d,  key:%d"), bomb, key);
	TextOut(getMemDC(), 10, 10, buffer, lstrlen(buffer));

	RectangleMake(getMemDC(), rc);
}

