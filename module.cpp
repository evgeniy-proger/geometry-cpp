#include "triangle.h"
#include "rectangle.h"
#include <cmath>
#include <stdexcept>

// Triangle:

// Базовый конструктор: фиксированный прямоугольный треугольник A(0,0) B(0,1) C(1,1)
Triangle::Triangle() : x1(0), y1(0), x2(0), y2(1), x3(1), y3(1) {}

// Конструктор с параметрами: проверяет вырожденность и диапазон
Triangle::Triangle(double nx1, double ny1, double nx2, double ny2, double nx3, double ny3): x1(nx1), y1(ny1), x2(nx2), y2(ny2), x3(nx3), y3(ny3) {
    if (isDegenerate() || !isValidPointInTriangle()) {
        throw std::invalid_argument("Ошибка: Треугольник с такими координатами не может существовать."); 
    }
} 

// Проверка вырожденности: площадь меньше 1e-9 считается нулевой
bool Triangle::isDegenerate() const {
    double area = 0.5 * std::fabs((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1));
    return area < 1e-9;
}

// Сеттер с откатом: если новые координаты невалидны — восстанавливаем старые
void Triangle::setCoordinates(double nx1, double ny1, double nx2, double ny2, double nx3, double ny3){
    // сохраняем старые значения на случай отката
    double ox1 = x1, oy1 = y1, ox2 = x2, oy2 = y2, ox3 = x3, oy3 = y3;
    x1 = nx1; y1 = ny1;
    x2 = nx2; y2 = ny2;
    x3 = nx3; y3 = ny3;

    if (isDegenerate() || !isValidPointInTriangle()) {
        // откат к сохранённым значениям
        x1 = ox1; y1 = oy1;
        x2 = ox2; y2 = oy2;
        x3 = ox3; y3 = oy3;
        throw std::invalid_argument("Ошибка: Новые координаты делают треугольник вырожденным.");
    }
}

// Проверка, что все три точки лежат в диапазоне (-100; 100) строго
bool Triangle::isValidPointInTriangle() const {
    return (x1 > -100 && x1 < 100 && y1 > -100 && y1 < 100 &&
            x2 > -100 && x2 < 100 && y2 > -100 && y2 < 100 &&
            x3 > -100 && x3 < 100 && y3 > -100 && y3 < 100);
}

// Длина стороны A (AB)
double Triangle::getSideA() const {
    return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
}

// Длина стороны B (BC)
double Triangle::getSideB() const {
    return std::sqrt(std::pow(x3 - x2, 2) + std::pow(y3 - y2, 2));
}

// Длина стороны C (AC)
double Triangle::getSideC() const {
    return std::sqrt(std::pow(x3 - x1, 2) + std::pow(y3 - y1, 2));
}

// Периметр = сумма длин всех сторон
double Triangle::getPerimeter() const {
    return getSideA() + getSideB() + getSideC();
}

// Площадь через определитель (формула Гаусса)
double Triangle::getArea() const {
    return 0.5 * std::fabs((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1));
}

// Центроид (точка пересечения медиан) = среднее арифметическое координат вершин
Point Triangle::getMedianIntersection() const {
    Point center;
    center.x = (x1 + x2 + x3) / 3.0;
    center.y = (y1 + y2 + y3) / 3.0;
    return center;
}

// Rectangle:

// Базовый конструктор: квадрат 1x1 A(0,0) B(0,1) C(1,1) D(1,0)
Rectang::Rectang()
    : Triangle(0, 0, 0, 1, 1, 1), 
      x4(1), y4(0) {}

// Конструктор с параметрами: базовый класс проверит треугольник, затем isValid() — прямоугольник
Rectang::Rectang(double nx1, double ny1, double nx2, double ny2, double nx3, double ny3, double nx4, double ny4)
    : Triangle(nx1, ny1, nx2, ny2, nx3, ny3),
      x4(nx4), y4(ny4) {
    if (!isValid()) {
        throw std::invalid_argument("Ошибка: прямоугольник должен быть со всеми прямыми углами");
    }
}

