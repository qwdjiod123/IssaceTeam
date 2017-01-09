#pragma once
#include "gameNode.h"
#define ITEMSIZE 50  // 아이템 매니져만씀 이미지(렉트)사이즈
#define BOMBSIZE 100 // 아이템매니져만씀  폭팔할떄(렉트)사이즈


class cSceneManager;
class cPlayer;

//==================================================================
//		## 아이템종류 여기에다 추가예정 ## 상호참조하면 다른데서 이거 참조가능
//==================================================================

enum EITEM
{		
	폭탄=0,
	열쇠,
	동전,
	혈사,
};

enum EWEAPON
{
	기본총알=100,			
};


struct tag_Item
{
	float x;
	float y;
	RECT rc;
	int state; // 이아이템이 무엇인지 
	int currentmap; // 현재 무슨맵에 생성되어있는 아이템인지
	
	bool IsBomb;  // 폭탄사용하는거떄문에 따로만든 변수 
	int contdown=0; // 폭탄사용하는거떄문에 따로만든 변수 
};

class cItemManager : public gameNode
{
private:

	RECT temp;

//==================================================================
//		## 아이템관리 백터 ##
//==================================================================
	vector<tag_Item> vItem;	 // 맵에 기본적으로 셋팅되있는 아이템들
	vector<tag_Item> vNewItem; // 무언가 유동적으로 생기는아이템들! 상점에서 템사면 생성되는아이템들 혹은 플레이거 폭탄사용할떄 여기추가함

	cSceneManager* _sm;
	cPlayer* _player;
	
	RECT test;

public:

	void SetIM(cSceneManager* ssm) { _sm = ssm; }
	void SetPlayer(cPlayer* pplayer) { _player = pplayer; }

	void ItemMapSet(float _x, float _y, int _state, int _currentmap); // 맵만드는사람이씁니다.
		
	void ItemUse(int itemNumber,int money=0); // 플레이어에서씁니다. 맵만드는사람이 쓸수도있슴.
	void ItemMake(float _x, float _y, int _state, int _currentmap);

	void DeleteItem(int index); // 아이템매니져에서만 씁니다.
	void DeleteNewItem(int index); // 아이템매니져에서만 씁니다.
	
	void ItemUpdate(int _currentmap);      //아이템 매니져에서만씀
	void NewItemUpdate(int _currentmap);   //아이템 매니져에서만씀
	void ItemRender(int _currentmap);      //아이템 매니져에서만씀 , 맵만드는사람이쓸수도있슴(확인용)
	void NewItemRender(int _currentmap);   //아이템 매니져에서만씀 , 맵만드는사람이쓸수도있슴(확인용)
	


	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	
	cItemManager() {}
	~cItemManager() {}
};

