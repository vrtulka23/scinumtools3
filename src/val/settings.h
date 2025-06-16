#ifndef VAL_VALUES_SETTINGS_H
#define VAL_VALUES_SETTINGS_H

#include "puq/quantity.h"

namespace val {

  // Keywords
  constexpr std::string_view KEYWORD_TRUE        = "true";
  constexpr std::string_view KEYWORD_FALSE       = "false";
  
  // Various settings
  constexpr int DISPLAY_FLOAT_PRECISION      = 4;

  // Define a pointer type for OpenSNT-puq Quantity
  // TODO: move this to the puq
  namespace Quantity {
    typedef std::unique_ptr<puq::Quantity> PointerType;
  }  
  
  // Define common array types
  namespace Array {
    struct RangeStruct {
      int dmin;
      int dmax;
      bool operator==(const RangeStruct& other) const {
	return (dmin == other.dmin) && (dmax == other.dmax);
      };
    };
    typedef std::vector<std::string> StringType; // holds raw string values
    typedef std::vector<RangeStruct> RangeType;  // array dimension ranges
    typedef std::vector<int> ShapeType;          // array shape
    constexpr int max_range = -1;                // maximum range value
  }

}

#endif // VAL_VALUES_SETTINGS_H
