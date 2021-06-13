#include <string>

#include "test_framework/generic_test.h"
using std::string;
string ShortestEquivalentPath(const string& path) {
  if (path.empty()) return "";
  
  bool absolute = path[0] == '/';
  std::stack<std::string> st;

  std::stringstream ss(path);
  std::string token;
  while (std::getline(ss, token, '/'))
  {
    if (token == "" || token == ".") continue;
    else if (token != "..") st.push(token);
    else
    {
      if (!st.empty() && st.top() != "..")
      {
        st.pop();
      }
      // Either the top directory is a .. or there is no top directory
      // If the top directory is a .., then continue adding to it
      // If there is no top directory, 
        // if we are absolute, do nothing
        // if we are relative, add the ..
      else if (!absolute)
      {
        st.push(token);
      }
    }
  }

  // reverse order of elements
  std::stack<std::string> st2;
  while (!st.empty())
  {
    st2.push(st.top());
    st.pop();
  }

  std::stringstream retSS;
  if (absolute) retSS << "/";
  while (!st2.empty())
  {
		retSS << st2.top();
    st2.pop();
    if (!st2.empty())
    {
      retSS << "/";
    }
  }

  std::string path_ = retSS.str();
  return path_;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"path"};
  return GenericTestMain(args, "directory_path_normalization.cc",
                         "directory_path_normalization.tsv",
                         &ShortestEquivalentPath, DefaultComparator{},
                         param_names);
}
