#include <memory>

#import "main.h"

int main() {

  // modifying default operator symbols
  exs::OperatorList<CustomAtom> operators;
  operators.append(exs::LOWER_OPERATOR, std::make_shared<exs::OperatorLower<CustomAtom>>());
  operators.append(LENGTH_OPERATOR, std::make_shared<OperatorLength>());

  // changing default operation steps
  exs::StepList steps;
  steps.append(exs::GROUP_OPERATION, {LENGTH_OPERATOR});
  steps.append(exs::BINARY_OPERATION, {exs::LOWER_OPERATOR});
  
  exs::Solver<CustomAtom> solver(operators, steps);
  CustomAtom atom = solver.solve("apple < len(hospital)");
  atom.print();

  /*
   * Equivalent c++ notation:
   * std::string("apple").size() < std::string("hospital").size() == true
   */
}

