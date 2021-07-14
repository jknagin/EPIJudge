#include <string>
#include <vector>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

const std::array<std::string, 10> mapping = {
  "0",
  "1",
  "ABC",
  "DEF",
  "GHI",
  "JKL",
  "MNO",
  "PQRS",
  "TUV",
  "WXYZ",
};

void helper(const std::string& phone_number, int i, std::string& pnemonic, std::vector<std::string>& pnemonics)
{
  if (i == phone_number.length())
  {
    pnemonics.push_back(pnemonic);
    return;
  }
  std::string characters = mapping[phone_number[i] - '0'];
  for(const char& c : characters)
  {
    pnemonic.push_back(c);
    helper(phone_number, i + 1, pnemonic, pnemonics);
    pnemonic.erase(pnemonic.end() - 1);
  }
}

vector<string> PhoneMnemonic(const string& phone_number) {
  std::string pnemonic = "";
  std::vector<std::string> pnemonics;
  helper(phone_number, 0, pnemonic, pnemonics);
  return pnemonics;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"phone_number"};
  return GenericTestMain(args, "phone_number_mnemonic.cc",
                         "phone_number_mnemonic.tsv", &PhoneMnemonic,
                         UnorderedComparator{}, param_names);
}
