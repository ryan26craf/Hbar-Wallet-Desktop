cmake_minimum_required(VERSION 3.20)
project(HbarWalletDesktop VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Options
option(BUILD_TESTS "Build tests" ON)
option(ENABLE_WALLET_ENCRYPTION "Enable wallet encryption" ON)

# Find required packages
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Network)
find_package(OpenSSL REQUIRED)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
    ${OPENSSL_INCLUDE_DIR}
)

# Source files
set(SOURCES
    src/main.cpp
    src/wallet/wallet.cpp
    src/wallet/account.cpp
    src/wallet/transaction.cpp
    src/crypto/keypair.cpp
    src/crypto/encryption.cpp
    src/network/hedera_client.cpp
    src/network/rest_client.cpp
    src/ui/main_window.cpp
    src/ui/create_wallet_dialog.cpp
    src/ui/send_dialog.cpp
    src/ui/receive_dialog.cpp
    src/ui/settings_dialog.cpp
    src/storage/wallet_storage.cpp
    src/storage/config.cpp
    src/utils/logger.cpp
    src/utils/converter.cpp
)

# Header files
set(HEADERS
    include/wallet/wallet.h
    include/wallet/account.h
    include/wallet/transaction.h
    include/crypto/keypair.h
    include/crypto/encryption.h
    include/network/hedera_client.h
    include/network/rest_client.h
    include/ui/main_window.h
    include/ui/create_wallet_dialog.h
    include/ui/send_dialog.h
    include/ui/receive_dialog.h
    include/ui/settings_dialog.h
    include/storage/wallet_storage.h
    include/storage/config.h
    include/utils/logger.h
    include/utils/converter.h
)

# Qt MOC files
set(MOC_HEADERS
    include/ui/main_window.h
    include/ui/create_wallet_dialog.h
    include/ui/send_dialog.h
    include/ui/receive_dialog.h
    include/ui/settings_dialog.h
)

# Qt resource files
set(RESOURCES
    resources/resources.qrc
)

# Process Qt files
qt_add_executable(HbarWalletDesktop
    ${SOURCES}
    ${HEADERS}
    ${RESOURCES}
)

# Link libraries
target_link_libraries(HbarWalletDesktop PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::Network
    OpenSSL::SSL
    OpenSSL::Crypto
)

# Platform-specific settings
if(WIN32)
    # Windows specific
    target_compile_definitions(HbarWalletDesktop PRIVATE WIN32_LEAN_AND_MEAN)
    set_target_properties(HbarWalletDesktop PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
    
    # Add icon
    target_sources(HbarWalletDesktop PRIVATE resources/app.rc)
endif()

# Compiler warnings
if(MSVC)
    target_compile_options(HbarWalletDesktop PRIVATE /W4)
else()
    target_compile_options(HbarWalletDesktop PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Install rules
install(TARGETS HbarWalletDesktop
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

# Install Qt dependencies on Windows
if(WIN32)
    install(CODE "
        include(InstallRequiredSystemLibraries)
        set(CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP TRUE)
    ")
endif()

# Tests
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
