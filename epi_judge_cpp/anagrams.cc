#include <string>
#include <vector>
#include <unordered_map>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

vector<vector<string> > FindAnagrams(const vector<string>& dictionary) {
  // Create copy of dictionary and sort each word lexicographically
  std::vector<std::string> wordsSorted(dictionary);
  for(auto& word : wordsSorted) std::sort(word.begin(), word.end());

  // Map sorted words to their indices in the sorted words array
  std::unordered_map<std::string, std::vector<int> > words2indices;
  for(int i=0;i<wordsSorted.size();++i)
  {
    if (!words2indices.count(wordsSorted[i])) words2indices[wordsSorted[i]] = {};
    words2indices[wordsSorted[i]].push_back(i);
  }

  // For each sorted word, get its indices, use the indices to make vectors of strings which are anagrams of each other
  // Ensure each group of anagrams is at least 2 elements large
  std::vector<std::vector<std::string> > ret;
  for(auto it = words2indices.begin();it != words2indices.end();++it)
  {
    std::vector<int> indices = it->second;
    if (indices.size() > 1)
    {
      ret.push_back({});
      for(int i=0;i<indices.size();++i)
      {
        ret.back().push_back(dictionary[indices[i]]);
      }
    }
  }
  return ret;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"dictionary"};
  return GenericTestMain(args, "anagrams.cc", "anagrams.tsv", &FindAnagrams,
                         UnorderedComparator{}, param_names);
}
