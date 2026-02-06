#ifndef WALLET_H
#define WALLET_H

#include <string>
#include <vector>
#include <memory>
#include "account.h"
#include "transaction.h"

class Wallet
{
public:
    Wallet();
    ~Wallet();
    
    // Wallet management
    bool create(const std::string& password);
    bool load(const std::string& filePath, const std::string& password);
    bool save(const std::string& filePath);
    bool isLocked() const;
    bool unlock(const std::string& password);
    void lock();
    
    // Account management
    std::shared_ptr<Account> createAccount(const std::string& name = "");
    std::shared_ptr<Account> importAccount(const std::string& privateKey, 
                                          const std::string& name = "");
    std::vector<std::shared_ptr<Account>> getAccounts() const;
    std::shared_ptr<Account> getAccount(const std::string& accountId) const;
    bool removeAccount(const std::string& accountId);
    
    // Balance and transactions
    double getTotalBalance() const;
    std::vector<Transaction> getTransactionHistory() const;
    
    // Backup and recovery
    std::string getMnemonic() const;
    bool restoreFromMnemonic(const std::string& mnemonic, 
                            const std::string& password);
    std::string exportPrivateKey(const std::string& accountId) const;
    
    // Network
    void setNetwork(const std::string& network); // mainnet, testnet, previewnet
    std::string getNetwork() const;
    
private:
    class Impl;
    std::unique_ptr<Impl> pImpl;
};

#endif // WALLET_H
