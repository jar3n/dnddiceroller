#include "range.h"
#include "gtest/gtest.h"

class RangeConverterTest : public testing::Test {
    protected:
    AltRangeConverter * abilityRC;
    RangeConverter * proficiencyRC;
    int32_t abilityScoreMin = 1;
    int32_t abilityScoreMax = 20;
    int32_t abilityModMin = -5;
    int32_t abilityModMax = 10;
    int32_t levelMin = 1;
    int32_t levelMax = 20;
    int32_t bonusMin = 2;
    int32_t bonusMax = 6;

    void SetUp(){
        abilityRC = new AltRangeConverter(10, 2);

        proficiencyRC = new RangeConverter(levelMin, 
                                           levelMax, 
                                           bonusMin, 
                                           bonusMax);

    }

    void TearDown(){
        delete abilityRC;
        delete proficiencyRC;

    }
};


TEST_F(RangeConverterTest, AbilityModMinCheck) {

    int32_t input = 1;
    int32_t expected = -5; 
    int32_t actual = abilityRC->convertVal(input);

    ASSERT_EQ(expected, actual);
}

TEST_F(RangeConverterTest, AbilityModCheck){
    int32_t input = 10;
    int32_t expected = 0;
    int32_t actual = abilityRC->convertVal(input);

    ASSERT_EQ(expected, actual);
}

TEST_F(RangeConverterTest, AbilitModAdditionlCheck){
    int32_t input = 16;
    int32_t expected = 3;
    int32_t actual = abilityRC->convertVal(input);

    ASSERT_EQ(expected, actual);
}

TEST_F(RangeConverterTest, AbilityModMaxCheck){

    int32_t input = 30;
    int32_t expected = 10;
    int32_t actual = abilityRC->convertVal(input);

    ASSERT_EQ(expected, actual);
}

TEST_F(RangeConverterTest, ProficiencyBonusMinCheck){

    int32_t input = 1;
    int32_t expected = 2;
    int32_t actual = proficiencyRC->convertVal(input);

    ASSERT_EQ(expected, actual);
}

TEST_F(RangeConverterTest, ProficiencyBonusMaxCheck){
    
    int32_t input = 20;
    int32_t expected = 6;
    int32_t actual = proficiencyRC->convertVal(input);

    ASSERT_EQ(expected, actual);    
}