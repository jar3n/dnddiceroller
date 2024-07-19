#include "range.h"
#include "gtest/gtest.h"

class RangeConverterTest : public testing::Test {
    protected:
    RangeConverter * abilityRC;
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
        abilityRC = new RangeConverter(abilityScoreMin, 
                                                abilityScoreMax, 
                                                abilityModMin, 
                                                abilityModMax);

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
    // unit test checking the range calculation
    // for dnd ability score to mod


    // score of 1 means mod of -5
    int32_t input = 1;
    int32_t expected = -5; 
    int32_t actual = abilityRC->convertVal(input);

    ASSERT_EQ(expected, actual);
}
TEST_F(RangeConverterTest, AbilityModMaxCheck){

    // score 20 means mod 10
    int32_t input = 20;
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