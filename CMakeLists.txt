cmake_minimum_required(VERSION 3.28.0)
project(DND_Dice_Roller VERSION 0.0.1 LANGUAGES C CXX)


# find the boost and protobuf libraries and include them
find_package(Boost REQUIRED COMPONENTS program_options)
find_package(Protobuf REQUIRED)
include_directories(${Boost_INCLUDE_DIR} ${Protobuf_INCLUDE_DIR})

set(BASE ${CMAKE_CURRENT_LIST_DIR}/library/base)
set(SERIAL ${CMAKE_CURRENT_LIST_DIR}/library/serial)
set(PROTOS ${CMAKE_CURRENT_LIST_DIR}/library/protos)

# generate the characterbook protobuf cpp files in the cmake build directory
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTOS}/characterbook.proto)

set(DICE ${BASE}/dice.cc ${BASE}/dice.h)
set(LEDGER ${SERIAL}/ledger.cc ${SERIAL}/ledger.h)

add_executable(dnddice main.cc ${PROTO_SRCS} ${PROTO_HDRS} ${DICE} ${LEDGER})
target_link_libraries(dnddice PUBLIC Boost::program_options ${Protobuf_LIBRARIES})

# this is so that the compiler knows to look in the cmake build directory for the protobuf files
target_include_directories(dnddice PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

include(CTest)
enable_testing()

