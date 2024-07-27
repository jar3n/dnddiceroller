include(character)
include(ledger)

add_library(creator creator.cc)
target_include_directories(creator PUBLIC include)