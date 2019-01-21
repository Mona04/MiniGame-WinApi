#pragma once
#include "backBuffer.h"

class gameNode
{
private:
	backBuffer* _backBuffer;
	void setBackBuffer();

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	virtual void animate();
	virtual void timer_update(int);

	backBuffer* getBackBuffer() {
		if (_backBuffer == NULL) {
			setBackBuffer();
		}
		return _backBuffer; 
	}
	
	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);
	gameNode();
	~gameNode();
};

