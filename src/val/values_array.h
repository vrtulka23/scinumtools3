#ifndef VAL_VALUES_ARRAY_H
#define VAL_VALUES_ARRAY_H

#include <typeinfo>

#include "settings.h"

namespace val {
  
  // Array values

  // here we need a forward declaration
  template <typename T> class BaseArrayValue; 
  template <typename T> class ArrayValue; 
  
  template <typename T>
  class BaseArrayValue: public BaseValue {
  protected:
    std::vector<T> value;
  public:
    BaseArrayValue(const T& val): value({val}), BaseValue(this->deduce_dtype(), {1}) {};
    BaseArrayValue(const std::vector<T>&  arr, const Array::ShapeType& sh): value(arr), BaseValue(this->deduce_dtype(), sh) {};
    BaseArrayValue(const BaseValue* other): BaseValue(this->deduce_dtype(), other->get_shape()) {
      const BaseArrayValue<T>* otherT;
      if (this->dtype==other->get_dtype()) {
	otherT = dynamic_cast<const BaseArrayValue<T>*>(other);
      } else {
	BaseValue::PointerType casted_other = other->cast_as(this->dtype);
	otherT = dynamic_cast<const BaseArrayValue<T>*>(casted_other.get());
      }
      if (otherT) 
	this->value = otherT->value;
      else
	throw std::runtime_error("ArrayValue could not be initialized from the given BaseValue.");
    };
    void print() override {std::cout << to_string() << std::endl;};
    std::vector<T> get_values() const {return value;};
    T get_value(const size_t index) const {return value.at(index);};
    size_t get_size() const override {return value.size();};
  protected:
    static constexpr DataType deduce_dtype() {
      if constexpr (std::is_same_v<T, bool>) {
	return DataType::Boolean;
      } else if constexpr (std::is_same_v<T, char>) {
	return DataType::Character;
      } else if constexpr (std::is_same_v<T, int16_t>) {
	return DataType::Integer16;
      } else if constexpr (std::is_same_v<T, int32_t>) {
	return DataType::Integer32;
      } else if constexpr (std::is_same_v<T, int64_t>) {
	return DataType::Integer64;
      } else if constexpr (std::is_same_v<T, uint16_t>) {
	return DataType::Integer16_U;
      } else if constexpr (std::is_same_v<T, uint32_t>) {
	return DataType::Integer32_U;
      } else if constexpr (std::is_same_v<T, uint64_t>) {
	return DataType::Integer64_U;
      } else if constexpr (std::is_same_v<T, float>) {
	return DataType::Float32;
      } else if constexpr (std::is_same_v<T, double>) {
	return DataType::Float64;
      } else if constexpr (std::is_same_v<T, long double>) {
	return DataType::Float128;
      } else if constexpr (std::is_same_v<T, std::string>) {
            return DataType::String;
      } else {
	static_assert(sizeof(T) == 0, "Unsupported type T");
      }
    }
    virtual void value_to_string(std::ostringstream& oss, size_t& offset, int precision=0) const = 0;
    std::string to_string_dim(size_t& offset, const int& precision=0, int dim=0) const {
      std::ostringstream oss;
      if (value.size()>1)
	oss << "[";
      for (int i=0; i<shape[dim];i++) {
	if (i>0) oss << ", ";
	if (dim+1<shape.size()) {
	  oss << to_string_dim(offset, precision, dim+1);
	} else {
	  value_to_string(oss, offset, precision);
	  offset++;
	}
      }
      if (value.size()>1)
	oss << "]";
      return oss.str();
    }
  public:
    std::string to_string(const int precision=0) const override {
      size_t offset = 0;
      if (precision==0) {
	return to_string_dim(offset);
      } else {
	return to_string_dim(offset, precision);
      }
    };
    /*
     * Operations
     */
  protected:
    template <typename V, typename Func>
    std::unique_ptr<ArrayValue<V>> operate_unary(Func f) const {
      // apply operation
      std::vector<V> arr(value.size());
      for (int i=0; i<value.size();i++)
	arr[i] = f(value[i]);
      return std::make_unique<ArrayValue<V>>(arr, this->shape);
    };
    template <typename V, typename Func>
    std::unique_ptr<ArrayValue<V>> operate_binary(const BaseValue* other, Func f) const {
      // test if shape match
      for (int i=0; i<shape.size();i++)
	if (shape[i]!=other->get_shape()[i])
	  throw std::runtime_error("Arrays have incompatible shape");
      // apply operation
      const ArrayValue<T> otherT(other);
      std::vector<V> arr(value.size());
      for (int i=0; i<value.size();i++)
	arr[i] = f(value[i], otherT.value[i]);
      return std::make_unique<ArrayValue<V>>(arr, this->shape);
    };
  public:
    BaseValue::PointerType compare_equal(const BaseValue* other) const override {
      return operate_binary<bool>(other,[](T a, T b) {return a == b;});
    };
    BaseValue::PointerType compare_not_equal(const BaseValue* other) const override {
      return operate_binary<bool>(other,[](T a, T b) {return a != b;});
    };
    BaseValue::PointerType compare_less(const BaseValue* other) const override {
      return operate_binary<bool>(other,[](T a, T b) {return a < b;});
    };
    BaseValue::PointerType compare_greater(const BaseValue* other) const override {
      return operate_binary<bool>(other,[](T a, T b) {return a > b;});
    };
    BaseValue::PointerType compare_less_equal(const BaseValue* other) const override {
      return operate_binary<bool>(other,[](T a, T b) {return a <= b;});
    };
    BaseValue::PointerType compare_greater_equal(const BaseValue* other) const override {
      return operate_binary<bool>(other,[](T a, T b) {return a >= b;});
    };
    /*
     * Array slicing
     */
    BaseValue::PointerType slice_value(const Array::RangeType& slice) {
      if (slice.size()!=this->shape.size())
	throw std::runtime_error("Array slice size does not correspond with array shape: "+std::to_string(slice.size())+"!="+std::to_string(this->shape.size()));
      // calculate new shape and size
      Array::ShapeType new_shape;
      size_t new_size = 0;
      for (size_t i=0; i<this->shape.size(); i++) {
	int dmin = slice[i].dmin;
	int dmax = (slice[i].dmax==Array::max_range) ? this->shape[i]-1 : slice[i].dmax;
	int new_dim = dmax + 1 - dmin;
	if (new_dim>1) {
	  new_shape.push_back(new_dim);
	  new_size += new_dim;
	}
      }
      // allocate variables
      std::vector<T> new_value;
      new_value.reserve(new_size);
      Array::ShapeType coord(this->shape.size(),0);
      // list through all values and copy sliced
      for (size_t i=0; i<this->value.size(); i++) {
	// copy only values within the given ranges
	bool push = true;
	for (size_t dim = 0; dim<this->shape.size(); dim++) {
	  int dmin = slice[dim].dmin;
	  int dmax = (slice[dim].dmax==Array::max_range) ? this->shape[dim]-1 : slice[dim].dmax;
	  if (coord[dim]<dmin or dmax<coord[dim])
	    push = false;
	}
	if (push)
	  new_value.push_back(this->value[i]);
	// increase the coodrinates
	for (size_t dim = this->shape.size(); dim-->0;) {
	  if (++coord[dim] < this->shape[dim]) break;
	  coord[dim] = 0;  // carry over
	}
      }
      if (new_size>1)
	return std::make_unique<ArrayValue<T>>(new_value, new_shape);
      else
	return std::make_unique<ArrayValue<T>>(new_value[0]);
    };
    /*
     * Unit conversion
     */
    void convert_units(const std::string& from_units, const puq::Quantity::PointerType& to_quantity) override {
      throw std::runtime_error("Array value of type '"+std::string(DataTypeNames[dtype])+"' does not support unit conversion.");
    };
    void convert_units(const puq::Quantity::PointerType& from_quantity, const std::string& to_units) override {
      throw std::runtime_error("Array value of type '"+std::string(DataTypeNames[dtype])+"' does not support unit conversion.");
    };
    BaseValue::PointerType math_log() const override {throw std::runtime_error("Function is not implemented for this type.");};
    BaseValue::PointerType math_log10() const override {throw std::runtime_error("Function is not implemented for this type.");};
    BaseValue::PointerType math_sqrt() const override {throw std::runtime_error("Function is not implemented for this type.");};
    BaseValue::PointerType math_cbrt() const override {throw std::runtime_error("Function is not implemented for this type.");};
    BaseValue::PointerType math_exp() const override {throw std::runtime_error("Function is not implemented for this type.");};
    BaseValue::PointerType math_floor() const override {throw std::runtime_error("Function is not implemented for this type.");};
    BaseValue::PointerType math_ceil() const override {throw std::runtime_error("Function is not implemented for this type.");};
    BaseValue::PointerType math_abs() const override {throw std::runtime_error("Function is not implemented for this type.");};
    BaseValue::PointerType math_pow(const BaseValue* other) const override {throw std::runtime_error("Function is not implemented for this type.");};
    BaseValue::PointerType math_max(const BaseValue* other) const override {throw std::runtime_error("Function is not implemented for this type.");};
    BaseValue::PointerType math_min(const BaseValue* other) const override {throw std::runtime_error("Function is not implemented for this type.");};
  };
  
