#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>
#include <string>
#include <iterator>

namespace cs1c {


template<class T>
class vector
{
private:
    T * data;
    std::size_t length;
    std::size_t size;
public:

    // beginning of iterator class definition and iterator methods.
    class iterator {


    public:
        // defining aliases for the different types to be used
        typedef iterator self_type;
        typedef T value_type;
        typedef T& reference;
        typedef T* pointer;
        typedef std::random_access_iterator_tag iterator_category;
        typedef std::ptrdiff_t difference_type;
        iterator(pointer ptr) : ptr_{ptr} {};
        self_type operator++() {
            self_type i = *this;
            ptr_++;
            return i;
        }
		self_type operator++(int) {
            ptr_++;
            return *this;
        }
        self_type operator--() {
            self_type i = *this;
            ptr_--;
            return i;
        }
		self_type operator--(int) {
            --ptr_;
            return *this;
        }
        std::size_t operator-(const self_type& rhs) {
            return ptr_ - rhs.ptr_;
        }
        self_type operator-(std::size_t num) {
            return ptr_ - num;
        }
        self_type operator+(std::size_t num) {
            return ptr_ + num;
        }
        self_type operator+= (int value) {
            ptr_+=value;
            return ptr_;
        }
        self_type operator-= (int value) {
            ptr_-=value;
            return ptr_;
        }
        std::size_t operator+(const self_type& rhs) {
            return ptr_ + rhs.ptr_;
        }
        bool operator<(const self_type& rhs) {return ptr_ < rhs.ptr_;}
        bool operator>(const self_type& rhs) {return ptr_ > rhs.ptr_;}
        bool operator<=(const self_type& rhs) {return ptr_ <= rhs.ptr_;}
        bool operator>=(const self_type& rhs) {return ptr_ >= rhs.ptr_;}
        reference operator*() { return *ptr_; }
        pointer operator->() { return ptr_; }
        bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
        bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }
        const T& operator[](std::size_t i) {return ptr_[i];}
    private:
        pointer ptr_;
    };

    class const_iterator {


    public:
        // defining aliases for the different types to be used
        typedef const_iterator self_type;
        typedef T value_type;
        typedef T& reference;
        typedef T* pointer;
        typedef std::random_access_iterator_tag iterator_category;
        typedef std::ptrdiff_t difference_type;
        const_iterator(pointer ptr) : ptr_{ptr} {};
        self_type operator++() {
            self_type i = *this;
            ptr_++;
            return i;
        }
        self_type operator+= (int value) {
            ptr_+=value;
            return ptr_;
        }
        self_type operator-= (int value) {
            ptr_-=value;
            return ptr_;
        }
		self_type operator++(int) {
            ptr_++;
            return *this;
        }
        self_type operator--() {
            self_type i = *this;
            ptr_--;
            return i;
        }
		self_type operator--(int) {
            --ptr_;
            return *this;
        }
        std::size_t operator-(const self_type& rhs) {
            return ptr_ - rhs.ptr_;
        }
        self_type operator-(std::size_t num) {
            return ptr_ - num;
        }
        self_type operator+(std::size_t num) {
            return ptr_ + num;
        }
        std::size_t operator+(const self_type& rhs) {
            return ptr_ + rhs.ptr_;
        }
        bool operator<(const self_type& rhs) {return ptr_ < rhs.ptr_;}
        bool operator>(const self_type& rhs) {return ptr_ > rhs.ptr_;}
        bool operator<=(const self_type& rhs) {return ptr_ <= rhs.ptr_;}
        bool operator>=(const self_type& rhs) {return ptr_ >= rhs.ptr_;}
        const T& operator*() { return  *ptr_; }
        const T* operator->() { return ptr_; }
        bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
        bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }
        const T& operator[](std::size_t i) {return ptr_[i];}
    private:
        pointer ptr_;
    };
    iterator begin() { return iterator(data); }
    iterator end() { return iterator(data+length); }
    const_iterator cbegin() { return const_iterator(data); }
    const_iterator cend() { return const_iterator(data+length); }
    /*!
     * \brief default constructor of vector. does not allocate memory
     * 
     * 
     */
    vector() : data{nullptr}, length{0}, size{0} {};
    /*!
     * \brief copy constructor of vector
     * \param cosnt reference to a vector<T> object
     */
    vector(const vector<T>&);
    /*!
     * \brief move constructor of vector<T>
     * \param r-value reference to the original vector
     */
    vector(vector<T>&&);
    /*!
     * \brief paramterized constructor for vector<T>
     * \param size of array to be allocated
     */
    explicit vector(std::size_t size)
        : data{size? new T[size]: nullptr}, length{size},
        size{size} {
        for (std::size_t i = 0; i < size; i++)
            data[i] = T();
    }
    /*!
     * \brief returns length of the array
     */
    std::size_t getLength();
    /*!
     * \brief gets the size of the allocated array
     */
    std::size_t getSize();
    /*!
     * \brief deallocates the array and sets all values to null
     */
    void clear() noexcept {
        delete[] data;
        data = nullptr;
        length = 0;
        size = 0;
    }
    /*!
     * \brief adds an element to the vector
     * \param T type element to be added to back of the vector
     */
    void push_back(const T&);
    /*!
     * \brief returns a const reference to the first element
     */
    const T& top() {
        return data[0];
    }
    /*!
     * \brief index of operator 
     * \param index of the element to be accessed
     */
    T& operator[](int index) {
        return data[index];
    }
    /*!
     * \brief assignment operator of vector<T>
     * \param orig vector<T> to be copied
     */
    vector<T>& operator=(const vector<T>&);
    /*!
     * \brief move assignment operator of vector<T>
     * \param orig vector<T> to be copied
     */
    vector<T>& operator=(vector<T>&&);
    /*!
     * \brief erases an element pointed to by an iterator
     * \param pos iterator to the element to be removed
     */
    typename vector<T>::iterator erase(iterator);
    /*!
     * \brief assignment operator of vector<T>
     * \param pos iterator to insert in front of
     * \param val T object to be inserted
     */
    typename vector<T>::iterator insert(iterator, const T&);
    /*!
     * \brief resizes the array and allocates to specified capacity
     * \param size is number of elements to be allocated
     */
    void resize(std::size_t);
    /*!
     * \brief resizes the array and allocates to specified capacity
     * \param size of the array to be allocated;
     */
    bool reserve(std::size_t);
    /*!
     * \brief dealocates the data pointer
     */
    ~vector() {
        if (data != nullptr) {
            delete[] data;
            data = nullptr;
        }
    }
};

