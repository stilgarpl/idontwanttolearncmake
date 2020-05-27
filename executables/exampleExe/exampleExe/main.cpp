#include <exampleLib/ExampleLibClass.h>
#include <boost/regex.hpp>
#include <iostream>
int main() {
  std::string s = "Boost Libraries";
  boost::regex expr{"\\w+\\s\\w+"};
  std::cout << std::boolalpha << boost::regex_match(s, expr) << '\n';
    ExampleLibClass example;
    example.printSuccess();
    return 0;

}