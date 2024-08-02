#include "character.h"
#include "gtest/gtest.h"

TEST(CharacterTest, DefaultConstructor) {
  Character character;
  EXPECT_EQ(character.getName(), "");
  EXPECT_EQ(character.getShortName(), "");
  EXPECT_EQ(character.getLevel(), 1);
  EXPECT_EQ(character.getBackstory(), "");
  for (size_t i = 0; i < NUM_ABILITY_SCORES; i++) {
    EXPECT_EQ(character.getAbilityScore(i), 0);
  }
  for (size_t i = 0; i < NUM_SKILLS; i++) {
    EXPECT_FALSE(character.isProficient(i));
    EXPECT_FALSE(character.isExpert(i));
  }
}

TEST(CharacterTest, SetGetName) {
  Character character;
  character.setName("John Doe");
  EXPECT_EQ(character.getName(), "John Doe");
}

TEST(CharacterTest, SetGetShortName) {
  Character character;
  character.setShortName("JD");
  EXPECT_EQ(character.getShortName(), "JD");
}

TEST(CharacterTest, SetGetLevel) {
  Character character;
  character.setLevel(5);
  EXPECT_EQ(character.getLevel(), 5);
}

TEST(CharacterTest, SetGetBackstory) {
  Character character;
  character.setBackstory("Born in a small village");
  EXPECT_EQ(character.getBackstory(), "Born in a small village");
}

TEST(CharacterTest, SetGetAbilityScore) {
  Character character;
  character.setAbilityScore(0, 16);
  EXPECT_EQ(character.getAbilityScore(0), 16);
}

TEST(CharacterTest, GetAbilityMod) {
  Character character;
  character.setAbilityScore(0, 16);
  EXPECT_EQ(character.getAbilityMod(0), 3);
}

TEST(CharacterTest, GetSkillMod) {
  Character character;
  character.setAbilityScore(0, 16);
  character.setProficiency(0, true);
  EXPECT_EQ(character.getSkillMod(0), 5);
}

TEST(CharacterTest, GetProficiencyBonus) {
  Character character;
  character.setLevel(5);
  EXPECT_EQ(character.getProficiencyBonus(), 3);
}

TEST(Charactertest, GetMinProficiencyBonus){
    Character character;
    character.setLevel(1);
    EXPECT_EQ(character.getProficiencyBonus(), 2);
}

TEST(CharacterTest, getMaxProficiencyBonus){
    Character character;
    character.setLevel(20);
    EXPECT_EQ(character.getProficiencyBonus(), 6);
}

TEST(CharacterTest, SetGetProficiency) {
  Character character;
  character.setProficiency(0, true);
  EXPECT_TRUE(character.isProficient(0));
}

TEST(CharacterTest, SetGetExpertise) {
  Character character;
  character.setExpertise(0, true);
  EXPECT_TRUE(character.isExpert(0));
}

TEST(CharacterTest, CheckGivenIndex) {
  Character character;
  EXPECT_THROW(character.getAbilityScore(NUM_ABILITY_SCORES), CharacterException);
  EXPECT_THROW(character.setAbilityScore(NUM_ABILITY_SCORES, 16), CharacterException);
  EXPECT_THROW(character.getSkillMod(NUM_SKILLS), CharacterException);
  EXPECT_THROW(character.setProficiency(NUM_SKILLS, true), CharacterException);
  EXPECT_THROW(character.setExpertise(NUM_SKILLS, true), CharacterException);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
