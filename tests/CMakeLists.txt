# Tests configuration
add_executable(wallet_tests test_wallet.cpp)
target_link_libraries(wallet_tests PRIVATE Qt6::Test)
add_test(NAME WalletTests COMMAND wallet_tests)
