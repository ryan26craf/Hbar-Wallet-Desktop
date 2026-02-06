#ifndef WALLET_STORAGE_H
#define WALLET_STORAGE_H

#include <string>
#include <vector>
#include <memory>

// Forward declaration
class Account;

class WalletStorage {
public:
    std::vector<uint8_t> load(const std::string& path);
    void save(const std::string& path, const std::vector<uint8_t>& data);
    std::vector<uint8_t> serializeWalletData(
        const std::vector<std::shared_ptr<Account>>& accounts,
        const std::string& mnemonic,
        const std::string& network);
    void parseWalletData(
        const std::vector<uint8_t>& data,
        std::vector<std::shared_ptr<Account>>& accounts,
        std::string& mnemonic,
        std::string& network);
};

#endif // WALLET_STORAGE_H
