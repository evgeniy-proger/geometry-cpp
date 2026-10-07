#include <iostream>
#include <windows.h>
#include <stdexcept>
#include "triangle.h"
#include "rectangle.h"

// Главная функция: меню из 12 пунктов + выход.
int main() {
    // Настройка кодировки консоли для корректного вывода кириллицы
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    // Буферные переменные для ввода координат
    double x1, y1, x2, y2, x3, y3, x4, y4;

    // Указатели на текущие объекты. nullptr = объект ещё не создан.
    Triangle* t1 = nullptr;
    Rectang* rect = nullptr;

    int ch = -1;

    // Главный цикл меню: работает, пока пользователь не выберет 0
    while (ch != 0) {
        // === Вывод меню ===
        std::cout << "\n=== МЕНЮ ===\n";
        std::cout << "1  - Ввести координаты треугольника\n";
        std::cout << "2  - Длины сторон треугольника\n";
        std::cout << "3  - Периметр треугольника\n";
        std::cout << "4  - Площадь треугольника\n";
        std::cout << "5  - Точка пересечения медиан\n";
        std::cout << "6  - Изменить координаты треугольника\n";
        std::cout << "7  - Ввести координаты прямоугольника\n";
        std::cout << "8  - Ширина и высота прямоугольника\n";
        std::cout << "9  - Периметр прямоугольника\n";
        std::cout << "10 - Площадь прямоугольника\n";
        std::cout << "11 - Точка пересечения диагоналей\n";
        std::cout << "12  - Изменить координаты прямоугольника\n";
        std::cout << "0  - Выход\n";
        std::cout << "Выбор: ";

        // Чтение пункта меню с защитой от нечислового ввода
        if (!(std::cin >> ch)) {
            std::cin.clear();                    // сброс флагов ошибки
            std::cin.ignore(10000, '\n');        // очистка буфера до перевода строки
            std::cout << "Введите число!\n";
            continue;                            // возврат к началу меню
        }
        std::cin.ignore(10000, '\n');            // убрать остаток строки

        // Обработка выбранного пункта
        try {
            switch (ch) {
            // Создание треугольника
            case 1: {
                std::cout << "Введите (-100, 100) x1 y1 x2 y2 x3 y3:  ";
                if (!(std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3)) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "Ошибка ввода чисел!\n";
                    break;
                }
                std::cin.ignore(10000, '\n');

                // new до delete: если new бросит — старый объект останется жив
                Triangle* newT = new Triangle(x1, y1, x2, y2, x3, y3);  // может не создаться
                delete t1;             // удаляем старый только после успешного new
                t1 = newT;
                std::cout << "Треугольник создан.\n";
                break;
            }

            // Длины сторон треугольника
            case 2:
                if (!t1) { std::cout << "Сначала создайте треугольник!\n"; break; }
                std::cout << "A=" << t1->getSideA()
                          << ", B=" << t1->getSideB()
                          << ", C=" << t1->getSideC() << "\n";
                break;

            // Периметр треугольника
            case 3:
                if (!t1) { std::cout << "Сначала создайте треугольник!\n"; break; }
                std::cout << "Периметр: " << t1->getPerimeter() << "\n";
                break;

            // Площадь треугольника
            case 4:
                if (!t1) { std::cout << "Сначала создайте треугольник!\n"; break; }
                std::cout << "Площадь: " << t1->getArea() << "\n";
                break;

            // Точка пересечения медиан
            case 5:
                if (!t1) { std::cout << "Сначала создайте треугольник!\n"; break; }
                std::cout << "Медианы: " << t1->getMedianIntersection() << "\n";
                break;

            // Изменение координат треугольника
            case 6:
                if (!t1) { std::cout << "Сначала создайте треугольник!\n"; break; }
                {
                    std::cout << "Введите новые (-100, 100) x1 y1 x2 y2 x3 y3: ";
                    if (!(std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3)) {
                        std::cin.clear();
                        std::cin.ignore(10000, '\n');
                        std::cout << "Ошибка ввода чисел!\n";
                        break;
                    }
                    std::cin.ignore(10000, '\n');
                    // сеттер сам проверит координаты и откатит их при ошибке
                    t1->setCoordinates(x1, y1, x2, y2, x3, y3);
                    std::cout << "Координаты изменены.\n";
                }
                break;

            // Создание прямоугольника
            case 7: {
                std::cout << "Мы строим прямоугольник на основе треугольника, поэтому внимательно с начальными 3-я точками! \n";
                std::cout << "Введите (-100, 100) x1 y1 x2 y2 x3 y3 x4 y4: ";
                if (!(std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4)) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "Ошибка ввода чисел!\n";
                    break;
                }
                std::cin.ignore(10000, '\n');

                // new до delete: если new бросит — старый прямоугольник останется жив
                Rectang* newR = new Rectang(x1, y1, x2, y2, x3, y3, x4, y4);
                delete rect;
                rect = newR;
                std::cout << "Прямоугольник создан.\n";
                break;
            }

            // Ширина и высота прямоугольника
            case 8:
                if (!rect) { std::cout << "Сначала создайте прямоугольник!\n"; break; }
                std::cout << "Ширина: " << rect->getWidth()
                          << ", Высота: " << rect->getHeight() << "\n";
                break;

            // Периметр прямоугольника
            case 9:
                if (!rect) { std::cout << "Сначала создайте прямоугольник!\n"; break; }
                std::cout << "Периметр: " << rect->getPerimeter() << "\n";
                break;

            // Площадь прямоугольника
            case 10:
                if (!rect) { std::cout << "Сначала создайте прямоугольник!\n"; break; }
                std::cout << "Площадь: " << rect->getArea() << "\n";
                break;

            // Точка пересечения диагоналей
            case 11:
                if (!rect) { std::cout << "Сначала создайте прямоугольник!\n"; break; }
                std::cout << "Диагонали: " << rect->getDiagonalIntersection() << "\n";
                break;

            // Изменение координат прямоугольника
            case 12: {
                if (!rect) { std::cout << "Сначала создайте прямоугольник!\n"; break; }
                std::cout << "Изменение координат меняет основу - треугольник, внимательно с первыми 3-я точками! \n";
                std::cout << "Введите (-100, 100) x1 y1 x2 y2 x3 y3 x4 y4: ";
                if (!(std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4)) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "Ошибка ввода чисел! \n";
                    break;
                }
                std::cin.ignore(10000, '\n');
                // сеттер прямоугольника откатит все 8 координат при ошибке
                rect->setCoordinatesRect(x1, y1, x2, y2, x3, y3, x4, y4);
                std::cout << "Координаты успешно заменены. ";
                break;
            }

            // Выход
            case 0:
                std::cout << "Выход.\n";
                break;

            // Неизвестный пункт
            default:
                std::cout << "Неверный пункт!\n";
                break;
            }
        } catch (const std::exception& e) {
            // Ловим исключения из конструкторов и сеттеров
            std::cerr << "Ошибка: " << e.what() << "\n";
        }
    }

    // Освобождение памяти перед выходом
    delete t1;
    delete rect;
    return 0;
}