#pragma once

namespace Util
{
	typedef struct movement_vector {
		double x;
		double y;
	} Movement_Vector;

	Movement_Vector Make_Distance_U_V(RECT to_r, RECT from_r);
}