// end of class declaration
template<class T>
typename vector<T>::iterator vector<T>::erase(iterator pos) {
    if (pos == end())
        return pos;
    for (auto it = pos + 1; it != end(); ++it)
        *(it - 1) = *it;
    *(end() - 1) = 0;
    length--;
    return pos;
}

template<class T>
void vector<T>::resize(std::size_t newsize) {
    reserve(newsize);
    for (std::size_t i = length; i < newsize; ++i) {
        data[i] = T();
    }
//     = newsize;
}

template<class T>
typename vector<T>::iterator vector<T>::insert(iterator it, const T& val) {
    std::size_t offset;
    if (data == nullptr) {
        std::cout << 1;
        push_back(val);
    } else if (length == size) {
        offset = it - begin();
        std::cout << 2;
        reserve(2 * size);
        it = begin()+offset;
    }
    for (auto i = end(); i != it; --i)
        *i = *(i - 1);
    ++length;
    *it = val;
    return it;
}

template<class T>
std::size_t vector<T>::getLength() {
    return length;
}

template <class T>
std::size_t vector<T>::getSize(){
    return size;
}

template<class T>
vector<T>::vector(const vector<T>& orig) {
    if (orig.size == 0){
        data = nullptr;
        size = 0;
        length = 0;
    }
    else {
        size = orig.size;
        length = orig.length;
        data = new T[size];
		for (size_t i = 0; i < orig.length; ++i) {
            data[i] = orig.data[i];
        }
    }
}

template<class T>
vector<T>::vector(vector&& orig) : data{nullptr}, length{0}, size{0} {
    data = orig.data;
    orig.data = nullptr;
    size = orig.size;
    length = orig.length;
}

template<class T>
bool vector<T>::reserve(std::size_t newSize) {
    if (newSize <= size) {
        return false;
        // cant reserve less than existing.
    }
    else {
        T * newData = new T[newSize];
        for (std::size_t i = 0; i < length; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        size = newSize;
        return true;
    }
}

template<class T>
void vector<T>::push_back(const T& newElement) {
    if (data == nullptr) {
        size = 16;
        length = 0;
        data = new T[size];
        data[length] = newElement;
        length++;
    }
    else if (length >= size) {
        reserve(size*2);
        data[length] = newElement;
        length++;
    }
    else {
        data[length] = newElement;
        length++;
    }
}

template<class T>
vector<T>& vector<T>::operator=(const vector<T>& orig) {
    // check for self-assignment
    if (this == &orig) {
        return *this;
    }
    // delete data in the array and return data * to nullptr
    if (data != nullptr) {
        delete[] data;
        data = nullptr;
        size = 0;
        length = 0;
    }

    size = orig.size;
    length = orig.length;
    data = new T[size];
    for (std::size_t i = 0; i < length; ++i) {
        data[i] = orig.data[i];
    }
    return *this;
}

template<class T>
vector<T>& vector<T>::operator=(vector<T>&& orig) {
//    check for self assignment
    if (this == &orig) {
        return *this;
    }
    if ( data != nullptr) {
        delete[] data;
        data = nullptr;
    }
    size = orig.size;
    length = orig.length;
    data = orig.data;
    orig.data = nullptr;
    return *this;
}

}
#endif // VECTOR_H

