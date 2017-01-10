#pragma once
#include "enemy.h"
#define KONCKBACKPOWER 1.0f
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
	float _x;						//중심 x
	float _y;						//중심 Y
	float _moveSpeed;				//움직임 속도
	int _HP;						//몹의 체력
	MOVESTATE _move;				//움직이는 타입을 고르는 이넘문
	int _attackCount;				//공격중인 카운트 시간
	cPlayer* _player;				//플레이어의 주소 저장 변수
	bool isAttack;					//지금 공격중인지? 확인하는 불리언
	int _moveCount;					//움직임의 변화를 주는변수
	float _knockBackAngle;			//넉백 각도
	int _knockBackCount;			//넉백 타이머
public:

	virtual HRESULT init(void);
	HRESULT init(char* V_ImgName, char* H_ImaName, POINT position,float moveSpeed,cPlayer* player);
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

