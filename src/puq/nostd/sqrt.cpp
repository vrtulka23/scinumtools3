#include "nostd.h"

namespace puq {
  namespace nostd {

    MAGNITUDE_PRECISION sqrt(const MAGNITUDE_PRECISION& m) {
      return std::sqrt(m);
    }

#ifdef MAGNITUDE_ARRAYS
    Array sqrt(const Array& a) {
      ArrayValue av;
      av.resize(a.size());
      for (int i=0; i<a.size(); i++)
	av[i] = std::sqrt(a[i]);
      return Array(av,a.shape());
    }
#endif
  
#ifdef MAGNITUDE_ERRORS
    Magnitude sqrt(const Magnitude& m) {
      // y ± Dz = pow(x ± Dx, 0.5) -> Dy = 0.5 * pow(x, -0.5) * Dx
      return Magnitude(sqrt(m.value), 0.5*pow(m.value, -0.5)*m.error);  
    }
#endif
    
  }
}
