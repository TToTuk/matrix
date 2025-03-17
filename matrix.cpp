#include "matrix.h"
#include <cmath>

class matrixExeption : public std::exception
{
public:
    matrixExeption(const std::string& message) : message{ message }
    {}
    const char* what() const noexcept override
    {
        return message.c_str();  //получаем из std::string строку const char*
    }
private:
    std::string message;  //сообщение об ошибке
};

// Приватные методы

void Matrix::allocateMemory() {
    data = new double* [rows];
    if (data == nullptr) throw matrixExeption("Memory not allocated");
    for (int i = 0; i < rows; ++i) {
        data[i] = new double[cols]();
        if (data[i] == nullptr) throw matrixExeption("Memory not allocated");
    }
}

void Matrix::freeMemory() {
    for (int i = 0; i < rows; ++i) {
        delete[] data[i];
    }
    delete[] data;
}

// Конструктор пустой матрицы
Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols) { // с помощью : мы напрямую передаем введенные в консткуктор данные в элементы класса
    if (rows <= 0 || cols <= 0) {
        throw matrixExeption("Rows and columns must be greater than 0");
    }
    allocateMemory();
}

// ККонструктор с инициализацией значений из массива
Matrix::Matrix(int rows, int cols, double* arr) : rows(rows), cols(cols){

    if (rows <= 0 || cols <= 0) {
        throw matrixExeption("Rows and columns must be greater than 0");
    }

    allocateMemory();
    int c = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            data[i][j] = arr[c++];
        }
    }
}
// ККонструктор с инициализацией значений из массива объявленногодинамически
Matrix::Matrix(int rows, int cols, double*& arr) : rows(rows), cols(cols) {
    if (rows <= 0 || cols <= 0) {
        throw matrixExeption("Rows and columns must be greater than 0");
    }

    // Указываем `data` на переданный массив, распределяем его по строкам и столбцам
    data = new double* [rows];
    for (int i = 0; i < rows; ++i) {
        data[i] = &arr[i * cols];
    }
}

// Конструктор с инициализацией значений из списка
Matrix::Matrix(int rows, int cols, std::initializer_list<double> values) : rows(rows), cols(cols) {

    if (rows <= 0 || cols <= 0) {
        throw matrixExeption("Rows and columns must be greater than 0");
    }

    if (values.size() != static_cast<size_t>(rows * cols)) {
        throw matrixExeption("Number of values does not match matrix dimensions");
    }

    allocateMemory();

    // Заполнение матрицы из списка значений
    auto it = values.begin();
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            data[i][j] = *it;
            ++it;
        }
    }
}

// Конструктор копирования
Matrix::Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
    allocateMemory();
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            data[i][j] = other.data[i][j];
        }
    }
}

// Оператор присваивания
Matrix& Matrix::operator=(const Matrix& other) {
    if (this == &other) return *this;

    freeMemory();

    rows = other.rows;
    cols = other.cols;
    allocateMemory();

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            data[i][j] = other.data[i][j];
        }
    }

    return *this;
}

// Деструктор
Matrix::~Matrix() {
    freeMemory();
}

// Методы

int Matrix::getRows() const {
    return rows;
}

int Matrix::getCols() const {
    return cols;
}

double& Matrix::at(int row, int col) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        throw matrixExeption("Index out of range");
    }
    return data[row][col];
}

const double& Matrix::at(int row, int col) const {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        throw matrixExeption("Index out of range");
    }
    return data[row][col];
}

void Matrix::print() const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Функция для обмена строк
void Matrix::swapRows(int row1, int row2) {
    if (row1 < 0 || row1 >= rows || row2 < 0 || row2 >= rows) {
        throw matrixExeption("Row indices are out of range");
    }

    std::swap(data[row1], data[row2]); // Меняем указатели на строки
}

// Функция для обмена столбцов
void Matrix::swapColumns(int col1, int col2) {
    if (col1 < 0 || col1 >= cols || col2 < 0 || col2 >= cols) {
        throw matrixExeption("Column indices are out of range");
    }

    // Обмен значений столбцов
    for (int i = 0; i < rows; ++i) {
        std::swap(data[i][col1], data[i][col2]);
    }
}

// Умножение строки на число
void Matrix::multiplyRow(int row, double scalar) {
    if (row < 0 || row >= rows) {
        throw matrixExeption("Row index is out of range");
    }

    for (int j = 0; j < cols; ++j) {
        data[row][j] *= scalar;
    }
}

// Умножение столбца на число
void Matrix::multiplyColumns(int col, double scalar) {
    if (col < 0 || col >= cols) {
        throw matrixExeption("Column index is out of range");
    }

    for (int i = 0; i < rows; ++i) {
        data[i][col] *= scalar;
    }
}

