#include "nostd.h"

namespace puq {
  namespace nostd {

    MAGNITUDE_PRECISION exp(const MAGNITUDE_PRECISION& e) {
      return std::exp(e);
    }

#if defined(MAGNITUDE_ARRAYS)
    Array exp(const Array& e) {
      ArrayValue av(e.size());
      for (int i=0; i<e.size(); i++)
	av[i] = std::exp(e[i]);
      return Array(av,e.shape());
    }
#elif defined(MAGNITUDE_VALUES)
    val::BaseValue::PointerType exp(val::BaseValue::PointerType a)
      return a->math_exp();
    }        
#endif
  
#ifdef MAGNITUDE_ERRORS
    Magnitude exp(const Magnitude& e) {
      // z ± Dz = pow(e, y ± Dy) -> Dz = pow(e, y) * log(e) * Dy
      return Magnitude(exp(e.value), exp(e.value)*e.error);
    }
#endif

    UnitValue exp(const UnitValue& uv) {
      return UnitValue(exp(uv.magnitude), uv.baseunits);
    }
    
  }
}
