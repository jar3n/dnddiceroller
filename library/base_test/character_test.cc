#include "character.h"
#include "gtest/gtest.h"

TEST(CharacterTest, DefaultConstructor) {
  Character character;
  EXPECT_EQ(character.getName(), "");
  EXPECT_EQ(character.getShortName(), "");
  EXPECT_EQ(character.getLevel(), 1);
  EXPECT_EQ(character.getBackstory(), "");
  for (size_t i = 0; i < NUM_ABILITY_SCORES; i++) {
    EXPECT_EQ(character.getAbilityScore((ability_score)(i)), 0);
  }
  for (size_t i = 0; i < NUM_SKILLS; i++) {
    EXPECT_FALSE(character.isSkillProficient(i));
    EXPECT_FALSE(character.isSkillExpert(i));
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
  character.setAbilityScore((ability_score)(0), 16);
  EXPECT_EQ(character.getAbilityScore((ability_score)(0)), 16);
}

TEST(CharacterTest, GetAbilityMod) {
  Character character;
  character.setAbilityScore((ability_score)(0), 16);
  EXPECT_EQ(character.getAbilityMod((ability_score)(0)), 3);
}

TEST(CharacterTest, GetSkillMod) {
  Character character;
  character.setAbilityScore((ability_score)(0), 16);
  character.setSkillProficiency(0, true);
  EXPECT_EQ(character.getSkillMod((skill)(0)), 5);
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
  character.setSkillProficiency(0, true);
  EXPECT_TRUE(character.isSkillProficient(0));
}

TEST(CharacterTest, SetGetExpertise) {
  Character character;
  character.setSkillExpertise(0, true);
  EXPECT_TRUE(character.isSkillExpert(0));
}

TEST(CharacterTest, CheckGivenIndex) {
  Character character;
  EXPECT_THROW(character.getAbilityScore((ability_score)(NUM_ABILITY_SCORES)), CharacterException);
  EXPECT_THROW(character.setAbilityScore((ability_score)(NUM_ABILITY_SCORES), 16), CharacterException);
  EXPECT_THROW(character.getSkillMod((skill)(NUM_SKILLS)), CharacterException);
  EXPECT_THROW(character.setSkillProficiency(NUM_SKILLS, true), CharacterException);
  EXPECT_THROW(character.setSkillExpertise(NUM_SKILLS, true), CharacterException);
  EXPECT_THROW(character.setSaveProficiency(NUM_ABILITY_SCORES, true), CharacterException);
}

TEST(CharacterTest, GetSaveProficiency) {
  Character character;
  character.setSaveProficiency((ability_score)(0), true);
  EXPECT_TRUE(character.isSaveProficient((ability_score)(0)));
}

TEST(CharacterTest, GetSaveProficiencyDefault) {
  Character character;
  EXPECT_FALSE(character.isSaveProficient((ability_score)(0)));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