// Проверка прямоугольника:
// 1) все точки в диапазоне (-100; 100);
// 2) |AB| == |CD| и |BC| == |DA| (противоположные стороны равны);
// 3) AB · AD == 0 (угол при A прямой);
// 4) стороны ненулевые.
bool Rectang::isValid() const {
    const double E = 1e-9;
    
    if (getX1() > -100 && getX1() < 100 && getY1() > -100 && getY1() < 100 && 
        getX2() > -100 && getX2() < 100 && getY2() > -100 && getY2() < 100 &&
        getX3() > -100 && getX3() < 100 && getY3() > -100 && getY3() < 100 && 
        getX4() > -100 && getX4() < 100 && getY4() > -100 && getY4() < 100) {

        // длина AB
        double leftLen = std::sqrt(std::pow((getX2() - getX1()), 2) + std::pow((getY2() - getY1()), 2));
        // длина CD
        double rightLen = std::sqrt(std::pow((getX4() - getX3()), 2) + std::pow((getY4() - getY3()), 2));
        bool bokRaven = std::fabs(leftLen - rightLen) < E;

        // длина BC
        double upLen = std::sqrt(std::pow((getX3() - getX2()), 2) + std::pow((getY3() - getY2()), 2));
        // длина DA
        double downLen = std::sqrt(std::pow((getX4() - getX1()), 2) + std::pow((getY4() - getY1()), 2));
        bool HorizontRaven = std::fabs(upLen - downLen) < E;

        bool nonDegenerate = (leftLen > E) && (upLen > E);

        // скалярное произведение AB и AD: равно 0, если угол прямой
        double dotAB_AD = (getX2() - getX1()) * (getX4() - getX1()) + (getY2() - getY1()) * (getY4() - getY1());
        if (std::fabs(dotAB_AD) > E) return false;

        return bokRaven && HorizontRaven && nonDegenerate;
    } else {return false; }
}

// Ширина = |AB| (длина стороны AB)
double Rectang::getWidth() const {
    double dx = getX2() - getX1();
    double dy = getY2() - getY1();
    return std::sqrt(dx*dx + dy*dy);  
}

// Высота = |AD| (длина стороны AD)
double Rectang::getHeight() const {
    double dx = getX4() - getX1();
    double dy = getY4() - getY1();
    return std::sqrt(dx*dx + dy*dy);  
}

// Сеттер с полным откатом всех 8 координат при ошибке
void Rectang::setCoordinatesRect(double nx1, double ny1, double nx2, double ny2, double nx3, double ny3, double nx4, double ny4) {
    // сохраняем старые значения всех четырёх вершин
    double ox1 = getX1(), oy1 = getY1();
    double ox2 = getX2(), oy2 = getY2();
    double ox3 = getX3(), oy3 = getY3();
    double ox4 = x4, oy4 = y4;

    try {
        // Пробуем изменить первые 3 точки через базовый сеттер (он сам проверит треугольник)
        setCoordinates(nx1, ny1, nx2, ny2, nx3, ny3);
        
        // Меняем четвертую точку
        x4 = nx4; 
        y4 = ny4;

        // Проверяем прямоугольник
        if (!isValid()) {
            throw std::invalid_argument("Новые координаты не образуют корректный прямоугольник.");
        }
    }
    catch (...) {
        // Если базовый сеттер выбросил исключение ИЛИ прямоугольник не прошел проверку:
        // Восстанавливаем старое состояние базового класса без проверок (старые точки были правильными)
        setCoordinates(ox1, oy1, ox2, oy2, ox3, oy3);
        x4 = ox4;
        y4 = oy4;
        
        // Пробрасываем исключение дальше, чтобы его поймал try-catch в main()
        throw; 
    }
}

// Переопределённый периметр: 2 * (ширина + высота)
double Rectang::getPerimeter() const {
    return 2 * (getHeight() + getWidth());
}

// Переопределённая площадь: ширина * высота
double Rectang::getArea() const {
    return (getHeight() * getWidth());
}

// Точка пересечения диагоналей — середина диагонали AC
Point Rectang::getDiagonalIntersection() const {
    Point center;
    center.x = (getX1() + getX3()) / 2.0;
    center.y = (getY1() + getY3()) / 2.0;
    return center;
}