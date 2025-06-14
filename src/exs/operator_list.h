#ifndef EXS_OPERATOR_LIST_H
#define EXS_OPERATOR_LIST_H

#include <unordered_map>
#include <memory>
#include <vector>

namespace exs {
  
template <class A, typename S = EmptySettings>
class OperatorList {
  typedef std::unordered_map<int, std::shared_ptr<OperatorBase<A, S>>> OperatorListType;
public:
  OperatorListType operators;
  std::vector<int> order;
  OperatorBase<A, S>* select(int otype) {
    auto it = operators.find(otype);
    if (it != operators.end()) {
      return &(*(it->second));
    } else {
      throw std::logic_error("Selecting non existing operator");
    }
  };
  void append(int t, std::shared_ptr<OperatorBase<A, S>> o) {
    operators[t] = o;
    order.push_back(t);
  };
};

}
  
#endif // EXS_OPERATOR_LIST_H
