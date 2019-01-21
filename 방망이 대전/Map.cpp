#include "stdafx.h"
#include "Map.h"

void Map::Init(int map_name, int block_name)
{
	background_chip = LoadBitmap(hInst, MAKEINTRESOURCE(map_name));
	block_chip = LoadBitmap(hInst, MAKEINTRESOURCE(block_name));
	block_size = 30;

	for (int i = 0; i < Total_Block; i++) {
		blo_chip_rc[i] = { 0, 0, 0 + block_size, 0 + block_size };
	}
	for (int i = 0; i < 22; i++) {
		blo_chip_rc[i] = { 290 + block_size*i, WINSIZEY - block_size*2,
			290 + block_size * i + block_size, WINSIZEY - block_size * 2 + block_size};
	}
	for (int i = 22; i < 22 + 6; i++) {
		blo_chip_rc[i] = { 290, WINSIZEY - block_size * (2*(i-22)+4),
			290 + block_size, WINSIZEY - block_size * (2 * (i - 22) + 4) + block_size };
	}
	for (int i = 28; i < 28 + 6; i++) {
		blo_chip_rc[i] = { 920, WINSIZEY - block_size * (2 * (i - 28) + 4),
			920 + block_size, WINSIZEY - block_size * (2 * (i - 28) + 4) + block_size };
	}

}

void Map::Show(HDC hdc)
{
	HDC mem_DC = CreateCompatibleDC(hdc);
	HBITMAP tp_bit = CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);

	o_chip = (HBITMAP)SelectObject(mem_DC, background_chip);
	TransparentBlt(hdc, 0, 0, WINSIZEX, WINSIZEY, mem_DC,
		0, 0, 1900, 990, RGB(255, 0, 255));

	o_chip = (HBITMAP)SelectObject(mem_DC, block_chip);
	for (int i = 0; i < Total_Block; i++) {
		TransparentBlt(hdc, blo_chip_rc[i].left, blo_chip_rc[i].top, block_size, block_size, mem_DC,
			0, 0, 72, 72, RGB(255, 0, 255));
	}

	DeleteDC(mem_DC);
}

void Map::Release()
{
	HDC hdc = GetDC(hWnd);
	HDC memDC = CreateCompatibleDC(hdc);

	SelectObject(memDC, o_chip);
	DeleteObject(block_chip);
	DeleteObject(background_chip);
	DeleteDC(memDC);
	ReleaseDC(hWnd, hdc);
}

Map::Map()
{
}


Map::~Map()
{
}
