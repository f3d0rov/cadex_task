
#pragma once

#include <cmath>

#include "datatypes.h"


// Общий интерфейс для кривых 
class CurveInterface {
	public:
		virtual ~CurveInterface ();

		virtual Point3D pointAt (Dimension t) const = 0;
		virtual Point3D firstDerivativeAt (Dimension t) const = 0;
};
