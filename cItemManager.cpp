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
	/////////////////////////////////아이템 교체하는 텀 주기위해 만들어놓은 로직 ////////////////////////////////////
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

	ItemUpdate(맵11);
	ItemUpdate(맵12);

	NewItemUpdate(맵11);
	NewItemUpdate(맵12);



	///테스트입니다.
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		_player->SetHp(_player->GetHp() - 1);
	}

}

void cItemManager::render(void)
{
	ItemRender(맵11);
	ItemRender(맵12);

	NewItemRender(맵11);
	NewItemRender(맵12);

	//테스트입니다.
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
	if (_item == 폭탄)
	{
		_player->SetBomb(_player->GetBomb() - 1);
		tag_Item item;
		item.x = _player->GetX();
		item.y = _player->GetY();
		item.IsBomb = true;
		item.state = 폭탄;
		item.currentmap = _sm->GetCurrentMap();
		//item.rc = RectMakeCenter(10, 10, 100, 100); // 폭탄이 터질때 랙트생성함 update()에서처리함
		vNewItem.push_back(item);
	}
	if (_item == 박사의조정기)
	{

	}
	if (_item == 모래시계)
	{

	}
	if (_item == 카드)
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
				//하트나 돈이 풀일때 안먹게하기위한 움직임					
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
					if (vItem[i].state == 보물상자)
					{
						ItemMake(vItem[i].x, vItem[i].y, 빨간하트반, vItem[i].currentmap, true);
						IsChange = true;
						DeleteItem(i);
						break;
					}
					if (vItem[i].state == 열쇠)
					{
						_player->SetKey(_player->GetKey() + 1);
						DeleteItem(i);
						break;
					}
					if (vItem[i].state == 폭탄)
					{
						_player->SetBomb(_player->GetBomb() + 1);
						DeleteItem(i);
						break;
					}
					if (vItem[i].state == 빨간하트반)
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
					if (vItem[i].state == 빨간하트)
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
					if (vItem[i].state == 동전1)
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
					if (vItem[i].state == 동전99)
					{
						_player->SetMoney(99);
						DeleteItem(i);
						break;
					}
					if (vItem[i].state == 썩은고기)
					{
						_player->SetmaxHp(_player->GetmaxHp() + 2);
						_player->SetHp(_player->GetHp() + 2);
						_player->addInVentory(썩은고기);
						DeleteItem(i);
						break;
					}
					if (vItem[i].state == 알약)
					{
						//플레이어 사거리 대미지 속도 증가
					}
					if (vItem[i].state == 유황)
					{
						_player->SetArrow(유황);
						_player->addInVentory(유황);
						DeleteItem(i);
						break;
					}
					if (vItem[i].state == 구렁텅이의군주)
					{
						_player->addInVentory(구렁텅이의군주);
						DeleteItem(i);
						break;
					}
					if (vItem[i].state == 박사의조정기&&IsChange == false)
					{
						if (_player->GetSpace() == 없음)
						{

						}
						else
						{
							ItemMake(vItem[i].x, vItem[i].y, 모래시계, _currentmap, false);
						}
						IsChange = true;
						_player->SetSpace(박사의조정기);
						DeleteItem(i);
						break;
					}
					if (vItem[i].state == 모래시계&&IsChange == false)
					{
						if (_player->GetSpace() == 없음)
						{

						}
						else
						{
							ItemMake(vItem[i].x, vItem[i].y, 박사의조정기, _currentmap, false);
						}
						IsChange = true;
						_player->SetSpace(모래시계);
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
				//		## 아이템움직이는로직 ## 상점에서 튀어나오는애들
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
					if (vNewItem[i].state == 열쇠&&IsChange == false)
					{
						_player->SetKey(_player->GetKey() + 1);
						DeleteNewItem(i);
						break;
					}
					if (vNewItem[i].state == 빨간하트반&&IsChange == false)
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
					if (vNewItem[i].state == 빨간하트&&IsChange == false)
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
					if (vNewItem[i].state == 동전1&&IsChange == false)
					{
						_player->SetMoney(_player->GetMoney() + 1);
						DeleteNewItem(i);
						break;
					}
					if (vNewItem[i].state == 동전99&&IsChange == false)
					{
						_player->SetMoney(99);
						DeleteNewItem(i);
						break;
					}
					if (vNewItem[i].state == 박사의조정기&&IsChange == false)
					{
						if (_player->GetSpace() == 없음)
						{

						}
						else
						{
							ItemMake(vNewItem[i].x, vNewItem[i].y, 모래시계, _currentmap, false);
						}
						IsChange = true;
						_player->SetSpace(박사의조정기);
						DeleteNewItem(i);
						break;
					}
					if (vNewItem[i].state == 모래시계&&IsChange == false)
					{
						if (_player->GetSpace() == 없음)
						{

						}
						else
						{
							ItemMake(vNewItem[i].x, vNewItem[i].y, 박사의조정기, _currentmap, false);
						}
						IsChange = true;
						_player->SetSpace(모래시계);
						DeleteNewItem(i);
						break;
					}
					if (vNewItem[i].state == 폭탄&&vNewItem[i].IsBomb == false && IsChange == false)
					{
						_player->SetBomb(_player->GetBomb() + 1);
						DeleteNewItem(i);
						break;
					}
				}

				if (vNewItem[i].state == 폭탄&&vNewItem[i].IsBomb == true)
				{
					vNewItem[i].contdown++;  // 폭발하기 100초전						
					if (100<vNewItem[i].contdown&& vNewItem[i].contdown<120) // 폭발 20초동안
					{
						vNewItem[i].rc = RectMakeCenter(vNewItem[i].x, vNewItem[i].y, BOMBSIZE, BOMBSIZE);
					}
					if (vNewItem[i].contdown>120)
					{
						vNewItem[i].contdown = 0; // 얘는 안해줘도되는데 찜찜해서 그냥함
						DeleteNewItem(i);   // 폭발후 삭제
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
				if (vItem[i].state == 열쇠)
				{
					//IMAGEMANAGER->render("열쇠", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 50, 50);
					RectangleMake(getMemDC(), vItem[i].rc);
					TextOut(getMemDC(), vItem[i].rc.left, vItem[i].rc.top, TEXT("열쇠"), lstrlen(TEXT("열쇠")));
				}
				if (vItem[i].state == 폭탄)
				{
					IMAGEMANAGER->render("폭탄", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 50, 50);
				}
				if (vItem[i].state == 빨간하트반)
				{
					//IMAGEMANAGER->render("열쇠", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 50, 50);
					RectangleMake(getMemDC(), vItem[i].rc);
					TextOut(getMemDC(), vItem[i].rc.left, vItem[i].rc.top, TEXT("빨간하트반"), lstrlen(TEXT("빨간하트반")));
				}
				if (vItem[i].state == 빨간하트)
				{
					//IMAGEMANAGER->render("열쇠", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 50, 50);
					RectangleMake(getMemDC(), vItem[i].rc);
					TextOut(getMemDC(), vItem[i].rc.left, vItem[i].rc.top, TEXT("빨간하트"), lstrlen(TEXT("빨간하트")));
				}
				if (vItem[i].state == 동전1)
				{
					RectangleMake(getMemDC(), vItem[i].rc);
					TextOut(getMemDC(), vItem[i].rc.left, vItem[i].rc.top, TEXT("동전1"), lstrlen(TEXT("동전1")));
					//IMAGEMANAGER->render("동전1", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 50, 50);
				}
				if (vItem[i].state == 동전99)
				{
					RectangleMake(getMemDC(), vItem[i].rc);
					TextOut(getMemDC(), vItem[i].rc.left, vItem[i].rc.top, TEXT("동전99"), lstrlen(TEXT("동전99")));
					//IMAGEMANAGER->render("동전1", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 50, 50);
				}
				if (vItem[i].state == 유황)
				{
					RectangleMake(getMemDC(), vItem[i].rc);
					TextOut(getMemDC(), vItem[i].rc.left, vItem[i].rc.top, TEXT("유황"), lstrlen(TEXT("유황")));
					//IMAGEMANAGER->render("동전1", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 50, 50);
				}
				if (vItem[i].state == 구렁텅이의군주)
				{
					RectangleMake(getMemDC(), vItem[i].rc);
					TextOut(getMemDC(), vItem[i].rc.left, vItem[i].rc.top, TEXT("구렁텅이의군주"), lstrlen(TEXT("구렁텅이의군주")));
					//IMAGEMANAGER->render("동전1", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 50, 50);
				}
				if (vItem[i].state == 썩은고기)
				{
					RectangleMake(getMemDC(), vItem[i].rc);
					TextOut(getMemDC(), vItem[i].rc.left, vItem[i].rc.top, TEXT("썩은고기"), lstrlen(TEXT("썩은고기")));
					//IMAGEMANAGER->render("동전1", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 50, 50);
				}
				if (vItem[i].state == 알약)
				{
					RectangleMake(getMemDC(), vItem[i].rc);
					TextOut(getMemDC(), vItem[i].rc.left, vItem[i].rc.top, TEXT("알약"), lstrlen(TEXT("알약")));
					//IMAGEMANAGER->render("동전1", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 50, 50);
				}
				if (vItem[i].state == 박사의조정기)
				{
					RectangleMake(getMemDC(), vItem[i].rc);
					TextOut(getMemDC(), vItem[i].rc.left, vItem[i].rc.top, TEXT("박사의조정기"), lstrlen(TEXT("박사의조정기")));
					//IMAGEMANAGER->render("동전1", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 50, 50);
				}
				if (vItem[i].state == 모래시계)
				{
					RectangleMake(getMemDC(), vItem[i].rc);
					TextOut(getMemDC(), vItem[i].rc.left, vItem[i].rc.top, TEXT("모래시계"), lstrlen(TEXT("모래시계")));
					//IMAGEMANAGER->render("동전1", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 50, 50);
				}
				if (vItem[i].state == 보물상자)
				{
					RectangleMake(getMemDC(), vItem[i].rc);
					TextOut(getMemDC(), vItem[i].rc.left, vItem[i].rc.top, TEXT("보물상자"), lstrlen(TEXT("보물상자")));
					//IMAGEMANAGER->render("동전1", getMemDC(), vItem[i].rc.left, vItem[i].rc.top, 0, 0, 50, 50);
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
				if (vNewItem[i].state == 열쇠)
				{
					RectangleMake(getMemDC(), vNewItem[i].rc);
					IMAGEMANAGER->render("열쇠", getMemDC(), vNewItem[i].rc.left, vNewItem[i].rc.top, 0, 0, 50, 50);
				}
				if (vNewItem[i].state == 폭탄&&vNewItem[i].IsBomb == false)
				{
					RectangleMake(getMemDC(), vNewItem[i].rc);
					IMAGEMANAGER->render("폭탄", getMemDC(), vNewItem[i].rc.left, vNewItem[i].rc.top, 0, 0, 50, 50);
				}
				if (vNewItem[i].state == 폭탄&&vNewItem[i].IsBomb == true)
				{
					IMAGEMANAGER->render("폭탄", getMemDC(), vNewItem[i].x, vNewItem[i].y, 0, 0, 50, 50);
					RectangleMake(getMemDC(), vNewItem[i].rc);
				}
				if (vNewItem[i].state == 빨간하트반)
				{
					//IMAGEMANAGER->render("폭탄", getMemDC(), vNewItem[i].x, vNewItem[i].y, 0, 0, 50, 50);
					RectangleMake(getMemDC(), vNewItem[i].rc);
					TextOut(getMemDC(), vNewItem[i].rc.left, vNewItem[i].rc.top, TEXT("빨간하트반"), lstrlen(TEXT("빨간하트반")));
				}
				if (vNewItem[i].state == 빨간하트)
				{
					//IMAGEMANAGER->render("폭탄", getMemDC(), vNewItem[i].x, vNewItem[i].y, 0, 0, 50, 50);
					RectangleMake(getMemDC(), vNewItem[i].rc);
					TextOut(getMemDC(), vNewItem[i].rc.left, vNewItem[i].rc.top, TEXT("빨간하트"), lstrlen(TEXT("빨간하트")));
				}
				if (vNewItem[i].state == 동전1)
				{
					RectangleMake(getMemDC(), vNewItem[i].rc);
					TextOut(getMemDC(), vNewItem[i].rc.left, vNewItem[i].rc.top, TEXT("동전1"), lstrlen(TEXT("동전1")));
				}
				if (vNewItem[i].state == 동전99)
				{
					RectangleMake(getMemDC(), vNewItem[i].rc);
					TextOut(getMemDC(), vNewItem[i].rc.left, vNewItem[i].rc.top, TEXT("동전99"), lstrlen(TEXT("동전99")));
				}
				if (vNewItem[i].state == 박사의조정기)
				{
					RectangleMake(getMemDC(), vNewItem[i].rc);
					TextOut(getMemDC(), vNewItem[i].rc.left, vNewItem[i].rc.top, TEXT("박사의조정기"), lstrlen(TEXT("박사의조정기")));
				}
				if (vNewItem[i].state == 모래시계)
				{
					RectangleMake(getMemDC(), vNewItem[i].rc);
					TextOut(getMemDC(), vNewItem[i].rc.left, vNewItem[i].rc.top, TEXT("모래시계"), lstrlen(TEXT("모래시계")));
				}

			}

		}
	}
}


