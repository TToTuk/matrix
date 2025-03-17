#include "matrix.h"
#include <cmath>

class matrixExeption : public std::exception
{
public:
    matrixExeption(const std::string& message) : message{ message }
    {}
    const char* what() const noexcept override
    {
        return message.c_str();  //�������� �� std::string ������ const char*
    }
private:
    std::string message;  //��������� �� ������
};

// ��������� ������

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

// ����������� ������ �������
Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols) { // � ������� : �� �������� �������� ��������� � ����������� ������ � �������� ������
    if (rows <= 0 || cols <= 0) {
        throw matrixExeption("Rows and columns must be greater than 0");
    }
    allocateMemory();
}

// ������������ � �������������� �������� �� �������
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
// ������������ � �������������� �������� �� ������� �����������������������
Matrix::Matrix(int rows, int cols, double*& arr) : rows(rows), cols(cols) {
    if (rows <= 0 || cols <= 0) {
        throw matrixExeption("Rows and columns must be greater than 0");
    }

    // ��������� `data` �� ���������� ������, ������������ ��� �� ������� � ��������
    data = new double* [rows];
    for (int i = 0; i < rows; ++i) {
        data[i] = &arr[i * cols];
    }
}

// ����������� � �������������� �������� �� ������
Matrix::Matrix(int rows, int cols, std::initializer_list<double> values) : rows(rows), cols(cols) {

    if (rows <= 0 || cols <= 0) {
        throw matrixExeption("Rows and columns must be greater than 0");
    }

    if (values.size() != static_cast<size_t>(rows * cols)) {
        throw matrixExeption("Number of values does not match matrix dimensions");
    }

    allocateMemory();

    // ���������� ������� �� ������ ��������
    auto it = values.begin();
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            data[i][j] = *it;
            ++it;
        }
    }
}

// ����������� �����������
Matrix::Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
    allocateMemory();
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            data[i][j] = other.data[i][j];
        }
    }
}

// �������� ������������
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

// ����������
Matrix::~Matrix() {
    freeMemory();
}

// ������

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

// ������� ��� ������ �����
void Matrix::swapRows(int row1, int row2) {
    if (row1 < 0 || row1 >= rows || row2 < 0 || row2 >= rows) {
        throw matrixExeption("Row indices are out of range");
    }

    std::swap(data[row1], data[row2]); // ������ ��������� �� ������
}

// ������� ��� ������ ��������
void Matrix::swapColumns(int col1, int col2) {
    if (col1 < 0 || col1 >= cols || col2 < 0 || col2 >= cols) {
        throw matrixExeption("Column indices are out of range");
    }

    // ����� �������� ��������
    for (int i = 0; i < rows; ++i) {
        std::swap(data[i][col1], data[i][col2]);
    }
}

// ��������� ������ �� �����
void Matrix::multiplyRow(int row, double scalar) {
    if (row < 0 || row >= rows) {
        throw matrixExeption("Row index is out of range");
    }

    for (int j = 0; j < cols; ++j) {
        data[row][j] *= scalar;
    }
}

// ��������� ������� �� �����
void Matrix::multiplyColumns(int col, double scalar) {
    if (col < 0 || col >= cols) {
        throw matrixExeption("Column index is out of range");
    }

    for (int i = 0; i < rows; ++i) {
        data[i][col] *= scalar;
    }
}

// ����������� � ������ ������ ������, ���������� �� �����������
void Matrix::addRowMultiple(int sourceRow, int targetRow, double scalar) {
    if (targetRow < 0 || targetRow >= rows || sourceRow < 0 || sourceRow >= rows) {
        throw matrixExeption("Row indices are out of range");
    }

    for (int j = 0; j < cols; ++j) {
        data[targetRow][j] += scalar * data[sourceRow][j];
    }
}

