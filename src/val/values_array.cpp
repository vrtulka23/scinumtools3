#include "values.h"
#include "values_array.h"

namespace val {

  BaseValue::PointerType ArrayValue<std::string>::cast_as(DataType dt) const {
    switch (dt) {
    case DataType::Boolean: {
      std::vector<bool> arr(this->value.size());
      for (size_t i=0; i<this->value.size(); i++) {
	if (this->value[i]==KEYWORD_TRUE)
	  arr[i] = true;
	else if (this->value[i]==KEYWORD_FALSE)
	  arr[i] = false;
	else
	  throw std::runtime_error("Could not cast value as boolean: "+this->value[i]); 
      }
      return std::make_unique<ArrayValue<bool>>(arr, this->shape, dt);
    }
    case DataType::Integer16: {
      std::vector<int16_t> arr(this->value.size());
      for (size_t i=0; i<this->value.size(); i++)
	arr[i] = (int16_t)std::stoi(this->value[i]);
      return std::make_unique<ArrayValue<int16_t>>(arr, this->shape, dt);
    }
    case DataType::Integer32: {
      std::vector<int32_t> arr(this->value.size());
      for (size_t i=0; i<this->value.size(); i++) {
	long n = std::stol(this->value[i]);
	if (n < INT32_MIN || n > INT32_MAX)
	  throw std::out_of_range("value out of int32_t range");
	arr[i] = static_cast<int32_t>(n);
      }
      return std::make_unique<ArrayValue<int32_t>>(arr, this->shape, dt);
    }
    case DataType::Integer64: {
      std::vector<int64_t> arr(this->value.size());
      for (size_t i=0; i<this->value.size(); i++) {
	long long n = std::stoll(this->value[i]);
	if (n < INT64_MIN || n > INT64_MAX)
	  throw std::out_of_range("value out of int64_t range");
	arr[i] = static_cast<int64_t>(n);
      }
      return std::make_unique<ArrayValue<int64_t>>(arr, this->shape, dt);
    }
    case DataType::Integer16_U: {
      std::vector<uint16_t> arr(this->value.size());
      for (size_t i=0; i<this->value.size(); i++)
	arr[i] = (uint16_t)std::stoi(this->value[i]);
      return std::make_unique<ArrayValue<uint16_t>>(arr, this->shape, dt);
    }
    case DataType::Integer32_U: {
      std::vector<uint32_t> arr(this->value.size());
      for (size_t i=0; i<this->value.size(); i++) {
	unsigned long n = std::stoul(this->value[i]);
	if (n > UINT32_MAX)
	  throw std::out_of_range("value out of uint32_t range");
	arr[i] = static_cast<uint32_t>(n);
      }
      return std::make_unique<ArrayValue<uint32_t>>(arr, this->shape, dt);
    }
    case DataType::Integer64_U: {
      std::vector<uint64_t> arr(this->value.size());
      for (size_t i=0; i<this->value.size(); i++) {
	unsigned long long n = std::stoull(this->value[i]);
	if (n > UINT64_MAX)
	  throw std::out_of_range("value out of uint64_t range");
	arr[i] = static_cast<uint64_t>(n);
      }
      return std::make_unique<ArrayValue<uint64_t>>(arr, this->shape, dt);
    }
    case DataType::Float32: {
      std::vector<float> arr(this->value.size());
      for (size_t i=0; i<this->value.size(); i++)
	arr[i] = std::stof(this->value[i]);
      return std::make_unique<ArrayValue<float>>(arr, this->shape, dt);
    }
    case DataType::Float64: {
      std::vector<double> arr(this->value.size());
      for (size_t i=0; i<this->value.size(); i++)
	arr[i] = std::stod(this->value[i]);
      return std::make_unique<ArrayValue<double>>(arr, this->shape, dt);
    }
    case DataType::Float128: {
      std::vector<long double> arr(this->value.size());
      for (size_t i=0; i<this->value.size(); i++)
	arr[i] = std::stold(this->value[i]);
      return std::make_unique<ArrayValue<long double>>(arr, this->shape, dt);
    }
    case DataType::String: {
      return std::make_unique<ArrayValue<std::string>>(this->value, this->shape, dt);
    }
    default:
      throw std::runtime_error("Not implemented");
      return nullptr;
    }
  };

  BaseValue::PointerType ArrayValue<bool>::cast_as(DataType dt) const {
    switch (dt) {
    case DataType::Boolean: {
      return std::make_unique<ArrayValue<bool>>(this->value, this->shape, dt);
    }
    case DataType::Integer16: {
      std::vector<int16_t> arr(this->value.size());
      for (size_t i=0; i<this->value.size(); i++)
	arr[i] = static_cast<int16_t>(this->value[i]);
      return std::make_unique<ArrayValue<int16_t>>(arr, this->shape, dt);
    }
    case DataType::Integer32: {
      std::vector<int32_t> arr(this->value.size());
      for (size_t i=0; i<this->value.size(); i++)
	arr[i] = static_cast<int32_t>(this->value[i]);
      return std::make_unique<ArrayValue<int32_t>>(arr, this->shape, dt);
    }
    case DataType::Integer64: {
      std::vector<int64_t> arr(this->value.size());
      for (size_t i=0; i<this->value.size(); i++)
	arr[i] = static_cast<int64_t>(this->value[i]);
      return std::make_unique<ArrayValue<int64_t>>(arr, this->shape, dt);
    }
    case DataType::Integer16_U: {
      std::vector<uint16_t> arr(this->value.size());
      for (size_t i=0; i<this->value.size(); i++)
	arr[i] = static_cast<uint16_t>(this->value[i]);
      return std::make_unique<ArrayValue<uint16_t>>(arr, this->shape, dt);
    }
    case DataType::Integer32_U: {
      std::vector<uint32_t> arr(this->value.size());
      for (size_t i=0; i<this->value.size(); i++)
	arr[i] = static_cast<uint32_t>(this->value[i]);
      return std::make_unique<ArrayValue<uint32_t>>(arr, this->shape, dt);
    }
    case DataType::Integer64_U: {
      std::vector<uint64_t> arr(this->value.size());
      for (size_t i=0; i<this->value.size(); i++)
	arr[i] = static_cast<uint64_t>(this->value[i]);
      return std::make_unique<ArrayValue<uint64_t>>(arr, this->shape, dt);
    }
    case DataType::Float32: {
      std::vector<float> arr(this->value.size());
      for (size_t i=0; i<this->value.size(); i++)
	arr[i] = static_cast<float>(this->value[i]);
      return std::make_unique<ArrayValue<float>>(arr, this->shape, dt);
    }
    case DataType::Float64: {
      std::vector<double> arr(this->value.size());
      for (size_t i=0; i<this->value.size(); i++)
	arr[i] = static_cast<double>(this->value[i]);
      return std::make_unique<ArrayValue<double>>(arr, this->shape, dt);
    }
    case DataType::Float128: {
      std::vector<long double> arr(this->value.size());
      for (size_t i=0; i<this->value.size(); i++)
	arr[i] = static_cast<long double>(this->value[i]);
      return std::make_unique<ArrayValue<long double>>(arr, this->shape, dt);
    }
    case DataType::String: {
      std::vector<std::string> arr(this->value.size());
      for (size_t i=0; i<this->value.size(); i++) {
	if (this->value[i])
	  arr[i] = std::string(KEYWORD_TRUE);
	else
	  arr[i] = std::string(KEYWORD_FALSE);
      }
      return std::make_unique<ArrayValue<std::string>>(arr, this->shape, dt);
    }
    default:
      throw std::runtime_error("Not implemented");
      return nullptr;
    }
  };
  
}
