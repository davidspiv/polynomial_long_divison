#include <iostream>

std::string getString(const std::string& prompt);

template <typename T>
void print(T output, bool carriageReturn = 1) {
  if (carriageReturn) {
    std::cout << output << std::endl;
    return;
  }

  std::cout << output << std::flush;
}
