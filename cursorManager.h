#pragma once
#include "singletonBase.h"
#include "cursor.h"

class cursorManager : public singletonBase<cursorManager>
{

private:
	cursor*			  _cursor;  // Ŀ�� 
	cursorBasic* _cursorBasic;  // �⺻�̹��� 
	cursorPoint* _cursorPoint;	// ����Ʈ �̹��� 
	cursorBuild* _cursorBuild;
	cursorInven* _cursorInven;
	cursorEnemyBoss* _cursorEnemyBoss;

	cursorFarming* _cursorFarming;
public:

	cursorManager();
	~cursorManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void imageSetting();

	void setCursor();		// �⺻
	void setBossPoint();    // ����
	void setCropsPoint();	// ������Ʈ
	void setBuildPoint();   // �ǹ�
	void setBridgePoint();  // �ٸ�
	void setInvenCursor();  // �κ��丮

	cursor* getCursor(){ return _cursor; }
};

