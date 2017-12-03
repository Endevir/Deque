#include <cstdio>
#include <iterator>
//#include "deque_iterator.h"

#include <iterator>
#include <iostream>

/*
 * ===============================================================
 *                  DECLARATION - DequeIterator
 * ===============================================================
 */

template<class T, class Tpointer, class Treference>
class DequeIterator : public std::iterator<std::random_access_iterator_tag, T> {

public:
    DequeIterator() {}

    DequeIterator(const DequeIterator &b);

    DequeIterator(T *data, int maxsize_, int head, int tail, int current);

    DequeIterator &operator=(const DequeIterator &b);

    // Access operations

    Treference operator*();

    Tpointer operator->();

    // Step operations

    DequeIterator &operator+=(int step);

    DequeIterator &operator-=(int step);

    DequeIterator operator+(int step) const;

    DequeIterator operator-(int step) const;

    int operator-(const DequeIterator &b) const;

    // Single-step operations

    DequeIterator &operator++();

    DequeIterator &operator--();

    DequeIterator operator++(int);

    DequeIterator operator--(int);

    // Bool operations

    bool operator==(const DequeIterator &b) const;

    bool operator<(const DequeIterator &b) const;

    bool operator>(const DequeIterator &b) const;

    bool operator!=(const DequeIterator &b) const;

    bool operator<=(const DequeIterator &b) const;

    bool operator>=(const DequeIterator &b) const;

    // Special operations, similar to basic std::deque RandomAccessIterator class functions

    T &operator[](int step);

private:
    T *data_;
    int max_size_;
    int head_;
    int tail_;

    int current_;

    int get_position(int pos) const {
        return (head_ + pos) % max_size_;
    }
};

/*
 * ===============================================================
 *                  IMPLEMENTATION - DequeIterator
 * ===============================================================
 */


template<class T, class Tpointer, class Treference>
DequeIterator<T, Tpointer, Treference>::DequeIterator(T *data, int maxsize_, int head, int tail, int current) :
        data_(data), max_size_(maxsize_), head_(head), tail_(tail), current_(current) {

}

template<class T, class Tpointer, class Treference>
DequeIterator<T, Tpointer, Treference>::DequeIterator(const DequeIterator &b) {
    (*this) = b;
}

template<class T, class Tpointer, class Treference>
DequeIterator<T, Tpointer, Treference> &DequeIterator<T, Tpointer, Treference>::operator=(const DequeIterator &b) {
    data_ = b.data_;
    max_size_ = b.max_size_;
    head_ = b.head_;
    tail_ = b.tail_;
    current_ = b.current_;
    return *this;
}

// Bool operations

template<class T, class Tpointer, class Treference>
bool DequeIterator<T, Tpointer, Treference>::operator==(const DequeIterator &b) const {
    return current_ == b.current_;
}

template<class T, class Tpointer, class Treference>
bool DequeIterator<T, Tpointer, Treference>::operator!=(const DequeIterator &b) const {
    return !(*this == b);
}

template<class T, class Tpointer, class Treference>
bool DequeIterator<T, Tpointer, Treference>::operator<(const DequeIterator &b) const {
    return current_ < b.current_;
}

template<class T, class Tpointer, class Treference>
bool DequeIterator<T, Tpointer, Treference>::operator>(const DequeIterator &b) const {
    return current_ > b.current_;
}

template<class T, class Tpointer, class Treference>
bool DequeIterator<T, Tpointer, Treference>::operator<=(const DequeIterator &b) const {
    return !(*this > b);
}

template<class T, class Tpointer, class Treference>
bool DequeIterator<T, Tpointer, Treference>::operator>=(const DequeIterator &b) const {
    return !(*this < b);
}

// Access operations

template<class T, class Tpointer, class Treference>
Treference DequeIterator<T, Tpointer, Treference>::operator*() {
    return *(data_ + get_position(current_));
}

template<class T, class Tpointer, class Treference>
Tpointer DequeIterator<T, Tpointer, Treference>::operator->() {
    return &*(*this);
}

// Step operations

template<class T, class Tpointer, class Treference>
DequeIterator<T, Tpointer, Treference> &DequeIterator<T, Tpointer, Treference>::operator+=(int step) {
    current_ += step;
    return *this;
}

