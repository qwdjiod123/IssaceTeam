#include "stdafx.h"
#include "cSceneGame.h"


HRESULT cSceneGame::init(void)
{
	_player =new cPlayer();	
	_sm = new cSceneManager();
	_im = new cItemManager();

	_player->SetIM(_im);
	_sm->SetPlayer(_player);	
	_sm->SetIM(_im);
	_im->SetIM(_sm);
	_im->SetPlayer(_player);

	_player->init();	
	_sm->init();
	_im->init();
	
	
	

	return S_OK;
}

void cSceneGame::release(void)
{
	_player->release();
	_im->release();
	_sm->release();
}

void cSceneGame::update(void)
{		
	_player->update();
	_im->update();
	_sm->update();
}

void cSceneGame::render(void)
{		
	_sm->render();
	_player->render();
	_im->render();

}

