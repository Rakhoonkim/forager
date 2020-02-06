#pragma once

class player;
//�÷��̾��� ���� 
// MOVE
// ATTACK
// JUMP
// DEAD
// FISHING

class playerState
{
protected:
	tagPlayer* _player;
	float _angle;
	float _speed;
	int _direction; // 0 ���� 1 ������ 
public:
	playerState();
	virtual	~playerState();

	HRESULT init(tagPlayer* player);
	virtual void update();
	virtual void changeImage(int right);
	virtual void setAngle(float angle) { _angle = angle; }
	virtual void setSpeed(float speed) { _speed = speed; }
};


class playerMove : public playerState
{
public:
	playerMove(tagPlayer* player);
	virtual void update();
	virtual void changeImage(int right);
};


class playerIdle : public playerState
{
public:
	playerIdle(tagPlayer* player);
	virtual void update();
	virtual void changeImage(int right);
};


