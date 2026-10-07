#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <iostream>

// Точка на плоскости с координатами (x; y)
struct Point {
    double x = 0.0;
    double y = 0.0;

    // Оператор вывода точки в поток в формате (x;y)
    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        os << "(" << p.x << ";" << p.y << ")";
        return os;
    }
};


// Класс «Треугольник»: хранит три вершины, умеет вычислять
// длины сторон, периметр, площадь и точку пересечения медиан
class Triangle {
private:
    double x1, y1;   // вершина A
    double x2, y2;   // вершина B
    double x3, y3;   // вершина C

    // Приватный вспомогательный метод: проверка вырожденности
    bool isDegenerate() const;
public:
    // Конструкторы 
    Triangle();
    Triangle(double nx1, double ny1, double nx2, double ny2, double nx3, double ny3);


    // Геттеры координат вершин
    double getX1() const { return x1; }
    double getY1() const { return y1; }
    double getX2() const { return x2; }
    double getY2() const { return y2; }
    double getX3() const { return x3; }
    double getY3() const { return y3; }

    // Сеттер координат с откатом при неудачной проверке
    void setCoordinates(double nx1, double ny1, double nx2, double ny2, double nx3, double ny3);

    // Проверка, что все точки лежат в диапазоне (-100; 100)
    bool isValidPointInTriangle() const;

    // Методы вычислений
    double getSideA() const;    // длина AB
    double getSideB() const;    // длина BC
    double getSideC() const;    // длина AC
    virtual double getPerimeter() const;
    virtual double getArea() const;
    Point getMedianIntersection() const;   // точка пересечения медиан

    // Виртуальный деструктор — обязателен при наследовании
    virtual ~Triangle() = default;
};

#endif