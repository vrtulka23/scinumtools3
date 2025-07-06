#ifndef VAL_VALUES_H
#define VAL_VALUES_H

#include <typeinfo>
#include <cstdint>

#include "settings.h"

namespace val {

  enum class DataType { // TODO: INTX and FLOATX should support arbitrary precision types
    Boolean,     String,
    Integer16,   Integer32,   Integer64,    IntegerX,   
    Integer16_U, Integer32_U, Integer64_U,  
    Float32,     Float64,     Float128,     FloatX
  };

  extern std::unordered_map<DataType, std::string> DataTypeNames;

  template <typename T> class ArrayValue;
  
  class BaseValue {
  public:
    typedef std::unique_ptr<BaseValue> PointerType;
    DataType dtype;
    Array::ShapeType shape;
    BaseValue(DataType dt, Array::ShapeType sh): dtype(dt), shape(sh) {};
    virtual ~BaseValue() = default;
    virtual void print() = 0;
    virtual std::string to_string(const int precision=0) const = 0;
    virtual Array::ShapeType get_shape() const = 0;
    virtual size_t get_size() const = 0;
    virtual BaseValue::PointerType clone() const = 0;
    virtual BaseValue::PointerType cast_as(DataType dt) const = 0;
    virtual BaseValue::PointerType slice(const Array::RangeType& slice) = 0;
    virtual void convert_units(const std::string& from_units, const puq::Quantity::PointerType& to_quantity) = 0;
    virtual void convert_units(const puq::Quantity::PointerType& from_quantity, const std::string& to_units) = 0;
    virtual bool operator==(const BaseValue* other) const = 0;
    virtual bool operator<(const BaseValue* other) const = 0;
  };

}

#include "values_array.h"

namespace val {  

  // helper function that create a array value pointer from a C++ data type
  template <typename T>
  BaseValue::PointerType create_array_value(const std::vector<T>&  arr, Array::ShapeType sh={}) {
    if (sh.empty())
      sh.push_back(arr.size());
    if constexpr (std::is_same_v<T, bool>)
      return std::make_unique<ArrayValue<bool>>(ArrayValue<bool>(arr, sh));
    else if constexpr (std::is_same_v<T, int16_t>)
      return std::make_unique<ArrayValue<int16_t>>(ArrayValue<int16_t>(arr, sh, DataType::Integer16));
    else if constexpr (std::is_same_v<T, uint16_t>)
      return std::make_unique<ArrayValue<uint16_t>>(ArrayValue<uint16_t>(arr, sh, DataType::Integer16_U));
    else if constexpr (std::is_same_v<T, int32_t>)
      return std::make_unique<ArrayValue<int32_t>>(ArrayValue<int32_t>(arr, sh, DataType::Integer32));
    else if constexpr (std::is_same_v<T, uint32_t>)
      return std::make_unique<ArrayValue<uint32_t>>(ArrayValue<uint32_t>(arr, sh, DataType::Integer32_U));
    else if constexpr (std::is_same_v<T, int64_t>)
      return std::make_unique<ArrayValue<int64_t>>(ArrayValue<int64_t>(arr, sh, DataType::Integer64));
    else if constexpr (std::is_same_v<T, uint64_t>)
      return std::make_unique<ArrayValue<uint64_t>>(ArrayValue<uint64_t>(arr, sh, DataType::Integer64_U));
    else if constexpr (std::is_same_v<T, float>)
      return std::make_unique<ArrayValue<float>>(ArrayValue<float>(arr, sh, DataType::Float32));
    else if constexpr (std::is_same_v<T, double>)
      return std::make_unique<ArrayValue<double>>(ArrayValue<double>(arr, sh, DataType::Float64));
    else if constexpr (std::is_same_v<T, long double>)
      return std::make_unique<ArrayValue<long double>>(ArrayValue<long double>(arr, sh, DataType::Float128));
    else if constexpr (std::is_same_v<T, std::string>)
      return std::make_unique<ArrayValue<std::string>>(ArrayValue<std::string>(arr, sh));
    else 
      static_assert(std::is_integral_v<T>, "Given data type is not associated with any array value");
  };
  
}

#endif // VAL_VALUES_H
