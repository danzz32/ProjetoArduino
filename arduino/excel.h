#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class excel {
private:
  std::string arquivo;
  std::vector<std::vector<std::string>> dados;

public:
  excel() {
    this->arquivo = "dados.csv";
    this->dados = NULL;
  }
}