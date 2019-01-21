#pragma once

class backBuffer
{
	typedef struct tagBackBufferInfo
	{
		HDC hMemDC;
		HBITMAP hBit;
		HBITMAP hOBit;
		float x;
		float y;
		int width;
		int height;
	}backBuffer_Info, *LPBackBuffer_Info;

private:
	LPBackBuffer_Info _backBufferInfo;

public:
	HRESULT init(int width, int height);
	void release();
	void render(HDC hdc, int destX, int destY);

	inline HDC getMemDC() { return _backBufferInfo->hMemDC; }

	backBuffer();
	~backBuffer();
};

