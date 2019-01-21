#include "stdafx.h"
#include "Util.h"


namespace Util
{
	Movement_Vector Make_Distance_U_V(RECT to_r, RECT from_r)
	{
		double _x = (to_r.left + to_r.right) / 2 - (from_r.left + from_r.right) / 2;
		double _y = (to_r.top + to_r.bottom) / 2 - (from_r.top + from_r.bottom) / 2;
		double denominator = sqrt(pow(_x, 2) + pow(_y, 2));

		Movement_Vector result;

		result.x = _x / denominator;
		result.y = _y / denominator;

		return result;
	}
}