#pragma once
#include "gameNode.h"
#include "bullet.h"
<<<<<<< HEAD
=======
#define PLAYERSIZEX 18*3 // �÷��̾Ʈ������
#define PLAYERSIZEY 15*3
#define PLAYERHEADSIZEX 28*3
#define PLAYERHEADSIZEY 25*3
>>>>>>> origin/master
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
<<<<<<< HEAD
	missile* _��Ȳ;
=======
	bullet* _��Ȳ;
>>>>>>> origin/master
	cItemManager* _im;
	PlayerFaceState faceState;
	PlayerFaceState keyState;
	RECT rc;
	RECT rcHead;
	float x;
	float y;
	//�ִϸ��̼� 
	int bulletCount;
	int frameCount;
	int returnCount;
	bool fire;
	bool bulletFire;
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
	int maxHp;
	int range; //�Ѿ˹���
	int damage;	//�����
	int tears; //�Ѿ˹߻簣��,����ӵ�
	float moveSpeed; //�̵��ӵ�
	float bulletSpeed; //�Ѿ˼ӵ� ��� �ٲ�°��� �ƴ��� �𸣰ٽ�;

<<<<<<< HEAD
					   //==================================================================
					   //		## ������ ##  �߰��ε��� �����ʼ�!
					   //==================================================================
=======
	//==================================================================
	//		## ������ ##  �߰��ε��� �����ʼ�!
	//==================================================================
>>>>>>> origin/master
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

	int GetHp() { return hp; }
	void SetHp(int _hp) { hp = _hp; }

	int GetmaxHp() { return maxHp; }
	void SetmaxHp(int _maxHp) { maxHp = _maxHp; }

<<<<<<< HEAD
	int GetRange() { return range; }
	void SetRange(int _range) { range = _range; }

	int GetDamage() { return damage; }
	void SetDamage(int _damage) { damage = _damage; }

	int GetBulletSpeed() { return bulletSpeed; }
	void SetBulletDamage(int _bulletSpeed) { bulletSpeed = _bulletSpeed; }
=======
>>>>>>> origin/master
	void addInVentory(int _item); // ������ �Ŵ������� ��

	RECT GetRC() { return rc; }

	bullet* getBullet() { return _bullet; }
<<<<<<< HEAD
	missile* get��Ȳ() { return _��Ȳ; }
=======

>>>>>>> origin/master
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void animation(void);
	void bulletFire(void);
	void PlayerKeyState(void);
	cPlayer() {}
	~cPlayer() {}
};

