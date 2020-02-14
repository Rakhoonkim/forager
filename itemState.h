#pragma once

class itemState
{
protected:
	tagItem* _item;
public:
	itemState();
	~itemState();

	virtual HRESULT init(tagItem* item);
	virtual void release();
	virtual void update();
	virtual void render();
	virtual void jump();
	virtual void move();
};

class itemDrop : public itemState
{
public:
	itemDrop(tagItem* item) { _item = item; }
	~itemDrop() {}

	virtual void update();
	virtual void render();
	virtual void jump();
	virtual void move();
};

class itemGain : public itemState
{
public:
	itemGain(tagItem* item) { _item = item; }
	~itemGain() {}

	virtual void update();
	virtual void render();

	virtual void move();
};