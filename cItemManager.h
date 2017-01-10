#pragma once
#include "gameNode.h"
#define ITEMSIZE 50  // 아이템 매니져만씀 이미지(렉트)사이즈
#define BOMBSIZE 100 // 아이템매니져만씀  폭팔할떄(렉트)사이즈

class cSceneManager;
class cPlayer;



//==================================================================
//		## 아이템종류 여기에다 추가예정 ## 상호참조하면 다른데서 이거 참조가능
//==================================================================

enum EITEM  // 패시브아이템다포함
{	
	기본총알 = 0,
	폭탄,
	열쇠,
	동전,	
	썩은고기, //피통+1 하트+1

	유황, // 기본공격 바뀜! (이미지바뀜) 
	구렁텅이의군주, // 날라다님지형물무시 (이미지바뀜)

	악마아기,//얘는 할지안할지 미정 뒤에 따라다니면서 미사일쏘면서 도와줄수도있고 다른효과 낼수도있듬 !! 시간남으면 만들예정 !!
	
};

enum EACTIVEITEM // 스페이스바눌러서쓰는템들
{
	없음=100,
	박사의조정기, // 일정부분에 미사일생성 발사되기전까지 조준경위치변경가능 // 얘도할지안할지미정
	모래시계, // 적의움직임과 발사체를 느리게함 혹은 멈추게하는것도 괸찮을듯
};

enum EACTIVECARD // 카드는그냥 먹었을때 스탯등등 증가하는거보여주기위해 1개만만들예정
{
	카드=1000, // 사거리+2, 공격력+2, 이동속도+2, 공격속도+2 
};



struct tag_Item
{
	RECT rc;
	float x;
	float y;
	float angle; // 아이템도 움직임 ㅠㅠ
	float moveSpeed; // 아이템도 움직임 ㅠㅠ	
	int state; // 이아이템이 무엇인지 예 : state=폭탄
	int currentmap; // 현재 무슨맵에 생성되어있는 아이템인지
	
	bool IsBomb=false;  // 폭탄사용하는거떄문에 따로만든 변수 
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
		

public:

	void SetIM(cSceneManager* ssm) { _sm = ssm; }
	void SetPlayer(cPlayer* pplayer) { _player = pplayer; }

	void ItemMapSet(float _x, float _y, int _state, int _currentmap); // 맵만드는사람이씁니다.
		
	void ItemUse(int _item,int _money=0); // 플레이어에서씁니다. 맵만드는사람이 쓸수도있슴.
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

