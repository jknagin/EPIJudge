#include <vector>
#include <unordered_map>
#include <list>
#include <utility>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"

class LruCache {
 private:
  // table maps from integer keys to iterators in linked list lst, as well as the value associated with the key
  std::unordered_map<int, std::pair<std::list<int>::iterator, int> > table;
  std::list<int> lst;
  int capacity;

  // Erase key from lst by iterator
  // Push key to front of lst
  // Update iterator mapped to by isbn to lst.begin()
  void moveToFront(const int& isbn)
  {
    std::list<int>::iterator it = table[isbn].first;
    lst.erase(it);
    lst.push_front(isbn);
    table[isbn].first = lst.begin();
  }

 public:
  LruCache(size_t capacity) {
    this->capacity = capacity;
  }

  // If key exists, move it to the front and return the value associated with it
  int Lookup(int isbn) {
    if (table.count(isbn))
    {
      moveToFront(isbn);
      return table[isbn].second;
    }
    else return -1;
  }

  // If the key exists, just move it to the front
  // Otherwise, if the cache is full, evict the LRU element. Then add the new element
  void Insert(int isbn, int price) {
    if (table.count(isbn))
    {
      moveToFront(isbn);
    }
    else
    {
      // To evict, erase from lst by iterator, and erase from table by key
      if (table.size() == capacity)
      {
        int isbnToRemove = lst.back();
        std::list<int>::iterator it = table[isbnToRemove].first;
        lst.erase(it);
        table.erase(isbnToRemove);
      }

      // Push new key to front of lst
      // Add key to table, with value from make_pair of begin of lst, and price
      lst.push_front(isbn);
      table[isbn] = std::make_pair(lst.begin(), price);
    }
  }

  // If key exists, erase it from lst by iterator and from table by value, and return true
  // Else, return falses
  bool Erase(int isbn)
  {
    if (table.count(isbn))
    {
      std::list<int>::iterator it = table[isbn].first;
      lst.erase(it);
      table.erase(isbn);
      return true;
    }
    else return false;
  }

};

struct Op {
  std::string code;
  int arg1;
  int arg2;
};

namespace test_framework {
template <>
struct SerializationTrait<Op> : UserSerTrait<Op, std::string, int, int> {};
}  // namespace test_framework

void LruCacheTester(const std::vector<Op>& commands) {
  if (commands.empty() || commands[0].code != "LruCache") {
    throw std::runtime_error("Expected LruCache as first command");
  }
  LruCache cache(commands[0].arg1);

  for (int i = 1; i < commands.size(); i++) {
    auto& cmd = commands[i];
    if (cmd.code == "lookup") {
      int result = cache.Lookup(cmd.arg1);
      if (result != cmd.arg2) {
        throw TestFailure("Lookup: expected " + std::to_string(cmd.arg2) +
                          ", got " + std::to_string(result));
      }
    } else if (cmd.code == "insert") {
      cache.Insert(cmd.arg1, cmd.arg2);
    } else if (cmd.code == "erase") {
      bool result = cache.Erase(cmd.arg1);
      if (result != cmd.arg2) {
        throw TestFailure("Erase: expected " + std::to_string(cmd.arg2) +
                          ", got " + std::to_string(result));
      }
    } else {
      throw std::runtime_error("Unexpected command " + cmd.code);
    }
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"commands"};
  return GenericTestMain(args, "lru_cache.cc", "lru_cache.tsv", &LruCacheTester,
                         DefaultComparator{}, param_names);
}
