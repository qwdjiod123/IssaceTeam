#pragma once
#include "gameNode.h"
#define ITEMSIZE 50  // ������ �Ŵ������� �̹���(��Ʈ)������
#define BOMBSIZE 100 // �����۸Ŵ�������  �����ҋ�(��Ʈ)������

class cSceneManager;
class cPlayer;



//==================================================================
//		## ���������� ���⿡�� �߰����� ## ��ȣ�����ϸ� �ٸ����� �̰� ��������
//==================================================================

enum EITEM  // �нú�����۴�����
{	
	�⺻�Ѿ� = 0,
	��ź,
	����,
	����,	
	�������, //����+1 ��Ʈ+1

	��Ȳ, // �⺻���� �ٲ�! (�̹����ٲ�) 
	���������Ǳ���, // ����ٴ����������� (�̹����ٲ�)

	�Ǹ��Ʊ�,//��� ���������� ���� �ڿ� ����ٴϸ鼭 �̻��Ͻ�鼭 �����ټ����ְ� �ٸ�ȿ�� �������ֵ� !! �ð������� ���鿹�� !!
	
};

enum EACTIVEITEM // �����̽��ٴ����������۵�
{
	����=100,
	�ڻ���������, // �����κп� �̻��ϻ��� �߻�Ǳ������� ���ذ���ġ���氡�� // �굵��������������
	�𷡽ð�, // ���ǿ����Ӱ� �߻�ü�� �������� Ȥ�� ���߰��ϴ°͵� ��������
};

enum EACTIVECARD // ī��±׳� �Ծ����� ���ȵ�� �����ϴ°ź����ֱ����� 1�������鿹��
{
	ī��=1000, // ��Ÿ�+2, ���ݷ�+2, �̵��ӵ�+2, ���ݼӵ�+2 
};



struct tag_Item
{
	RECT rc;
	float x;
	float y;
	float angle; // �����۵� ������ �Ф�
	float moveSpeed; // �����۵� ������ �Ф�	
	int state; // �̾������� �������� �� : state=��ź
	int currentmap; // ���� �����ʿ� �����Ǿ��ִ� ����������
	
	bool IsBomb=false;  // ��ź����ϴ°ŋ����� ���θ��� ���� 
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
		

public:

	void SetIM(cSceneManager* ssm) { _sm = ssm; }
	void SetPlayer(cPlayer* pplayer) { _player = pplayer; }

	void ItemMapSet(float _x, float _y, int _state, int _currentmap); // �ʸ���»���̾��ϴ�.
		
	void ItemUse(int _item,int _money=0); // �÷��̾�����ϴ�. �ʸ���»���� �������ֽ�.
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

