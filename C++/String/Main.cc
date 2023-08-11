#include <cstring>
#include <iostream>

#include "MyString.h"

template <std::size_t N>
MyString ToMyString(const char (&s)[N]) {
  return {s, N - 1};
}

int main() {  
  MyString s1 = "AABCCC", s2 = "88244", s3;
  s1.insert(1, s2, 2, 3);
  std::cout << "Insert result: " << (s1 == "A244ABCCC") << std::endl;
  s1.insert(s1.begin() + 3, 4, 'k');
  std::cout << "Insert result: " << (s1 == "A24kkkk4ABCCC") << std::endl;
  MyString::iterator it = s3.insert(s3.end(), 1, 'v');
  std::cout << "Insert result: " << (it == s3.begin()) << std::endl;
  s1.erase(s1.begin() + 3, s1.begin() + 6);
  std::cout << "Erase result: " << (s1 == "A24k4ABCCC") << std::endl;
  s1.erase(s1.begin() + 3);
  std::cout << "Erase result: " << (s1 == "A244ABCCC") << std::endl;
  std::cout << "Find result: " << (s1.find("CC") == 6) << std::endl;
  std::cout << "Find result: " << (s1.find('4') == 2) << std::endl;
  return 0;
}