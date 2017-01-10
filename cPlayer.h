#pragma once
#include "gameNode.h"
#include "bullet.h"
#define PLAYERSIZE 50 // �÷��̾Ʈ������

class cItemManager;

enum ESTATE
{
	IDLE,
	DAMAGED,
	// ī��ִϸ��̼��ϋ� ī������� �������ʿ��� �ɷ�ġ�÷��ְ� �÷��̾���¸� ��ιٲ� 
	// �÷��̾��ʿ����� ������϶� ���¾ִϸ��̼�? ����ϰ� �������� �ִ�� ���� IDLE�� �ٲٴ·���¥��ɵ�
	CARDANIM, 
};


class cPlayer : public gameNode
{
private:

	cItemManager* _im;
	bullet* _bullet;

	RECT rc;
	float x;
	float y;	
	int state = IDLE;

	// ���࿡ ����������(���������Ǳ���?)�� ������ ������ �Ŵ����ʿ��� �긦 true�� �ٲܰ���.
	// �ʸŴ����ʿ��� �ȼ��浹�� IsFly==false�϶��� �˻��ϰ� true���Ǹ� �ȼ��浹 �����ʰ� ¥��ɵ�?
	bool IsFly = false; 

	vector<int> vInventory;

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
	int card; //�ɷ�ġ�÷��ִ�ī��

public:
	void SetIM(cItemManager* iim) { _im = iim; }
	
	bool GetIsFly() { return IsFly; }
	void SetIsFly(bool _IsFly) { IsFly = _IsFly; }

	int GetMoney() { return money; }
	void SetMoney(int _money) { money = _money; }

	int GetKey() { return key; }
	void SetKey(int _key) { key = _key; }	

	int GetBomb() { return bomb; }
	void SetBomb(int _bomb) { bomb = _bomb; }

	int GetArrow() { return arrow; }
	void SetArrow(int _arrow) { arrow = _arrow; }

	int GetSpace() { return space; }
	void SetSpace(int _space) { space = _space; }

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

