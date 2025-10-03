#ifndef NOSTD_LOG10_H
#define NOSTD_LOG10_H

#include "nostd.h"

namespace snt::nostd {

  extern MAGNITUDE_PRECISION log10(const MAGNITUDE_PRECISION& m);
#if defined(MAGNITUDE_VALUES)
  extern val::BaseValue::PointerType log10(val::BaseValue::PointerType a);
#endif
#ifdef MAGNITUDE_ERRORS
  extern puq::Magnitude log10(const puq::Magnitude& m);
#endif

} // namespace snt::nostd

#endif // NOSTD_LOG10_H
