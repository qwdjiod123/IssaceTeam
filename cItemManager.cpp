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
	ItemUpdate(��11);
	ItemUpdate(��12);

	NewItemUpdate(��11);
	NewItemUpdate(��12);
}

void cItemManager::render(void)
{	
	ItemRender(��11);
	ItemRender(��12);

	NewItemRender(��11);
	NewItemRender(��12);		


	RectangleMake(getMemDC(), test);
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

void cItemManager::ItemUse(int itemNumber, int money)
{
	
	if (itemNumber==��ź)
	{
		_player->SetBomb(_player->GetBomb() - 1);
		tag_Item item;
		item.x = _player->GetX();
		item.y = _player->GetY();
		item.IsBomb = true;		
		item.state = ��ź;
		item.currentmap = _sm->GetCurrentMap();
		item.rc = RectMakeCenter(10, 10, 100, 100); // ��ź�� ������ ��Ʈ������ update()����ó����
		vNewItem.push_back(item);
	}
	if (itemNumber==����)
	{
		_player->SetKey(_player->GetKey() - 1);
	}
	if (itemNumber==����)
	{
		_player->SetMoney(_player->GetMoney() - money);
	}

}

void cItemManager::ItemMake(float _x, float _y, int _state, int _currentmap)
{
	tag_Item item;
	item.IsBomb = false;	
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
						if (vItem[i].state == ����)
						{
							_player->SetKey(_player->GetKey() + 1);
						}
						if (vItem[i].state == ��ź)
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
					if (IntersectRect(&temp,&_player->GetRC(),&vNewItem[i].rc))
					{
						if (vNewItem[i].state == ����)
						{
							_player->SetKey(_player->GetKey() + 1);
							DeleteNewItem(i);
						}
						if (vNewItem[i].state == ��ź&&vNewItem[i].IsBomb == false)
						{
							_player->SetBomb(_player->GetBomb() + 1);
							DeleteNewItem(i);
							break;
						}
					}
					
					if (vNewItem[i].state == ��ź&&vNewItem[i].IsBomb == true)
					{
						//cout << vNewItem[i].contdown << endl;
						vNewItem[i].contdown++;
						if (vNewItem[i].contdown>100)
						{
							//test = RectMakeCenter(vNewItem[i].x, vNewItem[i].y, BOMBSIZE, BOMBSIZE);
							vNewItem[i].rc = RectMakeCenter(vNewItem[i].x, vNewItem[i].y, BOMBSIZE, BOMBSIZE);	
							//cout << vNewItem[i].x << endl;
							
							vNewItem[i].contdown = 0;
							//DeleteNewItem(i);
							break;
						}
						//cout << nCount << endl;
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
				if (vItem[i].state == ����)
				{
					IMAGEMANAGER->render("����", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 50, 50);
				}
				if (vItem[i].state == ��ź)
				{
					IMAGEMANAGER->render("��ź", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 50, 50);
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
				if (vNewItem[i].state == ����)
				{
					IMAGEMANAGER->render("����", getMemDC(), _player->GetX(), _player->GetY(), 0, 0, 50, 50);
				}
				if (vNewItem[i].state == ��ź)
				{
					IMAGEMANAGER->render("��ź", getMemDC(), vNewItem[i].x, vNewItem[i].y, 0, 0, 50, 50);
				}
				
							
			}
			RectangleMake(getMemDC(), vNewItem[i].rc);			
		}		
	}	
}


