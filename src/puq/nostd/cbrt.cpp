#include "nostd.h"

namespace puq {
  namespace nostd {

    MAGNITUDE_PRECISION cbrt(const MAGNITUDE_PRECISION& m) {
      return std::cbrt(m);
    }

#ifdef MAGNITUDE_ARRAYS
    Array cbrt(const Array& a) {
      ArrayValue av(a.size());
      for (int i=0; i<a.size(); i++)
	av[i] = std::cbrt(a[i]);
      return Array(av,a.shape());
    }
#endif
  
#ifdef MAGNITUDE_ERRORS
    Magnitude cbrt(const Magnitude& m) {
      // y ± Dz = pow(x ± Dx, 1/3) -> Dy = 1/3 * pow(x, -2/3) * Dx
      constexpr MAGNITUDE_PRECISION third = 1./3.;
      return Magnitude(cbrt(m.value), third*pow(m.value, -2*third)*m.error);  
    }
#endif
    
  }
}
