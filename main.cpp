#include <sstream>
#include <string>
#include <vector>

#include "io.h"

using namespace std;

struct SubResult {
  int quotient;
  vector<int> remainder;
};

vector<int> constructPolynomial(string input) {
  stringstream ss(input);
  vector<int> polynomial;
  string coefficient;
  while (getline(ss, coefficient, ' ')) {
    // TODO: error handling for stod
    polynomial.push_back(stod(coefficient));
  }
  return polynomial;
}

SubResult dividePolynomial(const vector<int> &numerator,
                           const vector<int> &denominator) {
  vector<int> product;
  vector<int> remainder;

  const int leadingTermN = numerator[0];
  const size_t degreeN = numerator.size() - 1;
  const int leadingTermD = denominator[0];
  const size_t degreeD = denominator.size() - 1;

  if (degreeN < degreeD) {
    return {0, numerator};
  }

  const int quotient = leadingTermN / leadingTermD;

  for (size_t i = 0; i < denominator.size(); i++) {
    product.push_back(denominator[i] * (leadingTermN / leadingTermD));
  }

  for (size_t i = 1; i < numerator.size(); i++) {
    remainder.push_back(numerator[i] - product[i]);
  }

  return {quotient, remainder};
}

bool isSamePolynomial(vector<int> polynomialA, vector<int> polynomialB) {
  if (polynomialA.size() != polynomialB.size()) {
    return false;
  }
  for (size_t i = 0; i < polynomialA.size(); i++) {
    if (polynomialA[i] != polynomialB[i]) {
      return false;
    }
  }
  return true;
};

bool isNullPolynomial(const vector<int> &polynomial) {
  if (!polynomial.size()) {
    return true;
  }
  return polynomial.size() <= 1 && !polynomial[0];
}

string polynomialToString(vector<int> polynomial) {
  string resultString = "";
  int coefficient;
  for (size_t i = 0; i < polynomial.size(); i++) {
    if (!polynomial[i]) {
      continue;
    }

    if (resultString.length()) {
      if (polynomial[i] < 0) {
        resultString += " - ";
      } else {
        resultString += " + ";
      }
      coefficient = abs(polynomial[i]);
    } else {
      coefficient = polynomial[i];
    }

    const int degree = polynomial.size() - i - 1;

    if (!degree || coefficient != 1) {
      resultString += to_string(coefficient);
    }

    if (degree > 1) {
      resultString += "x^" + to_string(degree);
    } else if (degree == 1) {
      resultString += "x";
    }
  }
  return resultString;
}

void printResult(const vector<int> &quotient, const vector<int> &remainder,
                 const vector<int> &denominator) {
  string displayString = polynomialToString(quotient);

  if (!isNullPolynomial(remainder)) {
    const string remainderAsString = "\\frac{" + polynomialToString(remainder) +
                                     "}{" + polynomialToString(denominator) +
                                     "}";
    if (displayString.length()) {
      displayString += " + ";
    }
    displayString += remainderAsString;
  }

  print(displayString);
}

int main() {
  //   const string numeratorAsString = getString("Enter the numerator: ");
  //   const string denominatorAsString = getString("Enter the denominator: ");
  //   const vector<int> denominator = constructPolynomial(denominatorAsString);
  //   vector<int> numerator = constructPolynomial(numeratorAsString);

  const vector<int> denominator = {1, -7};
  vector<int> numerator = {1, 2, -3, 4};

  vector<int> quotient;
  SubResult subResult;

  do {
    if (!isNullPolynomial(subResult.remainder)) {
      numerator = subResult.remainder;
    }

    subResult = dividePolynomial(numerator, denominator);

    if (subResult.quotient) {
      quotient.push_back(subResult.quotient);
    }

  } while (!isSamePolynomial(subResult.remainder, numerator) &&
           !isNullPolynomial(subResult.remainder));

  printResult(quotient, subResult.remainder, denominator);
}
