#pragma once
#include "gameNode.h"
#include "minion.h"
#include "bullet.h"
#include"groundEnemy.h"
//��ȣ������ �÷��̾� Ŭ���� ���漱��

class cPlayer;
class cItemManager;
class enemyManager : public gameNode
{
private:
	vector<enemy*> _vMinion;
	vector<enemy*>::iterator _viMinion;

	cPlayer* _player;
	cItemManager* _im;
	bullet* _bullet;
	int _count;

		//�����Ҵ� �ϸ� �ȵȴ�!!!

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//�̴Ͼ� ���� => �ʱ�ȭ�� �־��ٰ�
	void setMinion(void);

	//�̴Ͼ� �Ѿ˹߻�
	void minionBulletFire(void);

	//�̴Ͼ� ����
	void removeMinion(int index);

	//�浹�Լ�
	void collision();

	//�̴Ͼ� ���� ��������
	vector<enemy*> getVMinion() { return _vMinion; }

	void setPlayer(cPlayer* player) { _player = player; }
	void setPlayer(cItemManager* im) { _im = im; }

	//��ȣ������ �÷��̾������͸� �ѱ� �����Լ�
	

	enemyManager() {}
	~enemyManager() {}
};

