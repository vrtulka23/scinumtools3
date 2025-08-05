#include "nostd.h"

namespace puq {
  namespace nostd {

    extern MAGNITUDE_PRECISION max(const MAGNITUDE_PRECISION& m1, const MAGNITUDE_PRECISION& m2) {
      return std::max(m1, m2);
    }

#if defined(MAGNITUDE_ARRAYS)
    extern Array max(const Array& a1, const Array& a2) {
      auto fn = [](const MAGNITUDE_PRECISION& v1, const MAGNITUDE_PRECISION& v2) {
	return std::max(v1, v2);
      };
      return Array::const_operation(a1, a2, fn);
    }
#elif defined(MAGNITUDE_VALUES)
    val::BaseValue::PointerType max(val::BaseValue::PointerType a1, val::BaseValue::PointerType a2) {
      return a1->math_max(a2.get());
    }            
#endif
  
#ifdef MAGNITUDE_ERRORS
    extern Magnitude max(const Magnitude& m1, const Magnitude& m2) {
      // x ± Dx = max(x ± Dx, y ± Dy)  <- if x > y
      // y ± Dy = max(x ± Dx, y ± Dy)  <- if y > x
#ifdef MAGNITUDE_VALUES
      MAGNITUDE_VALUE value = m1.value->math_max(m2.value.get());
      if (m1.error && m2.error)
	return Magnitude(std::move(value), m1.error->where(value->compare_equal(m1.value.get()).get(), m2.error.get()));
      else if (m1.error)
	return Magnitude(std::move(value), m1.error->clone());
      else if (m2.error)
	return Magnitude(std::move(value), m2.error->clone());
      else
	return Magnitude(std::move(value));
#else
      MAGNITUDE_VALUE value = max(m1.value, m2.value);
      return Magnitude(value, (value==m1.value) ? m1.error : m2.error );
#endif
    }
#endif

  }
}
