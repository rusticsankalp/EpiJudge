#include <vector>
#include <unordered_map>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"

class LruCache {
 public:
  LruCache(size_t capct): capacity(capct){}
  int Lookup(int isbn) {
      auto iter = isbn_price_table_.find(isbn);
      if (iter == isbn_price_table_.end())
          return -1;
      
      MoveToTop(iter->first, iter);
      return iter->second.second;
  }

  void Insert(int isbn, int price) {
      auto iter = isbn_price_table_.find(isbn);

      if (iter != isbn_price_table_.end()) {
          MoveToTop(iter->first, iter);
          return;
      }
      if (isbn_price_table_.size() == capacity) {
          int n = lru_queue_.back();
          isbn_price_table_.erase(n);
          lru_queue_.pop_back();
      }

      lru_queue_.emplace_front(isbn);
      isbn_price_table_[isbn] = { lru_queue_.begin(), price };
  }

  bool Erase(int isbn) {
      auto iter = isbn_price_table_.find(isbn);
      if (iter == isbn_price_table_.end())
          return false;

      lru_queue_.erase(iter->second.first);
      isbn_price_table_.erase(iter);
      return true;
  }

private:
    typedef std::unordered_map<int, std::pair<std::list<int>::iterator, int>> Table;

    void MoveToTop(int isbn, Table::iterator iter) {
        lru_queue_.erase(iter->second.first);
        lru_queue_.emplace_front(isbn);

        iter->second.first = lru_queue_.begin();
    }

    Table isbn_price_table_;
    std::list<int> lru_queue_;
    const size_t capacity;

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