// ����������� � ������� ������� �������, ����������� �� �����������
void Matrix::addColumnMultiple(int sourceCol, int targetCol, double scalar) {
    if (targetCol < 0 || targetCol >= cols || sourceCol < 0 || sourceCol >= cols) {
        throw matrixExeption("Column indices are out of range");
    }

    for (int i = 0; i < rows; ++i) {
        data[i][targetCol] += scalar * data[i][sourceCol];
    }
}

// ���������� ����� �������
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

// ����������������
Matrix Matrix::transpose() const {
    Matrix result(cols, rows); // ������� �������� �������
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.data[j][i] = data[i][j]; // ������������ ��������
        }
    }
    return result;
}

// ������������ ������� ������
double Matrix::determinant() const {
    if (rows != cols) {
        throw matrixExeption("Determinant is defined only for square matrices");
    }

    // �������� ������� ������� ��� ������
    Matrix temp(*this);
    double det = 1.0;
    int n = rows;

    // ������ ��� ������
    for (int k = 0; k < n; ++k) {
        // ����� ������������� �������� � ������� �������
        int maxRow = k;
        for (int i = k + 1; i < n; ++i) {
            if (std::fabs(temp.at(i, k)) > std::fabs(temp.at(maxRow, k))) {
                maxRow = i;
            }
        }

        // ���� ������� ������� ����� 0, ������������ ����� 0
        if (std::fabs(temp.at(maxRow, k)) < 1e-9) {
            return 0.0;
        }

        // ���� ������� ������ �� ������������, ������ ������ �������
        if (maxRow != k) {
            temp.swapRows(k, maxRow);
            det *= -1; // ������ ���� ������������
        }

        // ����������� ������� ������ ���, ����� ������� ������� ���� ����� 1
        double diagElement = temp.at(k, k);
        det *= diagElement; // �������� ������������ �� ������������ �������
        temp.multiplyRow(k, 1.0 / diagElement);

        // �������� �������� ���� �������� � ������� �������
        for (int i = k + 1; i < n; ++i) {
            double num = temp.at(i, k);
            temp.addRowMultiple(i, k, -num); // �������� ������� ������
        }
    }

    return det;
}

// ���������� �������� ������� � �������������� ������������ ��������������
Matrix Matrix::inverse() const {
    if (rows != cols) {
        throw matrixExeption("Inverse is defined only for square matrices");
    }

    int n = rows;
    Matrix augmented(n, 2 * n); // ������ ����������� ������� (A | I)

    // ��������� ����������� �������: ����� ����� � A, ������ ����� � E
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            augmented.at(i, j) = data[i][j];       // ����� ����� � A
            augmented.at(i, n + j) = (i == j) ? 1 : 0; // ������ ����� � E
        }
    }

    // ������ ���: ���������� � ������������ ����
    for (int k = 0; k < n; ++k) {
        // ����� ������ � ������������ ��������� � ������� �������
        int maxRow = k;
        for (int i = k + 1; i < n; ++i) {
            if (std::fabs(augmented.at(i, k)) > std::fabs(augmented.at(maxRow, k))) {
                maxRow = i;
            }
        }

        // ���� ������� �� ��������� ����� 0, �������� ������� ����������� ��������
        if (std::fabs(augmented.at(maxRow, k)) < 1e-9) {
            throw matrixExeption("Matrix is singular and cannot be inverted");
        }

        // ������ ������ �������, ���� ��� ����������
        if (maxRow != k) {
            augmented.swapRows(k, maxRow);
        }

        // ����������� ������� ������
        double diagElement = augmented.at(k, k);
        for (int j = 0; j < 2 * n; ++j) {
            augmented.at(k, j) /= diagElement;
        }

        // �������� �������� ���� ��������
        for (int i = k + 1; i < n; ++i) {
            double num = augmented.at(i, k);
            for (int j = 0; j < 2 * n; ++j) {
                augmented.at(i, j) -= num * augmented.at(k, j);
            }
        }
    }

    // �������� ���. ���������� � ��������� �������
    for (int k = n - 1; k >= 0; --k) {
        for (int i = k - 1; i >= 0; --i) {
            double num = augmented.at(i, k);
            for (int j = 0; j < 2 * n; ++j) {
                augmented.at(i, j) -= num * augmented.at(k, j);
            }
        }
    }

    // ��������� �������� �������
    Matrix inverseMatrix(n, n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            inverseMatrix.at(i, j) = augmented.at(i, n + j);
        }
    }

    return inverseMatrix;
}


