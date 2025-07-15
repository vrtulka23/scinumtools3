#include <sstream>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <format>
#include <algorithm>

#include "magnitude.h"
#include "nostd/nostd.h"

#ifdef MAGNITUDE_ERRORS

namespace puq {
  
#if defined(MAGNITUDE_ARRAYS)

  Magnitude::Magnitude(const Array& m): value(m), error(0) {
    ArrayValue av;
    for (int i=0; i<m.size(); i++)
      av.push_back(0);
    error = Array(av,m.shape());
  }

  Magnitude::Magnitude(const Array& m, const Array& e): value(m), error(e) {
    if (m.size()!=e.size()) 
      throw std::invalid_argument("Value and error arrays have different size: "+std::to_string(m.size())+" != "+std::to_string(e.size()));
  }

#elif defined(MAGNITUDE_VALUES)

  Magnitude::Magnitude(val::BaseValue::PointerType m): value(m), error(0) {
    ArrayValue av;
    for (int i=0; i<m->size(); i++)
      av.push_back(0);
    error = Array(av,m->shape());
  }

  Magnitude::Magnitude(val::BaseValue::PointerType m, val::BaseValue::PointerType e): value(m), error(e) {
    if (m->size()!=e->size()) 
      throw std::invalid_argument("Value and error arrays have different size: "+std::to_string(m->size())+" != "+std::to_string(e->size()));
  }

#endif

  /*
   * Convert absolute and relative (in %) errors
   */
  MAGNITUDE_PRECISION Magnitude::abs_to_rel(const MAGNITUDE_PRECISION& v, const MAGNITUDE_PRECISION& e) {
    return 100*e/v;
  };

  MAGNITUDE_PRECISION Magnitude::rel_to_abs(const MAGNITUDE_PRECISION& v, const MAGNITUDE_PRECISION& e) {
    return v*e/100;
  };

#if defined(MAGNITUDE_ARRAYS)

  Array Magnitude::abs_to_rel(const Array& v, const Array& e) {
    return Array::filled(100, v.size())*e/v;
  };

  Array Magnitude::rel_to_abs(const Array& v, const Array& e) {
    return v*e/Array::filled(100, v.size());
  };

#elif defined(MAGNITUDE_VALUESS)
  // DEBUG: need to implement properly
  Array Magnitude::abs_to_rel(val::BaseValue::PointerType v, val::BaseValue::PointerType e) {
    return Array::filled(100, v.size())*e/v;
  };

  Array Magnitude::rel_to_abs(val::BaseValue::PointerType v, val::BaseValue::PointerType e) {
    return v*e/Array::filled(100, v.size());
  };

#endif

  /*
   * Return a string representation of a magnitude
   */
  std::string _to_string(const MAGNITUDE_PRECISION& value, const MAGNITUDE_PRECISION& error, const UnitFormat& format) {
    std::stringstream ss;
    int exp_val  = std::floor(std::log10(value));
    if (error==0 || !format.display_error()) {
      ss << std::setprecision(format.precision);
      ss << value << std::scientific;
    } else {
      int exp_err  = std::floor(std::log10(error));
      int exp_diff = std::abs(exp_val-exp_err)+1;
      MAGNITUDE_PRECISION val_mag = value*std::pow(10,-exp_val);
      int val_err  = std::round(error*std::pow(10,1-exp_err));
      ss << std::vformat("{:.0"+std::to_string(exp_diff)+"f}", std::make_format_args(val_mag));
      ss << std::format("({:2d})", val_err);
      if (exp_val!=0)
	ss << (exp_val>=0 ? "e+" : "e-") << std::format("{:-02d}", std::abs(exp_val));
    }
    return ss.str();  
  }
  std::string Magnitude::to_string(const UnitFormat& format) const {
    std::stringstream ss;
    if (error==0 || !format.display_error()) {
#if defined(MAGNITUDE_ARRAYS)
      ss << value.to_string(format);
#elif defined(MAGNITUDE_VALUES)
      // TODO: implement format
      ss << value->to_string(format);
#else
      ss << std::setprecision(format.precision);
      ss << value << std::scientific;
#endif
    }
    else {
#if defined(MAGNITUDE_ARRAYS)
      if (value.size()==1)
	ss << _to_string(value[0], error[0], format);
      else if (value.size()==2) {
	ss << SYMBOL_ARRAY_START << _to_string(value[0], error[0], format);
	ss << SYMBOL_ARRAY_SEPARATOR << " " << _to_string(value[1], error[1], format);
	ss << SYMBOL_ARRAY_END;
      } else {
	ss << SYMBOL_ARRAY_START << _to_string(value[0], error[0], format); 
	ss << SYMBOL_ARRAY_SEPARATOR << " " << _to_string(value[1], error[1], format);
	ss << SYMBOL_ARRAY_SEPARATOR << " " << SYMBOL_ARRAY_MORE << SYMBOL_ARRAY_END;
      }
#elif defined(MAGNITUDE_VALUES)
      if (value->size()==1)
	ss << _to_string(value->get_value(0), error->get_value(0), format);
      else if (value->size()==2) {
	ss << SYMBOL_ARRAY_START << _to_string(value->get_value(0), error->get_value(0), format);
	ss << SYMBOL_ARRAY_SEPARATOR << " " << _to_string(value->get_value(1), error->get_value(1), format);
	ss << SYMBOL_ARRAY_END;
      } else {
	ss << SYMBOL_ARRAY_START << _to_string(value->get_value(0), error->get_value(0), format); 
	ss << SYMBOL_ARRAY_SEPARATOR << " " << _to_string(value->get_value(1), error->get_value(1), format);
	ss << SYMBOL_ARRAY_SEPARATOR << " " << SYMBOL_ARRAY_MORE << SYMBOL_ARRAY_END;
      }
#else
      ss << _to_string(value, error, format);
#endif
    }
    return format.format_order(ss.str());
  }