template<class T, class Tpointer, class Treference>
DequeIterator<T, Tpointer, Treference> DequeIterator<T, Tpointer, Treference>::operator+(int step) const {
    DequeIterator new_iter(*this);
    new_iter += step;
    return new_iter;
}

template<class T, class Tpointer, class Treference>
DequeIterator<T, Tpointer, Treference> &DequeIterator<T, Tpointer, Treference>::operator-=(int step) {
    current_ -= step;
    return *this;
}

template<class T, class Tpointer, class Treference>
DequeIterator<T, Tpointer, Treference> DequeIterator<T, Tpointer, Treference>::operator-(int step) const {
    DequeIterator new_iter(*this);
    new_iter -= step;
    return new_iter;
}

template<class T, class Tpointer, class Treference>
int DequeIterator<T, Tpointer, Treference>::operator-(const DequeIterator<T, Tpointer, Treference> &b) const {
    return current_ - b.current_;
};

template<class T, class Tpointer, class Treference>
DequeIterator<T, Tpointer, Treference> operator+(int step, const DequeIterator<T, Tpointer, Treference> &iterator) {
    return iterator + step;
}

// Single-step operations

template<class T, class Tpointer, class Treference>
DequeIterator<T, Tpointer, Treference> &DequeIterator<T, Tpointer, Treference>::operator++() {
    *this += 1;
    return *this;
}

template<class T, class Tpointer, class Treference>
DequeIterator<T, Tpointer, Treference> DequeIterator<T, Tpointer, Treference>::operator++(int) {
    DequeIterator new_iter(*this);
    ++(*this);
    return new_iter;
}

template<class T, class Tpointer, class Treference>
DequeIterator<T, Tpointer, Treference> &DequeIterator<T, Tpointer, Treference>::operator--() {
    *this -= 1;
    return *this;
}

template<class T, class Tpointer, class Treference>
DequeIterator<T, Tpointer, Treference> DequeIterator<T, Tpointer, Treference>::operator--(int) {
    DequeIterator<T, Tpointer, Treference> new_iter(*this);
    --(*this);
    return new_iter;
}

// std::queue iterator functions
template<class T, class Tpointer, class Treference>
T &DequeIterator<T, Tpointer, Treference>::operator[](int step) {
    return *(*this + step);
}


/*
 * ===============================================================
 *                  DECLARATION - Deque
 * ===============================================================
 */

template<class T>
class Deque {

private:
    T *data_ = nullptr;

    size_t head_;
    size_t tail_;
    size_t max_size_;
    size_t size_;

    const size_t DECREASE_CAPACITY_THRESHOLD = 4;
    const size_t CHANGE_CAPACITY_RATIO = 2;
    const size_t INITIAL_CAPACITY = 4;

    inline void reallocate(const size_t &new_max_size);

    inline void try_to_decrease_size();

    inline void try_to_increase_size();

    inline void move_up(size_t &value) const;

    inline void move_down(size_t &value) const;

public:

    // Typedef iterators

    typedef DequeIterator<T, T *, T &> iterator;
    typedef DequeIterator<const T, const T *, const T &> const_iterator;
    typedef std::reverse_iterator<DequeIterator<T, T *, T &>> reverse_iterator;
    typedef std::reverse_iterator<DequeIterator<const T, const T *, const T &>> const_reverse_iterator;


// Constructors & destructors

    Deque();

    Deque(const Deque &b);

    ~Deque();

    Deque &operator=(const Deque &b);

    // Element access functions

    T &operator[](size_t pos);

    const T &operator[](size_t pos) const;

    T &front();

    const T &front() const;

    T &back();

    const T &back() const;

    // Capacity

    bool empty() const;

    size_t size() const;

    // Modifiers

    void clear();

    void push_back(const T &elem);

    void pop_back();

    void push_front(const T &elem);

    void pop_front();

    // Iterators

    iterator begin() {
        return iterator(data_, max_size_, head_, tail_, 0);
    }

    const_iterator begin() const {
        return const_iterator(data_, max_size_, head_, tail_, 0);
    }

    const_iterator cbegin() const {
        return const_iterator(data_, max_size_, head_, tail_, 0);
    }

    iterator end() {
        return iterator(data_, max_size_, head_, tail_, size());
    }

    const_iterator end() const {
        return const_iterator(data_, max_size_, head_, tail_, size());
    }

