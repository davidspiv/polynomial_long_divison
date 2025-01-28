#include <sstream>
#include <string>
#include <vector>

#include "io.h"

using namespace std;

struct Result {
  vector<double> quotient;
  vector<double> remainder;
};

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

Result dividePolynomial(vector<double> numerator, vector<double> denominator) {
  vector<double> quotient;
  vector<double> product;
  vector<double> remainder(quotient.size());

  const double leadingTermN = numerator[0];
  const size_t degreeN = numerator.size() - 1;
  const double leadingTermD = denominator[0];
  const size_t degreeD = denominator.size() - 1;

  quotient.push_back(leadingTermN / leadingTermD);
  for (size_t i = 0; i < (degreeN - degreeD); i++) {
    quotient.push_back(0);
  }

  for (size_t i = 0; i < denominator.size(); i++) {
    product.push_back(denominator[i] * (leadingTermN / leadingTermD));
  }

  for (size_t i = 0; i < (degreeN - degreeD); i++) {
    product.push_back(0);
  }

  for (size_t i = 0; i < numerator.size(); i++) {
    remainder.push_back(numerator[i] - product[i]);
  }

  return {quotient, remainder};
}

int main() {
  //   string numeratorAsString = getString("Enter the numerator: ");
  //   string denominatorAsString = getString("Enter the denominator: ");
  //   vector<double> numerator = constructPolynomial(numeratorAsString);
  //   denominator = constructPolynomial(denominatorAsString);
  vector<double> numerator = {1, 5, 6};
  vector<double> denominator = {1, 2};
  vector<double> quotient;
  vector<double> newNumerator;

  Result result = dividePolynomial(numerator, denominator);

  result = dividePolynomial(result.remainder, denominator);

  for (size_t i = 0; i < result.remainder.size(); i++) {
    print(result.remainder[i]);
  }

  //   print(leadingTermN, 0);
  //   print(" ");
  //   print(degreeN);

  //   print(leadingTermD, 0);
  //   print(" ");
  //   print(degreeD);
}
