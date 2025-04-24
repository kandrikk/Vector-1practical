#include "../Include/Vector.h"

    //! Деструктор
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

	//! Вставка в конец
void Vector::pushBack(const ValueType& value)
{
    if (_size == _capacity)
    {
        if (_capacity == 0)
        {
            _capacity = 1;
        }
        _capacity = _capacity * _multiplicativeCoef;

        ValueType* new_data = new ValueType[_capacity];

        for (size_t i = 0; i < _size; ++i)
        {
            new_data[i] = _data[i];
        }

         delete[] _data;
         _data = new_data;
    }

    _data[_size] = value;
    ++_size;
};

	//! Вставка в начало
void Vector::pushFront(const ValueType& value)
{
    if (_size == _capacity)
    {
        size_t new_capacity = _capacity == 0 ? 1 : _capacity * _multiplicativeCoef;
        ValueType* new_data = new ValueType[new_capacity];

        for (size_t i = 0; i < _size; ++i)
        {
            new_data[i + 1] = _data[i];
        }
        delete[] _data;
        _data = new_data;
        _capacity = new_capacity;
    }
    else
    {
        for (size_t i = _size; i > 0; --i)
        {
            _data[i] = _data[i - 1];
        }
    }

    _data[0] = value;
    ++_size;
};


	//! Вставка элемента value в позицию pos
void Vector::insert(const ValueType& value, size_t pos)
{
    if (pos > _size)
    {
        std::cout << "Ошибка [pos > _size\n"; 
    } 
    else
    {
        if (_capacity == 0)
        {
            _capacity = 1;
        } 
        if (_capacity == _size)
        {
            _capacity = _capacity * _multiplicativeCoef;
        } 
    
        ValueType* new_data = new ValueType[_capacity];

        for (size_t i = 0; i < pos; ++i)
        {
            new_data[i] = _data[i];
        }

        for (size_t i = pos; i < _size; ++i)
        {
            new_data[i+1] = _data[i];
        }
        delete[] _data;
        new_data[pos] = value;
        _data = new_data;
        ++_size;
    }
};

    //! Вставка массива элементов типа ValueType в позицию pos
void Vector::insert(const ValueType* values, size_t size, size_t pos)
{
    if (pos > _size)
    {
        std::cout << "Ошибка [pos > _size]\n"; 
    } 
    else if (values == nullptr && size > 0)
    {
        std::cout << "Ошибка [values == nullptr && size > 0]\n";
    }
    else
    {
        _size = _size + size;
        if (_capacity == 0)
        {
            _capacity = 1;
        } 
        if (_capacity == _size)
        {
            _capacity = _capacity * _multiplicativeCoef;
        } 
    
        ValueType* new_data = new ValueType[_capacity];

        for (size_t i = 0; i < pos; ++i)
        {
            new_data[i] = _data[i];
        }
        for (size_t i = pos; i < _size - size; ++i)
        {
            new_data[i + size] = _data[i];
        }
        for (size_t i = 0; i < size; ++i)
        {
            new_data[i + pos] = values[i];
        }
        delete[] _data;
        _data = new_data;
    }
};

	//! Вставка содержимого вектора в позицию pos
void Vector::insert(const Vector& vector, size_t pos)
{   
    if (pos > _size)
    {
        std::cout << "Ошибка [pos > _size]\n"; 
    } 
    else if (vector.size() == 0)
    {
        return;
    }
    else
    {
        
        _size = _size + vector._size;

        if (_capacity == 0)
        {
            _capacity = 1;
        } 
        if (_capacity <= _size)
        {
            _capacity = _size * _multiplicativeCoef;
        }

        ValueType* new_data = new ValueType[_capacity];

        for (size_t i = 0; i < pos; ++i)
        {
            new_data[i] = _data[i];
        }

        for (size_t i = pos; i < _size - vector._size; ++i)
        {
            new_data[i + vector._size] = _data[i];
        }

        for (size_t i = 0; i < vector._size; ++i)
        {
            new_data[i + pos] = vector._data[i];
        }

        delete[] _data;
        _data = new_data;
    }
};

	//! Удаление с конца
void Vector::popBack()
{
    if (_size > 0)
    {
        --_size;
    } else {
        std::cout << "Ошибка: PopBack(_size <= 0)\n";
    }
};

	//! Удаление из начала
