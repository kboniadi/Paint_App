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
	std::size_t size_;
	std::size_t capacity_;
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
			++ptr_;
			return *this;
        }
		self_type operator++(int) {
			self_type i = *this;
			ptr_++;
			return i;
        }
        self_type operator--() {
			--ptr_;
			return *this;
        }
		self_type operator--(int) {
			self_type i = *this;
			ptr_--;
			return i;
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
		self_type operator+= (int value) {
			ptr_+=value;
			return ptr_;
		}
		self_type operator-= (int value) {
			ptr_-=value;
			return ptr_;
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
			++ptr_;
			return *this;
		}
		self_type operator++(int) {
			self_type i = *this;
			ptr_++;
			return i;
		}
		self_type operator--() {
			--ptr_;
			return *this;
		}
		self_type operator--(int) {
			self_type i = *this;
			ptr_--;
			return i;
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
		self_type operator+= (int value) {
			ptr_+=value;
			return ptr_;
		}
		self_type operator-= (int value) {
			ptr_-=value;
			return ptr_;
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
	iterator end() { return iterator(data+size_); }
	const_iterator begin() const { return const_iterator(data); }
	const_iterator end() const { return const_iterator(data+size_); }
    /*!
     * \brief default constructor of vector. does not allocate memory
     * 
     * 
     */
	vector() : data{nullptr}, size_{0}, capacity_{0} {};
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
		: data{size? new T[size]: nullptr}, size_{size},
		capacity_{size} {
		for (std::size_t i = 0; i < capacity_; i++)
            data[i] = T();
    }
    /*!
	 * \brief returns size_ of the array
     */
	std::size_t size() const {return size_;}
    /*!
     * \brief gets the size of the allocated array
     */
	std::size_t capacity() const {return capacity_;}

	bool empty() const {return size_ == 0;}
    /*!
     * \brief deallocates the array and sets all values to null
     */
    void clear() noexcept {
        delete[] data;
        data = nullptr;
		size_ = 0;
		capacity_ = 0;
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
	const T& operator[](int index) const
	{
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
	size_--;
    return pos;
}

template<class T>
void vector<T>::resize(std::size_t newsize) {
    reserve(newsize);
	for (std::size_t i = size_; i < newsize; ++i) {
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
	} else if (size_ == capacity_) {
        offset = it - begin();
        std::cout << 2;
		reserve(2 * capacity_);
        it = begin()+offset;
    }
    for (auto i = end(); i != it; --i)
        *i = *(i - 1);
	++size_;
    *it = val;
    return it;
}

template<class T>
vector<T>::vector(const vector<T>& orig) {
	if (orig.capacity_ == 0){
        data = nullptr;
		capacity_ = 0;
		size_ = 0;
    }
    else {
		capacity_ = orig.capacity_;
		size_ = orig.size_;
		data = new T[capacity_];
		for (size_t i = 0; i < orig.size_; ++i) {
            data[i] = orig.data[i];
        }
    }
}

template<class T>
vector<T>::vector(vector&& orig) : data{nullptr}, size_{0}, capacity_{0} {
    data = orig.data;
    orig.data = nullptr;
	capacity_ = orig.capacity_;
	size_ = orig.size_;
}

template<class T>
bool vector<T>::reserve(std::size_t newSize) {
	if (newSize <= capacity_) {
        return false;
        // cant reserve less than existing.
    }
    else {
        T * newData = new T[newSize];
		for (std::size_t i = 0; i < size_; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
		capacity_ = newSize;
        return true;
    }
}

template<class T>
void vector<T>::push_back(const T& newElement) {
    if (data == nullptr) {
		capacity_ = 16;
		size_ = 0;
		data = new T[capacity_];
		data[size_] = newElement;
		size_++;
    }
	else if (size_ >= capacity_) {
		reserve(capacity_*2);
		data[size_] = newElement;
		size_++;
    }
    else {
		data[size_] = newElement;
		size_++;
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
		capacity_ = 0;
		size_ = 0;
    }

	capacity_ = orig.capacity_;
	size_ = orig.size_;
	data = new T[capacity_];
	for (std::size_t i = 0; i < size_; ++i) {
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
	capacity_ = orig.capacity_;
	size_ = orig.size_;
    data = orig.data;
    orig.data = nullptr;
    return *this;
}

}
#endif // VECTOR_H

