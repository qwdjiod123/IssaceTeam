#pragma once
#include "gameNode.h"
class cPlayer;
class cItemManager;
#define MAPMAX 5 // �ʸŴ����������� 



enum EMAPSTATE
{
	��11,
	��12,
	��13,
	��14,
	��1����
	//����
};

  
class cSceneManager : public gameNode
{
private:

	cPlayer* _player;
	cItemManager* _im;

	RECT rc; // �׽�Ʈ��! �����δ� �ȼ��� ������!
	RECT rc2; // �׽�Ʈ��! �����δ� �ȼ��� ������!	
	RECT temp; //�׽�Ʈ��! ��Ʈ�浹�Լ��������!
	RECT store;


	bool ItemSetting[MAPMAX]; // ��ü�����Ҷ� �����۸����ϴ°Ÿ������� �ʴ���ڸ���� �߿���������
	int currentMap;	 // ���� ���������� ���Ŭ������ �̰� ������

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

