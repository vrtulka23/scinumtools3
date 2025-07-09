#ifndef VAL_SETTINGS_H
#define VAL_SETTINGS_H

#include "../settings.h"
#include "../puq/quantity.h"

namespace val {
    
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

#endif // VAL_SETTINGS_H