  template <typename T>
  class ArrayValue: public BaseArrayValue<T> {
  public:
    ArrayValue(const T& val): BaseArrayValue<T>(val) {};
    ArrayValue(const std::vector<T>&  arr, const Array::ShapeType& sh): BaseArrayValue<T>(arr,sh) {};
    ArrayValue(const std::vector<T>&  arr): BaseArrayValue<T>(arr,{static_cast<int>(arr.size())}) {};
    ArrayValue(const BaseValue* other): BaseArrayValue<T>(other) {};
  private:
    void value_to_string(std::ostringstream& oss, size_t& offset, int precision=0) const override {
      if (precision==0) precision=snt::DISPLAY_FLOAT_PRECISION;
      int exponent = static_cast<int>(std::log10(std::fabs(this->value[offset])));
      if (exponent > 3 || exponent < -3) {
        oss << std::scientific << std::setprecision(precision) << this->value[offset];
      } else {
        oss << std::fixed << std::setprecision(precision-exponent) << this->value[offset];
      }
    };
  public:
    BaseValue::PointerType clone() const override {
      return std::make_unique<ArrayValue<T>>(this->value, this->shape);
    };
    BaseValue::PointerType cast_as(DataType dt) const override {
      switch (dt) {
      case DataType::Boolean: {
	std::vector<bool> arr(this->value.size());
	for (size_t i=0; i<this->value.size(); i++)
	  arr[i] = static_cast<bool>(this->value[i]);
	return std::make_unique<ArrayValue<bool>>(arr, this->shape);
      }
      case DataType::Character: {
	std::vector<char> arr(this->value.size());
	for (size_t i=0; i<this->value.size(); i++)
	  arr[i] = static_cast<char>(this->value[i]);
	return std::make_unique<ArrayValue<char>>(arr, this->shape);
      }
      case DataType::Integer16: {
	std::vector<int16_t> arr(this->value.size());
	for (size_t i=0; i<this->value.size(); i++)
	  arr[i] = static_cast<int16_t>(this->value[i]);
	return std::make_unique<ArrayValue<int16_t>>(arr, this->shape);
      }
      case DataType::Integer32: {
	std::vector<int32_t> arr(this->value.size());
	for (size_t i=0; i<this->value.size(); i++)
	  arr[i] = static_cast<int32_t>(this->value[i]);
	return std::make_unique<ArrayValue<int32_t>>(arr, this->shape);
      }
      case DataType::Integer64: {
	std::vector<int64_t> arr(this->value.size());
	for (size_t i=0; i<this->value.size(); i++)
	  arr[i] = static_cast<int64_t>(this->value[i]);
	return std::make_unique<ArrayValue<int64_t>>(arr, this->shape);
      }
      case DataType::Integer16_U: {
	std::vector<uint16_t> arr(this->value.size());
	for (size_t i=0; i<this->value.size(); i++)
	  arr[i] = static_cast<uint16_t>(this->value[i]);
	return std::make_unique<ArrayValue<uint16_t>>(arr, this->shape);
      }
      case DataType::Integer32_U: {
	std::vector<uint32_t> arr(this->value.size());
	for (size_t i=0; i<this->value.size(); i++)
	  arr[i] = static_cast<uint32_t>(this->value[i]);
	return std::make_unique<ArrayValue<uint32_t>>(arr, this->shape);
      }
      case DataType::Integer64_U: {
	std::vector<uint64_t> arr(this->value.size());
	for (size_t i=0; i<this->value.size(); i++)
	  arr[i] = static_cast<uint64_t>(this->value[i]);
	return std::make_unique<ArrayValue<uint64_t>>(arr, this->shape);
      }
      case DataType::Float32: {
	std::vector<float> arr(this->value.size());
	for (size_t i=0; i<this->value.size(); i++)
	  arr[i] = static_cast<float>(this->value[i]);
	return std::make_unique<ArrayValue<float>>(arr, this->shape);
      }
      case DataType::Float64: {
	std::vector<double> arr(this->value.size());
	for (size_t i=0; i<this->value.size(); i++)
	  arr[i] = static_cast<double>(this->value[i]);
	return std::make_unique<ArrayValue<double>>(arr, this->shape);
      }
      case DataType::Float128: {
	std::vector<long double> arr(this->value.size());
	for (size_t i=0; i<this->value.size(); i++)
	  arr[i] = static_cast<long double>(this->value[i]);
	return std::make_unique<ArrayValue<long double>>(arr, this->shape);
      }
      case DataType::String: {
	std::vector<std::string> arr(this->value.size());
	for (size_t i=0; i<this->value.size(); i++)
	  arr[i] = std::to_string(this->value[i]);
	return std::make_unique<ArrayValue<std::string>>(arr, this->shape);
	}
      default:
	throw std::runtime_error("Not implemented");
	return nullptr;
      }
    };
    BaseValue::PointerType slice(const Array::RangeType& slice) override {
      return this->slice_value(slice);
    };
    void convert_units(const std::string& from_units, const puq::Quantity::PointerType& to_quantity) override {
      // TODO: use the same BaseValue pointers in the puq to allow variable precision
      std::vector<double> input(this->value.begin(), this->value.end());
      puq::Quantity quantity = puq::Quantity(input, from_units);
      quantity = quantity.convert(*to_quantity);
      std::vector<double> output = quantity.value.magnitude.value.value;
      std::copy(output.begin(), output.end(), this->value.begin());
    };
    void convert_units(const puq::Quantity::PointerType& from_quantity, const std::string& to_units) override {
      // TODO: use the same BaseValue pointers in the puq to allow variable precision
      std::vector<double> input(this->value.begin(), this->value.end());
      puq::Quantity quantity = input * (*from_quantity);
      quantity = quantity.convert(to_units);
      std::vector<double> output = quantity.value.magnitude.value.value;
      std::copy(output.begin(), output.end(), this->value.begin());
    };
    BaseValue::PointerType math_log() const override {
      return this->template operate_unary<T>([](T a) {return std::log(a);});
    };
    BaseValue::PointerType math_log10() const override {
      return this->template operate_unary<T>([](T a) {return std::log10(a);});
    };
    BaseValue::PointerType math_sqrt() const override {
      return this->template operate_unary<T>([](T a) {return std::sqrt(a);});
    };
    BaseValue::PointerType math_cbrt() const override {
      return this->template operate_unary<T>([](T a) {return std::cbrt(a);});
    };
    BaseValue::PointerType math_exp() const override {
      return this->template operate_unary<T>([](T a) {return std::exp(a);});
    };
    BaseValue::PointerType math_floor() const override {
      return this->template operate_unary<T>([](T a) {return std::floor(a);});
    };
    BaseValue::PointerType math_ceil() const override {
      return this->template operate_unary<T>([](T a) {return std::ceil(a);});
    };
    BaseValue::PointerType math_abs() const override {
      return nullptr;
      //return this->template operate_unary<T>([](T a) {return std::abs(a);});
    };
    BaseValue::PointerType math_pow(const BaseValue* other) const override {return nullptr;};
    BaseValue::PointerType math_max(const BaseValue* other) const override {return nullptr;};
    BaseValue::PointerType math_min(const BaseValue* other) const override {return nullptr;};
    BaseValue::PointerType logical_and(const BaseValue* other) const override {
      return this->template operate_binary<bool>(other,[](T a, T b) {return a && b;});
    };
    BaseValue::PointerType logical_or(const BaseValue* other) const override {
      return this->template operate_binary<bool>(other,[](T a, T b) {return a || b;});
    };
    BaseValue::PointerType logical_not() const override {
      return this->template operate_unary<bool>([](T a) {return !a;});
    };
    bool any_of() const override {
      return std::any_of(this->value.begin(), this->value.end(), [](T b) { return b; });
    };
    bool all_of() const override {
      return std::all_of(this->value.begin(), this->value.end(), [](T b) { return b; });
    };
    bool none_of() const override {
      return std::none_of(this->value.begin(), this->value.end(), [](T b) { return b; });
    };
  };
  