void Vector::popFront()
{
    if (_size > 0)
    {
        for (size_t i = 1; i < _size; ++i)
        {
            _data[i-1] = _data[i];
        }
        --_size;
    } else {
        std::cout << "Ошибка: PopFront(_size <= 0)\n";
    }
};

    /*!
        \brief Удалить элемент(ы) из вектора
        \param pos: позиция начала удаляемого участка
        \param count: количество удаляемых элементов
        если (pos + count) > size, то элементы интервала [pos, size) должны быть удалены
    */
void Vector::erase(size_t pos, size_t count)
{
    if (pos >= _size)
    {
        std::cout << "Ошибка [pos >= _size]\n";
        return;
    }

    count = std::min(count, _size - pos);

    for (size_t i = pos; i < _size - count; ++i) 
    {
        _data[i] = std::move(_data[i + count]);
    }

    _size -= count;
};

    /*!
        \brief Удалить элемент(ы) из вектора
        \param beginPos: позиция начала удаляемого участка
        \param endPos: позиция окончания удаляемого участка
        Все элементы интервала [beginPos, endPos) должны быть удалены:
            [1, 2, 3, 4] -> erase(1, 3) -> [1, 4]
        если endPos > size, то элементы интервала [beginPos, size) должны быть удалены
    */
   void Vector::eraseBetween(size_t beginPos, size_t endPos) 
   {
    if (beginPos >= _size || beginPos >= endPos) {
        std::cout << "Ошибка [beginPos >= _size || beginPos >= endPos]\n";
        return;
    }

    endPos = std::min(endPos, _size);

    size_t count = endPos - beginPos + 1;

    for (size_t i = beginPos; i < _size - count; ++i) {
        _data[i] = std::move(_data[i + count]);
    }

    _size -= count;
};

	//! Количество элементов
size_t Vector::size() const
{
    return _size;
};
	//! Максимальное количество элементов
size_t Vector::capacity() const
{
    return _capacity;
};

	//! Фактор загруженности
double Vector::loadFactor() const
{
    if (_capacity == 0) {return 0.0;}
    double tmp = double(_size) / double(_capacity);
    return tmp;
};

    //! Доступ к элементу по индексу
ValueType& Vector::operator[](size_t idx)
{
    if (_size <= idx)
    {
        std::cout << "Индекс не подходит\n";
    }
    return _data[idx];
};

    //! Доступ к элементу по индексу
const ValueType& Vector::operator[](size_t idx) const
{
    if (_size < idx)
    {
        std::cout << "Индекс не подходит\n";
    }
    return _data[idx];
};

    //! Поиск первого вхождения значения
    //! \return - индекс элемента
long long Vector::find(const ValueType& value) const
{
    if (_size == 0)
    {
        std::cout << "Ошибка, вектор не имеет значений\n";
        return -1;
    }

    for (size_t i = 0; i < _size; ++i)
    {
        if (_data[i] == value)
        {
            return static_cast<long long>(i);
        }
    } 
    std::cout << "Элемента нет в векторе\n";
    return -1;
};

    //! Если capacity > _capacity, то выделить новый участок памяти размером capacity и перенести вектор туда, иначе - ничего
void Vector::reserve(size_t capacity)
{
    if (capacity > _capacity)
    {
        _capacity = capacity;
    }
};

	//! Уменьшить capacity до size
void Vector::shrinkToFit()
{
    _capacity = _size;
};

