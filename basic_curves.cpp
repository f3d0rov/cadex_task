
#include "basic_curves.h"
#include <iostream>

#define _USE_MATH_DEFINES /* M_PI */
#include <math.h> /* std::sin, std::cos */


Circle::Circle (Dimension radius):
_radius (radius) {

}


Dimension Circle::radius () const {
	return this->_radius;
}


Point3D Circle::pointAt (Dimension t) const {
	// x = R * cos (t)
	// y = R * sin (t)
	return Point3D (std::cos (t), std::sin (t)) * this->_radius;
}


Point3D Circle::firstDerivativeAt (Dimension t) const {
	// x = (R * cos (t))' = -R * sin (t)
	// y = (R * sin (t))' =  R * cos (t)
	return Point3D (- std::sin (t), std::cos (t)) * this->_radius;
}




Ellipse::Ellipse (Dimension radiusX, Dimension radiusY):
_radiusX (radiusX), _radiusY (radiusY) {
	
}


Dimension Ellipse::radiusX () const {
	return this->_radiusX;
}


Dimension Ellipse::radiusY () const {
	return this->_radiusY;
}


Point3D Ellipse::pointAt (Dimension t) const {
	// x = Rx * cos (t)
	// y = Ry * sin (t)
	return Point3D (this->_radiusX * std::cos (t), this->_radiusY * std::sin (t));
}


Point3D Ellipse::firstDerivativeAt (Dimension t) const {
	// x = (Rx * cos (t))' = -Rx * sin (t)
	// y = (Ry * sin (t))' =  Ry * cos (t)
	return Point3D (- this->_radiusX * std::sin (t), this->_radiusY * std::cos (t));
}




Helix::Helix (Dimension radius, Dimension step):
_radius (radius), _step (step) {

}


Dimension Helix::radius () const {
	return this->_radius;
}


Dimension Helix::step () const {
	return this->_step;
}


Point3D Helix::pointAt (Dimension t) const {
	// x = R * cos (t)
	// y = R * sin (t)
	// z = step * t / (2 * pi) // 1 полный оборот за `2 * pi`
	return Point3D (
		this->_radius * std::cos (t),
		this->_radius * std::sin (t),
		this->_step * t / (2 * M_PI)
	);
}


Point3D Helix::firstDerivativeAt (Dimension t) const {
	// x = (R * cos (t))' = - R * sin (t) 
	// y = (R * sin (t))' =   R * cos (t)
	// z = (step * t / (2 * pi))' = step / (2 * pi)
	return Point3D (
		- this->_radius * std::sin (t),
		  this->_radius * std::cos (t),
		  this->_step / (2 * M_PI)	
	);
}

