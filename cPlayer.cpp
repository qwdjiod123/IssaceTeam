#include "stdafx.h"
#include "cPlayer.h"
#include"cItemManager.h"

HRESULT cPlayer::init(void)
{
	//기본 플레이어 정보 
	IsFly = false;
	key = 0;
	money = 0;
	bomb = 0;
	arrow = 기본총알;
	space = 없음;
	x = WINSIZEX / 2;
	y = WINSIZEY / 2;
	moveSpeed = 3.0f;
	faceState = pIDLE;
	keyState = pIDLE;
	range = 500;
	damage = 1;
	tears = 10;
	bulletSpeed = 3;
	hp = 6;
	maxHp = 6;
	rc = RectMakeCenter(x, y, PLAYERSIZEX, PLAYERSIZEY); //플레이어 몸통
	rcHead = RectMakeCenter(x, y - PLAYERSIZEY / 2 - PLAYERHEADSIZEY / 2 + 10, PLAYERHEADSIZEX, PLAYERHEADSIZEY);//플레이어 머리 
																												 //애니메이션 필요한 Count 
	frameCount = 0;
	leftFrame = 0;               //왼쪽걸어갈때 
	rightFrame = 0;            //오른쪽걸어갈때
	upDownFrame = 0;       //아래 위 카운트
	returnCount = 0;         //다시 머리 고개를 돌리는 카운트 
	bulletCount = 0;         //총알발사되는 카운트 
	fire = false;               //총알이 발사 되었냐?
								//여기서 총알종류 두가지 만들 것임! 
	_bullet = new bullet;
	_bullet->init("기본총알", 200);
	_유황 = new missile;
	_유황->init(200, 200);
	return S_OK;
}

void cPlayer::release(void)
{
	_bullet->release();
	SAFE_DELETE(_bullet);
	_유황->release();
	SAFE_DELETE(_유황);
}

void cPlayer::update(void)
{
	PlayerKeyState();
	bulletFire();
	animation();
	_bullet->update();
	_유황->update();

}

