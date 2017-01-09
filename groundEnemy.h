#pragma once
#include "enemy.h"

enum MOVESTATE
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class cPlayer;


class groundEnemy :
	public enemy
{
private:
	RECT _rc;
	image* _v_img;
	image* _h_img;
	float _x;
	float _y;
	float _moveSpeed;
	int _HP;
	MOVESTATE _move;
public:

	virtual HRESULT init(void);
	HRESULT init(char* V_ImgName, char* H_ImaName, POINT position,float moveSpeed);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void move();			//업데이트에 넣기
	virtual void draw();			//렌더 안에 넣기
	virtual void animation();		//업데이트에 넣기

	float getX() { return _x; }
	float getY() { return _y; }
	int getHP() { return _HP; }
	void setHP(int HP) { _HP = HP; }
	void damage(int dmg) { _HP -= dmg; }

	float getSpeed() { return _moveSpeed; }
	void setSpeed(float speed) { _moveSpeed = speed; }

	groundEnemy();
	~groundEnemy();
};

