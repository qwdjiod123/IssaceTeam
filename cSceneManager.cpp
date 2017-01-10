#include "stdafx.h"
#include "cSceneManager.h"
#include"cPlayer.h"
#include"cItemManager.h"



HRESULT cSceneManager::init(void)
{

	currentMap = ��11;
	_player->SetX(WINSIZEX / 2);
	_player->SetY(WINSIZEY / 2);

	for (int i = 0; i < MAPMAX; i++)
	{
		ItemSetting[i] = false;

	}				

	return S_OK;
}

void cSceneManager::release(void)
{
}

void cSceneManager::update(void)
{	
	//���� �׽�Ʈ��
	if (currentMap==��11)
	{
		store = RectMakeCenter(100, 100, 100, 100);
		int static nCount = 0;
		nCount++;
		if (nCount>1000)
		{
			nCount = 0;
		}
		if (nCount%50==0)
		{
			if (IntersectRect(&temp, &_player->GetRC(), &store))
			{
				_im->ItemMake(WINSIZEX/2, WINSIZEY/2, ��ź, ��11);
			}
		}
		
		
	}

	// �ʿ������� ����
	if (currentMap == ��11&&ItemSetting[��11] == false)
	{
		_im->ItemMapSet(200, 400, ��ź, ��11);
		_im->ItemMapSet(400, 400, ��ź, ��11);
		_im->ItemMapSet(600, 400, ��ź, ��11);	
		ItemSetting[��11] = true;
	}

	if (currentMap == ��12&&ItemSetting[��12] == false)
	{
		_im->ItemMapSet(100, 100, ����, ��12);
		_im->ItemMapSet(300, 100, ����, ��12);
		_im->ItemMapSet(500, 100, ����, ��12);
		ItemSetting[��12] = true;
	}

/////////////////////////////////////////////////////////////////�ӽ÷� ��Ʈ�浹���� �ȼ��浹���ؾ���!
	if (currentMap==��11)
	{		
		 rc = RectMakeCenter(30, 250,50, 50);
		if (IntersectRect(&temp, &rc, &_player->GetRC()))
		{	
			_player->SetX(WINSIZEX-100);
			_player->SetY(WINSIZEY/2);
			currentMap = ��12;		
			return;
		}		
	}
	if (currentMap == ��12)
	{	
		rc = RectMakeCenter(WINSIZEX-20, 250, 50, 50);
		rc2 = RectMakeCenter(30, 250, 50, 50);
		if (IntersectRect(&temp, &rc, &_player->GetRC()))
		{
			_player->SetX(100);
			_player->SetY(WINSIZEY / 2);
			currentMap = ��11;			
		}
		if (IntersectRect(&temp, &rc2, &_player->GetRC()))
		{			
			_player->SetX(WINSIZEX-100);
			_player->SetY(WINSIZEY / 2);
			currentMap = ��13;
		}
		return;
	}

	if (currentMap == ��13)
	{
		rc = RectMakeCenter(WINSIZEX - 20, 250, 50, 50);
		if (IntersectRect(&temp, &rc, &_player->GetRC()))
		{
			_player->SetX(100);
			_player->SetY(WINSIZEY / 2);
			currentMap = ��12;
		}
		return;
	}

}

void cSceneManager::render(void)
{
		if (currentMap==��11)
		{
			IMAGEMANAGER->render("map1", getMemDC());
		}
		if (currentMap == ��12)
		{
			IMAGEMANAGER->render("map2", getMemDC());
		}
		if (currentMap == ��13)
		{
			IMAGEMANAGER->render("map3", getMemDC());
		}
			
		RectangleMake(getMemDC(), rc);
		RectangleMake(getMemDC(), rc2);
		RectangleMake(getMemDC(), store);
}