    const_iterator cend() const {
        return const_iterator(data_, max_size_, head_, tail_, size());
    }

    reverse_iterator rbegin() {
        return reverse_iterator(end());
    }

    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(cend());
    }

    const_reverse_iterator crbegin() const {
        return const_reverse_iterator(cend());
    }

    reverse_iterator rend() {
        return reverse_iterator(begin());
    }

    const_reverse_iterator rend() const {
        return const_reverse_iterator(cbegin());
    }

    const_reverse_iterator crend() const {
        return const_reverse_iterator(cbegin());
    }
};

/*
 * ===============================================================
 *                  IMPLEMENTATION - Deque
 * ===============================================================
 */

template<class T>
inline void Deque<T>::reallocate(const size_t &new_max_size) {
    T *tempdata_ = new T[new_max_size];

    size_t oldsize_ = size();
    tail_ = size();

    for (size_t i = 0; i < oldsize_; ++i) {
        tempdata_[i] = data_[head_];
        move_up(head_);
    }

    delete[] data_;
    data_ = tempdata_;

    head_ = 0;

    max_size_ = new_max_size;
}

template<class T>
inline void Deque<T>::try_to_decrease_size() {
    if (size() * DECREASE_CAPACITY_THRESHOLD >= max_size_ || max_size_ < (INITIAL_CAPACITY << 1))
        return;
    reallocate(max_size_ >> CHANGE_CAPACITY_RATIO);
}

template<class T>
inline void Deque<T>::try_to_increase_size() {
    if (head_ != (tail_ + 1) % max_size_)
        return;
    reallocate(max_size_ << CHANGE_CAPACITY_RATIO);
}

template<class T>
inline void Deque<T>::move_up(size_t &value) const {
    ++value;
    if (value == max_size_)
        value = 0;
}

template<class T>
inline void Deque<T>::move_down(size_t &value) const {
    if (value == 0)
        value = max_size_ - 1;
    else
        --value;
}

// ================================

template<class T>
Deque<T>::Deque() {
    max_size_ = INITIAL_CAPACITY;
    data_ = new T[max_size_];
    head_ = 0;
    tail_ = 0;
    size_ = 0;
}

template<class T>
Deque<T>::Deque(const Deque &b) {
    (*this) = b;
}

template<class T>
Deque<T>::~Deque() {
    delete[] data_;
}

template<class T>
Deque<T> &Deque<T>::operator=(const Deque &b) {
    if (data_ != nullptr)
        delete[] data_;
    if (b.data_ == nullptr) {
        *this = Deque();
        return *this;
    }
    data_ = new T[b.max_size_];
    std::copy(b.data_, b.data_ + b.max_size_, data_);
    head_ = b.head_;
    tail_ = b.tail_;
    max_size_ = b.max_size_;
    size_ = b.size_;
    return *this;
}

// ================================

template<class T>
T &Deque<T>::operator[](size_t pos) {
    return data_[(head_ + pos) % max_size_];
}

template<class T>
const T &Deque<T>::operator[](size_t pos) const {
    return data_[(head_ + pos) % max_size_];
}

template<class T>
T &Deque<T>::front() {
    return (*this)[0];
}

template<class T>
const T &Deque<T>::front() const {
    return (*this)[0];
}

template<class T>
T &Deque<T>::back() {
    return (*this)[size() - 1];
}

template<class T>
const T &Deque<T>::back() const {
    return (*this)[size() - 1];
}

// ================================

template<class T>
bool Deque<T>::empty() const {
    return !size();
}

template<class T>
size_t Deque<T>::size() const {
    return size_;
}

// ================================

template<class T>
void Deque<T>::clear() {
    (*this) = Deque();
}

template<class T>
void Deque<T>::push_back(const T &elem) {
    try_to_increase_size();
    data_[tail_] = elem;
    ++size_;
    move_up(tail_);
}

template<class T>
void Deque<T>::pop_back() {
    try_to_decrease_size();
    --size_;
    move_down(tail_);
}

template<class T>
void Deque<T>::push_front(const T &elem) {
    try_to_increase_size();
    move_down(head_);
    ++size_;
    data_[head_] = elem;
}

template<class T>
void Deque<T>::pop_front() {
    try_to_decrease_size();
    --size_;
    move_up(head_);
}
