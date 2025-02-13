cmake_minimum_required(VERSION 3.10)
project(test)

set(CMAKE_CXX_STANDARD 17)

# OpenSSL Paths
set(OPENSSL_ROOT_DIR "C:/msys64/mingw64")
set(OPENSSL_INCLUDE_DIR "${OPENSSL_ROOT_DIR}/include")
set(OPENSSL_LIB_DIR "${OPENSSL_ROOT_DIR}/lib")

# Find OpenSSL
find_package(OpenSSL REQUIRED)

# Add executable
add_executable(bank bank.cpp)

# Link OpenSSL
target_include_directories(bank PRIVATE ${OPENSSL_INCLUDE_DIR})
target_link_directories(bank PRIVATE ${OPENSSL_LIB_DIR})
target_link_libraries(bank PRIVATE crypto ssl)