  template <>
  class ArrayValue<std::string>: public BaseArrayValue<std::string> {
  public:
    ArrayValue(const std::string& val): BaseArrayValue(val) {};
    ArrayValue(const Array::StringType&  arr, const Array::ShapeType& sh): BaseArrayValue(arr,sh) {};
    ArrayValue(const Array::StringType&  arr): BaseArrayValue(arr,{static_cast<int>(arr.size())}) {};
    ArrayValue(const BaseValue* other): BaseArrayValue<std::string>(other) {};
  private:
    void value_to_string(std::ostringstream& oss, size_t& offset, int precision=0) const override {
      oss << "'" << value[offset] << "'";
    }
  public:
    std::string to_string(int precision=0) const override {
      size_t offset = 0;
      if (precision==0) {
	return to_string_dim(offset);
      } else {
	throw std::runtime_error("String value does not support precision parameter for to_string() method.");
      }
    };
    BaseValue::PointerType clone() const override {
      return std::make_unique<ArrayValue<std::string>>(this->value, this->shape);
    };
    BaseValue::PointerType slice(const Array::RangeType& slice) override {
      return this->slice_value(slice);
    };
    BaseValue::PointerType cast_as(DataType dt) const override;
    BaseValue::PointerType logical_and(const BaseValue* other) const override;
    BaseValue::PointerType logical_or(const BaseValue* other) const override;
    BaseValue::PointerType logical_not() const override;
    bool any_of() const override {
      return std::any_of(this->value.begin(), this->value.end(), [](std::string b) { return !b.empty(); });
    };
    bool all_of() const override {
      return std::all_of(this->value.begin(), this->value.end(), [](std::string b) { return !b.empty(); });
    };
    bool none_of() const override {
      return std::none_of(this->value.begin(), this->value.end(), [](std::string b) { return !b.empty(); });
    };
  };