// ���������
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
        throw std::invalid_argument("Matrix dimensions must match for comparison"); // ������������ ���������� �.�. �������� �����������
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (data[i][j] <= other.data[i][j]) {
                return false; // ���� ���� �� ���� ������� �� ������, ���������� false
            }
        }
    }
    return true; // ��� �������� ������
}

bool Matrix::operator<(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Matrix dimensions must match for comparison"); // ������������ ���������� �.�. �������� �����������
    }


    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (data[i][j] >= other.data[i][j]) {
                return false; // ���� ���� �� ���� ������� �� ������, ���������� false
            }
        }
    }
    return true; // ��� �������� ������
}

bool Matrix::operator==(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        return false; // ������� ������� ������� �� �����
    } // �� ����������� ���������� �.�. ��������� ��������

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (data[i][j] != other.data[i][j]) {
                return false; // ������� ������������ ���������
            }
        }
    }
    return true; // ��� �������� �����
}

bool Matrix::operator!=(const Matrix& other) const {
    return !(*this == other); // ���������� ==
}

// ���������� ��������� (++m): ����������� ��������� �������
Matrix& Matrix::operator++() {
    if (rows != cols) {
        throw matrixExeption("Increment is defined only for square matrices");
    }
    for (int i = 0; i < rows; ++i) {
        ++data[i][i]; // ���������� 1 � ������������ ���������
    }
    return *this; // ���������� ������� ������
}

// ����������� ��������� (m++): ����������� ��������� �������
Matrix Matrix::operator++(int) {
    Matrix temp(*this);
    ++(*this);
    return temp;
}

// ���������� ��������� (--m): ��������� ��������� �������
Matrix& Matrix::operator--() {
    if (rows != cols) {
        throw matrixExeption("Decrement is defined only for square matrices");
    }
    for (int i = 0; i < rows; ++i) {
        --data[i][i];
    }
    return *this;
}

// ����������� ��������� (m--): ��������� ��������� �������
Matrix Matrix::operator--(int) {
    Matrix temp(*this);
    --(*this);
    return temp;
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    matrix.print(); // ����� ������� print ��� ������ �������
    return os;      // ������� ������ ��� ���������� �������
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
    // ���������, ��� ������ ������� ����������
    if (other.rows != other.cols) {
        throw matrixExeption("The divisor matrix must be square");
    }

    // �������� ������ ������� �� ��������
    return *this * other.inverse();
}

//���������� � ����������� (+=)
Matrix& Matrix::operator+=(const Matrix& other) {
    if (rows != other.rows || cols != other.cols) {
        throw matrixExeption("Matrix dimensions must match for addition");
    }
    *this = *this + other;
    return *this; // ���������� ������ �� ������� ������
}

//���������� � ����������� (-=)
Matrix& Matrix::operator-=(const Matrix& other) {
    if (rows != other.rows || cols != other.cols) {
        throw matrixExeption("Matrix dimensions must match for subtraction");
    }
    *this = *this - other;
    return *this; // ���������� ������ �� ������� ������
}


// ��������� ������� �� �����
Matrix Matrix::operator*(double scalar) const {
    Matrix result(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result.at(i, j) = data[i][j] * scalar;
        }
    }
    return result;
}
// ��������� ����� �� �������
Matrix operator*(double scalar, const Matrix& matrix) {
    Matrix result(matrix.rows, matrix.cols);
    for (int i = 0; i < matrix.rows; ++i) {
        for (int j = 0; j < matrix.cols; ++j) {
            result.at(i, j) = matrix.data[i][j] * scalar;
        }
    }
    return result;
}