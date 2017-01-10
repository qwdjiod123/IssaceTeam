#pragma once
#include "gameNode.h"
#include "bullet.h"
#define PLAYERSIZEX 18*3 // �÷��̾Ʈ������
#define PLAYERSIZEY 15*3
#define PLAYERHEADSIZEX 28*3
#define PLAYERHEADSIZEY 25*3
enum PlayerFaceState
{
	pLEFT,
	pRIGHT,
	pIDLE,
    pUP,
};
class cItemManager;

class cPlayer : public gameNode
{
private:

	cItemManager* _im;
	bullet* _bullet;
	PlayerFaceState faceState; 
	PlayerFaceState keyState;
	RECT rc;
	RECT rcHead;
	float x;
	float y;	
	int currentmap;
	//�ִϸ��̼� 
	int frameCount;
	int returnCount;
	bool fire;
	int leftFrame;
	int rightFrame;
	int upDownFrame;

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
	void animation(void);
	cPlayer() {}
	~cPlayer(){}
};

