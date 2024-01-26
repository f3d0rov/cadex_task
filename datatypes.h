
#pragma once

#include <istream> // std::ostream

// Используем `double` в качестве типа измерения
typedef double Dimension;


// Структура данных, представляющая точку
struct Point3D {
	Dimension x = 0, y = 0, z = 0;

	Point3D ();
	Point3D (Dimension x, Dimension y, Dimension z = 0);
	Point3D (const Point3D &p);
	Point3D (Point3D &&p);

	Point3D operator* (Dimension s);
};


// Перегрузка вывода в стрим для структуры-точки
std::ostream &operator<< (std::ostream &out, const Point3D &p);
