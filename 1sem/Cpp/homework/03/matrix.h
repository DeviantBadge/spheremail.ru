#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <exception>


//*******************************************************************************
//                              Matrix Row
//*******************************************************************************

class MatrixRow {
private:
    std::vector<int> row_values;
public:
    MatrixRow(std::size_t cols);

    int &operator[](std::size_t i);

    const int &operator[](std::size_t i) const;

    MatrixRow &operator*=(int value);

    bool operator==(const MatrixRow &other) const;

    bool operator!=(const MatrixRow &other) const;
};

MatrixRow::MatrixRow(std::size_t cols) :
        row_values(cols, 0) {
}

int &MatrixRow::operator[](std::size_t i) {
    if (i >= row_values.size())
        throw std::out_of_range("");
    return row_values[i];
}

const int &MatrixRow::operator[](std::size_t i) const {
    if (i >= row_values.size())
        throw std::out_of_range("");
    return row_values[i];
}

MatrixRow &MatrixRow::operator*=(int value) {
    for (auto &row_value: row_values)
        row_value *= value;
    return *this;
}

bool MatrixRow::operator==(const MatrixRow &other) const {
    if (row_values.size() != other.row_values.size())
        return false;
    for (int i = 0; i < row_values.size(); i++)
        if (row_values[i] != other.row_values[i])
            return false;
    return true;
}

bool MatrixRow::operator!=(const MatrixRow &other) const {
    return !((*this) == other);
}


//*******************************************************************************
//                                  Matrix
//*******************************************************************************

class Matrix {
private:

public:
    std::vector <MatrixRow> values;
    std::size_t rows_amount;
    std::size_t cols_amount;

public:

    Matrix(std::size_t rows, std::size_t cols);

    std::size_t getRows() const;

    std::size_t getColumns() const;

    MatrixRow &operator[](std::size_t i);

    const MatrixRow &operator[](std::size_t i) const;

    Matrix &operator*=(int value);

    bool operator==(const Matrix &other) const;

    bool operator!=(const Matrix &value) const;
};

Matrix::Matrix(std::size_t rows, std::size_t cols) :
        values(rows, MatrixRow(cols)),
        rows_amount(rows),
        cols_amount(cols) {
}

std::size_t Matrix::getRows() const {
    return rows_amount;
}

std::size_t Matrix::getColumns() const {
    return cols_amount;
}

MatrixRow &Matrix::operator[](std::size_t i) {
    if (i >= rows_amount)
        throw std::out_of_range("");
    return values[i];
}

const MatrixRow &Matrix::operator[](std::size_t i) const {
    if (i >= rows_amount)
        throw std::out_of_range("");
    return values[i];
}

Matrix &Matrix::operator*=(int value) {
    for (auto &row: values)
        row *= value;
    return (*this);
}

bool Matrix::operator==(const Matrix &other) const {
    if (rows_amount != other.getRows() ||
        cols_amount != other.getColumns())
        return false;
    for (int i = 0; i < rows_amount; i++)
        if (values[i] != other.values[i])
            return false;
    return true;
}

bool Matrix::operator!=(const Matrix &value) const {
    return !((*this) == value);
}

#endif