#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"
class Queue {
 public:
   std::vector<int> data;
   int head;
	 int tail;
   size_t numElements;
   Queue(size_t capacity) : head(0), tail(0), numElements(0), data(capacity)
   {
   }

  void Enqueue(int x) {
    /* If we add to a full queue:
      * left shift the head back to the start of data
      * set head to 0, right to numElements (queue is in interval [head, tail) )
      * increase the size of data
      */
    if (numElements == data.size())
    {
      std::rotate(data.begin(), data.begin() + head, data.end());
      head = 0;
      tail = numElements;
      data.resize(2 * data.size());
    }

    // Normal insertion, modulo tail by data.size() to wrap it back to 0 if it goes out of bounds
		data[tail] = x;
		++numElements;
		++tail;
    tail = tail % data.size();
  }
  int Dequeue() {
    // Normal removal, just increment head and wrap it around to 0 with modulo data.size()
    int ret = data[head];
    ++head;
    head = head % data.size();
    --numElements;
    return ret;
  }

  int Size() const {
    return numElements;
  }
};
struct QueueOp {
  enum class Operation { kConstruct, kDequeue, kEnqueue, kSize } op;
  int argument;

  QueueOp(const std::string& op_string, int arg) : argument(arg) {
    if (op_string == "Queue") {
      op = Operation::kConstruct;
    } else if (op_string == "dequeue") {
      op = Operation::kDequeue;
    } else if (op_string == "enqueue") {
      op = Operation::kEnqueue;
    } else if (op_string == "size") {
      op = Operation::kSize;
    } else {
      throw std::runtime_error("Unsupported queue operation: " + op_string);
    }
  }

  void execute(Queue& q) const {
    switch (op) {
      case Operation::kConstruct:
        // Hack to bypass deleted assign operator
        q.~Queue();
        new (&q) Queue(argument);
        break;
      case Operation::kDequeue: {
        int result = q.Dequeue();
        if (result != argument) {
          throw TestFailure("Dequeue: expected " + std::to_string(argument) +
                            ", got " + std::to_string(result));
        }
      } break;
      case Operation::kEnqueue:
        q.Enqueue(argument);
        break;
      case Operation::kSize: {
        int s = q.Size();
        if (s != argument) {
          throw TestFailure("Size: expected " + std::to_string(argument) +
                            ", got " + std::to_string(s));
        }
      } break;
    }
  }
};

namespace test_framework {
template <>
struct SerializationTrait<QueueOp> : UserSerTrait<QueueOp, std::string, int> {};
}  // namespace test_framework

void QueueTester(const std::vector<QueueOp>& ops) {
  Queue q(0);
  for (auto& op : ops) {
    op.execute(q);
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"ops"};
  return GenericTestMain(args, "circular_queue.cc", "circular_queue.tsv",
                         &QueueTester, DefaultComparator{}, param_names);
}
