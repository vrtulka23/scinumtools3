#include <gtest/gtest.h>

#include "val/values.h"

TEST(Values, Arithmetics) {

  std::vector<bool> arr = {true,false,false,true,true};
  val::Array::ShapeType sh = {5};
  val::BaseValue::PointerType val = std::make_unique<val::ArrayValue<bool>>(arr,sh); 

  val::BaseValue::PointerType bval = val->cast_as(val::ValueDtype::Boolean);
    
  EXPECT_EQ("foo", "foo");

}
