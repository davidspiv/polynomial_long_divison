#include <sstream>
#include <string>
#include <vector>

#include "io.h"

using namespace std;

struct Result {
  vector<int> quotient;
  vector<int> remainder;
};

vector<int> constructPolynomial(string input) {
  stringstream ss(input);
  vector<int> polynomial;
  string coefficient;
  while (getline(ss, coefficient, ' ')) {
    // toDO: error handling for stod
    polynomial.push_back(stod(coefficient));
  }
  return polynomial;
}

Result dividePolynomial(const vector<int> &numerator, vector<int> denominator) {
  vector<int> quotient;
  vector<int> product;
  vector<int> remainder(quotient.size());

  const int leadingTermN = numerator[0];
  const size_t degreeN = numerator.size() - 1;
  const int leadingTermD = denominator[0];
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

  for (size_t i = 1; i < numerator.size(); i++) {
    remainder.push_back(numerator[i] - product[i]);
  }

  return {quotient, remainder};
}

string getTerm(const vector<int> &polynomial) {
  for (size_t i = 0; i < polynomial.size(); i++) {
    if (polynomial[i] != 0) {
      const string coeff = to_string(polynomial[i]);
      if (polynomial.size() - 1 - i == 0) {
        return coeff;
      } else if (polynomial.size() - 1 - i == 1) {
        return coeff + "x";
      }
      const string degree = to_string(polynomial.size() - 1 - i);

      return coeff + "x^" + degree;
    }
  }
  return "";
}

int main() {
  //   string numeratorAsString = getString("Enter the numerator: ");
  //   string denominatorAsString = getString("Enter the denominator: ");
  //   vector<int> numerator = constructPolynomial(numeratorAsString);
  //   denominator = constructPolynomial(denominatorAsString);
  vector<int> numerator = {2, 8, -6, 10};
  vector<int> denominator = {1, -2};
  vector<int> quotient;

  string displayResult = "";

  Result result = dividePolynomial(numerator, denominator);

  displayResult += getTerm(result.quotient);

  result = dividePolynomial(result.remainder, denominator);

  displayResult += " + " + getTerm(result.quotient);

  result = dividePolynomial(result.remainder, denominator);

  displayResult += " + " + getTerm(result.quotient);

  for (size_t i = 0; i < result.remainder.size(); i++) {
    print(result.remainder[i]);
  }

  print(displayResult);
}
