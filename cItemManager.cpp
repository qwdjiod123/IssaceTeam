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
	
	if (_item ==��ź)
	{
		_player->SetBomb(_player->GetBomb() - 1);
		tag_Item item;
		item.x = _player->GetX();
		item.y = _player->GetY();
		item.IsBomb = true;		
		item.state = ��ź;
		item.currentmap = _sm->GetCurrentMap();
		//item.rc = RectMakeCenter(10, 10, 100, 100); // ��ź�� ������ ��Ʈ������ update()����ó����
		vNewItem.push_back(item);
	}
	if (_item ==����)
	{
		_player->SetKey(_player->GetKey() - 1);
	}
	if (_item ==����)
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
						vNewItem[i].contdown++;  // �����ϱ� 100����						
						if (100<vNewItem[i].contdown&& vNewItem[i].contdown<120) // ���� 20�ʵ���
						{
							vNewItem[i].rc = RectMakeCenter(vNewItem[i].x, vNewItem[i].y, BOMBSIZE, BOMBSIZE);
						}
						if (vNewItem[i].contdown>120)
						{
							vNewItem[i].contdown = 0; // ��� �����൵�Ǵµ� �����ؼ� �׳���
							DeleteNewItem(i);   // ������ ����
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
					RectangleMake(getMemDC(), vNewItem[i].rc);
					IMAGEMANAGER->render("����", getMemDC(), vNewItem[i].rc.left, vNewItem[i].rc.top, 0, 0, 50, 50);
				}
				if (vNewItem[i].state == ��ź&&vNewItem[i].IsBomb==false)
				{
					RectangleMake(getMemDC(), vNewItem[i].rc);
					IMAGEMANAGER->render("��ź", getMemDC(), vNewItem[i].rc.left, vNewItem[i].rc.top, 0, 0, 50, 50);
				}
				if (vNewItem[i].state == ��ź&&vNewItem[i].IsBomb == true)
				{					
					IMAGEMANAGER->render("��ź", getMemDC(), vNewItem[i].x, vNewItem[i].y, 0, 0, 50, 50);
					RectangleMake(getMemDC(), vNewItem[i].rc);
				}
			}
			
		}		
	}	
}


