#pragma once
#include "gameNode.h"
class cPlayer;
class cItemManager;
#define MAPMAX 5 // 맵매니져에서만씀 



enum EMAPSTATE
{
	맵11,
	맵12,
	맵13,
	맵14,
	맵1보스
	//등등등
};

  
class cSceneManager : public gameNode
{
private:

	cPlayer* _player;
	cItemManager* _im;

	RECT rc; // 테스트용! 실제로는 픽셀로 만들자!
	RECT rc2; // 테스트용! 실제로는 픽셀로 만들자!	
	RECT temp; //테스트용! 렉트충돌함수에서사용!
	RECT store;


	bool ItemSetting[MAPMAX]; // 맵체인지할때 아이템리셋하는거막기위해 맵담당자말고는 중요하지않음
	int currentMap;	 // 현재 무슨맵인지 모든클래스가 이거 참조함

public:



	int GetCurrentMap() { return currentMap; }
	
	void SetIM(cItemManager* iim) { _im = iim; }
	void SetPlayer(cPlayer* pplayer) { _player = pplayer; }
	
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);



	cSceneManager() {}
	~cSceneManager() {}
};

