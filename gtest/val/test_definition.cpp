#include <gtest/gtest.h>

#include "val/values.h"

TEST(Values, DefineBoolean) {

  std::vector<bool> arr = {true,false,false,true,true,false};
  val::Array::ShapeType sh = {2,3};
  val::BaseValue::PointerType val;

  val = std::make_unique<val::ArrayValue<bool>>(false); 
  EXPECT_EQ(val->to_string(), "false");
  EXPECT_EQ(val->get_dtype(), val::DataType::Boolean);
  EXPECT_EQ(val->get_shape(), val::Array::ShapeType({1}));
  
  val = std::make_unique<val::ArrayValue<bool>>(arr); 
  EXPECT_EQ(val->to_string(), "[true, false, false, true, true, false]");
  EXPECT_EQ(val->get_dtype(), val::DataType::Boolean);
  EXPECT_EQ(val->get_shape(), val::Array::ShapeType({6}));
  
  val = std::make_unique<val::ArrayValue<bool>>(arr, sh); 
  EXPECT_EQ(val->to_string(), "[[true, false, false], [true, true, false]]");
  EXPECT_EQ(val->get_dtype(), val::DataType::Boolean);
  EXPECT_EQ(val->get_shape(), sh);
    
}

TEST(Values, DefineCharacter) {

  std::vector<char> arr = {65, 66, 67, 68, 69, 70};
  val::Array::ShapeType sh = {2,3};
  val::BaseValue::PointerType val;
  
  val = std::make_unique<val::ArrayValue<char>>(65); 
  EXPECT_EQ(val->to_string(), "A");
  EXPECT_EQ(val->get_dtype(), val::DataType::Character);
  EXPECT_EQ(val->get_shape(), val::Array::ShapeType({1}));
  
  val = std::make_unique<val::ArrayValue<char>>(arr); 
  EXPECT_EQ(val->to_string(), "[A, B, C, D, E, F]");
  EXPECT_EQ(val->get_dtype(), val::DataType::Character);
  EXPECT_EQ(val->get_shape(), val::Array::ShapeType({6}));
  
  val = std::make_unique<val::ArrayValue<char>>(arr, sh); 
  EXPECT_EQ(val->to_string(), "[[A, B, C], [D, E, F]]");
  EXPECT_EQ(val->get_dtype(), val::DataType::Character);
  EXPECT_EQ(val->get_shape(), sh);
    
}

TEST(Values, DefineInteger) {

  std::vector<int> arr = {0, 2, 33, 45, 2343, 100023};
  val::Array::ShapeType sh = {2,3};
  val::BaseValue::PointerType val;
  
  val = std::make_unique<val::ArrayValue<int>>(4); 
  EXPECT_EQ(val->to_string(), "4");
  EXPECT_EQ(val->get_dtype(), val::DataType::Integer32);
  EXPECT_EQ(val->get_shape(), val::Array::ShapeType({1}));
  
  val = std::make_unique<val::ArrayValue<int>>(arr); 
  EXPECT_EQ(val->to_string(), "[0, 2, 33, 45, 2343, 100023]");
  EXPECT_EQ(val->get_dtype(), val::DataType::Integer32);
  EXPECT_EQ(val->get_shape(), val::Array::ShapeType({6}));
  
  val = std::make_unique<val::ArrayValue<int>>(arr, sh); 
  EXPECT_EQ(val->to_string(), "[[0, 2, 33], [45, 2343, 100023]]");
  EXPECT_EQ(val->get_dtype(), val::DataType::Integer32);
  EXPECT_EQ(val->get_shape(), sh);
    
}

TEST(Values, DefineFloat) {

  std::vector<double> arr = {0, 2, 33.3, 45e2, 3.4e2, -100023e3};
  val::Array::ShapeType sh = {2,3};
  val::BaseValue::PointerType val;

  val = std::make_unique<val::ArrayValue<double>>(-1.234e+05); 
  EXPECT_EQ(val->to_string(), "-1.2340e+05");
  EXPECT_EQ(val->get_dtype(), val::DataType::Float64);
  EXPECT_EQ(val->get_shape(), val::Array::ShapeType({1}));
  
  val = std::make_unique<val::ArrayValue<double>>(arr); 
  EXPECT_EQ(val->to_string(), "[0.0000e+00, 2.0000, 33.300, 4500.0, 340.00, -1.0002e+08]");
  EXPECT_EQ(val->get_dtype(), val::DataType::Float64);
  EXPECT_EQ(val->get_shape(), val::Array::ShapeType({6}));
  
  val = std::make_unique<val::ArrayValue<double>>(arr, sh); 
  EXPECT_EQ(val->to_string(), "[[0.0000e+00, 2.0000, 33.300], [4500.0, 340.00, -1.0002e+08]]");
  EXPECT_EQ(val->get_dtype(), val::DataType::Float64);
  EXPECT_EQ(val->get_shape(), sh);
    
}


TEST(Values, DefineString) {

  std::vector<std::string> arr = {"a", "b", "c", "d", "e", "f"};
  val::Array::ShapeType sh = {2,3};
  val::BaseValue::PointerType val;
  
  val = std::make_unique<val::ArrayValue<std::string>>("Hello World"); 
  EXPECT_EQ(val->to_string(), "'Hello World'");
  EXPECT_EQ(val->get_dtype(), val::DataType::String);
  EXPECT_EQ(val->get_shape(), val::Array::ShapeType({1}));
  
  val = std::make_unique<val::ArrayValue<std::string>>(arr); 
  EXPECT_EQ(val->to_string(), "['a', 'b', 'c', 'd', 'e', 'f']");
  EXPECT_EQ(val->get_dtype(), val::DataType::String);
  EXPECT_EQ(val->get_shape(), val::Array::ShapeType({6}));
  
  val = std::make_unique<val::ArrayValue<std::string>>(arr, sh); 
  EXPECT_EQ(val->to_string(), "[['a', 'b', 'c'], ['d', 'e', 'f']]");
  EXPECT_EQ(val->get_dtype(), val::DataType::String);
  EXPECT_EQ(val->get_shape(), val::Array::ShapeType(sh));
    
}
