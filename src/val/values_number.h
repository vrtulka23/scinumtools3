#ifndef VAL_VALUES_NUMBER_H
#define VAL_VALUES_NUMBER_H

#include <typeinfo>

#include "values.h"

namespace val {

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
      if constexpr (std::is_same_v<T, uint16_t> || std::is_same_v<T, uint32_t> || std::is_same_v<T, uint64_t>) {
	throw std::runtime_error("Absolute value is not implemented for unsigned integers");
      } else {
	return this->template operate_unary<T>([](T a) {return std::abs(a);});
      }
    };
    BaseValue::PointerType math_neg() const override {
      return this->template operate_unary<T>([](T a) {return -a;});
    };
    BaseValue::PointerType math_add(const BaseValue* other) const override {
      return this->template operate_binary<T>(other,[](T a, T b) {return a + b;});
    };
    BaseValue::PointerType math_add(const double num) const override {
      return this->template operate_unary<T>([&num](T a) {return a + num;});
    };
    BaseValue::PointerType math_sub(const BaseValue* other) const override {
      return this->template operate_binary<T>(other,[](T a, T b) {return a - b;});
    };
    BaseValue::PointerType math_sub(const double num) const override {
      return this->template operate_unary<T>([&num](T a) {return a - num;});
    };
    BaseValue::PointerType math_mul(const BaseValue* other) const override {
      return this->template operate_binary<T>(other,[](T a, T b) {return a * b;});
    };
    BaseValue::PointerType math_mul(const double num) const override {
      return this->template operate_unary<T>([&num](T a) {return a * num;});
    };
    BaseValue::PointerType math_div(const BaseValue* other) const override {
      return this->template operate_binary<T>(other,[](T a, T b) {return a / b;});
    };
    BaseValue::PointerType math_div(const double num) const override {
      return this->template operate_unary<T>([&num](T a) {return a / num;});
    };
    void math_add_equal(const BaseValue* other) override {
      this->template operate_binary_equal<T>(other,[](T a, T b) {return a + b;});
    };
    void math_sub_equal(const BaseValue* other) override {
      this->template operate_binary_equal<T>(other,[](T a, T b) {return a - b;});
    };
    void math_mul_equal(const BaseValue* other) override {
      this->template operate_binary_equal<T>(other,[](T a, T b) {return a * b;});
    };
    void math_div_equal(const BaseValue* other) override {
      this->template operate_binary_equal<T>(other,[](T a, T b) {return a / b;});
    };
    BaseValue::PointerType math_pow(const BaseValue* other) const override {return nullptr;};
    BaseValue::PointerType math_pow(const double exp) const override {
      return this->template operate_unary<T>([&exp](T a) {return std::pow(a, exp);});      
    };
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
    bool is_unity() const override {
      return std::all_of(this->value.begin(), this->value.end(), [](T b) { return b==1; });
    };
  };
  
}

#endif // VAL_VALUES_NUMBER_H
