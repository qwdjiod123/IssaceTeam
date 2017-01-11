#include "stdafx.h"
#include "fly.h"
#include"cPlayer.h"

HRESULT fly::init(void)
{
	return S_OK;
}

HRESULT fly::init(string imageName, int x, int y, cPlayer * player)
{
	_img = IMAGEMANAGER->findImage(imageName);
	_x = x;
	_y = y;
	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
	_player = player;
	_angle = 0;
	_moveSpeed = 0;
	_HP = 2;
	_isMove = false;
	_currentFrameX = 0;
	_currentFrameY = 0;

	return S_OK;
}

void fly::release(void)
{
}

void fly::update(void)
{
	move();
	animation();
}

void fly::render(void)
{
	draw();

}

void fly::move()
{
	if (_isMove)
	{
		_angle = getAngle(_x, _y, _player->GetX(), _player->GetY());
		_moveSpeed = 2;
	}

	_x += cosf(_angle)*_moveSpeed;
	_y += -sinf(_angle)*_moveSpeed;

	if (_knockBackCount > 0)
	{
		_knockBackCount--;
		_x += cosf(_knockBackAngle)*KONCKBACKPOWER;
		_y += -sinf(_knockBackAngle)*KONCKBACKPOWER;
	}
	else
	{
		_knockBackCount = 0;
		_knockBackAngle = 0;
	}


	if (getDistance(_x, _y, _player->GetX(), _player->GetY()))
	{
		_isMove = true;
	}
	_rc = RectMakeCenter(_x, _y, _img->getFrameWidth(), _img->getFrameHeight());
}

void fly::draw()
{
	_img->frameRender(getMemDC(), _rc.left, _rc.top, _currentFrameX, _currentFrameY);
}

void fly::animation()
{
	if (_currentFrameX > _img->getMaxFrameX())
	{
		_currentFrameX = 0;
	}
	else
	{
		_currentFrameX++;
	}
}

void fly::collision()
{
	RECT temp;
	if (IntersectRect(&temp, &_rc, &_player->GetRC()))//몸통박치기 당한경우 
	{

	}

	RECT colTemp;
	for (int i = 0; i < _player->getBullet()->getVBulletPt()->size(); i++)
	{
		if (IntersectRect(&colTemp, &_rc, &_player->getBullet()->getVBulletPt()->at(i).rc))
		{
			_knockBackCount = 5;
			_knockBackAngle = getAngle(_player->getBullet()->getVBulletPt()->at(i).x, _player->getBullet()->getVBulletPt()->at(i).y, _x, _y);
			_player->getBullet()->getVBulletPt()->erase(_player->getBullet()->getVBulletPt()->begin() + i);
			_HP--;//겟 데미지로 수정 필수
			break;
		}
	}

}
