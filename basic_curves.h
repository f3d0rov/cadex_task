
#include "datatypes.h"
#include "curve_interface.h"


class Circle: public CurveInterface {
	private:
		Dimension _radius;

	public:
		Circle (Dimension radius);

		Dimension radius () const;

		Point3D pointAt (Dimension t) const final;
		Point3D firstDerivativeAt (Dimension t) const final;
};


class Ellipse: public CurveInterface {
	private:
		Dimension _radiusX, _radiusY;

	public:
		Ellipse (Dimension radiusX, Dimension radiusY);

		Dimension radiusX () const;
		Dimension radiusY () const;

		Point3D pointAt (Dimension t) const final;
		Point3D firstDerivativeAt (Dimension t) const final;
};


class Helix: public CurveInterface {
	private:
		Dimension _radius, _step;

	public:
		Helix (Dimension radius, Dimension step);

		Dimension radius () const;
		Dimension step () const;

		Point3D pointAt (Dimension t) const final;
		Point3D firstDerivativeAt (Dimension t) const final;
};