  std::size_t Magnitude::size() const {
    return value.size();
  }  

#if defined(MAGNITUDE_ARRAYS)
  ArrayShape Magnitude::shape() const {
    return value.shape();
  }
#elif defined(MAGNITUDE_VALUES)
  val::Array::ShapeType Magnitude::shape() const {
    return value->get_shape();
  }
#endif
  
  /*
   * Add two magnitudes
   */
  Magnitude operator+(const Magnitude& m1, const Magnitude& m2) {
    // z ± Dz = (x ± Dx) + (y ± Dy) -> Dz = Dx + Dy     (average errors)
    Array Dz = m1.error+m2.error;
    //Array Dz = nostd::sqrt(nostd::pow(m1.error,2)+nostd::pow(m2.error,2)); // Gaussian error propagation
    return Magnitude(m1.value+m2.value, Dz);
  }

  void Magnitude::operator+=(const Magnitude& m) {
    value += m.value;
    error += m.error;
    //error = nostd::sqrt(nostd::pow(error,2)+nostd::pow(m.error,2));
  }

  /*
   * Subtract two magnitudes
   */
  Magnitude operator-(const Magnitude& m1) {
    return Magnitude(-m1.value, m1.error);
  }
  Magnitude operator-(const Magnitude& m1, const Magnitude& m2) {
    // z ± Dz = (x ± Dx) - (y ± Dy) -> Dz = Dx + Dy     (average errors)
    return Magnitude(m1.value-m2.value, m1.error+m2.error);
  }

  std::ostream& operator<<(std::ostream& os, const Magnitude& m) {
    os << m.to_string();
    return os;
  }
  
  void Magnitude::operator-=(const Magnitude& m) {
    value -= m.value;
    error += m.error;
  }

  /*
   * Multiply magnitude by another magnitude
   */
  const Magnitude multiply(const Magnitude* m, const Magnitude* n) {
    Magnitude nm(m->value * n->value);
    if (m->error==0 && n->error==0) {
      nm.error = (m->error.size()>n->error.size()) ? m->error : n->error;
    } else if (m->error==0 && n->error!=0) {
      nm.error = n->error * m->value;
    } else if (m->error!=0 && n->error==0) {
      nm.error = m->error * n->value;    
    } else {
      MAGNITUDE_VALUE maxerror = nostd::abs((m->value+m->error)*(n->value+n->error) - nm.value);
      MAGNITUDE_VALUE minerror = nostd::abs((m->value-m->error)*(n->value-n->error) - nm.value);
      nm.error = nostd::max(maxerror,minerror);
    }
    return nm;
  }

  Magnitude operator*(const Magnitude& m1, const Magnitude& m2) {
    return multiply(&m1, &m2);
  }

  void Magnitude::operator*=(const Magnitude& m) {
    Magnitude nm = multiply(this, &m);
    value = nm.value;
    error = nm.error;
  }

  /*
   * Divide magnitude by another magnitude
   */
  const Magnitude divide(const Magnitude* m, const Magnitude* n) {
    Magnitude nm(m->value / n->value);
    if (m->error==0 && n->error==0) {
      nm.error = (m->error.size()>n->error.size()) ? m->error : n->error;
    } else if (m->error==0 && n->error!=0) {
      MAGNITUDE_VALUE maxerror = nostd::abs(m->value/(n->value+n->error) - nm.value);
      MAGNITUDE_VALUE minerror = nostd::abs(m->value/(n->value-n->error) - nm.value);
      nm.error = nostd::max(maxerror,minerror);
    } else if (m->error!=0 && n->error==0) {
      nm.error = m->error / n->value;    
    } else {
      MAGNITUDE_VALUE maxerror = nostd::abs((m->value+m->error)/(n->value-n->error) - nm.value);
      MAGNITUDE_VALUE minerror = nostd::abs((m->value-m->error)/(n->value+n->error) - nm.value);
      nm.error = nostd::max(maxerror,minerror);
    }
    return nm;
  }

  Magnitude operator/(const Magnitude& m1, const Magnitude& m2) {
    return divide(&m1, &m2);
  }

  void Magnitude::operator/=(const Magnitude& m) {
    Magnitude nm = divide(this, &m);
    value = nm.value;
    error = nm.error;
  }

  void Magnitude::pow(const EXPONENT_TYPE& e) {
    value = nostd::pow(value, (EXPONENT_REAL_PRECISION)e);
  } 
 
  bool Magnitude::operator==(const Magnitude& a) const {
    return (value==a.value) && (error==a.error);
  };
 
  bool Magnitude::operator!=(const Magnitude& a) const {
    return (value!=a.value) || (error!=a.error);
  };

}
 
#endif
