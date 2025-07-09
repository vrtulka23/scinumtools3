#include <gtest/gtest.h>

#include "val/values.h"

TEST(Values, CompareEqual) {

    std::vector<bool> arr1 = {true,false,false,true,true};
    std::vector<bool> arr2 = {true,false,false,true,true};
    std::vector<bool> arr3 = {false,false,false,false,true};
    val::BaseValue::PointerType val1 = std::make_unique<val::ArrayValue<bool>>(arr1); 
    val::BaseValue::PointerType val2 = std::make_unique<val::ArrayValue<bool>>(arr2); 
    val::BaseValue::PointerType val3 = std::make_unique<val::ArrayValue<bool>>(arr3); 

    val::BaseValue::PointerType val4 = val1->compare_equal(val2.get());
    EXPECT_EQ(val4->to_string(), "[true, true, true, true, true]");

    val::BaseValue::PointerType val5 = val1->compare_equal(val3.get());
    EXPECT_EQ(val5->to_string(), "[false, true, true, false, true]");

}
