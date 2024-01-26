
#include "datatypes.h"
#include <sstream>
#include <iomanip>

Point3D::Point3D () {

}

Point3D::Point3D (Dimension x, Dimension y, Dimension z):
x (x), y (y), z (z) {

}

Point3D::Point3D (const Point3D &copy):
Point3D (copy.x, copy.y, copy.z) {

} 

Point3D::Point3D (Point3D &&move):
Point3D (move.x, move.y, move.z) {

}

Point3D Point3D::operator* (Dimension s) {
	return Point3D (s * this->x, s * this->y, s * this->z);
}




std::ostream &operator<< (std::ostream &out, const Point3D &p) {
	// Выводим точку в виде "(1, 2, 3)"
	std::stringstream ss; // Выводим сначала в`stringstream` для сохранения формата вывода
	ss << "(" << std::fixed << std::setprecision (5) << p.x << ", " << p.y << ", " << p.z << ")";
	out << ss.str();
	return out;
}