// Прибавление к строке другой строки, умноженной на коэффициент
void Matrix::addRowMultiple(int sourceRow, int targetRow, double scalar) {
    if (targetRow < 0 || targetRow >= rows || sourceRow < 0 || sourceRow >= rows) {
        throw matrixExeption("Row indices are out of range");
    }

    for (int j = 0; j < cols; ++j) {
        data[targetRow][j] += scalar * data[sourceRow][j];
    }
}

// Прибавление к столбцу другого столбца, умноженного на коэффициент
void Matrix::addColumnMultiple(int sourceCol, int targetCol, double scalar) {
    if (targetCol < 0 || targetCol >= cols || sourceCol < 0 || sourceCol >= cols) {
        throw matrixExeption("Column indices are out of range");
    }

    for (int i = 0; i < rows; ++i) {
        data[i][targetCol] += scalar * data[i][sourceCol];
    }
}

// Нахождение следа матрицы
double Matrix::trace() const {
    if (rows != cols) {
        throw matrixExeption("Trace is defined only for square matrices");
    }

    double traceSum = 0.0;
    for (int i = 0; i < rows; ++i) {
        traceSum += data[i][i];
    }

    return traceSum;
}

// Транспонирование
Matrix Matrix::transpose() const {
    Matrix result(cols, rows); // Размеры меняются местами
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.data[j][i] = data[i][j]; // Переставляем элементы
        }
    }
    return result;
}

// Определитель методом Гаусса
double Matrix::determinant() const {
    if (rows != cols) {
        throw matrixExeption("Determinant is defined only for square matrices");
    }

    // Копируем текущую матрицу для работы
    Matrix temp(*this);
    double det = 1.0;
    int n = rows;

    // Прямой ход Гаусса
    for (int k = 0; k < n; ++k) {
        // Поиск максимального элемента в текущем столбце
        int maxRow = k;
        for (int i = k + 1; i < n; ++i) {
            if (std::fabs(temp.at(i, k)) > std::fabs(temp.at(maxRow, k))) {
                maxRow = i;
            }
        }

        // Если ведущий элемент равен 0, определитель равен 0
        if (std::fabs(temp.at(maxRow, k)) < 1e-9) {
            return 0.0;
        }

        // Если текущая строка не максимальная, меняем строки местами
        if (maxRow != k) {
            temp.swapRows(k, maxRow);
            det *= -1; // Меняем знак определителя
        }

        // Нормализуем текущую строку так, чтобы ведущий элемент стал равен 1
        double diagElement = temp.at(k, k);
        det *= diagElement; // Умножаем определитель на диагональный элемент
        temp.multiplyRow(k, 1.0 / diagElement);

        // Обнуляем элементы ниже текущего в текущем столбце
        for (int i = k + 1; i < n; ++i) {
            double num = temp.at(i, k);
            temp.addRowMultiple(i, k, -num); // Вычитаем текущую строку
        }
    }

    return det;
}

// Нахождение обратной матрицы с использованием элементарных преобразований
Matrix Matrix::inverse() const {
    if (rows != cols) {
        throw matrixExeption("Inverse is defined only for square matrices");
    }

    int n = rows;
    Matrix augmented(n, 2 * n); // Создаём расширенную матрицу (A | I)

    // Заполняем расширенную матрицу: левая часть — A, правая часть — E
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            augmented.at(i, j) = data[i][j];       // Левая часть — A
            augmented.at(i, n + j) = (i == j) ? 1 : 0; // Правая часть — E
        }
    }

    // Прямой ход: приведение к треугольному виду
    for (int k = 0; k < n; ++k) {
        // Поиск строки с максимальным элементом в текущем столбце
        int maxRow = k;
        for (int i = k + 1; i < n; ++i) {
            if (std::fabs(augmented.at(i, k)) > std::fabs(augmented.at(maxRow, k))) {
                maxRow = i;
            }
        }

        // Если элемент на диагонали равен 0, обратную матрицу невовзможно получить
        if (std::fabs(augmented.at(maxRow, k)) < 1e-9) {
            throw matrixExeption("Matrix is singular and cannot be inverted");
        }

        // Меняем строки местами, если это необходимо
        if (maxRow != k) {
            augmented.swapRows(k, maxRow);
        }

        // Нормализуем текущую строку
        double diagElement = augmented.at(k, k);
        for (int j = 0; j < 2 * n; ++j) {
            augmented.at(k, j) /= diagElement;
        }

        // Обнуляем элементы ниже текущего
        for (int i = k + 1; i < n; ++i) {
            double num = augmented.at(i, k);
            for (int j = 0; j < 2 * n; ++j) {
                augmented.at(i, j) -= num * augmented.at(k, j);
            }
        }
    }

    // Обратный ход. приведение к единичной матрице
    for (int k = n - 1; k >= 0; --k) {
        for (int i = k - 1; i >= 0; --i) {
            double num = augmented.at(i, k);
            for (int j = 0; j < 2 * n; ++j) {
                augmented.at(i, j) -= num * augmented.at(k, j);
            }
        }
    }

    // Извлекаем обратную матрицу
    Matrix inverseMatrix(n, n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            inverseMatrix.at(i, j) = augmented.at(i, n + j);
        }
    }

    return inverseMatrix;
}