void cPlayer::render(void)
{
	_bullet->render();
	_유황->render();
	for (int i = 0; i < vInventory.size(); i++)
	{
		if (vInventory[i] == 유황)
		{
			arrow = 유황;
		}
		if (vInventory[i] == 구렁텅이의군주)
		{
			//플레이어 이미지바꿈
		}
	}
	if (arrow == 기본총알)
	{
		if (KEYMANAGER->isStayKeyDown('D'))
		{
			IMAGEMANAGER->frameRender("아이작왼쪽몸통", getMemDC(), rc.left, rc.top, leftFrame, 1);
		}
		else if (KEYMANAGER->isStayKeyDown('A'))
		{
			IMAGEMANAGER->frameRender("아이작오른쪽몸통", getMemDC(), rc.left, rc.top, rightFrame, 1);
		}
		else if (KEYMANAGER->isStayKeyDown('W'))
		{
			IMAGEMANAGER->frameRender("아이작UPDOWN", getMemDC(), rc.left, rc.top, upDownFrame, 1);
		}
		else if (KEYMANAGER->isStayKeyDown('S'))
		{
			IMAGEMANAGER->frameRender("아이작UPDOWN", getMemDC(), rc.left, rc.top, upDownFrame, 1);
		}
		else
		{
			IMAGEMANAGER->render("아이작몸통", getMemDC(), rc.left, rc.top, 0, 0, PLAYERSIZEX, PLAYERSIZEY);
		}

		switch (faceState)
		{
		case pLEFT:
			IMAGEMANAGER->render("아이작왼쪽얼굴", getMemDC(), rcHead.left, rcHead.top, 0, 0, PLAYERHEADSIZEX, PLAYERHEADSIZEY);
			//	cout << "left" << endl;
			break;
		case pRIGHT:
			IMAGEMANAGER->render("아이작오른쪽얼굴", getMemDC(), rcHead.left, rcHead.top, 0, 0, PLAYERHEADSIZEX, PLAYERHEADSIZEY);
			break;
		case pIDLE:
			IMAGEMANAGER->render("아이작IDLE", getMemDC(), rcHead.left, rcHead.top, 0, 0, PLAYERHEADSIZEX, PLAYERHEADSIZEY);
			break;
		case pUP:
			IMAGEMANAGER->render("아이작뒷통수", getMemDC(), rcHead.left, rcHead.top, 0, 0, PLAYERHEADSIZEX, PLAYERHEADSIZEY);
			break;
		default:
			break;
		}
	}
	//RectangleMake(getMemDC(), rc);
	else if (arrow == 유황)
	{
		if (KEYMANAGER->isStayKeyDown('D'))
		{
			IMAGEMANAGER->frameRender("유황왼쪽몸통", getMemDC(), rc.left, rc.top, leftFrame, 1);
		}
		else if (KEYMANAGER->isStayKeyDown('A'))
		{
			IMAGEMANAGER->frameRender("유황오른쪽몸통", getMemDC(), rc.left, rc.top, rightFrame, 1);
		}
		else if (KEYMANAGER->isStayKeyDown('W'))
		{
			IMAGEMANAGER->frameRender("유황UPDOWN", getMemDC(), rc.left, rc.top, upDownFrame, 1);
		}
		else if (KEYMANAGER->isStayKeyDown('S'))
		{
			IMAGEMANAGER->frameRender("유황UPDOWN", getMemDC(), rc.left, rc.top, upDownFrame, 1);
		}
		else
		{
			IMAGEMANAGER->render("유황몸통", getMemDC(), rc.left, rc.top, 0, 0, PLAYERSIZEX, PLAYERSIZEY);
		}

		switch (faceState)
		{
		case pLEFT:
			IMAGEMANAGER->render("유황왼쪽얼굴", getMemDC(), rcHead.left, rcHead.top, 0, 0, PLAYERHEADSIZEX, PLAYERHEADSIZEY);
			//cout << "left" << endl;
			break;
		case pRIGHT:
			IMAGEMANAGER->render("유황오른쪽얼굴", getMemDC(), rcHead.left, rcHead.top, 0, 0, PLAYERHEADSIZEX, PLAYERHEADSIZEY);
			break;
		case pIDLE:
			IMAGEMANAGER->render("유황IDLE", getMemDC(), rcHead.left - 5, rcHead.top, 0, 0, PLAYERHEADSIZEX + 10, PLAYERHEADSIZEY);
			break;
		case pUP:
			IMAGEMANAGER->render("유황뒷통수", getMemDC(), rcHead.left, rcHead.top, 0, 0, PLAYERHEADSIZEX, PLAYERHEADSIZEY);
			break;
		default:
			break;
		}
	}

	//==================================================================
	//		## 수치확인용 ##
	//==================================================================
	for (int i = 0; i < vInventory.size(); i++)
	{
		wsprintf(buffer, TEXT("플레이어인벤:%d"), vInventory[i]);
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

void cPlayer::bulletFire(void)
{
	if (arrow == 기본총알)
	{
		bulletCount++;
		if (bulletCount % 10 == 0)
		{
			if (KEYMANAGER->isStayKeyDown(VK_UP))
			{
				if (KEYMANAGER->isStayKeyDown('A'))
				{
					_bullet->fire(x, y, (PI / 1.9), range, damage, bulletSpeed);
					//기본총알 이동거리 300, 데미지 10, 이동속도 5

				}
				else if (KEYMANAGER->isStayKeyDown('D'))
				{
					_bullet->fire(x, y, (PI / 2.1), range, damage, bulletSpeed);

				}
				else
				{
					_bullet->fire(x, y, (PI / 2), range, damage, bulletSpeed);

				}
				fire = true;
				faceState = pUP;
			}

			////////////////////
			if (KEYMANAGER->isStayKeyDown(VK_DOWN))
			{
				if (KEYMANAGER->isStayKeyDown('A'))
				{
					_bullet->fire(x, y, -(PI / 1.5), range, damage, bulletSpeed);

					//기본총알 이동거리 300, 데미지 10, 이동속도 5
				}
				else if (KEYMANAGER->isStayKeyDown('D'))
				{
					_bullet->fire(x, y, -(PI / 2.5), range, damage, bulletSpeed);

				}
				else
				{
					_bullet->fire(x, y, -(PI / 2), range, damage, bulletSpeed);

				}
				faceState = pIDLE;
				fire = true;

			}
			if (KEYMANAGER->isStayKeyDown(VK_LEFT))
			{
				if (KEYMANAGER->isStayKeyDown('W'))
				{
					_bullet->fire(x, y, (PI / 1.5), range, damage, bulletSpeed);

					//기본총알 이동거리 300, 데미지 10, 이동속도 5
				}
				else if (KEYMANAGER->isStayKeyDown('S'))
				{
					_bullet->fire(x, y, -(PI / 1.5), range, damage, bulletSpeed);

				}
				else
				{
					_bullet->fire(x, y, PI, range, damage, bulletSpeed);

				}
				faceState = pLEFT;
				fire = true;
			}
			if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
			{
				if (KEYMANAGER->isStayKeyDown('W'))
				{
					_bullet->fire(x, y, (PI / 2.5), range, damage, bulletSpeed);

					//기본총알 이동거리 300, 데미지 10, 이동속도 5
				}
				else if (KEYMANAGER->isStayKeyDown('S'))
				{
					_bullet->fire(x, y, -(PI / 2.5), range, damage, bulletSpeed);

				}
				else
				{
					_bullet->fire(x, y, (PI * 2), range, damage, bulletSpeed);

				}
				faceState = pRIGHT;
				fire = true;
			}
		}
	}
	else if (arrow == 유황)
	{
		bulletCount++;
		if (bulletCount % 20 == 0)
		{
			////유황일때 기본 range 200,damage 1, 속도 30 
			if (KEYMANAGER->isStayKeyDown(VK_UP))
			{
				_유황->fire(x, y - PLAYERSIZEY / 2 - PLAYERHEADSIZEY / 2 + 10, 3, range, damage, bulletSpeed);
				fire = true;
				faceState = pUP;
			}
			if (KEYMANAGER->isStayKeyDown(VK_DOWN))
			{
				_유황->fire(x, y - PLAYERSIZEY / 2 - PLAYERHEADSIZEY / 2 + 10, 4, range, damage, bulletSpeed);
				faceState = pIDLE;
				fire = true;
			}
			if (KEYMANAGER->isStayKeyDown(VK_LEFT))
			{
				_유황->fire(x, y - PLAYERSIZEY / 2 - PLAYERHEADSIZEY / 2 + 10, 2, range, damage, bulletSpeed);
				faceState = pLEFT;
				fire = true;
			}
			if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
			{
				_유황->fire(x, y - PLAYERSIZEY / 2 - PLAYERHEADSIZEY / 2 + 10, 1, range, damage, bulletSpeed);
				faceState = pRIGHT;
				fire = true;
			}
		}
	}
}

void cPlayer::PlayerKeyState(void)
{
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		if (fire == false)
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
			_im->ItemUse(폭탄);
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		if (space == 박사의조정기)
		{
			_im->ItemUse(박사의조정기);
		}
		if (space == 모래시계)
		{
			_im->ItemUse(모래시계);
		}
	}

	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		if (card == 카드)
		{
			_im->ItemUse(카드);
		}
	}
	rc = RectMakeCenter(x, y, PLAYERSIZEX, PLAYERSIZEY);
	rcHead = RectMakeCenter(x, y - PLAYERSIZEY / 2 - PLAYERHEADSIZEY / 2 + 10, PLAYERHEADSIZEX, PLAYERHEADSIZEY);
}

void cPlayer::addInVentory(int _item)
{
	vInventory.push_back(_item);
}