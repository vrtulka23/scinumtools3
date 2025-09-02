#ifndef PUQ_BASE_UNITS_H
#define PUQ_BASE_UNITS_H

#include "../exponent.h"
#include "../settings.h"
#include "dimensions.h"

namespace snt::puq {

  class BaseUnit {
  public:
    std::string prefix;
    std::string unit;
    EXPONENT_TYPE exponent;
    BaseUnit() {};
    BaseUnit(const EXPONENT_INT_PRECISION& n) : exponent(n) {};
#ifdef EXPONENT_FRACTIONS
    BaseUnit(const EXPONENT_INT_PRECISION& n, const EXPONENT_INT_PRECISION& d) : exponent(n, d) {};
#endif
    BaseUnit(const std::string& p, const std::string& u, const EXPONENT_TYPE& e) : prefix(p), unit(u), exponent(e) {};
#ifdef EXPONENT_FRACTIONS
    BaseUnit(const std::string& p, const std::string& u, const EXPONENT_INT_PRECISION& n, const EXPONENT_INT_PRECISION& d) : prefix(p), unit(u), exponent(n, d) {};
#endif
    std::string to_string(const UnitFormat& format = UnitFormat());
  };

  typedef std::vector<BaseUnit> BaseUnitsList;
  class BaseUnits {
  private:
    BaseUnitsList baseunits;

  public:
    BaseUnits() {}
    BaseUnits(const std::string& s);
    BaseUnits(const BaseUnitsList& bu) : baseunits(bu) {}
    void append(const BaseUnit& bu);
    void append(const std::string& p, const std::string& u, EXPONENT_TYPE e);
#ifdef EXPONENT_FRACTIONS
    void append(const std::string& p, const std::string& u, EXPONENT_INT_PRECISION n, EXPONENT_INT_PRECISION d);
#endif
    std::string to_string(const UnitFormat& format = UnitFormat()) const;
    const BaseUnit& operator[](int index) const;
    friend BaseUnits operator+(const BaseUnits& bu1, const BaseUnits& bu2);
    friend BaseUnits operator-(const BaseUnits& bu1, const BaseUnits& bu2);
    friend std::ostream& operator<<(std::ostream& os, const BaseUnits& bu);
    void operator+=(const BaseUnits& bu);
    void operator-=(const BaseUnits& bu);
    void operator*=(const EXPONENT_TYPE& e);
    BaseUnitsList::const_iterator begin() const;
    BaseUnitsList::const_iterator end() const;
    std::size_t size() const;
    Dimensions dimensions() const;
  };

} // namespace snt::puq

#endif // PUQ_BASE_UNITS_H
