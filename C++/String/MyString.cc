#include "MyString.h"

#include <cstring>
#include <iostream>
#include <utility>
#include <algorithm>

// 自己的头文件
// C 标准库
// C++ 标准库
// 其他的自己写的库

const MyString::size_type MyString::npos = -1;

MyString::MyString() 
    : size_(0), capacity_(0), data_(new value_type[capacity_ + 1]) {
  data_[0] = '\0';
}

MyString::MyString(size_type count, char ch) 
    : size_(count), capacity_(size_), data_(new value_type[capacity_ + 1]) {
  for (size_type i = 0; i < count; i++) data_[i] = ch;
  data_[size_] = '\0';
}

MyString::MyString(const MyString& other, size_type pos)
    : MyString(other, pos, other.size_ - pos) {}

MyString::MyString(const MyString& other, size_type pos, size_type count)
    : MyString(other.data_ + pos, count) {}

MyString::MyString(const char* s, size_type count)
    : size_(count), capacity_(size_), data_(new value_type[capacity_ + 1]) {
  memcpy(data_, s, count);
  data_[size_] = '\0';
}

MyString::MyString(const char* s) : MyString(s, strlen(s)) {}

MyString::MyString(const MyString& other) : MyString(other, 0) {}

MyString::~MyString() {
  delete[] data_;
}

MyString& MyString::operator=(const MyString& str) {
  if (capacity_ < str.size()) {
    delete[] data_;
    capacity_ = str.size();
    data_ = new value_type[capacity_ + 1];
  }
  strcpy(data_, str.data_);
  size_ = str.size();
  return *this;
}

// Capacity
void MyString::shrink_to_fit() {
  if (capacity_ > size_) reallocate(size_);
}

void MyString::reserve(size_type new_cap) {
  if (new_cap > capacity_) reallocate(new_cap);
}

void MyString::resize(size_type count) {
  resize(count, char{});
}

void MyString::resize(size_type count, char ch) {
  if (size_ < count) {
    reserve(count);
    for (size_type i = size_; i < count; i++) data_[i] = ch;
  }
  data_[count] = '\0';
  size_ = count;
}

// Operations
void MyString::swap(MyString& other) {
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
  std::swap(data_, other.data_);
}

void MyString::clear() {
  data_[0] = '\0';
  size_ = 0;
}

MyString& MyString::append(size_type count, char ch) {
  const size_type new_size = size_ + count;
  reserve(new_size);
  for (size_type i = size_; i < new_size; i++) {
    data_[i] = ch;
  }
  data_[new_size] = '\0';
  size_ = new_size;
  return *this;
}

MyString& MyString::append(const MyString& str) {
  return append(str, 0, str.size_);
}

MyString& MyString::append(const MyString& str, size_type pos, size_type count) {
  count = std::min(count, str.size_ - pos);
  return append(str.data_ + pos, count);
}

MyString& MyString::append(const char* s, size_type count) {
  const size_type new_size = size_ + count;
  reserve(new_size);
  char* dest = data_ + size_;
  memcpy(dest, s, count);
  data_[new_size] = '\0';
  size_ = new_size;
  return *this;
}

MyString& MyString::append(const char* s) {
  return append(s, strlen(s));
}

MyString& MyString::operator+=(const MyString& str) {
  return append(str);
}

MyString& MyString::operator+=(char ch) {
  return append(1, ch);
}

MyString& MyString::operator+=(const char* s) {
  return append(s);
}

void MyString::push_back(char ch) {
  if (size_ + 1> capacity_) reallocate(size_ + 1);
  data_[size_] = ch;
  size_++;
  data_[size_] = '\0'; 
}

void MyString::pop_back() {
  size_--;
  data_[size_] = '\0';
}

void MyString::insert_preparation(
    size_type new_size, difference_type bound, size_type count) {
  if (new_size > capacity_) reallocate(new_size);
  for (difference_type i = new_size - 1; i >= bound; i--) {
    data_[i] = data_[i - count];
  }
}

MyString& MyString::insert(size_type index, size_type count, char ch) {
  const size_type new_size = size_ + count;
  const difference_type bound = index + count;
  insert_preparation(new_size, bound, count);
  for (size_type i = index; i < bound; i++) data_[i] = ch;
  data_[new_size] = '\0';
  size_ = new_size;
  return *this;
}

MyString& MyString::insert(size_type index, const char* s) {
  return insert(index, s, strlen(s));
}

MyString& MyString::insert(size_type index, const char* s, size_type count) {
  const size_type new_size = size_ + count;
  insert_preparation(new_size, index + count, count);
  memcpy(data_ + index, s, count);
  data_[new_size] = '\0';
  size_ = new_size;
  return *this;
}

MyString& MyString::insert(size_type index, const MyString& str) {
  return insert(index, str.data_, str.size_);
}

// MyString& MyString::insert(size_type index, const MyString& str, size_type s_index, size_type count) {

// }

MyString& MyString::erase(size_type index, size_type count) {
  count = std::min(count, size_ - index);
  for (size_type i = index; i < size_ - count + 1; i++) {
    data_[i] = data_[i + count];
  }
  return *this;
}

MyString MyString::substr(size_type pos, size_type count) const {
  count = std::min(count, size_ - pos);
  return {*this, pos, count};
}

void MyString::reallocate(size_type new_capacity) {
  capacity_ = new_capacity;
  pointer tmp = data_;
  data_ = new value_type[capacity_ + 1];
  memcpy(data_, tmp, size_ + 1);
  delete tmp;
}

std::ostream& operator<<(std::ostream& os, const MyString& s) {
  return os << s.c_str();
}

template <class Iterator>
Iterator operator+(MyString::difference_type n, Iterator it) {
  return it + n;
}

template MyString::iterator operator+(
    MyString::difference_type n, MyString::iterator it);
template MyString::const_iterator operator+(
    MyString::difference_type n, MyString::const_iterator it);
