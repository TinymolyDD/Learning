#ifndef _MYSTRING_H_
#define _MYSTRING_H_
// 头文件保护

#include <cstddef>
#include <iostream>

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

   private:
    typedef Iterator<CharT> iterator;

   public:
    Iterator(CharT* element_ptr) : element_ptr_(element_ptr) {}
    Iterator() : element_ptr_(nullptr) {}

    reference operator*() const { return *element_ptr_; }

    iterator& operator++() {
      ++element_ptr_;
      return *this;
    }

    iterator operator++(int) { return {element_ptr_++}; }

    iterator& operator--() {
      --element_ptr_;
      return *this;
    }

    iterator operator--(int) { return {element_ptr_--}; }

    iterator& operator+=(difference_type n) {
      element_ptr_ += n;
      return *this;
    }

    iterator& operator-=(difference_type n) {
      element_ptr_ -= n;
      return *this;
    }

    iterator operator+(difference_type n) const { return {element_ptr_ + n}; }

    iterator operator-(difference_type n) const { return {element_ptr_ - n}; }

    reference operator[](difference_type n) const {
      return *(element_ptr_ + n);
    }

    difference_type operator-(iterator it) const {
      return this->element_ptr_ - it.element_ptr_;
    }

    bool operator<(iterator it) const { return *this - it < 0; }
    bool operator>(iterator it) const { return *this - it > 0; }
    bool operator>=(iterator it) const { return *this - it >= 0; }
    bool operator<=(iterator it) const { return *this - it <= 0; }

   private:
    CharT* element_ptr_;
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
  // MyString& insert(size_type index, const MyString& str, size_type s_index, size_type count);

  MyString& erase(size_type index = 0, size_type count = npos);

  MyString substr(size_type pos = 0, size_type count = npos) const;

 private:
  // Adjust the storage space size to `new_capacity`. Change `capacity_`
  // accordingly. Caller should ensure `new_capacity` > `size_`.
  void reallocate(size_type new_capacity);
  
 public: 
  static const size_type npos;

 private:
  size_type size_;
  size_type capacity_;
  value_type* data_;
};

template <class Iterator>
Iterator operator+(MyString::difference_type n, Iterator it);

std::ostream& operator<<(std::ostream& os, const MyString& s);

#endif  // _MYSTRING_H_
