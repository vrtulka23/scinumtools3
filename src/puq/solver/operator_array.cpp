#include "solver.h"

namespace puq {
  
#ifdef MAGNITUDE_ARRAYS

void OperatorArray::operate_group(exs::TokenListBase<UnitAtom> *tokens) {
  exs::Token<UnitAtom> group;
#ifdef MAGNITUDE_ERRORS
  ArrayValue nv;
  ArrayValue ne;
  for (size_t i=0; i<num_groups; i++) {
    group = tokens->get_left();
    nv.push_back( group.atom->value.magnitude.value[0] );
    ne.push_back( group.atom->value.magnitude.error[0] );
  }
  std::reverse(nv.begin(), nv.end());
  std::reverse(ne.begin(), ne.end());
  group.atom->value.magnitude.value = Array(nv,{nv.size()});
  group.atom->value.magnitude.error = Array(ne,{nv.size()});
#else
  ArrayValue nv;
  for (size_t i=0; i<num_groups; i++) {
    group = tokens->get_left();
    nv.push_back( group.atom->value.magnitude[0] );
  }
  std::reverse(nv.begin(), nv.end());
  group.atom->value.magnitude = Array(nv);
#endif
  tokens->put_left(group);
};

#endif

}
