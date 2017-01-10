#include "stdafx.h"
#include "cItemManager.h"
#include "cPlayer.h"
#include "cSceneManager.h"

HRESULT cItemManager::init(void)
{	
	return S_OK;
}

void cItemManager::release(void)
{


}

void cItemManager::update(void)
{
	ItemUpdate(¸Ê11);
	ItemUpdate(¸Ê12);

	NewItemUpdate(¸Ê11);
	NewItemUpdate(¸Ê12);
}

void cItemManager::render(void)
{	
	ItemRender(¸Ê11);
	ItemRender(¸Ê12);

	NewItemRender(¸Ê11);
	NewItemRender(¸Ê12);

}



void cItemManager::ItemMapSet(float _x, float _y, int _state, int _currentmap)
{
	tag_Item item;
	item.IsBomb = false;	
	item.x = _x;
	item.y = _y;
	item.state = _state;
	item.currentmap = _currentmap;
	item.rc = RectMakeCenter(item.x, item.y, ITEMSIZE, ITEMSIZE);
	vItem.push_back(item);
}

void cItemManager::ItemUse(int _item, int money)
{
	
	if (_item ==ÆøÅº)
	{
		_player->SetBomb(_player->GetBomb() - 1);
		tag_Item item;
		item.x = _player->GetX();
		item.y = _player->GetY();
		item.IsBomb = true;		
		item.state = ÆøÅº;
		item.currentmap = _sm->GetCurrentMap();
		//item.rc = RectMakeCenter(10, 10, 100, 100); // ÆøÅºÀÌ ÅÍÁú¶§ ·¢Æ®»ý¼ºÇÔ update()¿¡¼­Ã³¸®ÇÔ
		vNewItem.push_back(item);
	}
	if (_item ==¿­¼è)
	{
		_player->SetKey(_player->GetKey() - 1);
	}
	if (_item ==µ¿Àü)
	{
		_player->SetMoney(_player->GetMoney() - money);
	}

}

void cItemManager::ItemMake(float _x, float _y, int _state, int _currentmap)
{
	tag_Item item;
	item.IsBomb = false;
	
	item.moveSpeed = 5.0f;
	item.angle = RND->getFromFloatTo(0, 2 * PI);
	item.x = _x;
	item.y = _y;
	item.state = _state;
	item.currentmap = _currentmap;
	item.rc = RectMakeCenter(item.x, item.y, ITEMSIZE, ITEMSIZE);
	vNewItem.push_back(item);
}

void cItemManager::DeleteItem(int index)
{

	for (int i = 0; i < vItem.size(); i++)
	{
		vItem.erase(vItem.begin() + index);
		break;
	}
}

void cItemManager::DeleteNewItem(int index)
{
	for (int i = 0; i < vNewItem.size(); i++)
	{
		vNewItem.erase(vNewItem.begin() + index);
		break;
	}
}

void cItemManager::ItemUpdate(int _currentmap)
{	
		if (_sm->GetCurrentMap() == _currentmap)
		{
			for (int i = 0; i < vItem.size(); i++)
			{
				if (vItem[i].currentmap == _currentmap)
				{
					if (IntersectRect(&temp, &_player->GetRC(), &vItem[i].rc))
					{
						if (vItem[i].state == ¿­¼è)
						{
							_player->SetKey(_player->GetKey() + 1);
						}
						if (vItem[i].state == ÆøÅº)
						{
							_player->SetBomb(_player->GetBomb() + 1);
						}
						DeleteItem(i);
						break;
					}
				}
			}		
		}
}

void cItemManager::NewItemUpdate(int _currentmap)
{
	
		if (_sm->GetCurrentMap() == _currentmap)
		{
			for (int i = 0; i < vNewItem.size(); i++)
			{
				if (vNewItem[i].currentmap == _currentmap)
				{
						
					if (vNewItem[i].IsBomb==false)
					{
						if (vNewItem[i].moveSpeed>0.0f)
						{
							vNewItem[i].moveSpeed -= 0.1f;
							vNewItem[i].x += cosf(vNewItem[i].angle)*vNewItem[i].moveSpeed;
							vNewItem[i].y += -sinf(vNewItem[i].angle)*vNewItem[i].moveSpeed;
							vNewItem[i].rc = RectMakeCenter(vNewItem[i].x, vNewItem[i].y, ITEMSIZE, ITEMSIZE);
						}
					}

					if (IntersectRect(&temp,&_player->GetRC(),&vNewItem[i].rc))
					{
						if (vNewItem[i].state == ¿­¼è)
						{
							_player->SetKey(_player->GetKey() + 1);
							DeleteNewItem(i);
						}
						if (vNewItem[i].state == ÆøÅº&&vNewItem[i].IsBomb == false)
						{
							_player->SetBomb(_player->GetBomb() + 1);
							DeleteNewItem(i);
							break;
						}
					}
					
					if (vNewItem[i].state == ÆøÅº&&vNewItem[i].IsBomb == true)
					{						
						vNewItem[i].contdown++;  // Æø¹ßÇÏ±â 100ÃÊÀü						
						if (100<vNewItem[i].contdown&& vNewItem[i].contdown<120) // Æø¹ß 20ÃÊµ¿¾È
						{
							vNewItem[i].rc = RectMakeCenter(vNewItem[i].x, vNewItem[i].y, BOMBSIZE, BOMBSIZE);
						}
						if (vNewItem[i].contdown>120)
						{
							vNewItem[i].contdown = 0; // ¾ê´Â ¾ÈÇØÁàµµµÇ´Âµ¥ ÂòÂòÇØ¼­ ±×³ÉÇÔ
							DeleteNewItem(i);   // Æø¹ßÈÄ »èÁ¦
							break;
						}
					}
				}
			}			
		}

}

void cItemManager::ItemRender(int _currentmap)
{
	if (_sm->GetCurrentMap() == _currentmap)
	{
		for (int i = 0; i < vItem.size(); i++) 
		{
			if (vItem[i].currentmap == _currentmap)
			{
				if (vItem[i].state == ¿­¼è)
				{
					IMAGEMANAGER->render("¿­¼è", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 50, 50);
				}
				if (vItem[i].state == ÆøÅº)
				{
					IMAGEMANAGER->render("ÆøÅº", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 50, 50);
				}
				//RectangleMake(getMemDC(), vItem[i].rc);
			}
		}		
	}
}

void cItemManager::NewItemRender(int _currentmap)
{
	if (_sm->GetCurrentMap() == _currentmap)
	{
		for (int i = 0; i < vNewItem.size(); i++)
		{
			if (vNewItem[i].currentmap == _currentmap)
			{
				if (vNewItem[i].state == ¿­¼è)
				{
					RectangleMake(getMemDC(), vNewItem[i].rc);
					IMAGEMANAGER->render("¿­¼è", getMemDC(), vNewItem[i].rc.left, vNewItem[i].rc.top, 0, 0, 50, 50);
				}
				if (vNewItem[i].state == ÆøÅº&&vNewItem[i].IsBomb==false)
				{
					RectangleMake(getMemDC(), vNewItem[i].rc);
					IMAGEMANAGER->render("ÆøÅº", getMemDC(), vNewItem[i].rc.left, vNewItem[i].rc.top, 0, 0, 50, 50);
				}
				if (vNewItem[i].state == ÆøÅº&&vNewItem[i].IsBomb == true)
				{					
					IMAGEMANAGER->render("ÆøÅº", getMemDC(), vNewItem[i].x, vNewItem[i].y, 0, 0, 50, 50);
					RectangleMake(getMemDC(), vNewItem[i].rc);
				}
			}
			
		}		
	}	
}


