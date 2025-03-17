#include "matrix.h"

int main() {
    try {
        setlocale(LC_ALL, "Russian");

        Matrix a(3, 3);
        a(1, 0) = 2;
        a(2, 0) = 3;
        a(2, 0) = 4;
        a(1, 1) = 5;
        a(2, 1) = 6;
        a(2, 2) = 9;
        std::cout << "Матрица a:" << std::endl << a << std::endl;

        double arr[]{1, 2, 3, 4, 5, 6, 7, 8, 9};
        Matrix b(3, 3, arr);
        std::cout << "Матрица b:" << std::endl << b << std::endl;

        Matrix c1(2, 3, { 1, 2, 3, 4, 5, 6 });
        std::cout << "Матрица c1:" << std::endl << c1 << std::endl;

        Matrix c2 = c1;
        c2.at(0, 0) = 0;
        c2.at(1, 1) = 4;
        std::cout << "Матрица c2:" << std::endl << c1 << std::endl;


        Matrix d1(2, 2, { 4, 5,
                          7, 3 });
        std::cout << "Матрица d1:" << std::endl << d1 << std::endl;

        Matrix d2(2, 2, { 5, 7,
                          9, 10 });
        std::cout << "Матрица d2:" << std::endl << d2 << std::endl;

        std::cout << "Определитель матрицы a:" << std::endl << a.determinant() << std::endl;
        std::cout << "Определитель матрицы d2:" << std::endl << d2.determinant() << std::endl;

        std::cout << "Матрица 3*a + b:" << std::endl << 3*a+b << std::endl;

        std::cout << "Матрица a - ++b  (++b = b + E):" << std::endl << a - ++b << std::endl;

        std::cout << "Транспонированная матрица с2:" << std::endl << c2.transpose() << std::endl;

        std::cout << "Матрица с1 * с2^T:" << std::endl << c1 * c2.transpose() << std::endl;

        std::cout << "Матрица d1 / d2" << std::endl << d1 / d2 << std::endl;

        Matrix del(3, 3);
        del += a;
        del -= b;

        std::cout << "Матрица del" << std::endl <<del << std::endl;

        std::cout << "Сравним матрицы a и b" << std::endl;
        if (a > b) {
            std::cout << "a больше b" << std::endl;
        }
        else
        {
            std::cout << "a не больше b" << std::endl;
        }

        std::cout << "Сравним матрицы d1 и d2" << std::endl;
        if (d1 < d2) {
            std::cout << "d1 меньше d1" << std::endl;
        }
        else
        {
            std::cout << "d1 не меньше d2" << std::endl;
        }

        std::cout << "Обратная матрица ++b:" << std::endl << b.inverse() << std::endl; // ранее уже использовалось ++b

        std::cout << "След матрицы a" << std::endl << a.trace() << std::endl;

        std::cout << "Элементарные преобразований для матрицы a" << std::endl << a << std::endl;

        a.multiplyRow(1, 0.5);
        std::cout << "Вторую строку матрицы умножим на 0.5" << std::endl << a << std::endl;
        a.swapColumns(0, 1);
        std::cout << "Затем поменяем местами 1 и 3 стоблцы" << std::endl << a << std::endl;
        a.addColumnMultiple(0, 2, -2);
        std::cout << "Затем поменяем местами 1 и 3 стоблцы" << std::endl << a << std::endl;
        std::cout << "Присуствуют также аналогичные реализации для строк(солбцов)" << std::endl;

        std::cout <<std::endl<< "Приведем пример использования класса для решения задач\nРешим систему уравнений матричным методом" << std::endl;

        std::cout << std::endl << "Система:\n3x-2y+4z=21\n3x+4y-2z=9\n2x-y-z=10\n" << std::endl;
        Matrix A(3, 3, { 3, -2, 4, 3, 4, -2, 2, -1, -1 });
        Matrix B(3, 1, {21, 9, 10});
        
        double D = A.determinant();
        std::cout << "D = " << D << std::endl;
        if (D != 0) {
            std::cout << "Определитель не равен 0, система имеет единственное решение\n X = A^-1 * B\n";
            std::cout << "A:\n" << A << std::endl;
            Matrix Ai = A.inverse();
            std::cout << "A^-1:\n" << Ai << std::endl;
            Matrix X = Ai * B;
            std::cout << "Корни уравнения:\n" << X <<std::endl;
        }
    }


    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Unknown Error"<< std::endl;
    }
    return 0;
}