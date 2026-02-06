#include "storage/wallet_storage.h"
#include <fstream>

std::vector<uint8_t> WalletStorage::load(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    return std::vector<uint8_t>((std::istreambuf_iterator<char>(file)),
                                std::istreambuf_iterator<char>());
}

void WalletStorage::save(const std::string& path, const std::vector<uint8_t>& data) {
    std::ofstream file(path, std::ios::binary);
    file.write(reinterpret_cast<const char*>(data.data()), data.size());
}

std::vector<uint8_t> WalletStorage::serializeWalletData(
    const std::vector<std::shared_ptr<Account>>& accounts,
    const std::string& mnemonic,
    const std::string& network) {
    // Stub implementation
    return {};
}

void WalletStorage::parseWalletData(
    const std::vector<uint8_t>& data,
    std::vector<std::shared_ptr<Account>>& accounts,
    std::string& mnemonic,
    std::string& network) {
    // Stub implementation
}
