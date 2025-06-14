#include "nostd.h"

namespace puq {
  namespace nostd {

    extern MAGNITUDE_PRECISION max(const MAGNITUDE_PRECISION& m1, const MAGNITUDE_PRECISION& m2) {
      return std::max(m1, m2);
    }

#ifdef MAGNITUDE_ARRAYS
    extern Array max(const Array& a1, const Array& a2) {
      auto fn = [](const MAGNITUDE_PRECISION& v1, const MAGNITUDE_PRECISION& v2) {
	return std::max(v1, v2);
      };
      return Array::const_operation(a1, a2, fn);
    }
#endif
  
#ifdef MAGNITUDE_ERRORS
    extern Magnitude max(const Magnitude& m1, const Magnitude& m2) {
      // x ± Dx = max(x ± Dx, y ± Dy)  <- if x > y
      // y ± Dy = max(x ± Dx, y ± Dy)  <- if y > x
      MAGNITUDE_VALUE value = max(m1.value, m2.value);
      return Magnitude(value, (value==m1.value) ? m1.error : m2.error );
    }
#endif

  }
}
