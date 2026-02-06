#include "wallet/wallet.h"
#include "crypto/keypair.h"
#include "crypto/encryption.h"
#include "storage/wallet_storage.h"
#include "utils/logger.h"
#include <stdexcept>

class Wallet::Impl
{
public:
    bool locked = true;
    std::string network = "mainnet";
    std::string mnemonic;
    std::vector<std::shared_ptr<Account>> accounts;
    
    Encryption encryption;
    WalletStorage storage;
};

Wallet::Wallet() : pImpl(std::make_unique<Impl>())
{
}

Wallet::~Wallet() = default;

bool Wallet::create(const std::string& password)
{
    try {
        // Generate mnemonic
        pImpl->mnemonic = KeyPair::generateMnemonic();
        
        // Initialize encryption
        pImpl->encryption.initialize(password);
        
        // Create first account
        auto account = createAccount("Account 1");
        if (!account) {
            throw std::runtime_error("Failed to create default account");
        }
        
        pImpl->locked = false;
        
        Logger::getInstance().log(LogLevel::INFO, "Wallet created successfully");
        return true;
        
    } catch (const std::exception& e) {
        Logger::getInstance().log(LogLevel::ERROR, 
            std::string("Failed to create wallet: ") + e.what());
        return false;
    }
}

bool Wallet::load(const std::string& filePath, const std::string& password)
{
    try {
        // Load encrypted wallet data
        auto data = pImpl->storage.load(filePath);
        
        // Initialize decryption
        pImpl->encryption.initialize(password);
        
        // Decrypt wallet data
        auto decryptedData = pImpl->encryption.decrypt(data);
        
        // Parse and restore accounts
        pImpl->storage.parseWalletData(decryptedData, pImpl->accounts, 
                                       pImpl->mnemonic, pImpl->network);
        
        pImpl->locked = false;
        
        Logger::getInstance().log(LogLevel::INFO, "Wallet loaded successfully");
        return true;
        
    } catch (const std::exception& e) {
        Logger::getInstance().log(LogLevel::ERROR, 
            std::string("Failed to load wallet: ") + e.what());
        return false;
    }
}

bool Wallet::save(const std::string& filePath)
{
    try {
        if (pImpl->locked) {
            throw std::runtime_error("Wallet is locked");
        }
        
        // Serialize wallet data
        auto data = pImpl->storage.serializeWalletData(pImpl->accounts, 
                                                       pImpl->mnemonic, 
                                                       pImpl->network);
        
        // Encrypt data
        auto encryptedData = pImpl->encryption.encrypt(data);
        
        // Save to file
        pImpl->storage.save(filePath, encryptedData);
        
        Logger::getInstance().log(LogLevel::INFO, "Wallet saved successfully");
        return true;
        
    } catch (const std::exception& e) {
        Logger::getInstance().log(LogLevel::ERROR, 
            std::string("Failed to save wallet: ") + e.what());
        return false;
    }
}

bool Wallet::isLocked() const
{
    return pImpl->locked;
}

bool Wallet::unlock(const std::string& password)
{
    try {
        pImpl->encryption.initialize(password);
        pImpl->locked = false;
        return true;
    } catch (const std::exception& e) {
        Logger::getInstance().log(LogLevel::ERROR, 
            std::string("Failed to unlock wallet: ") + e.what());
        return false;
    }
}

void Wallet::lock()
{
    pImpl->locked = true;
    pImpl->encryption.clear();
}

std::shared_ptr<Account> Wallet::createAccount(const std::string& name)
{
    try {
        if (pImpl->locked) {
            throw std::runtime_error("Wallet is locked");
        }
        
        // Derive new keypair from mnemonic
        size_t index = pImpl->accounts.size();
        auto keyPair = KeyPair::fromMnemonic(pImpl->mnemonic, index);
        
        // Create account
        auto account = std::make_shared<Account>(
            keyPair.getPublicKey(),
            keyPair.getPrivateKey(),
            name.empty() ? "Account " + std::to_string(index + 1) : name
        );
        
        pImpl->accounts.push_back(account);
        
        Logger::getInstance().log(LogLevel::INFO, 
            "Created account: " + account->getAccountId());
        
        return account;
        
    } catch (const std::exception& e) {
        Logger::getInstance().log(LogLevel::ERROR, 
            std::string("Failed to create account: ") + e.what());
        return nullptr;
    }
}

