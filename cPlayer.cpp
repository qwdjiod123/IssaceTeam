#include "stdafx.h"
#include "cPlayer.h"
#include"cItemManager.h"

HRESULT cPlayer::init(void)
{
	//�⺻ �÷��̾� ���� 
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
	hp = 6;
	maxHp = 6;
	rc = RectMakeCenter(x, y, PLAYERSIZEX, PLAYERSIZEY); //�÷��̾� ����
	rcHead = RectMakeCenter(x, y - PLAYERSIZEY / 2 - PLAYERHEADSIZEY / 2 + 10, PLAYERHEADSIZEX, PLAYERHEADSIZEY);//�÷��̾� �Ӹ� 
																												 //�ִϸ��̼� �ʿ��� Count 
	frameCount = 0;
	leftFrame = 0;               //���ʰɾ�� 
	rightFrame = 0;            //�����ʰɾ��
	upDownFrame = 0;       //�Ʒ� �� ī��Ʈ
	returnCount = 0;         //�ٽ� �Ӹ� ���� ������ ī��Ʈ 
	bulletCount = 0;         //�Ѿ˹߻�Ǵ� ī��Ʈ 
	fire = false;               //�Ѿ��� �߻� �Ǿ���?
								//���⼭ �Ѿ����� �ΰ��� ���� ����! 
	_bullet = new bullet;
	_bullet->init("�⺻�Ѿ�", 200);
	_��Ȳ = new missile;
	_��Ȳ->init(200, 200);
	return S_OK;
}

void cPlayer::release(void)
{
	_bullet->release();
	SAFE_DELETE(_bullet);
	_��Ȳ->release();
	SAFE_DELETE(_��Ȳ);
}

void cPlayer::update(void)
{
	PlayerKeyState();
	bulletFire();
	animation();
	_bullet->update();
	_��Ȳ->update();

}

void cPlayer::render(void)
{
	_bullet->render();
	_��Ȳ->render();
	for (int i = 0; i < vInventory.size(); i++)
	{
		if (vInventory[i] == ��Ȳ)
		{
			arrow = ��Ȳ;
		}
		if (vInventory[i] == ���������Ǳ���)
		{
			//�÷��̾� �̹����ٲ�
		}
	}
	if (arrow == �⺻�Ѿ�)
	{
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
			//	cout << "left" << endl;
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
	}
	//RectangleMake(getMemDC(), rc);
	else if (arrow == ��Ȳ)
	{
		if (KEYMANAGER->isStayKeyDown('D'))
		{
			IMAGEMANAGER->frameRender("��Ȳ���ʸ���", getMemDC(), rc.left, rc.top, leftFrame, 1);
		}
		else if (KEYMANAGER->isStayKeyDown('A'))
		{
			IMAGEMANAGER->frameRender("��Ȳ�����ʸ���", getMemDC(), rc.left, rc.top, rightFrame, 1);
		}
		else if (KEYMANAGER->isStayKeyDown('W'))
		{
			IMAGEMANAGER->frameRender("��ȲUPDOWN", getMemDC(), rc.left, rc.top, upDownFrame, 1);
		}
		else if (KEYMANAGER->isStayKeyDown('S'))
		{
			IMAGEMANAGER->frameRender("��ȲUPDOWN", getMemDC(), rc.left, rc.top, upDownFrame, 1);
		}
		else
		{
			IMAGEMANAGER->render("��Ȳ����", getMemDC(), rc.left, rc.top, 0, 0, PLAYERSIZEX, PLAYERSIZEY);
		}

		switch (faceState)
		{
		case pLEFT:
			IMAGEMANAGER->render("��Ȳ���ʾ�", getMemDC(), rcHead.left, rcHead.top, 0, 0, PLAYERHEADSIZEX, PLAYERHEADSIZEY);
			//cout << "left" << endl;
			break;
		case pRIGHT:
			IMAGEMANAGER->render("��Ȳ�����ʾ�", getMemDC(), rcHead.left, rcHead.top, 0, 0, PLAYERHEADSIZEX, PLAYERHEADSIZEY);
			break;
		case pIDLE:
			IMAGEMANAGER->render("��ȲIDLE", getMemDC(), rcHead.left - 5, rcHead.top, 0, 0, PLAYERHEADSIZEX + 10, PLAYERHEADSIZEY);
			break;
		case pUP:
			IMAGEMANAGER->render("��Ȳ�����", getMemDC(), rcHead.left, rcHead.top, 0, 0, PLAYERHEADSIZEX, PLAYERHEADSIZEY);
			break;
		default:
			break;
		}
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

void cPlayer::bulletFire(void)
{
	if (arrow == �⺻�Ѿ�)
	{
		bulletCount++;
		if (bulletCount % 10 == 0)
		{
			if (KEYMANAGER->isStayKeyDown(VK_UP))
			{
				if (KEYMANAGER->isStayKeyDown('A'))
				{
					_bullet->fire(x, y, (PI / 1.9), range, damage, bulletSpeed);
					//�⺻�Ѿ� �̵��Ÿ� 300, ������ 10, �̵��ӵ� 5

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

					//�⺻�Ѿ� �̵��Ÿ� 300, ������ 10, �̵��ӵ� 5
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

					//�⺻�Ѿ� �̵��Ÿ� 300, ������ 10, �̵��ӵ� 5
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

					//�⺻�Ѿ� �̵��Ÿ� 300, ������ 10, �̵��ӵ� 5
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
	else if (arrow == ��Ȳ)
	{
		bulletCount++;
		if (bulletCount % 20 == 0)
		{
			////��Ȳ�϶� �⺻ range 200,damage 1, �ӵ� 30 
			if (KEYMANAGER->isStayKeyDown(VK_UP))
			{
				_��Ȳ->fire(x, y - PLAYERSIZEY / 2 - PLAYERHEADSIZEY / 2 + 10, 3, range, damage, bulletSpeed);
				fire = true;
				faceState = pUP;
			}
			if (KEYMANAGER->isStayKeyDown(VK_DOWN))
			{
				_��Ȳ->fire(x, y - PLAYERSIZEY / 2 - PLAYERHEADSIZEY / 2 + 10, 4, range, damage, bulletSpeed);
				faceState = pIDLE;
				fire = true;
			}
			if (KEYMANAGER->isStayKeyDown(VK_LEFT))
			{
				_��Ȳ->fire(x, y - PLAYERSIZEY / 2 - PLAYERHEADSIZEY / 2 + 10, 2, range, damage, bulletSpeed);
				faceState = pLEFT;
				fire = true;
			}
			if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
			{
				_��Ȳ->fire(x, y - PLAYERSIZEY / 2 - PLAYERHEADSIZEY / 2 + 10, 1, range, damage, bulletSpeed);
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
	rc = RectMakeCenter(x, y, PLAYERSIZEX, PLAYERSIZEY);
	rcHead = RectMakeCenter(x, y - PLAYERSIZEY / 2 - PLAYERHEADSIZEY / 2 + 10, PLAYERHEADSIZEX, PLAYERHEADSIZEY);
}

void cPlayer::addInVentory(int _item)
{
	vInventory.push_back(_item);
}