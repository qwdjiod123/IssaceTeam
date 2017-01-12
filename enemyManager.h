#pragma once
#include "gameNode.h"
#include "minion.h"
#include "bullet.h"
#include"groundEnemy.h"
//상호참조용 플레이어 클래스 전방선언

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

		//동적할당 하면 안된다!!!

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//미니언 세팅 => 초기화에 넣어줄것
	void setMinion(void);

	//미니언 총알발사
	void minionBulletFire(void);

	//미니언 삭제
	void removeMinion(int index);

	//충돌함수
	void collision();

	//미니언 벡터 가져오기
	vector<enemy*> getVMinion() { return _vMinion; }

	void setPlayer(cPlayer* player) { _player = player; }
	void setPlayer(cItemManager* im) { _im = im; }

	//상호참조시 플레이어포인터를 넘길 셋터함수
	

	enemyManager() {}
	~enemyManager() {}
};

