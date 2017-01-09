#include "stdafx.h"
#include "groundEnemy.h"
#include"cPlayer.h"

groundEnemy::groundEnemy()
{
}


groundEnemy::~groundEnemy()
{
}

HRESULT groundEnemy::init(void)
{
	return S_OK;
}

HRESULT groundEnemy::init(char * V_ImgName, char * H_ImaName, POINT position, float moveSpeed)
{
	_v_img = IMAGEMANAGER->findImage(V_ImgName);
	_h_img = IMAGEMANAGER->findImage(H_ImaName);
	_rc = RectMakeCenter(position.x, position.y, _v_img->getWidth(), _v_img->getHeight());
	_moveSpeed = moveSpeed;
	return E_NOTIMPL;
}



void groundEnemy::release(void)
{
}

void groundEnemy::update(void)
{
	move();
	animation();
}

void groundEnemy::render(void)
{
	draw();
}

void groundEnemy::move()
{
	switch (_move)
	{
	case UP:
		_y -= _moveSpeed;
		break;
	case DOWN:
		_y += _moveSpeed;
		break;
	case LEFT:
		_x -= _moveSpeed;
		break;
	case RIGHT:
		_x += _moveSpeed;
		break;
	}

	if (_move == UP || _move == DOWN)
	{
		_rc = RectMakeCenter(_x, _y, _v_img->getWidth(), _v_img->getHeight());
	}
	else
	{
		_rc = RectMakeCenter(_x, _y, _h_img->getWidth(), _h_img->getHeight());
	}

}

void groundEnemy::draw()
{
	if (_move == UP || _move == DOWN)
	{
		_v_img->render(getMemDC(), _rc.left, _rc.top);
	}
	else
	{
		_h_img->render(getMemDC(), _rc.left, _rc.top);
	}

	if (KEYMANAGER->isToggleKey('A'))
	{
		Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	}

}

void groundEnemy::animation()
{
}
