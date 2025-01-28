#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string getString(const string& prompt) {
  string input = "";
  cout << prompt;
  getline(cin, input);

  while (input == "") {
    cout << "No characters entered." << endl;
    cout << prompt;
    getline(cin, input);
  }

  return input;
}

template <typename T>
void print(T output, bool carriageReturn = 1) {
  if (carriageReturn) {
    cout << output << endl;
    return;
  }

  cout << output << flush;
}

vector<double> constructPolynomial(string input) {
  stringstream ss(input);
  vector<double> polynomial;
  string coefficient;
  while (getline(ss, coefficient, ' ')) {
    // toDO: error handling for stod
    polynomial.push_back(stod(coefficient));
  }
  return polynomial;
}

int main() {
  //   string numeratorAsString = getString("Enter the numerator: ");
  //   string denominatorAsString = getString("Enter the denominator: ");
  //   vector<double> numerator = constructPolynomial(numeratorAsString);
  //   denominator = constructPolynomial(denominatorAsString);
  vector<double> numerator = {1, 5, 6};
  vector<double> denominator = {1, 2};

  for (size_t i = 0; i < numerator.size(); i++) {
    print(numerator[i]);
  }
}
