cmake_minimum_required(VERSION 3.5.0)
project(DND_Dice_Roller VERSION 0.1.0 LANGUAGES C CXX)

find_package(Boost REQUIRED COMPONENTS program_options)

find_package(Protobuf REQUIRED)

include_directories(${Boost_INCLUDE_DIR} ${Protobuf_INCLUDE_DIR})

set(BASE ${CMAKE_CURRENT_LIST_DIR}/library/base)
set(SERIAL ${CMAKE_CURRENT_LIST_DIR}/library/serial)
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${SERIAL}/characterbook.proto)


add_executable(dnddice main.cc ${PROTO_SRCS} ${PROTO_HDRS} ${BASE}/dice.cc ${SERIAL}/ledger.cc ${BASE}/dice.h ${SERIAL}/ledger.h)
target_link_libraries(dnddice PUBLIC Boost::program_options ${Protobuf_LIBRARIES})
target_include_directories(dnddice PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

include(CTest)
enable_testing()

