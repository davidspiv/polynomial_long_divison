#include <sstream>
#include <string>
#include <vector>

#include "io.h"

using namespace std;

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
  vector<double> quotient;

  const double leadingTermN = numerator[0];
  const size_t degreeN = numerator.size() - 1;
  const double leadingTermD = denominator[0];
  const size_t degreeD = denominator.size() - 1;

  quotient.push_back(leadingTermN / leadingTermD);
  for (size_t i = 0; i < (degreeN - degreeD); i++) {
    quotient.push_back(0);
  }

  for (size_t i = 1; i < denominator.size(); i++) {
    print(denominator[i] * (leadingTermN / leadingTermD));
  }

  //   print(leadingTermN, 0);
  //   print(" ");
  //   print(degreeN);

  //   print(leadingTermD, 0);
  //   print(" ");
  //   print(degreeD);
}