int main() {

    //! Конструктор без параметров
    Vector v1;
    std::cout << "\nVector v1 created successfully!\n";
    std::cout << "=====================================================================\n";

    //! Конструктор с параметрами
    double arr[] = {1.1, 2.2, 3.3};
    Vector v2(arr, 3);
    std::cout << "Конструктор с параметрами \nv2: ";
    for (size_t i = 0; i < v2.size(); ++i){
        std::cout << v2[i] << "  ";
    }
    std::cout << std::endl;
    std::cout << "=====================================================================\n";

    //Копирование
    Vector v3(v2);
    std::cout << "Копирование \nv3: ";
    for (size_t i = 0; i < v3.size(); ++i){
        std::cout << v2[i] << "  ";
    }
    std::cout << std::endl;
    std::cout << "=====================================================================\n";

    //PUSHBACK
    v3.pushBack(4.4);
    std::cout << "PushBack '4.4' in v3: ";
    for (size_t i = 0; i < v3.size(); ++i){
        std::cout << v3[i] << "  ";
    }
    std::cout << std::endl;
    std::cout << "=====================================================================\n";

    //PUSHFRONT
    v3.pushFront(5.5);
    std::cout << "Pushfront '5.5' in v3: ";
    for (size_t i = 0; i < v3.size(); ++i){
        std::cout << v3[i] << "  ";
    }
    std::cout << std::endl;
    std::cout << "=====================================================================\n";

    //POPBACK
    v3.popBack();
    std::cout << "PopBack in v3: ";
    for (size_t i = 0; i < v3.size(); ++i){
        std::cout << v3[i] << "  ";
    }
    std::cout << std::endl;
    std::cout << "=====================================================================\n";

    //POPBACK
    v3.popFront();
    std::cout << "PopFront in v3: ";
    for (size_t i = 0; i < v3.size(); ++i){
        std::cout << v3[i] << "  ";
    }
    std::cout << std::endl;
    std::cout << "=====================================================================\n";

    ////! Вставка элемента value в позицию pos
    v3.insert(2.5, 2);
    std::cout << "Вставка элемента value в позицию pos v3: ";
    for (size_t i = 0; i < v3.size(); ++i){
        std::cout << v3[i] << "  ";
    }
    std::cout << std::endl;
    std::cout << "=====================================================================\n";

    //! Вставка массива элементов типа ValueType в позицию pos
    double arr_2[] = {2.2, 3.3, 4.4};
    Vector v4;
    v4.pushFront(1.1);
    v4.pushBack(5.5);
    v4.insert(arr_2, 3, 1);
    std::cout << "Вставка массива элементов типа ValueType в позицию pos v4: \n";
    for (size_t i = 0; i < v4.size(); ++i){
        std::cout << v4[i] << "  ";
    }
    std::cout << std::endl;
    v4.popBack();
    v4.popFront();
    std::cout << "=====================================================================\n";

    Vector v5;
    v5.pushFront(1.1);
    v5.pushBack(5.5);
    v5.insert(v4, 1);
    std::cout << "//! Вставка содержимого вектора в позицию pos v5: \n";
    for (size_t i = 0; i < v5.size(); ++i){
        std::cout << v5[i] << "  ";
    }
    std::cout << std::endl;
    std::cout << "=====================================================================\n";

    v5.erase(1, 3);
    std::cout << "Удалить элемент(ы) из вектора v5: \n";
    for (size_t i = 0; i < v5.size(); ++i){
        std::cout << v5[i] << "  ";
    }
    std::cout << std::endl;
    v5.insert(v4, 1);
    std::cout << "=====================================================================\n";

    v5.eraseBetween(1, 3);
    std::cout << "eraseBetween v5: \n";
    for (size_t i = 0; i < v5.size(); ++i){
        std::cout << v5[i] << "  ";
    }
    std::cout << std::endl;
    v5.insert(v4, 1);
    std::cout << "=====================================================================\n";

    //SIZE      CAPACITY        LOADFACTOR      SHRINKFIT       RESERVE
    std::cout << "size v5\t\t\t\t\t| " << v5.size() << "\n";
    std::cout << "=====================================================================\n";

    std::cout << "capacity v5\t\t\t\t| " << v5.capacity() << "\n";
    std::cout << "=====================================================================\n";

    std::cout << "loadFactor v5\t\t\t\t| " << v5.loadFactor() << "\n";
    std::cout << "=====================================================================\n";

    std::cout << "Индекс первого вхождения '3.3' в v5\t| " << v5.find(3.3) << "\n";
    std::cout << "=====================================================================\n";

    v5.shrinkToFit();
    std::cout << "v5.shrinkToFit\t\t\t\t|" <<  " Capacity = " << v5.capacity() << "\n";
    std::cout << "=====================================================================\n";

    v5.reserve(10);
    std::cout << "v5.reserve\t\t\t\t|" << " Capacity = " << v5.capacity() << "\n";
    std::cout << "=====================================================================\n";

    return 0;
}
