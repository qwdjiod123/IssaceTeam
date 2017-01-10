#pragma once
#include "gameNode.h"
#include "bullet.h"
#define PLAYERSIZEX 18*3 // 플레이어렉트사이즈
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
	//애니메이션 
	int frameCount;
	int returnCount;
	bool fire;
	int leftFrame;
	int rightFrame;
	int upDownFrame;

//==================================================================
//		## 스탯 ## 추가로들어갈거 수정필수!
//==================================================================
	int hp;  //체력
	int range; //총알범위
	int damage;	//대미지
	int tears; //총알발사간격,연사속도
	float moveSpeed; //이동속도
	float bulletSpeed; //총알속도 얘는 바뀌는건지 아닌지 모르겟슴;

//==================================================================
//		## 아이템 ##  추가로들어갈거 수정필수!
//==================================================================
	int money;	//돈
	int key;	//열쇠
	int bomb;   //폭탄
	int arrow;  //현재총알종류
	int space;  //아이템


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

