#include "stdafx.h"
#include "backBuffer.h"

HRESULT backBuffer::init(int width, int height)
{
	if (_backBufferInfo != NULL) release();

	HDC hdc = GetDC(hWnd);

	_backBufferInfo = new backBuffer_Info;
	_backBufferInfo->hMemDC = CreateCompatibleDC(hdc);
	_backBufferInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_backBufferInfo->hOBit = (HBITMAP)SelectObject(_backBufferInfo->hMemDC, _backBufferInfo->hBit);
	_backBufferInfo->width = width;
	_backBufferInfo->height = height;

	if (_backBufferInfo->hBit == NULL) {
		release();
		return E_FAIL;
	}
	
	ReleaseDC(hWnd, hdc);

	return S_OK;
}

void backBuffer::release()
{
	if (_backBufferInfo) {
		SelectObject(_backBufferInfo->hMemDC, _backBufferInfo->hOBit);
		DeleteObject(_backBufferInfo->hBit);
		DeleteDC(_backBufferInfo->hMemDC);

		delete _backBufferInfo;
	}
}

void backBuffer::render(HDC hdc, int destX, int destY)
{
	BitBlt(hdc, destX, destY,
		_backBufferInfo->width, _backBufferInfo->height,
		_backBufferInfo->hMemDC, 0, 0, SRCCOPY);
}


backBuffer::backBuffer()
{
}


backBuffer::~backBuffer()
{
}
