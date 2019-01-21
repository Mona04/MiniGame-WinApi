#include "stdafx.h"
#include "Skill.h"


void  Skill::Init(int name, POINT* from, POINT*size, int in_type, int in_timer_id, int in_timer_t)
{
	skill_chip = LoadBitmap(hInst, MAKEINTRESOURCE(name));

	is_on = 0;
	type = in_type;
	timer_id = in_timer_id;
	timer_t = in_timer_t;
	cur_dir = 0;
	cur_status = 0;

	for (int i = 0; i < 2; i++) {
		ski_chip_from[i] = from[i];
		ski_chip_size[i] = size[i];
	}
	
	origin_width = ski_chip_size[0].x;
	origin_height = ski_chip_size[0].y;

	Obj_Init({-100, -100, -100, -100}, 0, 0, 0);
}

int Skill::Show(HDC hdc)
{
	if (!is_on)
		return 0;

	HDC st_DC = CreateCompatibleDC(hdc);
	HDC tp_DC = CreateCompatibleDC(hdc);
	HBITMAP tp_bit = CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);

	o_chip = (HBITMAP)SelectObject(st_DC, skill_chip);
	SelectObject(tp_DC, tp_bit);

	int from_x = _rc.left;
	int from_y = _rc.top;
	int width = _rc.right - _rc.left;
	int height = _rc.bottom - _rc.top;

	switch (cur_dir)
	{
	case 0:   // dir is => 
		StretchBlt(tp_DC, from_x + width, from_y, -width - 1, height, st_DC,
			ski_chip_from[cur_status].x, ski_chip_from[cur_status].y,
			ski_chip_size[cur_status].x, ski_chip_size[cur_status].y, SRCCOPY);
		break;
	case 1:
		StretchBlt(tp_DC, from_x, from_y, width, height, st_DC,
			ski_chip_from[cur_status].x, ski_chip_from[cur_status].y,
			ski_chip_size[cur_status].x, ski_chip_size[cur_status].y, SRCCOPY);
		break;
	}

	TransparentBlt(hdc, from_x, from_y, width, height, tp_DC,
		from_x, from_y, width, height, RGB(255, 0, 255));

	SelectObject(st_DC, o_chip);
	SelectObject(tp_DC, o_chip);

	DeleteDC(st_DC);
	DeleteDC(tp_DC);
	DeleteObject(tp_bit);
}

void Skill::Release()
{
	HDC hdc = GetDC(hWnd);
	HDC memDC = CreateCompatibleDC(hdc);
	SelectObject(memDC, o_chip);
	DeleteObject(skill_chip);
	DeleteDC(memDC);
	ReleaseDC(hWnd, hdc);
}

void Skill::Activate(RECT player_rc, int player_dir)
{
	is_on = 1;
	cur_dir = player_dir;
	SetTimer(hWnd, timer_id, timer_t, NULL);

	RECT tmp = player_rc;

	switch (type)
	{
	case 0:
		set_RC(tmp);
		break;
	case 1:
		if (cur_dir == 0) {
			tmp.left = tmp.right;
			tmp.right = tmp.right + origin_width;
		}
		else {
			tmp.right = tmp.left;
			tmp.left = tmp.left - origin_width;
		}
		set_RC(tmp);
		break;
	case 2:
		if (cur_dir == 0) {
			tmp.left = tmp.right;
			tmp.right = tmp.right + origin_width/2;
		}
		else {
			tmp.right = tmp.left;
			tmp.left = tmp.left - origin_width/2;
		}
		tmp.bottom = tmp.top + origin_height/2;
		set_RC(tmp);
		break;
	}
}

void Skill::Deativate(int in_id)
{
	if (in_id == timer_id) {
		is_on = 0;
		cur_status = 0;
		Obj_Init({ -100, -100, -100, -100 }, 0, 0, 0);

		KillTimer(hWnd, timer_id);
	}
}

void Skill::change_status(Object* enemy) {

	Movement_Vector m_v;

	if (cur_status % 2 == 0) cur_status += 1;
	else cur_status -= 1;

	switch (type) {
	case 0:
		break;
	case 1:
		_rc.top -= 5;
		if (cur_dir == 0)
			set_horizontal_v(get_horizontal_v() / 2 + 10);
		else set_horizontal_v(get_horizontal_v() / 2 - 10);
		break;
	case 2:
		m_v = Make_Distance_U_V(enemy->get_RC(), _rc);
		set_horizontal_v(get_horizontal_v() / 2 + m_v.x*5);
		set_vertical_v(get_vertical_v() / 2 + m_v.y*5);
		break;
	}

}

Skill::Skill()
{
}


Skill::~Skill()
{
}
