#pragma once
#include "enemy.h"

#define KONCKBACKPOWER 3

class cPlayer;

class fly :
	public enemy
{
	RECT _rc;
	image* _img;
	float _x;						//�߽� x
	float _y;						//�߽� Y
	float _moveSpeed;				//������ �ӵ�
	int _HP;						//���� ü��
	cPlayer* _player;				//�÷��̾��� �ּ� ���� ����
	float _angle;
	
	int _currentFrameX;
	int _currentFrameY;

	bool _isMove;
	float _knockBackAngle;			//�˹� ����
	int _knockBackCount;			//�˹� Ÿ�̸�
public:

	virtual HRESULT init(void);
	HRESULT init(string imageName, int x, int y, cPlayer* player);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void move();			//������Ʈ�� �ֱ�
	virtual void draw();			//���� �ȿ� �ֱ�
	virtual void animation();		//������Ʈ�� �ֱ�



	virtual void setSpeed(float speed) { _moveSpeed = speed; }
	virtual float getSpeed() { return _moveSpeed; }

	virtual void setHP(float HP) { _HP = HP; }
	virtual float getHP() { return _HP; }


	float getX() { return _x; }
	float getY() { return _y; }

	void collision();

	void damage(int dmg) { _HP -= dmg; }



	fly() {};
	~fly() {};
};

