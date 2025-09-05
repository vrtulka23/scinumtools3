#ifndef PUQ_CALCULATOR_ATOM_H
#define PUQ_CALCULATOR_ATOM_H

#include "../../exs.h"
#include "../quantity.h"

namespace snt::puq {

  class CalculatorAtom : public exs::AtomBase<Quantity> {
  public:
    CalculatorAtom(CalculatorAtom& a) : AtomBase(a) {};
    CalculatorAtom(Quantity v) : AtomBase(v) {};
    static Quantity from_string(std::string& s);
    std::string to_string();
    void math_add(CalculatorAtom* other);
    void math_subtract(CalculatorAtom* other);
    void math_negate();
    void math_multiply(CalculatorAtom* other);
    void math_divide(CalculatorAtom* other);
  };  
  
}

#endif // PUQ_CALCULATOR_ATOM_H
