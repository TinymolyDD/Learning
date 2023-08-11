#ifndef _MYSTRING_H_
#define _MYSTRING_H_
// 头文件保护

#include <cstddef>
#include <iostream>
#include <iterator>

class MyString {
 public:
  // Member types
  typedef char value_type;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef char* pointer; 
  typedef const char* const_pointer;

  MyString();
  MyString(size_type count, char ch);
  MyString(const MyString& other, size_type pos);
  MyString(const MyString& other, size_type pos, size_type count);
  MyString(const char* s, size_type count);
  MyString(const char* s);
  MyString(const MyString& other);
  ~MyString();
  
  // Member functions
  MyString& operator=(const MyString& str);
  
  // Element access
  reference operator[](size_type n) { return *(data_ + n); }
  const_reference operator[](size_type n) const { return *(data_ + n); }

  pointer data() { return data_; }
  const_pointer data() const { return data_; }

  const_pointer c_str() const { return data_; }

 private:
  // Iterators
  template <class CharT>
  class Iterator {
   public:
    typedef CharT value_type;
    typedef value_type& reference;
    typedef std::ptrdiff_t difference_type;
    typedef CharT* pointer;
    typedef std::random_access_iterator_tag iterator_category;

   private:
    typedef Iterator<CharT> iterator;

   public:
    Iterator(CharT* element_ptr) : data_(element_ptr) {}
    Iterator() : data_(nullptr) {}

    reference operator*() const { return *data_; }

    iterator& operator++() {
      ++data_;
      return *this;
    }

    iterator operator++(int) { return {data_++}; }

    iterator& operator--() {
      --data_;
      return *this;
    }

    iterator operator--(int) { return {data_--}; }

    iterator& operator+=(difference_type n) {
      data_ += n;
      return *this;
    }

    iterator& operator-=(difference_type n) {
      data_ -= n;
      return *this;
    }

    iterator operator+(difference_type n) const { return {data_ + n}; }

    iterator operator-(difference_type n) const { return {data_ - n}; }

    reference operator[](difference_type n) const {
      return *(data_ + n);
    }

    difference_type operator-(iterator it) const {
      return this->data_ - it.data_;
    }

    bool operator<(iterator it) const { return *this - it < 0; }
    bool operator>(iterator it) const { return *this - it > 0; }
    bool operator>=(iterator it) const { return *this - it >= 0; }
    bool operator<=(iterator it) const { return *this - it <= 0; }
    bool operator!=(iterator it) const { return *this - it != 0; }
    bool operator==(iterator it) const { return *this - it == 0; }

   private:
    CharT* data_;
  };

 public:
  typedef Iterator<value_type> iterator;
  typedef Iterator<const value_type> const_iterator;

  iterator begin() { return iterator(data_);  }
  const_iterator begin() const { return const_iterator(data_);  }
  const_iterator cbegin() const { return const_iterator(data_); }

  iterator end() { return iterator(data_ + size_); }
  const_iterator end() const { return const_iterator(data_ + size_); }  
  const_iterator cend() const { return const_iterator(data_ + size_); }

  // Capacity
  size_type capacity() const { return capacity_; }
  size_type size() const { return size_; }
  size_type length() const { return size_; }

  void shrink_to_fit();
  
  void reserve(size_type new_cap);

  void resize(size_type count);
  void resize(size_type count, char ch);

  // Operations
  void swap(MyString& other);

  void clear();

  MyString& append(size_type count, char ch);
  MyString& append(const MyString& str);
  MyString& append(const MyString& str, size_type pos, size_type count);
  MyString& append(const char* s, size_type count);
  MyString& append(const char* s);

  MyString& operator+=(const MyString& str);
  MyString& operator+=(char ch);
  MyString& operator+=(const char* s);

  void push_back(char ch);

  void pop_back();

  void insert_preparation(size_type new_size, difference_type bound, size_type count);
  MyString& insert(size_type index, size_type count, char ch);
  MyString& insert(size_type index, const char* s);
  MyString& insert(size_type index, const char* s, size_type count);
  MyString& insert(size_type index, const MyString& str);
  MyString& insert(size_type index, const MyString& str, size_type s_index, size_type count = npos);
  iterator insert(iterator pos, char ch);
  iterator insert(iterator pos, size_type count, char ch);

  MyString& erase(size_type index = 0, size_type count = npos);
  iterator erase(iterator position);
  iterator erase(iterator first, iterator last);

  MyString substr(size_type pos = 0, size_type count = npos) const;

  size_type find(const MyString& str, size_type pos = 0) const;
  size_type find(const char* s, size_type pos, size_type count) const;
  size_type find(const char* s, size_type pos = 0) const;
  size_type find(char ch, size_type pos = 0) const;

  static const size_type npos;

 private:
  // Adjust the storage space size to `new_capacity`. Change `capacity_`
  // accordingly. Caller should ensure `new_capacity` > `size_`.
  void reallocate(size_type new_capacity);

  size_type size_;
  size_type capacity_;
  value_type* data_;
};

template <class Iterator>
Iterator operator+(MyString::difference_type n, Iterator it);

std::ostream& operator<<(std::ostream& os, const MyString& s);

bool operator==(const MyString& lhs, const MyString& rhs);
bool operator!=(const MyString& lhs, const MyString& rhs);

#endif  // _MYSTRING_H_
