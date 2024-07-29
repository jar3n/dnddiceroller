cmake_minimum_required(VERSION 3.28.0)
project(DND_Dice_Roller VERSION 0.0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find the boost and protobuf libraries and include them 
find_package(Boost REQUIRED COMPONENTS program_options filesystem)
find_package(Protobuf REQUIRED)

include_directories(${Boost_INCLUDE_DIR} ${Protobuf_INCLUDE_DIR})

include(CTest)
enable_testing()

add_subdirectory(library)

set(SERIAL ${CMAKE_CURRENT_LIST_DIR}/library/serial)
set(DNDINTERFACE ${CMAKE_CURRENT_LIST_DIR}/library/interface)
set(PROTOS ${CMAKE_CURRENT_LIST_DIR}/library/protos)

# generate the characterbook protobuf cpp files in the cmake build directory
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTOS}/characterbook.proto)

set(LEDGER ${SERIAL}/ledger.cc ${SERIAL}/ledger.h)
set(CREATOR ${DNDINTERFACE}/creator.cc ${DNDINTERFACE}/creator.h)
set(ACCESSOR ${DNDINTERFACE}/accessor.cc ${DNDINTERFACE}/accessor.h)

add_executable(dnddice main.cc ${PROTO_SRCS} ${PROTO_HDRS} ${LEDGER} ${CREATOR} ${ACCESSOR})
target_link_libraries(dnddice PUBLIC Boost::program_options Boost::filesystem ${Protobuf_LIBRARIES} dice range character)

# this is so that the compiler knows to look in the cmake build directory for the protobuf files
target_include_directories(dnddice PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
