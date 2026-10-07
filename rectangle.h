#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "triangle.h"

// Дочерний класс «Прямоугольник».
// Наследует Triangle: первые три вершины образуют треугольник,
// четвёртая вершина добавляет фигуру до прямоугольника.
class Rectang : public Triangle {
private:
    double  x4, y4;   // четвёртая вершина D

    // Приватный метод проверки корректности прямоугольника
    bool isValid() const;
public:

    // Конструкторы
    Rectang();
    Rectang(double nx1, double ny1, double nx2, double ny2, double nx3, double ny3, double nx4, double ny4);
    
    // Собственные свойства дочернего класса
    double getX4() const {return x4; };
    double getY4() const {return y4; };
    double getWidth() const;    // длина AB
    double getHeight() const;   // длина AD

    // Собственный сеттер дочернего класса (8 координат)
    void setCoordinatesRect(double nx1, double ny1, double nx2, double ny2, double nx3, double ny3, double nx4, double ny4);

    // Переопределение методов базового класса
    double getPerimeter() const override;
    double getArea() const override;
    
    // Собственный метод дочернего класса
    Point getDiagonalIntersection() const;   
};

#endif