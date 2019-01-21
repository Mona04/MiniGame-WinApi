#include "stdafx.h"
#include "gameNode.h"

POINT _ptMouse;


void gameNode::setBackBuffer()
{
	_backBuffer = new backBuffer;
	_backBuffer->init(WINSIZEX, WINSIZEY);
}

HRESULT gameNode::init()
{
	SetTimer(hWnd, 1, 33, NULL);   // basic
	SetTimer(hWnd, 2, 200, NULL);   // character

	if(_backBuffer == NULL)
		setBackBuffer();

	return S_OK;
}

void gameNode::release()
{
	KillTimer(hWnd, 1);
	delete(_backBuffer);
}

void gameNode::update()
{
	InvalidateRect(hWnd, NULL, FALSE);
}

void gameNode::render(HDC hdc) {}

void gameNode::animate() {}

void gameNode::timer_update(int) {}

LRESULT gameNode::MainProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			this->update();
			break;
		case 2:
			this->animate();
			break;
		}
		if(wParam>2)
			this->timer_update(wParam);
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		this->render(hdc);
		EndPaint(hWnd, &ps);
	}
		break;
	case WM_MOUSEMOVE:
	{
		_ptMouse.x = static_cast<float>LOWORD(lParam);
		_ptMouse.y = static_cast<float>HIWORD(lParam);
	}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}


gameNode::gameNode()
{
}

gameNode::~gameNode()
{
}

