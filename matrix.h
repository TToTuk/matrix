#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <stdexcept>

class Matrix {
private:
    int rows;
    int cols;
    double** data;

    void allocateMemory(); // Выделение памяти
    void freeMemory(); // Освовбождение памяти

public:
    // Конструкторы и деструктор
    Matrix(int rows, int cols);
    Matrix(int rows, int cols, double* arr);
    Matrix(int rows, int cols, double*& arr);
    Matrix(int rows, int cols, std::initializer_list<double> values);
    Matrix(const Matrix& other);
    Matrix& operator=(const Matrix& other);
    ~Matrix();

    // Методы
    int getRows() const; // Получить количество строк
    int getCols() const; // Получить количество столбцов
    double& at(int row, int col); // Элемент на позиции (вернуть/присвоить) реализация виде метода
    const double& at(int row, int col) const; // Для констнантных элементов на позиции (вернуть/присвоить)  реализация виде метода
    void print() const; // Вывести матрицу в консоль
    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix); //Аналогично print()

    //элементарные преобразования матриц
    void multiplyRow(int row, double scalar); // Умножить строку на скаляр
    void multiplyColumns(int col, double scalar); // Умножить столбец на скаляр
    void swapRows(int row1, int row2); // Поменять строки местами
    void swapColumns(int col1, int col2); // Поменять столбцы местами
    void addRowMultiple(int sourceRow, int targetRow, double scalar); // Прибавление строки (c коэф)
    void addColumnMultiple(int sourceCol, int targetCol, double scalar); // Прибавление столбца (c коэф)

    double trace() const; // Нахождение следа матрицы
    Matrix transpose() const; // Транспонированная матрица
    double determinant() const; // Определитель методом Гаусса
    Matrix inverse() const; // Обратная матрица

    // Операторы

    double& operator()(int row, int col); // Элемент на позиции (вернуть/присвоить) реализация ввиде перегрузки (n, m)
    const double& operator()(int row, int col) const; // Для констнантных элементов на позиции (вернуть/присвоить) реализация ввиде перегрузки (n, m)

    // Логические операторы
    bool operator>(const Matrix& other) const;
    bool operator<(const Matrix& other) const;
    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;


    // Операторы инкрементации и декрементации
    Matrix& operator++();    // Префиксный инкремент (++m)
    Matrix operator++(int); // Постфиксный инкремент (m++)
    Matrix& operator--();    // Префиксный декремент (--m)
    Matrix operator--(int); // Постфиксный декремент (m--)

    // математические операторы
    Matrix operator+(const Matrix& other) const; // Оператор сложения матриц
    Matrix operator-(const Matrix& other) const; // Оператор вычитания матриц
    Matrix operator*(const Matrix& other) const; // Оператор умножения матриц
    Matrix operator/(const Matrix& other) const; // Оператор деления матриц
    Matrix& operator+=(const Matrix& other); // Арифметика с накоплением
    Matrix& operator-=(const Matrix& other); // Арифметика с накоплением

    Matrix operator*(double scalar) const; // Умножение матрицы на число
    friend Matrix operator*(double scalar, const Matrix& matrix); // Умножение "числа на матрицу" (аналогично предыдушему)
};

#endif // MATRIX_H