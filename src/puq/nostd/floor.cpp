#include "nostd.h"

namespace puq {
  namespace nostd {

    MAGNITUDE_PRECISION floor(const MAGNITUDE_PRECISION& m) {
      return std::floor(m);
    }

#ifdef MAGNITUDE_ARRAYS
    Array floor(const Array& a) {
      ArrayValue av(a.size());
      for (int i=0; i<a.size(); i++)
	av[i] = std::floor(a[i]);
      return Array(av,a.shape());
    }
#endif
  
#ifdef MAGNITUDE_ERRORS
    Magnitude floor(const Magnitude& m) {
      return Magnitude(floor(m.value));
    }
#endif

  }
}
