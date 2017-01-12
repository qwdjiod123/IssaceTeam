#include "stdafx.h"
#include "enemyManager.h"
#include"cPlayer.h"

HRESULT enemyManager::init(void)
{
	//�̴Ͼ� ����
	
	_count = 0;
	setMinion();
	//�Ѿ�Ŭ���� ���� �� �ʱ�ȭ
	_bullet = new bullet;
	//_bullet->init("bullet", 15);

	return S_OK;
}

void enemyManager::release(void)
{
	//�Ѿ�Ŭ���� ����
	_bullet->release();
	SAFE_DELETE(_bullet);
}

void enemyManager::update(void)
{
	//���Ϳ� ��� �̴Ͼ�� ������Ʈ
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


	//�Ѿ�Ŭ���� ������Ʈ
	_bullet->update();

	//�̴Ͼ� �Ѿ˹߻�
	this->minionBulletFire();

	//�浹ó��
	this->collision();

}

void enemyManager::render(void)
{
	//���Ϳ� ��� �̴Ͼ�� ����
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

//���Ѿ˰� �÷��̾�
void enemyManager::collision()
{
	_viMinion = _vMinion.begin();
	for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
	{
		RECT temp;
		if (IntersectRect(&temp, &(*_viMinion)->getRect(), &_player->GetRC()))//�����ġ�� ���Ѱ�� 
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
