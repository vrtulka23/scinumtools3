#ifndef PUQ_MAGNITUDE_H
#define PUQ_MAGNITUDE_H

#include "settings.h"
#include "array.h"

namespace puq {

#ifdef MAGNITUDE_ERRORS
class Magnitude {
public:
#ifdef MAGNITUDE_ARRAYS
  Array value;
  Array error;
#else
  MAGNITUDE_PRECISION value;
  MAGNITUDE_PRECISION error;
#endif
  Magnitude(): value(1), error(0) {}
  Magnitude(const MAGNITUDE_PRECISION& m): value(m), error(0) {}
  Magnitude(const MAGNITUDE_PRECISION& m, const MAGNITUDE_PRECISION& e): value(m), error(e) {}
  static MAGNITUDE_PRECISION abs_to_rel(const MAGNITUDE_PRECISION& v, const MAGNITUDE_PRECISION& a);
  static MAGNITUDE_PRECISION rel_to_abs(const MAGNITUDE_PRECISION& v, const MAGNITUDE_PRECISION& r);
#ifdef MAGNITUDE_ARRAYS
  Magnitude(const Array& m);
  Magnitude(const Array& m, const Array& e);
  static Array abs_to_rel(const Array& v, const Array& a);
  static Array rel_to_abs(const Array& v, const Array& r);
#endif
  std::size_t size() const;
#ifdef MAGNITUDE_ARRAYS
  ArrayShape shape() const;
#endif
  std::string to_string(const UnitFormat& format = UnitFormat()) const;
  friend Magnitude operator-(const Magnitude& m1);
  friend Magnitude operator+(const Magnitude& m1, const Magnitude& m2);
  friend Magnitude operator-(const Magnitude& m1, const Magnitude& m2);
  friend Magnitude operator*(const Magnitude& m1, const Magnitude& m2);
  friend Magnitude operator/(const Magnitude& m1, const Magnitude& m2);
  friend std::ostream& operator<<(std::ostream& os, const Magnitude& m);
  void operator+=(const Magnitude& m);
  void operator-=(const Magnitude& m);
  void operator*=(const Magnitude& m);
  void operator/=(const Magnitude& m);
  bool operator==(const Magnitude& a) const;
  bool operator!=(const Magnitude& a) const;
  void pow(const EXPONENT_TYPE& e);
};
#endif
  
}
  
#endif // PUQ_MAGNITUDE_H
