
// Написано https://github.com/f3d0rov

// Компилируется с помощью
// clang++ ./basic_curves.cpp ./curve_interface.cpp ./datatypes.cpp ./main.cpp -o cadex_task.exe -std=c++17
// из директории с кодом.


#include <iostream> // std::cout
#include <iomanip> // std::setw
#include <vector> // std::vector
#include <memory> // std::shared_ptr, std::weak_ptr
#include <locale> // std::setlocale
#include <random> // std::rand, std::srand, RAND_MAX
#include <ctime> // std::time (для std::srand)
#include <functional> // std::function
#include <algorithm> // std::sort

#define _USE_MATH_DEFINES /* M_PI */
#include <math.h>


#include "basic_curves.h"




// Будем хранить кривые в векторе через `shared_ptr`-ы.
typedef std::vector <std::shared_ptr <CurveInterface> > CurveContainer;


// Случайное число от 0 до 1
Dimension randomDim () {
	return (1.0 * std::rand()) / RAND_MAX;
}


std::shared_ptr <CurveInterface> randomCurve (Dimension maxRadius, Dimension maxStep) {
	// Выбираем из трех классов кривых
	switch (std::rand() % 3) {
		case 0: { // Создаем случайный круг
			return std::make_shared <Circle> (
				maxRadius * randomDim ()
			);
		}
		case 1: { // Создаем случайный эллипсы
			return std::make_shared <Ellipse> (
				maxRadius * randomDim (),
				maxRadius * randomDim ()
			);
		}
		case 2: { // Создаем случайную спираль
			return std::make_shared <Helix> (
				maxRadius * randomDim (),
				maxStep * randomDim ()
			);
		}
	}

	throw std::logic_error ("randomCurve(): вид кривой не был выбран корректно");
}


// Функция генерации случайных кривых
CurveContainer generateCurves (Dimension maxRadius, Dimension maxStep, int count) {
	// Инициализируем контейнер `curves`
	CurveContainer curves;
	curves.reserve (count);

	// Заполняем `curves` случайными кривыми, всего `count` кривых
	for (int i = 0; i < count; i++) {
		curves.push_back (randomCurve (maxRadius, maxStep));
	}

	// Возвращаем контейнер
	return curves;
}


// Функция вывода значения точки и первой производной для заданного значения `t`.
// Переменной `logMax` можно задать максимальное количество выводимых элементов
void logValuesForT (const CurveContainer &curves, Dimension t, int logMax = 100'000) {
	const int width = 40; // Ширина столбца со значениями
	// Выводим заголовок
	std::cout << "При t = " << t << ":" << std::endl;
	std::cout << std::setw (6) << "#" << " | " << std::setw (width) << "p (t)" << " | " << std::setw (width) << "v (t)" << std::endl << std::endl;
	
	// Для каждой кривой (пока не достигнем максимума)
	for (int index = 0; index < curves.size() && index < logMax; index++) {
		auto &curve = curves [index];
		// Выводим индекс и значения
		std::cout << std::setw (6) << (index + 1) << " | "
			<< std::setw (width) << curve->pointAt (t) << " | "
			<< std::setw (width) << curve->firstDerivativeAt (t) << "\n";
	}

	// Если вывели не все
	if (curves.size() > logMax) {
		std::cout << "Выведено " << logMax << " из " << curves.size() << "\n\n";
	}

	std::cout << std::flush;
} 


CurveContainer filterCurves (const CurveContainer &curves, std::function <bool (std::shared_ptr <CurveInterface>)> conditionToPass) {
	// Инициализируем контейнер
	CurveContainer filtered;

	// Для каждой кривой
	for (auto &i: curves) {
		// Если кривая соответствует условию фильтра, добавить ее в контейнер
		if (conditionToPass (i)) {
			filtered.emplace_back (i);
		}
	}

	// Возвращаем контейнер
	return filtered;
}


// Последоваетльный расчет суммы радиусов окружностей
Dimension circleRadiiSequentialSum (const CurveContainer &circles) {
	Dimension total = 0;
	for (auto i: circles) {
		total += std::dynamic_pointer_cast <Circle> (i)->radius();
	}
	return total;
}


int main () {
	// Задаем русскую локаль для корректного вывода текста в консоль
	std::setlocale (LC_ALL, "Russian.UTF8");

	// Задаем параметры для случайной генерации
	std::srand (std::time (0));
	Dimension maxRadius = 10.0;
	Dimension maxStep = 10.0;
	int genCount = 100'000;

	// Генерируем кривые с помощью функции `generateCurves`
	CurveContainer curves = generateCurves (maxRadius, maxStep, genCount);

	// Выводим значения при t = pi/4 с помощью функции `logValuesForT`
	logValuesForT (curves, M_PI / 4, 40);

	// Получаем контейнер окружностей в `curves`
	CurveContainer circles = filterCurves (
		curves,
		[](std::shared_ptr <CurveInterface> ptr) -> bool {
			return dynamic_cast <Circle *> (ptr.get()) != nullptr; // `true`, если типа `Circle`
		}
	);

	std::cout << "Окружностей: " << circles.size() << " из " << curves.size() << std::endl;

	// Сортируем окружности по радиусу
	std::sort (
		circles.begin(),
		circles.end(),
		[] (std::shared_ptr <CurveInterface> a, std::shared_ptr <CurveInterface> b) {
			return std::dynamic_pointer_cast <Circle> (a)->radius() < std::dynamic_pointer_cast <Circle> (b)->radius();
		}
	);
	
	// Получаем сумму радиусов окружностей
	Dimension totalCircleRadii = circleRadiiSequentialSum (circles);
	std::cout << "Сумма радиусов окружностей: " << totalCircleRadii << std::endl;

	return 0;
}
