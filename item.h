#pragma once


class item 
{
private:
	tagItem _item;

public:
	item();
	~item();

	HRESULT init(const char* imageName, float x, float y);
	void release();
	void update();
	void render();

	void move();
	void dropMove();
	void setDrop(float x, float y);

	tagItem* getItem() { return &_item; }


};

