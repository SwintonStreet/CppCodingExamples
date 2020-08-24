#include <iostream>
#include <stdexcept>

template<typename T>
class Vector
{
  public:

    // constructor
    explicit Vector( size_t n, const T& v): size{n}
    {
        data = new T[n];

        for (size_t i = 0; i<n; ++i)
        {
            try
            {
                data[i] = v;
            }
            catch (...)
            {
                std::cout << "throw\n";

                if (data)
                {
                    delete[] data;
                }
                throw;
            }
        }
    }

    // copy assignment
    Vector& operator=(const Vector& other)
    {
        // only copy data if required
        // i.e. if this is a different vector
        if ( data != other.data )
        {
            delete[] data;

            data = new T[other.size];

            for (size_t i = 0; i<other.size; ++i)
            {
                try
                {
                    data[i] = other.data[i];
                }
                catch (...)
                {
                    if (data)
                    {
                        delete[] data;
                    }

                    throw;
                }
            }
        }

        return *this;
    }

    T& operator[](const unsigned int i)
    {
        if ( i >= size )
        {
            std::out_of_range oppps{"Out of range"};
            throw oppps;
        }

        return data[i];
    }

    ~Vector()
    {
        std::cout << "element 1: " << data[0] << '\n';
        delete[] data;
        std::cout << "deleting vector now\n";
    }

    // to allow for ranged for loops we need to define
    // iterators for the vector class
    typedef T*       iterator;
    typedef const T* const_iterator;

    iterator begin()
    {
        return &data[0];
    }

    iterator end()
    {
        return &data[size];
    }

    // members
    size_t size;
    T*     data;
};

int main()
{
    Vector<int> first(10, 5);
    Vector<int> second(20, 10);

    second = first;

    for ( const auto& element : first )
    {
        std::cout << "elelment: " << element << '\n';
    }

    for ( auto& element : first )
    {
        element = 10;
        std::cout << "elelment: " << element << '\n';
    }

    // try and grab an element that is out of range,
    // and the implementation will throw an out of range
    // error
    try
    {
        std::cout << first[10] << '\n';
    }
    catch (const std::out_of_range& oor)
    {
        std::cerr << oor.what() << '\n';
    }

    return 0;
}
