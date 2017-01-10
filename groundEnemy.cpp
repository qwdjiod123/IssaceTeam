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

HRESULT groundEnemy::init(char * V_ImgName, char * H_ImaName, POINT position, float moveSpeed, cPlayer* player)
{
	_v_img = IMAGEMANAGER->findImage(V_ImgName);
	_h_img = IMAGEMANAGER->findImage(H_ImaName);
	_rc = RectMakeCenter(position.x, position.y, _v_img->getWidth(), _v_img->getHeight());
	_moveSpeed = moveSpeed;
	_attackCount = 0;
	_player = player;
	isAttack = false;
	_moveCount = RND->getFromIntTo(10, 30);
	_move = LEFT;
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

	if (_move == UP || _move == DOWN)
	{
		_rc = RectMakeCenter(_x, _y, _v_img->getWidth(), _v_img->getHeight());
	}
	else
	{
		_rc = RectMakeCenter(_x, _y, _h_img->getWidth(), _h_img->getHeight());
	}

	if (_y < _player->GetRC().bottom&&_y > _player->GetRC().top)//y범위에 걸렸을 경우
	{
		if (_x < _player->GetRC().left)
		{
			isAttack = true;
			_attackCount = 30;
			_move = RIGHT;
			_moveSpeed = 3.0f;
		}

		if (_x < _player->GetRC().right)
		{
			isAttack = true;
			_attackCount = 30;
			_move = LEFT;
			_moveSpeed = 3.0f;
		}
	}

	if (_x > _player->GetRC().left&&_x < _player->GetRC().right)//y범위에 걸렸을 경우
	{
		if (_y < _player->GetRC().top)
		{
			isAttack = true;
			_attackCount = 30;
			_move = DOWN;
			_moveSpeed = 3.0f;
		}

		if (_y >_player->GetRC().bottom)
		{
			isAttack = true;
			_attackCount = 30;
			_move = UP;
			_moveSpeed = 3.0f;
		}
	}

	if (_attackCount > 0)
	{
		_attackCount--;
	}
	else
	{
		_moveSpeed = 2.0f;
		if (_moveCount > 0)
		{
			_moveCount--;
		}
		else
		{
			_moveCount = RND->getFromIntTo(100, 200);
			_move = (MOVESTATE)RND->getInt(4);
		}
	}


	//케릭터 몸이랑 몬스터 몸의 충돌
	RECT temp;
	if (IntersectRect(&temp, &_player->GetRC(), &_rc))
	{
		//몸통박치기 충돌 했을때.
	}



	//캐릭터 총알이랑 몬스터 몸체의 충돌
	RECT colTemp;
	for (int i = 0; i < _player->getBullet()->getVBullet().size(); i++)
	{
		if (IntersectRect(&colTemp, &_rc, &_player->getBullet()->getVBullet()[i].rc))
		{
			_knockBackCount = 5;
			_knockBackAngle = getAngle(_player->getBullet()->getVBullet()[i].x, _player->getBullet()->getVBullet()[i].y, _x, _y);
			_player->getBullet()->getVBullet().erase(_player->getBullet()->getVBullet().begin() + i);
			break;
		}
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

