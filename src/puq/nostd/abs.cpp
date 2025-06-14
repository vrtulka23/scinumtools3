#include "nostd.h"

namespace puq {
  namespace nostd {
  
    MAGNITUDE_PRECISION abs(const MAGNITUDE_PRECISION& m) {
      return std::abs(m);
    }

#ifdef MAGNITUDE_ARRAYS
    Array abs(const Array& a) {
      ArrayValue av(a.size());
      for (int i=0; i<a.size(); i++)
	av[i] = std::abs(a[i]);
      return Array(av,a.shape());
    }
#endif
  
#ifdef MAGNITUDE_ERRORS
    Magnitude abs(const Magnitude& m) {
      // abs(y ± Dy) = abs(y) ± Dy
      return Magnitude(abs(m.value), m.error);
    }
#endif
    
  }
}
