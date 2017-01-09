#pragma once
#include "gameNode.h"
#include "bullet.h"
#define PLAYERSIZE 50 // �÷��̾Ʈ������

class cItemManager;

class cPlayer : public gameNode
{
private:

	cItemManager* _im;
	bullet* _bullet;

	RECT rc;
	float x;
	float y;	

	int currentmap;

//==================================================================
//		## ���� ## �߰��ε��� �����ʼ�!
//==================================================================
	int hp;  //ü��
	int range; //�Ѿ˹���
	int damage;	//�����
	int tears; //�Ѿ˹߻簣��,����ӵ�
	float moveSpeed; //�̵��ӵ�
	float bulletSpeed; //�Ѿ˼ӵ� ��� �ٲ�°��� �ƴ��� �𸣰ٽ�;

//==================================================================
//		## ������ ##  �߰��ε��� �����ʼ�!
//==================================================================
	int money;	//��
	int key;	//����
	int bomb;   //��ź
	int arrow;  //�����Ѿ�����
	int space;  //������


public:
	void SetIM(cItemManager* iim) { _im = iim; }

	void SetCurrentMap(int _currentmap) { currentmap = _currentmap; }
	int GetCurrentMap() { return currentmap; }

	int GetKey() { return key; }
	void SetKey(int _key) { key = _key; }

	int GetMoney() { return money; }
	void SetMoney(int _money) { money = _money; }

	int GetBomb() { return bomb; }
	void SetBomb(int _bomb) { bomb = _bomb; }

	void SetX(float _x) { x = _x; }
	float GetX() { return x; }

	float GetY() { return y; }
	void SetY(float _y) { y = _y; }

	RECT GetRC() { return rc; }
	
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	cPlayer() {}
	~cPlayer(){}
};

