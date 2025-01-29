#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

template <typename T>
void print(T output, bool carriageReturn = 1) {
  if (carriageReturn) {
    cout << output << endl;
    return;
  }

  cout << output << flush;
}

string getString(const string &prompt) {
  string input = "";
  cout << prompt;
  getline(cin, input);

  while (input == "") {
    cout << "ERROR: no characters entered" << endl;
    cout << prompt;
    getline(cin, input);
  }

  return input;
}

struct SubResult {
  int quotient;
  vector<int> remainder;
};

bool validCharacters(string input) {
  for (size_t i = 0; i < input.length(); i++) {
    if (input[i] != ' ' && input[i] != '-' && !isdigit(input[i])) {
      print("ERROR: non-integer detected");
      return false;
    }
  }
  return true;
}

bool isNullString(string input) {
  for (size_t i = 0; i < input.length(); i++) {
    if (input[i] != ' ' && input[i] != '0') {
      return false;
    }
  }
  print("ERROR: polynomial is null");
  return true;
}

vector<int> getPoly(const string &message) {
  string polyAsString = getString(message);
  stringstream polyAsStream;
  string coefficient;
  vector<int> poly;

  while (!validCharacters(polyAsString) || isNullString(polyAsString)) {
    polyAsString = getString(message);
  };

  polyAsStream.str(polyAsString);

  while (getline(polyAsStream, coefficient, ' ')) {
    poly.push_back(stod(coefficient));
  }

  return poly;
}

bool isNullPoly(const vector<int> &poly) {
  if (!poly.size()) {
    return true;
  }
  return poly.size() <= 1 && !poly[0];
}

SubResult dividePoly(const vector<int> &numerator,
                     const vector<int> &denominator) {
  const int leadingTermNumerator = numerator[0];
  const int leadingTermDenominator = denominator[0];
  const int quotient = leadingTermNumerator / leadingTermDenominator;

  vector<int> product;
  vector<int> remainder;

  if (numerator.size() < denominator.size()) {
    return {0, numerator};
  }

  for (size_t i = 0; i < denominator.size(); i++) {
    product.push_back(denominator[i] * quotient);
  }

  for (size_t i = 1; i < numerator.size(); i++) {
    remainder.push_back(numerator[i] - product[i]);
  }

  return {quotient, remainder};
}

bool equivalentPolys(const vector<int> &polyA, const vector<int> &polyB) {
  if (polyA.size() != polyB.size()) {
    return false;
  }
  for (size_t i = 0; i < polyA.size(); i++) {
    if (polyA[i] != polyB[i]) {
      return false;
    }
  }
  return true;
};

string polyToString(const vector<int> &poly) {
  string resultString = "";
  int coefficient;
  for (size_t i = 0; i < poly.size(); i++) {
    if (!poly[i]) {
      continue;
    }

    if (resultString.length()) {
      if (poly[i] < 0) {
        resultString += " - ";
      } else {
        resultString += " + ";
      }
      coefficient = abs(poly[i]);
    } else {
      coefficient = poly[i];
    }

    const int degree = poly.size() - i - 1;

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

string buildResult(const vector<int> &quotient, const vector<int> &remainder,
                   const vector<int> &denominator) {
  string displayString = polyToString(quotient);

  if (!isNullPoly(remainder)) {
    const string remainderAsString = "\\frac{" + polyToString(remainder) +
                                     "}{" + polyToString(denominator) + "}";
    if (displayString.length()) {
      displayString += " + ";
    }
    displayString += remainderAsString;
  }
  return displayString;
}

int main() {
  vector<int> numerator = getPoly("Enter the numerator: ");
  const vector<int> denominator = getPoly("Enter the denominator: ");
  vector<int> quotient;
  SubResult subResult;

  do {
    if (!isNullPoly(subResult.remainder)) {
      numerator = subResult.remainder;
    }

    subResult = dividePoly(numerator, denominator);

    if (subResult.quotient) {
      quotient.push_back(subResult.quotient);
    }

  } while (!equivalentPolys(subResult.remainder, numerator) &&
           !isNullPoly(subResult.remainder));

  print("\nResult: " + buildResult(quotient, subResult.remainder, denominator));
}
