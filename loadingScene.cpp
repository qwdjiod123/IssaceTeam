#include "stdafx.h"
#include "loadingScene.h"

HRESULT loadingScene::init(void)
{
	//로딩클래스 생성 및 초기화
	_loading = new loading;
	_loading->init();

	//이미지 및 사운드 로딩
	this->loadingImage();
	this->loadingSound();

	return S_OK;
}

void loadingScene::release(void)
{
	//로딩클래스 해제
	SAFE_DELETE(_loading);
}

void loadingScene::update(void)
{
	//로딩클래스 업데이트
	_loading->update();

	if (_loading->loadingDone())
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			//로딩이 완료 됐으니 씬변경
			SCENEMANAGER->changeScene("게임화면");
		}
	}
}

void loadingScene::render(void)
{
	//로딩클래스 렌더
	_loading->render();
}

//로딩이미지 함수(이곳에 이미지를 전부 넣어라)
void loadingScene::loadingImage(void)
{
	//_loading->loadImage();
	//_loading->loadFrameImage();

	//로딩이 너무 빠르게 진행되서 천천히 돌아가도록 테스트용으로 만들어 놓자
	for (int i = 0; i < 100; i++)
	{
		_loading->loadImage("테스트", WINSIZEX, WINSIZEY);
	}

	//백그라운드 이미지
	//_loading->loadImage("백그라운드", "background.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("총알", "ball.bmp", 10, 10);
	_loading->loadImage("map1", "inGameInfo.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("map2", "map2.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("map3", "map3.bmp", WINSIZEX, WINSIZEY);
	_loading->loadImage("폭탄", "bomb.bmp", 50, 50);
	_loading->loadImage("열쇠", "key.bmp", 50, 50);
<<<<<<< HEAD
	//플레이어 이미지 
	_loading->loadImage("아이작왼쪽얼굴", "아이작LEFT.bmp", PLAYERHEADSIZEX, PLAYERHEADSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("아이작오른쪽얼굴", "아이작옆.bmp", PLAYERHEADSIZEX, PLAYERHEADSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("아이작IDLE", "아이작IDLE.bmp", PLAYERHEADSIZEX, PLAYERHEADSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("아이작뒷통수", "아이작뒷통수.bmp", PLAYERHEADSIZEX, PLAYERHEADSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("아이작몸통", "몸통.bmp", PLAYERSIZEX, PLAYERSIZEY, true, RGB(255, 0, 255));
	_loading->loadFrameImage("아이작왼쪽몸통", "WALKLEFT.bmp", PLAYERSIZEX * 10, PLAYERSIZEY, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("아이작오른쪽몸통", "아이작RIGHT.bmp", PLAYERSIZEX * 10, PLAYERSIZEY, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("아이작UPDOWN", "아이작UPDOWN.bmp", PLAYERSIZEX * 10, PLAYERSIZEY, 10, 1, true, RGB(255, 0, 255));
	//유황플레이어
	_loading->loadImage("유황왼쪽얼굴", "유황LEFT.bmp", PLAYERHEADSIZEX, PLAYERHEADSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("유황오른쪽얼굴", "유황RIGHT.bmp", PLAYERHEADSIZEX, PLAYERHEADSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("유황IDLE", "유황IDLE.bmp", PLAYERHEADSIZEX + 10, PLAYERHEADSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("유황뒷통수", "유황뒷통수.bmp", PLAYERHEADSIZEX, PLAYERHEADSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("유황몸통", "유황몸통.bmp", PLAYERSIZEX, PLAYERSIZEY, true, RGB(255, 0, 255));
	_loading->loadFrameImage("유황왼쪽몸통", "아이작유황LEFT.bmp", PLAYERSIZEX * 10, PLAYERSIZEY, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("유황오른쪽몸통", "아이작유황RIGHT.bmp", PLAYERSIZEX * 10, PLAYERSIZEY, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("유황UPDOWN", "아이작유황UPDOWN.bmp", PLAYERSIZEX * 10, PLAYERSIZEY, 10, 1, true, RGB(255, 0, 255));
	//총알이미지 
	_loading->loadImage("기본총알", "기본총알.bmp", 26, 26, true, RGB(255, 0, 255));
	//몬스터에 대한 이미지
	_loading->loadImage("worm_V", "wormTest_V.bmp", 20, 21, true, RGB(255, 0, 255));
	_loading->loadImage("worm_H", "wormTest_H.bmp", 30, 13, true, RGB(255, 0, 255));
=======
	_loading->loadImage("아이작왼쪽얼굴", "아이작LEFT.bmp", 28*3, 25*3, true, RGB(255, 0, 255));
	_loading->loadImage("아이작오른쪽얼굴", "아이작옆.bmp", 28*3, 25 * 3, true, RGB(255, 0, 255));
	_loading->loadImage("아이작IDLE", "아이작IDLE.bmp", 28 * 3, 25 * 3, true, RGB(255, 0, 255));
	_loading->loadImage("아이작뒷통수", "아이작뒷통수.bmp", 28 * 3, 25 * 3, true, RGB(255, 0, 255));
	_loading->loadImage("아이작몸통", "몸통.bmp", 18 * 3, 15 * 3, true, RGB(255, 0, 255));
	_loading->loadFrameImage("아이작왼쪽몸통", "WALKLEFT.bmp", 180 * 3, 15 * 3, 10, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("아이작오른쪽몸통", "아이작RIGHT.bmp", 180 * 3, 15 * 3, 10,1,true, RGB(255, 0, 255));
	_loading->loadFrameImage("아이작UPDOWN", "아이작UPDOWN.bmp", 180 * 3, 15 * 3, 10, 1, true, RGB(255, 0, 255));
	_loading->loadImage("기본총알", "기본총알.bmp", 26, 26, true, RGB(255, 0, 255));

	//몬스터에 대한 이미지
	_loading->loadImage("worm_V", "wormTest_V.bmp", 20, 21, true, RGB(255, 0, 255));
	_loading->loadImage("worm_H", "wormTest_H.bmp", 30, 13, true, RGB(255, 0, 255));		
>>>>>>> origin/master

}
//로딩사운드 함수(이곳에 사운드를 전부 넣어라)
void loadingScene::loadingSound(void)
{
}
