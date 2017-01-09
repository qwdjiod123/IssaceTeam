#pragma once
#include "gameNode.h"
#define ITEMSIZE 50  // ������ �Ŵ������� �̹���(��Ʈ)������
#define BOMBSIZE 100 // �����۸Ŵ�������  �����ҋ�(��Ʈ)������


class cSceneManager;
class cPlayer;

//==================================================================
//		## ���������� ���⿡�� �߰����� ## ��ȣ�����ϸ� �ٸ����� �̰� ��������
//==================================================================

enum EITEM
{		
	��ź=0,
	����,
	����,
	����,
};

enum EWEAPON
{
	�⺻�Ѿ�=100,			
};


struct tag_Item
{
	float x;
	float y;
	RECT rc;
	int state; // �̾������� �������� 
	int currentmap; // ���� �����ʿ� �����Ǿ��ִ� ����������
	
	bool IsBomb;  // ��ź����ϴ°ŋ����� ���θ��� ���� 
	int contdown=0; // ��ź����ϴ°ŋ����� ���θ��� ���� 
};

class cItemManager : public gameNode
{
private:

	RECT temp;

//==================================================================
//		## �����۰��� ���� ##
//==================================================================
	vector<tag_Item> vItem;	 // �ʿ� �⺻������ ���õ��ִ� �����۵�
	vector<tag_Item> vNewItem; // ���� ���������� ����¾����۵�! �������� �ۻ�� �����Ǵ¾����۵� Ȥ�� �÷��̰� ��ź����ҋ� �����߰���

	cSceneManager* _sm;
	cPlayer* _player;
	
	RECT test;

public:

	void SetIM(cSceneManager* ssm) { _sm = ssm; }
	void SetPlayer(cPlayer* pplayer) { _player = pplayer; }

	void ItemMapSet(float _x, float _y, int _state, int _currentmap); // �ʸ���»���̾��ϴ�.
		
	void ItemUse(int itemNumber,int money=0); // �÷��̾�����ϴ�. �ʸ���»���� �������ֽ�.
	void ItemMake(float _x, float _y, int _state, int _currentmap);

	void DeleteItem(int index); // �����۸Ŵ��������� ���ϴ�.
	void DeleteNewItem(int index); // �����۸Ŵ��������� ���ϴ�.
	
	void ItemUpdate(int _currentmap);      //������ �Ŵ�����������
	void NewItemUpdate(int _currentmap);   //������ �Ŵ�����������
	void ItemRender(int _currentmap);      //������ �Ŵ����������� , �ʸ���»���̾������ֽ�(Ȯ�ο�)
	void NewItemRender(int _currentmap);   //������ �Ŵ����������� , �ʸ���»���̾������ֽ�(Ȯ�ο�)
	


	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	
	cItemManager() {}
	~cItemManager() {}
};

