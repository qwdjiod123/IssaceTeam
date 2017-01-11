#pragma once
#include "gameNode.h"
#include "bullet.h"
#define PLAYERSIZEX 18*3 // �÷��̾Ʈ������
#define PLAYERSIZEY 15*3
#define PLAYERHEADSIZEX 28*3
#define PLAYERHEADSIZEY 25*3
class cItemManager;

enum PlayerFaceState
{
	pLEFT,
	pRIGHT,
	pIDLE,
	pUP,
};

class cPlayer : public gameNode
{
private:
	TCHAR buffer[256]; // Textout�Ҷ� ���¿뵵!

	bullet* _bullet;
	cItemManager* _im;
	PlayerFaceState faceState;
	PlayerFaceState keyState;
	RECT rc;
	RECT rcHead;
	float x;
	float y;
	//�ִϸ��̼� 
	int frameCount;
	int returnCount;
	bool fire;
	int leftFrame;
	int rightFrame;
	int upDownFrame;


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

	void addInVentory(int _item); // ������ �Ŵ������� ��

	RECT GetRC() { return rc; }

	bullet* getBullet() { return _bullet; }

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void animation(void);
	cPlayer() {}
	~cPlayer() {}
};