std::shared_ptr<Account> Wallet::importAccount(const std::string& privateKey, 
                                               const std::string& name)
{
    try {
        if (pImpl->locked) {
            throw std::runtime_error("Wallet is locked");
        }
        
        auto keyPair = KeyPair::fromPrivateKey(privateKey);
        
        auto account = std::make_shared<Account>(
            keyPair.getPublicKey(),
            keyPair.getPrivateKey(),
            name.empty() ? "Imported Account" : name
        );
        
        pImpl->accounts.push_back(account);
        
        Logger::getInstance().log(LogLevel::INFO, 
            "Imported account: " + account->getAccountId());
        
        return account;
        
    } catch (const std::exception& e) {
        Logger::getInstance().log(LogLevel::ERROR, 
            std::string("Failed to import account: ") + e.what());
        return nullptr;
    }
}

std::vector<std::shared_ptr<Account>> Wallet::getAccounts() const
{
    return pImpl->accounts;
}

std::shared_ptr<Account> Wallet::getAccount(const std::string& accountId) const
{
    for (const auto& account : pImpl->accounts) {
        if (account->getAccountId() == accountId) {
            return account;
        }
    }
    return nullptr;
}

bool Wallet::removeAccount(const std::string& accountId)
{
    auto it = std::remove_if(pImpl->accounts.begin(), pImpl->accounts.end(),
        [&accountId](const std::shared_ptr<Account>& acc) {
            return acc->getAccountId() == accountId;
        });
    
    if (it != pImpl->accounts.end()) {
        pImpl->accounts.erase(it, pImpl->accounts.end());
        Logger::getInstance().log(LogLevel::INFO, 
            "Removed account: " + accountId);
        return true;
    }
    
    return false;
}

double Wallet::getTotalBalance() const
{
    double total = 0.0;
    for (const auto& account : pImpl->accounts) {
        total += account->getBalance();
    }
    return total;
}

std::vector<Transaction> Wallet::getTransactionHistory() const
{
    std::vector<Transaction> allTransactions;
    for (const auto& account : pImpl->accounts) {
        auto txs = account->getTransactions();
        allTransactions.insert(allTransactions.end(), txs.begin(), txs.end());
    }
    return allTransactions;
}

std::string Wallet::getMnemonic() const
{
    if (pImpl->locked) {
        throw std::runtime_error("Wallet is locked");
    }
    return pImpl->mnemonic;
}

bool Wallet::restoreFromMnemonic(const std::string& mnemonic, 
                                 const std::string& password)
{
    try {
        if (!KeyPair::validateMnemonic(mnemonic)) {
            throw std::runtime_error("Invalid mnemonic");
        }
        
        pImpl->mnemonic = mnemonic;
        pImpl->encryption.initialize(password);
        pImpl->accounts.clear();
        
        // Create first account from mnemonic
        createAccount("Account 1");
        
        pImpl->locked = false;
        
        Logger::getInstance().log(LogLevel::INFO, 
            "Wallet restored from mnemonic");
        return true;
        
    } catch (const std::exception& e) {
        Logger::getInstance().log(LogLevel::ERROR, 
            std::string("Failed to restore from mnemonic: ") + e.what());
        return false;
    }
}

std::string Wallet::exportPrivateKey(const std::string& accountId) const
{
    if (pImpl->locked) {
        throw std::runtime_error("Wallet is locked");
    }
    
    auto account = getAccount(accountId);
    if (!account) {
        throw std::runtime_error("Account not found");
    }
    
    return account->getPrivateKey();
}

void Wallet::setNetwork(const std::string& network)
{
    pImpl->network = network;
    Logger::getInstance().log(LogLevel::INFO, 
        "Network set to: " + network);
}

std::string Wallet::getNetwork() const
{
    return pImpl->network;
}
