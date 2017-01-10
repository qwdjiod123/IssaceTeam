#include "stdafx.h"
#include "cPlayer.h"
#include"cItemManager.h"

HRESULT cPlayer::init(void)
{
	_bullet = new bullet();
	_bullet->init("총알",50);

	IsFly = false;

	key = 0;
	money = 0;
	bomb = 0;
	arrow = 기본총알;
	space = 없음;

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
//		## 총알 종류별로 로직짜야함 ##
//==================================================================
	if (arrow==기본총알)
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
	if (arrow==유황)
	{

	}

//==================================================================
//		## 플레이어 움직임 로직 ##
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
//		## 폭탄사용 ##
//==================================================================
	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		if (bomb>0)
		{
			_im->ItemUse(폭탄);
		}		
	}

//==================================================================
//		## 액티브아이템사용 ##
//==================================================================
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		if (space==박사의조정기)
		{
			_im->ItemUse(박사의조정기);
		}
		if (space == 모래시계)
		{
			_im->ItemUse(모래시계);
		}
	}

//==================================================================
//		## 카드아이템사용 ##
//==================================================================
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		if (card==카드)
		{
			_im->ItemUse(카드);
		}
	}


	_bullet->update();
	rc = RectMakeCenter(x, y, PLAYERSIZE, PLAYERSIZE);
}

void cPlayer::render(void)
{

	for (int i = 0; i < vInventory.size(); i++)
	{
		if (vInventory[i]==유황)
		{
			//플레이어 이미지바꿈
		}
		if (vInventory[i]==구렁텅이의군주)
		{
			//플레이어 이미지바꿈
		}
	}
	
	if (arrow==기본총알)
	{
		if (damage==1)
		{
			_bullet->render();
		}
		if (damage==3) //카드먹으면 공2올라감
		{
			//총알더큰걸로 이미지 출력
		}
	}
	if (arrow==유황)
	{
		// 총알에 이미지 바꿔서 출력
	}
	



	TCHAR buffer[256];
	wsprintf(buffer, TEXT("bomb:%d,  key:%d"), bomb, key);
	TextOut(getMemDC(), 10, 10, buffer, lstrlen(buffer));

	RectangleMake(getMemDC(), rc);
}