// Операторы
double& Matrix::operator()(int row, int col) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        throw matrixExeption("Matrix indices out of range");
    }
    return data[row][col];
}

const double& Matrix::operator()(int row, int col) const {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        throw matrixExeption("Matrix indices out of range");
    }
    return data[row][col];
}

bool Matrix::operator>(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Matrix dimensions must match for comparison"); // Выбрасывваем исключение т.к. операция неприменима
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (data[i][j] <= other.data[i][j]) {
                return false; // Если хотя бы один элемент не больше, возвращаем false
            }
        }
    }
    return true; // Все элементы больше
}

bool Matrix::operator<(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Matrix dimensions must match for comparison"); // Выбрасывваем исключение т.к. операция неприменима
    }


    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (data[i][j] >= other.data[i][j]) {
                return false; // Если хотя бы один элемент не меньше, возвращаем false
            }
        }
    }
    return true; // Все элементы меньше
}

bool Matrix::operator==(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        return false; // Матрицы разного размера не равны
    } // Не выбрасываем исключение т.к. результат очевиден

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (data[i][j] != other.data[i][j]) {
                return false; // Найдено несовпадение элементов
            }
        }
    }
    return true; // Все элементы равны
}

bool Matrix::operator!=(const Matrix& other) const {
    return !(*this == other); // Используем ==
}

// Префиксный инкремент (++m): прибавление единичной матрицы
Matrix& Matrix::operator++() {
    if (rows != cols) {
        throw matrixExeption("Increment is defined only for square matrices");
    }
    for (int i = 0; i < rows; ++i) {
        ++data[i][i]; // Прибавляем 1 к диагональным элементам
    }
    return *this; // Возвращаем текущий объект
}

// Постфиксный инкремент (m++): прибавление единичной матрицы
Matrix Matrix::operator++(int) {
    Matrix temp(*this);
    ++(*this);
    return temp;
}

// Префиксный декремент (--m): вычитание единичной матрицы
Matrix& Matrix::operator--() {
    if (rows != cols) {
        throw matrixExeption("Decrement is defined only for square matrices");
    }
    for (int i = 0; i < rows; ++i) {
        --data[i][i];
    }
    return *this;
}

// Постфиксный декремент (m--): вычитание единичной матрицы
Matrix Matrix::operator--(int) {
    Matrix temp(*this);
    --(*this);
    return temp;
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    matrix.print(); // Вызов функции print для вывода матрицы
    return os;      // Возврат потока для цепочности вызовов
}

Matrix Matrix::operator+(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw matrixExeption("Matrix dimensions must match for addition");
    }

    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw matrixExeption("Matrix dimensions must match for addition");
    }

    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.data[i][j] = data[i][j] - other.data[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (cols != other.rows) {
        throw matrixExeption("Matrix dimensions must match for multiplication");
    }

    Matrix result(rows, other.cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < other.cols; ++j) {
            for (int k = 0; k < cols; ++k) {
                result.data[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }
    return result;
}
Matrix Matrix::operator/(const Matrix& other) const {
    // Проверяем, что вторая матрица квадратная
    if (other.rows != other.cols) {
        throw matrixExeption("The divisor matrix must be square");
    }

    // Умножаем первую матрицу на обратную
    return *this * other.inverse();
}

//Арифметика с накоплением (+=)
Matrix& Matrix::operator+=(const Matrix& other) {
    if (rows != other.rows || cols != other.cols) {
        throw matrixExeption("Matrix dimensions must match for addition");
    }
    *this = *this + other;
    return *this; // Возвращаем ссылку на текущий объект
}

//Арифметика с накоплением (-=)
Matrix& Matrix::operator-=(const Matrix& other) {
    if (rows != other.rows || cols != other.cols) {
        throw matrixExeption("Matrix dimensions must match for subtraction");
    }
    *this = *this - other;
    return *this; // Возвращаем ссылку на текущий объект
}


// Умножение матрицы на число
Matrix Matrix::operator*(double scalar) const {
    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.at(i, j) = data[i][j] * scalar;
        }
    }
    return result;
}
// Умножение числа на матрицу
Matrix operator*(double scalar, const Matrix& matrix) {
    Matrix result(matrix.rows, matrix.cols);
    for (int i = 0; i < matrix.rows; ++i) {
        for (int j = 0; j < matrix.cols; ++j) {
            result.at(i, j) = matrix.data[i][j] * scalar;
        }
    }
    return result;
}