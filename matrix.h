#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <stdexcept>

class Matrix {
private:
    int rows;
    int cols;
    double** data;

    void allocateMemory(); // ��������� ������
    void freeMemory(); // ������������� ������

public:
    // ������������ � ����������
    Matrix(int rows, int cols);
    Matrix(int rows, int cols, double* arr);
    Matrix(int rows, int cols, double*& arr);
    Matrix(int rows, int cols, std::initializer_list<double> values);
    Matrix(const Matrix& other);
    Matrix& operator=(const Matrix& other);
    ~Matrix();

    // ������
    int getRows() const; // �������� ���������� �����
    int getCols() const; // �������� ���������� ��������
    double& at(int row, int col); // ������� �� ������� (�������/���������) ���������� ���� ������
    const double& at(int row, int col) const; // ��� ������������ ��������� �� ������� (�������/���������)  ���������� ���� ������
    void print() const; // ������� ������� � �������
    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix); //���������� print()

    //������������ �������������� ������
    void multiplyRow(int row, double scalar); // �������� ������ �� ������
    void multiplyColumns(int col, double scalar); // �������� ������� �� ������
    void swapRows(int row1, int row2); // �������� ������ �������
    void swapColumns(int col1, int col2); // �������� ������� �������
    void addRowMultiple(int sourceRow, int targetRow, double scalar); // ����������� ������ (c ����)
    void addColumnMultiple(int sourceCol, int targetCol, double scalar); // ����������� ������� (c ����)

    double trace() const; // ���������� ����� �������
    Matrix transpose() const; // ����������������� �������
    double determinant() const; // ������������ ������� ������
    Matrix inverse() const; // �������� �������

    // ���������

    double& operator()(int row, int col); // ������� �� ������� (�������/���������) ���������� ����� ���������� (n, m)
    const double& operator()(int row, int col) const; // ��� ������������ ��������� �� ������� (�������/���������) ���������� ����� ���������� (n, m)

    // ���������� ���������
    bool operator>(const Matrix& other) const;
    bool operator<(const Matrix& other) const;
    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;


    // ��������� ������������� � �������������
    Matrix& operator++();    // ���������� ��������� (++m)
    Matrix operator++(int); // ����������� ��������� (m++)
    Matrix& operator--();    // ���������� ��������� (--m)
    Matrix operator--(int); // ����������� ��������� (m--)

    // �������������� ���������
    Matrix operator+(const Matrix& other) const; // �������� �������� ������
    Matrix operator-(const Matrix& other) const; // �������� ��������� ������
    Matrix operator*(const Matrix& other) const; // �������� ��������� ������
    Matrix operator/(const Matrix& other) const; // �������� ������� ������
    Matrix& operator+=(const Matrix& other); // ���������� � �����������
    Matrix& operator-=(const Matrix& other); // ���������� � �����������

    Matrix operator*(double scalar) const; // ��������� ������� �� �����
    friend Matrix operator*(double scalar, const Matrix& matrix); // ��������� "����� �� �������" (���������� �����������)
};

#endif // MATRIX_H