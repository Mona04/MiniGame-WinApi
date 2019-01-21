#include "stdafx.h"
#include "Object.h"

void Object::Obj_Init(RECT in_rc, int in_vertical_v, int in_horizontal_v, int in_is_air)
{
	_rc = in_rc;
	_vertical_v = in_vertical_v;
	_horizontal_v = in_horizontal_v;
	_is_air = in_is_air;
};

void Object::Object_Engine(Map* in_map)
{
	RECT temp1;
	RECT temp2;
	int is_able = 1;
	int inteval = 1;
	int v_len, h_len;
	int v_dir, h_dir, dir;

	int temp = get_horizontal_v();
	h_dir = temp > -temp ? 2 : 0;
	h_len = temp > -temp ? temp : -temp;

	temp = get_vertical_v();
	v_dir = temp > -temp ? 3 : 1;
	v_len = temp > -temp ? temp : -temp;

	int i = 0;
	int j = 0;
	int o = 0;

	while (i < h_len || j < v_len) {

		temp2 = get_RC();

		if (o % 2 == 0) {
			dir = h_dir;
			o = 1;
			if (i >= h_len)
				continue;
		}
		else {
			dir = v_dir;
			o = 0;
			if (j >= v_len)
				continue;
		}
		is_able = 1;

		switch (dir)
		{
		case 0:
			temp2.left -= inteval; temp2.right -= inteval;
			i++;  break;
		case 1:
			temp2.top -= inteval; temp2.bottom -= inteval;
			j++;  break;
		case 2:
			temp2.left += inteval; temp2.right += inteval;
			i++; break;
		case 3:
			temp2.top += inteval; temp2.bottom += inteval;
			j++;  break;
		}

		for (int k = 0; k < Total_Block; k++) {
			if (IntersectRect(&temp1, &temp2, &in_map->get_blo_rc(k))) {
				is_able = 0;
				if (dir == 0 || dir == 2) {
					i = h_len;
				}
				else if (dir == 1 || dir == 3) {
					j = v_len;
				}
				break;
			}
		}

		if (is_able == 0)
			continue;
		_Move(dir);
	}
}


void Object::Graviate_Object(Map* in_map)
{
	RECT obj = get_RC();
	RECT tmp;
	double v_v = get_vertical_v();

	for (int i = 0; i < Total_Block; i++) {
		tmp = in_map->get_blo_rc(i);
		if ((tmp.left < obj.right && tmp.left > obj.left)
			|| (tmp.right > obj.left && tmp.right < obj.right)
			|| (tmp.right > obj.right && tmp.left < obj.left)) {
			if (obj.bottom >= tmp.top) {
				set_is_air(0);
				set_vertical_v(0);
				break;
			}
			else {
				set_is_air(1);
			}
		}
		if (i == Total_Block - 1) {
			set_is_air(1);
		}
	}

	if (get_is_air() == 1) {
		set_vertical_v(v_v + gravity);
	}

}