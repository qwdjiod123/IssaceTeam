#include "stdafx.h"
#include "cItemManager.h"
#include "cPlayer.h"
#include "cSceneManager.h"

HRESULT cItemManager::init(void)
{
	IsChange = false;
	return S_OK;
}

void cItemManager::release(void)
{


}

void cItemManager::update(void)
{
	/////////////////////////////////������ ��ü�ϴ� �� �ֱ����� �������� ���� ////////////////////////////////////
	if (IsChange == true)
	{
		int static nCount = 0;
		nCount++;
		if (nCount>100)
		{
			IsChange = false;
			nCount = 0;
		}
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	ItemUpdate(��11);
	ItemUpdate(��12);

	NewItemUpdate(��11);
	NewItemUpdate(��12);



	///�׽�Ʈ�Դϴ�.
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		_player->SetHp(_player->GetHp() - 1);
	}

}

void cItemManager::render(void)
{
	ItemRender(��11);
	ItemRender(��12);

	NewItemRender(��11);
	NewItemRender(��12);

	//�׽�Ʈ�Դϴ�.
	wsprintf(buffer, TEXT("HP:%d"), _player->GetHp());
	TextOut(getMemDC(), 400, 200, buffer, lstrlen(buffer));

	wsprintf(buffer, TEXT("SPACE:%d"), _player->GetSpace());
	TextOut(getMemDC(), 400, 230, buffer, lstrlen(buffer));

}



void cItemManager::ItemMapSet(float _x, float _y, int _state, int _currentmap)
{
	tag_Item item;
	item.IsBomb = false;
	item.moveSpeed = 0.0f;
	item.x = _x;
	item.y = _y;
	item.state = _state;
	item.currentmap = _currentmap;
	item.rc = RectMakeCenter(item.x, item.y, ITEMSIZE, ITEMSIZE);
	vItem.push_back(item);
}

void cItemManager::ItemUse(int _item)
{
	if (_item == ��ź)
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
	if (_item == �ڻ���������)
	{

	}
	if (_item == �𷡽ð�)
	{

	}
	if (_item == ī��)
	{

	}


}

