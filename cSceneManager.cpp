#include "stdafx.h"
#include "cSceneManager.h"
#include"cPlayer.h"
#include"cItemManager.h"



HRESULT cSceneManager::init(void)
{

	currentMap = ¸Ê11;
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
	//»óÁ¡ Å×½ºÆ®Áß
	if (currentMap==¸Ê11)
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
				_im->ItemMake(WINSIZEX/2, WINSIZEY/2, ÆøÅº, ¸Ê11);
			}
		}
		
		
	}

	// ¸Ê¿¡¾ÆÀÌÅÛ ¼ÂÆÃ
	if (currentMap == ¸Ê11&&ItemSetting[¸Ê11] == false)
	{
		_im->ItemMapSet(200, 400, ÆøÅº, ¸Ê11);
		_im->ItemMapSet(400, 400, ÆøÅº, ¸Ê11);
		_im->ItemMapSet(600, 400, ÆøÅº, ¸Ê11);	
		ItemSetting[¸Ê11] = true;
	}

	if (currentMap == ¸Ê12&&ItemSetting[¸Ê12] == false)
	{
		_im->ItemMapSet(100, 100, ¿­¼è, ¸Ê12);
		_im->ItemMapSet(300, 100, ¿­¼è, ¸Ê12);
		_im->ItemMapSet(500, 100, ¿­¼è, ¸Ê12);
		ItemSetting[¸Ê12] = true;
	}

/////////////////////////////////////////////////////////////////ÀÓ½Ã·Î ·ºÆ®Ãæµ¹·ÎÇÔ ÇÈ¼¿Ãæµ¹·ÎÇØ¾ßÇÔ!
	if (currentMap==¸Ê11)
	{		
		 rc = RectMakeCenter(30, 250,50, 50);
		if (IntersectRect(&temp, &rc, &_player->GetRC()))
		{	
			_player->SetX(WINSIZEX-100);
			_player->SetY(WINSIZEY/2);
			currentMap = ¸Ê12;		
			return;
		}		
	}
	if (currentMap == ¸Ê12)
	{	
		rc = RectMakeCenter(WINSIZEX-20, 250, 50, 50);
		rc2 = RectMakeCenter(30, 250, 50, 50);
		if (IntersectRect(&temp, &rc, &_player->GetRC()))
		{
			_player->SetX(100);
			_player->SetY(WINSIZEY / 2);
			currentMap = ¸Ê11;			
		}
		if (IntersectRect(&temp, &rc2, &_player->GetRC()))
		{			
			_player->SetX(WINSIZEX-100);
			_player->SetY(WINSIZEY / 2);
			currentMap = ¸Ê13;
		}
		return;
	}

	if (currentMap == ¸Ê13)
	{
		rc = RectMakeCenter(WINSIZEX - 20, 250, 50, 50);
		if (IntersectRect(&temp, &rc, &_player->GetRC()))
		{
			_player->SetX(100);
			_player->SetY(WINSIZEY / 2);
			currentMap = ¸Ê12;
		}
		return;
	}

}

void cSceneManager::render(void)
{
		if (currentMap==¸Ê11)
		{
			IMAGEMANAGER->render("map1", getMemDC());
		}
		if (currentMap == ¸Ê12)
		{
			IMAGEMANAGER->render("map2", getMemDC());
		}
		if (currentMap == ¸Ê13)
		{
			IMAGEMANAGER->render("map3", getMemDC());
		}
			
		RectangleMake(getMemDC(), rc);
		RectangleMake(getMemDC(), rc2);
		RectangleMake(getMemDC(), store);
}
