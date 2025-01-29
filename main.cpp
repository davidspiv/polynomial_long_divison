#include <sstream>
#include <string>
#include <vector>

#include "io.h"

using namespace std;

struct SubResult {
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

SubResult dividePolynomial(const vector<int> &numerator,
                           const vector<int> &denominator) {
  vector<int> quotient;
  vector<int> product;
  vector<int> remainder;

  const int leadingTermN = numerator[0];
  const size_t degreeN = numerator.size() - 1;
  const int leadingTermD = denominator[0];
  const size_t degreeD = denominator.size() - 1;

  quotient.push_back(leadingTermN / leadingTermD);
  if (degreeN < degreeD) {
    return {vector<int>(1, 0), numerator};
  }

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

int getTerm(const vector<int> &polynomial) {
  for (size_t i = 0; i < polynomial.size(); i++) {
    if (polynomial[i]) {
      return polynomial[i];
    }
  }
  print("GET TERM FAILED");
  return 0;
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

bool isValidPolynomial(const vector<int> &polynomial) {
  if (!polynomial.size()) {
    return false;
  }
  return polynomial.size() > 1 || polynomial[0] != 0;
}

string polynomialToString(vector<int> polynomial) {
  string resultString = "";
  for (size_t i = 0; i < polynomial.size(); i++) {
    if (i) {
      if (polynomial[i] < 0) {
        resultString += " - ";
      } else {
        resultString += " + ";
      }
    }
    const int coefficient = abs(polynomial[i]);
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

int main() {
  string numeratorAsString = getString("Enter the numerator: ");
  string denominatorAsString = getString("Enter the denominator: ");
  vector<int> numerator = constructPolynomial(numeratorAsString);
  vector<int> denominator = constructPolynomial(denominatorAsString);

  vector<int> quotient;
  SubResult subResult;

  do {
    string newTerm = "";
    if (isValidPolynomial(subResult.remainder)) {
      numerator = subResult.remainder;
    }
    subResult = dividePolynomial(numerator, denominator);

    if (isValidPolynomial(subResult.quotient)) {
      quotient.push_back(getTerm(subResult.quotient));
    }

  } while (!isSamePolynomial(subResult.remainder, numerator) &&
           isValidPolynomial(subResult.remainder));

  string displayString = polynomialToString(quotient);

  if (isValidPolynomial(subResult.remainder)) {
    const string remainder = " + \\frac{" +
                             polynomialToString(subResult.remainder) + "}{" +
                             polynomialToString(denominator) + "}";
    displayString += remainder;
  }

  print(displayString);
}