  template <>
  class ArrayValue<bool>: public BaseArrayValue<bool> {
  public:
    ArrayValue(const bool& val): BaseArrayValue(val) {};
    ArrayValue(const std::vector<bool>&  arr, const Array::ShapeType& sh): BaseArrayValue(arr,sh) {};
    ArrayValue(const std::vector<bool>&  arr): BaseArrayValue(arr,{static_cast<int>(arr.size())}) {};
    ArrayValue(const BaseValue* other): BaseArrayValue<bool>(other) {};
  private:
    void value_to_string(std::ostringstream& oss, size_t& offset, int precision=0) const override {
      if (value[offset])
	oss << snt::KEYWORD_TRUE;
      else
	oss << snt::KEYWORD_FALSE;
    }
  public:
    std::string to_string(int precision=0) const override {
      size_t offset = 0;
      if (precision==0) {
	return to_string_dim(offset);
      } else {
	throw std::runtime_error("Boolean value does not support precision parameter for to_string() method.");
      }
    };
    BaseValue::PointerType clone() const override {
      return std::make_unique<ArrayValue<bool>>(this->value, this->shape);
    };
    BaseValue::PointerType slice(const Array::RangeType& slice) override {
      return this->slice_value(slice);
    };
    BaseValue::PointerType cast_as(DataType dt) const override;
    BaseValue::PointerType logical_and(const BaseValue* other) const override;
    BaseValue::PointerType logical_or(const BaseValue* other) const override;
    BaseValue::PointerType logical_not() const override;
    bool any_of() const override {
      return std::any_of(this->value.begin(), this->value.end(), [](bool b) { return b; });
    };
    bool all_of() const override {
      return std::all_of(this->value.begin(), this->value.end(), [](bool b) { return b; });
    };
    bool none_of() const override {
      return std::none_of(this->value.begin(), this->value.end(), [](bool b) { return b; });
    };
  };

}

#endif // VAL_VALUES_ARRAY_H
