#include <gtest/gtest.h>

#include "val/values.h"

TEST(Values, CompareEqual) { // ==

    std::vector<bool> arr1 = {true,false,false};
    std::vector<bool> arr2 = {false,false,false};
    val::BaseValue::PointerType val1 = std::make_unique<val::ArrayValue<bool>>(arr1); 
    val::BaseValue::PointerType val2 = std::make_unique<val::ArrayValue<bool>>(arr2); 
    val::BaseValue::PointerType val3;

    val3 = val1->compare_equal(val1.get());
    EXPECT_EQ(val3->to_string(), "[true, true, true]");
    val3 = val1->compare_equal(val1.get(), val::EvalMode::Any);
    EXPECT_EQ(val3->to_string(), "true");
    val3 = val1->compare_equal(val1.get(), val::EvalMode::All);
    EXPECT_EQ(val3->to_string(), "true");

    val3 = val1->compare_equal(val2.get());
    EXPECT_EQ(val3->to_string(), "[false, true, true]");
    val3 = val1->compare_equal(val2.get(), val::EvalMode::Any);
    EXPECT_EQ(val3->to_string(), "true");
    val3 = val1->compare_equal(val2.get(), val::EvalMode::All);
    EXPECT_EQ(val3->to_string(), "false");

}

TEST(Values, CompareNotEqual) { // !=

    std::vector<bool> arr1 = {true,false,false};
    std::vector<bool> arr2 = {false,false,false};
    val::BaseValue::PointerType val1 = std::make_unique<val::ArrayValue<bool>>(arr1); 
    val::BaseValue::PointerType val2 = std::make_unique<val::ArrayValue<bool>>(arr2); 
    val::BaseValue::PointerType val3;
    
    val3 = val1->compare_not_equal(val1.get());
    EXPECT_EQ(val3->to_string(), "[false, false, false]");
    val3 = val1->compare_not_equal(val1.get(), val::EvalMode::Any);
    EXPECT_EQ(val3->to_string(), "false");
    val3 = val1->compare_not_equal(val1.get(), val::EvalMode::All);
    EXPECT_EQ(val3->to_string(), "false");

    val3 = val1->compare_not_equal(val2.get());
    EXPECT_EQ(val3->to_string(), "[true, false, false]");
    val3 = val1->compare_not_equal(val2.get(), val::EvalMode::Any);
    EXPECT_EQ(val3->to_string(), "true");
    val3 = val1->compare_not_equal(val2.get(), val::EvalMode::All);
    EXPECT_EQ(val3->to_string(), "false");

}
