cmake_minimum_required(VERSION 3.10)
project(test)  # Project name is "test"

set(CMAKE_CXX_STANDARD 17)  # C++17 standard

# OpenSSL Paths
set(OPENSSL_ROOT_DIR "C:/msys64/mingw64")
set(OPENSSL_INCLUDE_DIR "${OPENSSL_ROOT_DIR}/include")
set(OPENSSL_LIB_DIR "${OPENSSL_ROOT_DIR}/lib")

# Find OpenSSL
find_package(OpenSSL REQUIRED)

# Add executable
add_executable(bank bank.cpp)  # Executable name is "bank"

# Link OpenSSL
target_link_libraries(bank PRIVATE ${OPENSSL_CRYPTO_LIBRARY} ${OPENSSL_SSL_LIBRARY})

# Include directories (if needed for other includes)
target_include_directories(bank PRIVATE ${OPENSSL_INCLUDE_DIR})