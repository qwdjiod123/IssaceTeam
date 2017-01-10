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
	float _x;						//�߽� x
	float _y;						//�߽� Y
	float _moveSpeed;				//������ �ӵ�
	int _HP;						//���� ü��
	MOVESTATE _move;				//�����̴� Ÿ���� ���� �̳ѹ�
	int _attackCount;				//�������� ī��Ʈ �ð�
	cPlayer* _player;				//�÷��̾��� �ּ� ���� ����
	bool isAttack;					//���� ����������? Ȯ���ϴ� �Ҹ���
	int _moveCount;					//�������� ��ȭ�� �ִº���
	float _knockBackAngle;			//�˹� ����
	int _knockBackCount;			//�˹� Ÿ�̸�
public:

	virtual HRESULT init(void);
	HRESULT init(char* V_ImgName, char* H_ImaName, POINT position,float moveSpeed,cPlayer* player);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	virtual void move();			//������Ʈ�� �ֱ�
	virtual void draw();			//���� �ȿ� �ֱ�
	virtual void animation();		//������Ʈ�� �ֱ�
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

