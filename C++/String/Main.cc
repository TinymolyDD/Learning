#include <iostream>

#include "MyString.h"

int main() {  
  MyString s1(4, '=');
  std::cout << s1 << std::endl;
  MyString s2(s1, 1, 2);
  s1[1] = '6';
  std::cout << s1 << " " << s2 << std::endl;

  MyString s3 = "kkkgglla";
  s3.resize(8);
  std::cout << s3 << " " << s3.size() << std::endl;
  s3.resize(5);
  std::cout << s3 << " " << s3.size() << std::endl;
  s3.resize(10);
  std::cout << s3 << " " << s3.size() << std::endl;

  MyString s4 = "123";
  s4.append("xyz");
  std::cout << s4 << std::endl;
  s4.append(2, '-');
  std::cout << s4 << std::endl;
  s4.append("qqtttt", 3);
  std::cout << s4 << std::endl;
  MyString s5 = "haha";
  s4.append(s5, 1, 2);
  std::cout << s4 << std::endl;
  s4.insert(1, 3, '*');
  std::cout << s4 << std::endl;
  s4.insert(4, "ppp");
  std::cout << s4 << std::endl;
  s4.insert(4, "uuuuu", 2);
  std::cout << s4 << std::endl;
  MyString s6 = "lalala";
  s4.insert(5, s6);
  std::cout << s4 << std::endl;

  return 0;
}