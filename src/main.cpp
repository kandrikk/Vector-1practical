#include "../Include/Vector.h"

int main()
{
    //! Конструктор без параметров
    Vector vec1;
    std::cout << "\nVector v1 created successfully!\n";
    std::cout << "=====================================================================\n";

    //! Конструктор с параметрами
    double arr[] = {1.1, 2.2, 3.3};
    Vector vec2(arr, 3);
    std::cout << "Конструктор с параметрами \nv2 = ";
    vec2.printVec();
}