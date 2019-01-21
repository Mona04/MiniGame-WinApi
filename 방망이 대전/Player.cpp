#include "stdafx.h"
#include "Player.h"


void Player::Init(int name, POINT* from, POINT*size, RECT in_rc)
{
	character_chip = LoadBitmap(hInst, MAKEINTRESOURCE(name));

	cur_dir = 0;
	cur_status = 0;

	for (int i = 0; i < Num_Char_Skin; i++) {
		cha_chip_from[i] = from[i];
		cha_chip_size[i] = size[i];
	}
	
	Obj_Init(in_rc, 0, 0, 0);

	walk_p = 15;
	jump_p = 30;
	is_jump = 0;

	do_skill = 0;
	cur_weapon = 0;
	all_weapon = 2;

	is_attacked = 0;
	is_invincible = 0;

	hp_bar = 100;
}

void Player::Show(HDC hdc)
{
	HDC st_DC = CreateCompatibleDC(hdc);
	HDC tp_DC = CreateCompatibleDC(hdc);
	HBITMAP tp_bit = CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);

	o_chip = (HBITMAP)SelectObject(st_DC, character_chip);
	SelectObject(tp_DC, tp_bit);

	int from_x = _rc.left;
	int from_y = _rc.top + 7;
	int width = _rc.right - _rc.left;
	int height = _rc.bottom - _rc.top;

	switch (cur_dir)
	{
	case 0:   // dir is => 
		StretchBlt(tp_DC, from_x + width - 1, from_y, -width, height, st_DC,
			cha_chip_from[cur_status].x, cha_chip_from[cur_status].y,
			cha_chip_size[cur_status].x - 3, cha_chip_size[cur_status].y, SRCCOPY);
		break;
	case 1:
		StretchBlt(tp_DC, from_x, from_y, width, height, st_DC,
			cha_chip_from[cur_status].x, cha_chip_from[cur_status].y,
			cha_chip_size[cur_status].x - 3, cha_chip_size[cur_status].y, SRCCOPY);
		break;
	}
	
	TransparentBlt(hdc, from_x, from_y, width, height, tp_DC,
		from_x, from_y, width, height, RGB(255,0,255));

	SelectObject(st_DC, o_chip);
	SelectObject(tp_DC, o_chip);

	DeleteDC(st_DC);
	DeleteDC(tp_DC);
	DeleteObject(tp_bit);
}

void Player::Release()
{
	HDC hdc = GetDC(hWnd);
	HDC memDC = CreateCompatibleDC(hdc);
	SelectObject(memDC, o_chip);
	DeleteObject(character_chip);
	DeleteDC(memDC);
	ReleaseDC(hWnd, hdc);
}

void Player::Move(int var)
{
	if ( (var == 0 || var == 2) && (get_is_air() == 0))
		cur_status = 2 + cur_status % 2;

	switch (var)
	{
	case 0:
	{
		set_horizontal_v(-walk_p);
		if (cur_dir == 0)
			cur_dir = 1;
	} break;
	case 1:
	{
		if (is_jump == 0 && _is_air == 0) {
			is_jump = 1;
			set_vertical_v(-jump_p);
		}
	} break;
	case 2:
	{
		set_horizontal_v(walk_p);
		if (cur_dir == 1)
			cur_dir = 0;
	} break;
	case 3:
	{
		set_vertical_v(walk_p);
	} break;
	}
	TCHAR text[100];
}

void Player::Start_Skill(int timer_id, int timer_t)
{ // ÈÄµô °ü·Ã
	if (do_skill == 0) {
		switch (cur_weapon) {
		case 0:
			cur_status = 12;
			break;
		case 1:
			cur_status = 14;
			break;
		}
		do_skill = 1;
		SetTimer(hWnd, timer_id, timer_t, NULL);
	}
}

void Player::End_Skill(int timer_id)
{
	cur_status = 0;
	do_skill = 0;
	KillTimer(hWnd, timer_id);
}

int Player::Is_attacked(int timer_id, int timer_t, RECT in_rc, int att_type, int in_dir) {

	RECT tmp;
	switch (att_type) {
	case 0:
		if (IntersectRect(&tmp, &get_RC(), &in_rc)) {
			is_attacked = 1;
			cur_status = 6;
			hp_bar -= 20;
			if (in_dir == 1)
				set_horizontal_v(-20);
			else set_horizontal_v(20);
			set_vertical_v(-40);
			SetTimer(hWnd, timer_id, timer_t, NULL);
			return 1;
		}
		break;
	case 1:
		if (IntersectRect(&tmp, &get_RC(), &in_rc)) {
			is_attacked = 1;
			cur_status = 8;
			hp_bar -= 30;
			if (in_dir == 1)
				set_horizontal_v(-5);
			else set_horizontal_v(20);
			set_vertical_v(-10);
			SetTimer(hWnd, timer_id, timer_t, NULL);
			return 1;
		}
		break;
	}
	return 0;
}

void Player::End_attacked(int timer_id)
{
	is_attacked = 0;
	cur_status = 0;
	set_vertical_v(0);
	set_horizontal_v(0);
	KillTimer(hWnd, timer_id);
}

void Player::Start_invincible(int timer_id, int timer_t) 
{
	is_invincible = 1;
	SetTimer(hWnd, timer_id, timer_t, NULL);
}

void Player::End_invincible(int timer_id)
{
	is_invincible = 0;
	KillTimer(hWnd, timer_id);
}

Player::Player()
{
}


Player::~Player()
{
}
