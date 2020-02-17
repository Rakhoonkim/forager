#pragma once
//�÷��̾��� ���� 
// MOVE
// ATTACK
// JUMP
// DEAD
// FISHING

// �밢�� ���� ��
#define UP_LEFTANGLE 2.355f
#define UP_RIGHTANGLE 0.785f
#define DOWN_LEFTANGLE  3.925
#define DOWN_RIGHTANGLE 5.46f
#define ANGLESPEED 4*PI / 180

class player;

class playerState
{
protected:
	tagPlayer* _player;
	float _angle;
	float _speed;
	int _direction; // 0 ���� 1 ������ 
	float _width;
	float _height;
	float _acel;
public:
	playerState();
	virtual	~playerState();

	HRESULT init(tagPlayer* player);
	virtual void update();
	virtual void changeImage(int right);
	virtual void setAngle(float angle) { _angle = angle; }
	virtual void setSpeed(float speed) { _speed = speed; }
	virtual void setAngleKeyCollision();
	virtual void setWeaponXY();
	virtual void shadow();
	virtual void direction();
	virtual float getAngle() { return _angle; }
};


class playerMove : public playerState
{
public:
	playerMove(tagPlayer* player);
	virtual void update();
	virtual void changeImage(int right);
	virtual void setAngleKeyCollision();
	virtual void setWeaponXY();
	virtual void shadow();
};


class playerIdle : public playerState
{
public:
	playerIdle(tagPlayer* player);
	virtual void update();
	virtual void changeImage(int right);
	virtual void setWeaponXY();
};


