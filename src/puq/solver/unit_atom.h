#ifndef PUQ_UNIT_ATOM_H
#define PUQ_UNIT_ATOM_H

#include "../value/value.h"
#include "../../atom.h"

namespace puq {

  class AtomParsingExcept : public std::exception {
  private:
    std::string message;

  public:
    AtomParsingExcept(const std::string& m) : message(m) {}
    const char* what() const noexcept override {
      return message.c_str();
    }
  };

  class UnitAtom : public exs::AtomBase<UnitValue> {
  public:
    UnitAtom(UnitAtom& a) : AtomBase(a) {};
    UnitAtom(UnitValue v) : AtomBase(v) {};
    static UnitValue from_string(const std::string& s);
    std::string to_string();
    void math_power(EXPONENT_TYPE& e);
    void math_multiply(UnitAtom* other);
    void math_divide(UnitAtom* other);
  };

} // namespace puq

#endif // PUQ_UNIT_ATOM_H
