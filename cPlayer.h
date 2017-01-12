#pragma once
#include "gameNode.h"
#include "bullet.h"
<<<<<<< HEAD
=======
#define PLAYERSIZEX 18*3 // 플레이어렉트사이즈
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
	TCHAR buffer[256]; // Textout할때 쓰는용도!

	bullet* _bullet;
<<<<<<< HEAD
	missile* _유황;
=======
	bullet* _유황;
>>>>>>> origin/master
	cItemManager* _im;
	PlayerFaceState faceState;
	PlayerFaceState keyState;
	RECT rc;
	RECT rcHead;
	float x;
	float y;
	//애니메이션 
	int bulletCount;
	int frameCount;
	int returnCount;
	bool fire;
	bool bulletFire;
	int leftFrame;
	int rightFrame;
	int upDownFrame;


	// 만약에 날개아이템(구렁텅잉의군주?)을 먹으면 아이템 매니져쪽에서 얘를 true로 바꿀거임.
	// 맵매니져쪽에서 픽셀충돌을 IsFly==false일때만 검사하고 true가되면 픽셀충돌 하지않게 짜면될듯?
	bool IsFly = false;


	vector<int> vInventory;


	//==================================================================
	//		## 스탯 ## 추가로들어갈거 수정필수!
	//==================================================================
	int hp;  //체력
	int maxHp;
	int range; //총알범위
	int damage;	//대미지
	int tears; //총알발사간격,연사속도
	float moveSpeed; //이동속도
	float bulletSpeed; //총알속도 얘는 바뀌는건지 아닌지 모르겟슴;

<<<<<<< HEAD
					   //==================================================================
					   //		## 아이템 ##  추가로들어갈거 수정필수!
					   //==================================================================
=======
	//==================================================================
	//		## 아이템 ##  추가로들어갈거 수정필수!
	//==================================================================
>>>>>>> origin/master
	int money;	//돈
	int key;	//열쇠
	int bomb;   //폭탄
	int arrow;  //현재총알종류
	int space;  //아이템
	int card; //능력치올려주는카드

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
	void addInVentory(int _item); // 아이템 매니져에서 씀

	RECT GetRC() { return rc; }

	bullet* getBullet() { return _bullet; }
<<<<<<< HEAD
	missile* get유황() { return _유황; }
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

