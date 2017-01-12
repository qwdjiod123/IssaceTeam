#include "stdafx.h"
#include "enemyManager.h"
#include"cPlayer.h"

HRESULT enemyManager::init(void)
{
	//미니언 생성
	
	_count = 0;
	setMinion();
	//총알클래스 생성 및 초기화
	_bullet = new bullet;
	//_bullet->init("bullet", 15);

	return S_OK;
}

void enemyManager::release(void)
{
	//총알클래스 해제
	_bullet->release();
	SAFE_DELETE(_bullet);
}

void enemyManager::update(void)
{
	//벡터에 담긴 미니언들 업데이트
	_viMinion = _vMinion.begin();
	for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->update();
		
	}

	_viMinion = _vMinion.begin();
	for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
	{
		if ((*_viMinion)->getHP() <= 0)
		{
			_viMinion = _vMinion.erase(_viMinion);
			break;
		}
	}


	//총알클래스 업데이트
	_bullet->update();

	//미니언 총알발사
	this->minionBulletFire();

	//충돌처리
	this->collision();

}

void enemyManager::render(void)
{
	//벡터에 담긴 미니언들 렌더
	_viMinion = _vMinion.begin();
	for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
	{
		(*_viMinion)->render();
	}

	_bullet->render();
}

void enemyManager::setMinion(void)
{
	groundEnemy* temp = new groundEnemy;
	temp->init("worm_V","worm_H",100,100,3.0f,_player);
	_vMinion.push_back(temp);
}

void enemyManager::minionBulletFire(void)
{
	_viMinion = _vMinion.begin();
	for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
	{
		if ((*_viMinion)->bulletCountFire())
		{
			RECT rc = (*_viMinion)->getRect();
			//_bullet->fire(rc.left + (rc.right - rc.left) / 2, rc.bottom + 30, -PI / 2, 3.0f);
		}
	}
}

void enemyManager::removeMinion(int index)
{
	_vMinion.erase(_vMinion.begin() + index);
}

//적총알과 플레이어
void enemyManager::collision()
{
	_viMinion = _vMinion.begin();
	for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
	{
		RECT temp;
		if (IntersectRect(&temp, &(*_viMinion)->getRect(), &_player->GetRC()))//몸통박치기 당한경우 
		{

		}

		RECT colTemp;
		for (int i = 0; i < _player->getBullet()->getVBulletPt()->size(); i++)
		{
			if (IntersectRect(&colTemp, &(*_viMinion)->getRect(), &_player->getBullet()->getVBulletPt()->at(i).rc))
			{
				(*_viMinion)->setknockBackCount(5);
				(*_viMinion)->setknockBackAngle(getAngle(_player->getBullet()->getVBulletPt()->at(i).x, _player->getBullet()->getVBulletPt()->at(i).y, (*_viMinion)->getX(), (*_viMinion)->getY()));
				_player->getBullet()->getVBulletPt()->erase(_player->getBullet()->getVBulletPt()->begin() + i);
				(*_viMinion)->setHP(((*_viMinion)->getHP())-1);
				break;
			}
		}
	}
}