void cItemManager::ItemMake(float _x, float _y, int _state, int _currentmap, bool _IsMove)
{
	tag_Item item;
	item.IsBomb = false;
	item.IsMove = _IsMove;
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
				//////////////////////////////////////////////////////////////////////
				//��Ʈ�� ���� Ǯ�϶� �ȸ԰��ϱ����� ������					
				if (vItem[i].IsBomb == false)
				{
					if (vItem[i].moveSpeed>0.0f)
					{
						vItem[i].moveSpeed -= 0.1f;
						vItem[i].x += cosf(vItem[i].angle)*vItem[i].moveSpeed;
						vItem[i].y += -sinf(vItem[i].angle)*vItem[i].moveSpeed;
						vItem[i].rc = RectMakeCenter(vItem[i].x, vItem[i].y, ITEMSIZE, ITEMSIZE);
					}
				}
				//////////////////////////////////////////////////////////////////////
				if (IntersectRect(&temp, &_player->GetRC(), &vItem[i].rc))
				{
					if (vItem[i].state == ��������)
					{
						ItemMake(vItem[i].x, vItem[i].y, ������Ʈ��, vItem[i].currentmap, true);
						IsChange = true;
						DeleteItem(i);
						break;
					}
					if (vItem[i].state == ����)
					{
						_player->SetKey(_player->GetKey() + 1);
						DeleteItem(i);
						break;
					}
					if (vItem[i].state == ��ź)
					{
						_player->SetBomb(_player->GetBomb() + 1);
						DeleteItem(i);
						break;
					}
					if (vItem[i].state == ������Ʈ��)
					{
						if (_player->GetHp() + 1>_player->GetmaxHp())
						{
							float distance = getDistance(vItem[i].x, vItem[i].y, _player->GetX(), _player->GetY());
							if (distance<75)
							{
								vItem[i].angle = getAngle(_player->GetX(), _player->GetY(), vItem[i].x, vItem[i].y);
								vItem[i].moveSpeed = ITEMMOVETIME;
							}
						}
						else if (_player->GetHp() + 1 <= _player->GetmaxHp())
						{
							_player->SetHp(_player->GetHp() + 1);
							DeleteItem(i);
							break;
						}
					}
					if (vItem[i].state == ������Ʈ)
					{
						if (_player->GetHp() + 2>_player->GetmaxHp())
						{
							float distance = getDistance(vItem[i].x, vItem[i].y, _player->GetX(), _player->GetY());
							if (distance<75)
							{
								vItem[i].angle = getAngle(_player->GetX(), _player->GetY(), vItem[i].x, vItem[i].y);
								vItem[i].moveSpeed = ITEMMOVETIME;
							}
						}
						else if (_player->GetHp() + 2 <= _player->GetmaxHp())
						{
							_player->SetHp(_player->GetHp() + 2);
							DeleteItem(i);
							break;
						}
					}
					if (vItem[i].state == ����1)
					{
						if (_player->GetMoney() == 99)
						{
							float distance = getDistance(vItem[i].x, vItem[i].y, _player->GetX(), _player->GetY());
							if (distance<75)
							{
								vItem[i].angle = getAngle(_player->GetX(), _player->GetY(), vItem[i].x, vItem[i].y);
								vItem[i].moveSpeed = ITEMMOVETIME;
							}
						}
						if (_player->GetMoney()<99)
						{
							_player->SetMoney(_player->GetMoney() + 1);
							DeleteItem(i);
							break;
						}
					}
					if (vItem[i].state == ����99)
					{
						_player->SetMoney(99);
						DeleteItem(i);
						break;
					}
					if (vItem[i].state == �������)
					{
						_player->SetmaxHp(_player->GetmaxHp() + 2);
						_player->SetHp(_player->GetHp() + 2);
						_player->addInVentory(�������);
						DeleteItem(i);
						break;
					}
					if (vItem[i].state == �˾�)
					{
						//�÷��̾� ��Ÿ� ����� �ӵ� ����
					}
					if (vItem[i].state == ��Ȳ)
					{
						_player->SetArrow(��Ȳ);
						_player->addInVentory(��Ȳ);
						DeleteItem(i);
						break;
					}
					if (vItem[i].state == ���������Ǳ���)
					{
						_player->addInVentory(���������Ǳ���);
						DeleteItem(i);
						break;
					}
					if (vItem[i].state == �ڻ���������&&IsChange == false)
					{
						if (_player->GetSpace() == ����)
						{

						}
						else
						{
							ItemMake(vItem[i].x, vItem[i].y, �𷡽ð�, _currentmap, false);
						}
						IsChange = true;
						_player->SetSpace(�ڻ���������);
						DeleteItem(i);
						break;
					}
					if (vItem[i].state == �𷡽ð�&&IsChange == false)
					{
						if (_player->GetSpace() == ����)
						{

						}
						else
						{
							ItemMake(vItem[i].x, vItem[i].y, �ڻ���������, _currentmap, false);
						}
						IsChange = true;
						_player->SetSpace(�𷡽ð�);
						DeleteItem(i);
						break;
					}
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
				//==================================================================
				//		## �����ۿ����̴·��� ## �������� Ƣ����¾ֵ�
				//==================================================================	
				if (vNewItem[i].IsBomb == false && vNewItem[i].IsMove == true)
				{
					if (vNewItem[i].moveSpeed>0.0f)
					{
						vNewItem[i].moveSpeed -= 0.1f;
						vNewItem[i].x += cosf(vNewItem[i].angle)*vNewItem[i].moveSpeed;
						vNewItem[i].y += -sinf(vNewItem[i].angle)*vNewItem[i].moveSpeed;
						vNewItem[i].rc = RectMakeCenter(vNewItem[i].x, vNewItem[i].y, ITEMSIZE, ITEMSIZE);
					}
				}

				if (IntersectRect(&temp, &_player->GetRC(), &vNewItem[i].rc))
				{
					if (vNewItem[i].state == ����&&IsChange == false)
					{
						_player->SetKey(_player->GetKey() + 1);
						DeleteNewItem(i);
						break;
					}
					if (vNewItem[i].state == ������Ʈ��&&IsChange == false)
					{
						if (_player->GetHp() + 1>_player->GetmaxHp())
						{
							float distance = getDistance(vNewItem[i].x, vNewItem[i].y, _player->GetX(), _player->GetY());
							if (distance<75)
							{
								vNewItem[i].angle = getAngle(_player->GetX(), _player->GetY(), vNewItem[i].x, vNewItem[i].y);
								vNewItem[i].moveSpeed = ITEMMOVETIME;
							}
						}
						else if (_player->GetHp() + 1 <= _player->GetmaxHp())
						{
							_player->SetHp(_player->GetHp() + 1);
							DeleteNewItem(i);
							break;
						}
					}
					if (vNewItem[i].state == ������Ʈ&&IsChange == false)
					{
						if (_player->GetHp() + 2>_player->GetmaxHp())
						{
							float distance = getDistance(vNewItem[i].x, vNewItem[i].y, _player->GetX(), _player->GetY());
							if (distance<75)
							{
								vNewItem[i].angle = getAngle(_player->GetX(), _player->GetY(), vNewItem[i].x, vNewItem[i].y);
								vNewItem[i].moveSpeed = ITEMMOVETIME;
							}
						}
						else if (_player->GetHp() + 2 <= _player->GetmaxHp())
						{
							_player->SetHp(_player->GetHp() + 2);
							DeleteNewItem(i);
							break;
						}
					}
					if (vNewItem[i].state == ����1&&IsChange == false)
					{
						_player->SetMoney(_player->GetMoney() + 1);
						DeleteNewItem(i);
						break;
					}
					if (vNewItem[i].state == ����99&&IsChange == false)
					{
						_player->SetMoney(99);
						DeleteNewItem(i);
						break;
					}
					if (vNewItem[i].state == �ڻ���������&&IsChange == false)
					{
						if (_player->GetSpace() == ����)
						{

						}
						else
						{
							ItemMake(vNewItem[i].x, vNewItem[i].y, �𷡽ð�, _currentmap, false);
						}
						IsChange = true;
						_player->SetSpace(�ڻ���������);
						DeleteNewItem(i);
						break;
					}
					if (vNewItem[i].state == �𷡽ð�&&IsChange == false)
					{
						if (_player->GetSpace() == ����)
						{

						}
						else
						{
							ItemMake(vNewItem[i].x, vNewItem[i].y, �ڻ���������, _currentmap, false);
						}
						IsChange = true;
						_player->SetSpace(�𷡽ð�);
						DeleteNewItem(i);
						break;
					}
					if (vNewItem[i].state == ��ź&&vNewItem[i].IsBomb == false && IsChange == false)
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
	SetTextColor(getMemDC(), RGB(0, 0, 0));
	if (_sm->GetCurrentMap() == _currentmap)
	{
		for (int i = 0; i < vItem.size(); i++)
		{
			if (vItem[i].currentmap == _currentmap)
			{
				if (vItem[i].state == ����)
				{
					//IMAGEMANAGER->render("����", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 50, 50);
					RectangleMake(getMemDC(), vItem[i].rc);
					TextOut(getMemDC(), vItem[i].rc.left, vItem[i].rc.top, TEXT("����"), lstrlen(TEXT("����")));
				}
				if (vItem[i].state == ��ź)
				{
					IMAGEMANAGER->render("��ź", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 50, 50);
				}
				if (vItem[i].state == ������Ʈ��)
				{
					//IMAGEMANAGER->render("����", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 50, 50);
					RectangleMake(getMemDC(), vItem[i].rc);
					TextOut(getMemDC(), vItem[i].rc.left, vItem[i].rc.top, TEXT("������Ʈ��"), lstrlen(TEXT("������Ʈ��")));
				}
				if (vItem[i].state == ������Ʈ)
				{
					//IMAGEMANAGER->render("����", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 50, 50);
					RectangleMake(getMemDC(), vItem[i].rc);
					TextOut(getMemDC(), vItem[i].rc.left, vItem[i].rc.top, TEXT("������Ʈ"), lstrlen(TEXT("������Ʈ")));
				}
				if (vItem[i].state == ����1)
				{
					RectangleMake(getMemDC(), vItem[i].rc);
					TextOut(getMemDC(), vItem[i].rc.left, vItem[i].rc.top, TEXT("����1"), lstrlen(TEXT("����1")));
					//IMAGEMANAGER->render("����1", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 50, 50);
				}
				if (vItem[i].state == ����99)
				{
					RectangleMake(getMemDC(), vItem[i].rc);
					TextOut(getMemDC(), vItem[i].rc.left, vItem[i].rc.top, TEXT("����99"), lstrlen(TEXT("����99")));
					//IMAGEMANAGER->render("����1", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 50, 50);
				}
				if (vItem[i].state == ��Ȳ)
				{
					RectangleMake(getMemDC(), vItem[i].rc);
					TextOut(getMemDC(), vItem[i].rc.left, vItem[i].rc.top, TEXT("��Ȳ"), lstrlen(TEXT("��Ȳ")));
					//IMAGEMANAGER->render("����1", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 50, 50);
				}
				if (vItem[i].state == ���������Ǳ���)
				{
					RectangleMake(getMemDC(), vItem[i].rc);
					TextOut(getMemDC(), vItem[i].rc.left, vItem[i].rc.top, TEXT("���������Ǳ���"), lstrlen(TEXT("���������Ǳ���")));
					//IMAGEMANAGER->render("����1", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 50, 50);
				}
				if (vItem[i].state == �������)
				{
					RectangleMake(getMemDC(), vItem[i].rc);
					TextOut(getMemDC(), vItem[i].rc.left, vItem[i].rc.top, TEXT("�������"), lstrlen(TEXT("�������")));
					//IMAGEMANAGER->render("����1", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 50, 50);
				}
				if (vItem[i].state == �˾�)
				{
					RectangleMake(getMemDC(), vItem[i].rc);
					TextOut(getMemDC(), vItem[i].rc.left, vItem[i].rc.top, TEXT("�˾�"), lstrlen(TEXT("�˾�")));
					//IMAGEMANAGER->render("����1", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 50, 50);
				}
				if (vItem[i].state == �ڻ���������)
				{
					RectangleMake(getMemDC(), vItem[i].rc);
					TextOut(getMemDC(), vItem[i].rc.left, vItem[i].rc.top, TEXT("�ڻ���������"), lstrlen(TEXT("�ڻ���������")));
					//IMAGEMANAGER->render("����1", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 50, 50);
				}
				if (vItem[i].state == �𷡽ð�)
				{
					RectangleMake(getMemDC(), vItem[i].rc);
					TextOut(getMemDC(), vItem[i].rc.left, vItem[i].rc.top, TEXT("�𷡽ð�"), lstrlen(TEXT("�𷡽ð�")));
					//IMAGEMANAGER->render("����1", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 50, 50);
				}
				if (vItem[i].state == ��������)
				{
					RectangleMake(getMemDC(), vItem[i].rc);
					TextOut(getMemDC(), vItem[i].rc.left, vItem[i].rc.top, TEXT("��������"), lstrlen(TEXT("��������")));
					//IMAGEMANAGER->render("����1", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 50, 50);
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
				if (vNewItem[i].state == ��ź&&vNewItem[i].IsBomb == false)
				{
					RectangleMake(getMemDC(), vNewItem[i].rc);
					IMAGEMANAGER->render("��ź", getMemDC(), vNewItem[i].rc.left, vNewItem[i].rc.top, 0, 0, 50, 50);
				}
				if (vNewItem[i].state == ��ź&&vNewItem[i].IsBomb == true)
				{
					IMAGEMANAGER->render("��ź", getMemDC(), vNewItem[i].x, vNewItem[i].y, 0, 0, 50, 50);
					RectangleMake(getMemDC(), vNewItem[i].rc);
				}
				if (vNewItem[i].state == ������Ʈ��)
				{
					//IMAGEMANAGER->render("��ź", getMemDC(), vNewItem[i].x, vNewItem[i].y, 0, 0, 50, 50);
					RectangleMake(getMemDC(), vNewItem[i].rc);
					TextOut(getMemDC(), vNewItem[i].rc.left, vNewItem[i].rc.top, TEXT("������Ʈ��"), lstrlen(TEXT("������Ʈ��")));
				}
				if (vNewItem[i].state == ������Ʈ)
				{
					//IMAGEMANAGER->render("��ź", getMemDC(), vNewItem[i].x, vNewItem[i].y, 0, 0, 50, 50);
					RectangleMake(getMemDC(), vNewItem[i].rc);
					TextOut(getMemDC(), vNewItem[i].rc.left, vNewItem[i].rc.top, TEXT("������Ʈ"), lstrlen(TEXT("������Ʈ")));
				}
				if (vNewItem[i].state == ����1)
				{
					RectangleMake(getMemDC(), vNewItem[i].rc);
					TextOut(getMemDC(), vNewItem[i].rc.left, vNewItem[i].rc.top, TEXT("����1"), lstrlen(TEXT("����1")));
				}
				if (vNewItem[i].state == ����99)
				{
					RectangleMake(getMemDC(), vNewItem[i].rc);
					TextOut(getMemDC(), vNewItem[i].rc.left, vNewItem[i].rc.top, TEXT("����99"), lstrlen(TEXT("����99")));
				}
				if (vNewItem[i].state == �ڻ���������)
				{
					RectangleMake(getMemDC(), vNewItem[i].rc);
					TextOut(getMemDC(), vNewItem[i].rc.left, vNewItem[i].rc.top, TEXT("�ڻ���������"), lstrlen(TEXT("�ڻ���������")));
				}
				if (vNewItem[i].state == �𷡽ð�)
				{
					RectangleMake(getMemDC(), vNewItem[i].rc);
					TextOut(getMemDC(), vNewItem[i].rc.left, vNewItem[i].rc.top, TEXT("�𷡽ð�"), lstrlen(TEXT("�𷡽ð�")));
				}

			}

		}
	}
}


