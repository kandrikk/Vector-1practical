#include "../Include/Vector.h"

// Деструктор
Vector::~Vector()
{
    delete[] _data;
};

    //! Конструктор с параметрами
Vector::Vector(const ValueType* rawArray, const size_t size, float coef)
    : _size(size), _capacity(size), 
    _multiplicativeCoef(coef)
{
    if (_size > 0)
    {
        _data = new ValueType[_capacity];
        for (size_t i = 0; i < size; ++i)
        {
            _data[i] = rawArray[i];
        };
    }
};

    //! Конструктор копирования
    //! \param other - копируемый объект
Vector::Vector(const Vector& other)
    : _size(other._size), _capacity(other._size), 
    _multiplicativeCoef(other._multiplicativeCoef)
{
    // Если размер 0
    if (_size == 0) 
    {
        _data = nullptr;
        return;
    };

    _data = new ValueType[_size];
    for (size_t i = 0; i < _size; ++i)
    {
        _data[i] = other._data[i];
    }
};

    //! Оператор присваивания копированием
    //! \param other - копируемый объект
Vector& Vector::operator=(const Vector& other)
{
    if (this == &other)
    {
        return *this;
    }

    if (this != &other)
    {
        delete[] _data;
        _size = other._size;
        _capacity = other._size;
        _multiplicativeCoef = other._multiplicativeCoef;

        if (_size > 0) 
        {
            _data = new ValueType[_size];
            for (size_t i = 0; i < other._size; ++i)
            {
                _data[i] = other._data[i];
            };
        } 
        else
        {
            _data = nullptr;
        };
    };
    return *this;
};

//! Конструктор перемещения
//! \param other - перемещаемый объект
Vector::Vector(Vector&& other) noexcept
    : _data(other._data), _size(other._size), _capacity(other._capacity), 
    _multiplicativeCoef(other._multiplicativeCoef)
{
    other._data = nullptr;
    other._size = 0;
    other._capacity = 0;
};

//! Оператор присваивания перемещением
//! \param other - перемещаемый объект
Vector& Vector::operator=(Vector&& other) noexcept
{
    if (this != &other)
    {
        delete[] _data;

        _data = other._data;
        _size = other._size;
        _capacity = other._capacity;
        _multiplicativeCoef = other._multiplicativeCoef;

        other._data = nullptr;
        other._size = 0;
        other._capacity = 0;        
    };
    return *this;
};

// ======================================================================================================================
// OPERATOR

    //! Доступ к элементу по индексу
ValueType& Vector::operator[](size_t idx)
{
    if (_size <= idx) {std::cout << "Индекс неподходит\n";};
    return _data[idx];
};

    //! Доступ к элементу по индексу
const ValueType& Vector::operator[](size_t idx) const
{
    if (_size <= idx) {std::cout << "Индекс неподходит\n";};
    return _data[idx];
};

// OPERATOR
// ======================================================================================================================
// ITERATOR

Vector::Iterator::Iterator(ValueType* ptr) : _ptr(ptr) {}

ValueType& Vector::Iterator::operator*()
{
    return *_ptr;
};

const ValueType& Vector::Iterator::operator*() const
{
    return *_ptr;
};

ValueType* Vector::Iterator::operator->()
{
    return _ptr;
};

const ValueType* Vector::Iterator::operator->() const
{
    return _ptr;
};
Vector::Iterator Vector::Iterator::operator++()
{
    ++_ptr;
    return *this;
};
Vector::Iterator Vector::Iterator::operator++(int)
{
    Iterator tmp = *this;
    ++_ptr;
    return *this;
};
bool Vector::Iterator::operator==(const Iterator& other) const
{
    return _ptr == other._ptr;
};
bool Vector::Iterator::operator!=(const Iterator& other) const
{
    return _ptr != other._ptr;
};

	//! Получить итератор на начало вектора
Vector::Iterator Vector::begin()
{
    return Iterator(_data);
};

	//! Получить итератор на элемент вектора, следующий за последним
Vector::Iterator Vector::end()
{
    return Iterator(_data + _size);
};

// ITERATOR
// ======================================================================================================================
// FUNCTION

void Vector::printVec() const {  // Добавлен const, так как метод не изменяет вектор
    std::cout << "{ ";
    for (size_t i = 0; i < _size; ++i) {  // Используем size_ вместо vector.size()
        std::cout << _data[i];            // Используем data_ вместо vector[i]
        if (i != _size - 1) {             // Добавляем разделитель, кроме последнего элемента
            std::cout << ", ";
        }
    }
    std::cout << " }" << std::endl;       // Фигурная скобка и перенос строки
}

size_t Vector::size() const
{
    return _size;
};

size_t Vector::capacity() const
{
    return _capacity;
};

double Vector::loadFactor() const
{
    if (_capacity == 0) {return 0.0;};
    return double(_size) / double(_capacity);
};

void Vector::shrinkToFit()
{
    if (_size == _capacity) {return;}

    if (_size == 0)
    {
        delete[] _data;
        _data = nullptr;
        _capacity = 0;
        return;
    }

    ValueType* new_data = new ValueType[_size];
    for (size_t i = 0; i < _size; ++i)
    {
        new_data[i] = _data[i];
    };

    delete[] _data;
    _data = new_data;
    _capacity = _size;
};

