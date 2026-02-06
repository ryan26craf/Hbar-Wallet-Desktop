#include "wallet/account.h"
#include "network/hedera_client.h"
#include "utils/logger.h"
#include "utils/converter.h"
#include <openssl/sha.h>
#include <iomanip>
#include <sstream>

Account::Account(const std::string& publicKey, 
                 const std::string& privateKey,
                 const std::string& name)
    : publicKey(publicKey)
    , privateKey(privateKey)
    , name(name)
    , balance(0.0)
{
    accountId = generateAccountId(publicKey);
}

std::string Account::getAccountId() const
{
    return accountId;
}

std::string Account::getPublicKey() const
{
    return publicKey;
}

std::string Account::getPrivateKey() const
{
    return privateKey;
}

std::string Account::getName() const
{
    return name;
}

double Account::getBalance() const
{
    return balance;
}

void Account::setName(const std::string& name)
{
    this->name = name;
}

void Account::setBalance(double balance)
{
    this->balance = balance;
}

std::vector<Transaction> Account::getTransactions() const
{
    return transactions;
}

void Account::addTransaction(const Transaction& tx)
{
    transactions.push_back(tx);
}

bool Account::send(const std::string& toAddress, double amount, const std::string& memo)
{
    try {
        if (amount <= 0) {
            throw std::runtime_error("Invalid amount");
        }
        
        if (amount > balance) {
            throw std::runtime_error("Insufficient balance");
        }
        
        // Create and send transaction via Hedera client
        HederaClient client;
        auto txId = client.sendTransaction(accountId, toAddress, amount, memo, privateKey);
        
        // Create transaction record
        Transaction tx;
        tx.txId = txId;
        tx.from = accountId;
        tx.to = toAddress;
        tx.amount = amount;
        tx.memo = memo;
        tx.timestamp = std::time(nullptr);
        tx.status = "pending";
        
        transactions.push_back(tx);
        
        Logger::getInstance().log(LogLevel::INFO, 
            "Transaction sent: " + txId);
        
        return true;
        
    } catch (const std::exception& e) {
        Logger::getInstance().log(LogLevel::ERROR, 
            std::string("Failed to send transaction: ") + e.what());
        return false;
    }
}

std::string Account::generateAccountId(const std::string& pubKey) const
{
    // Simple account ID generation (in real implementation, this would
    // involve interacting with Hedera network)
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(pubKey.c_str()), 
           pubKey.length(), hash);
    
    std::stringstream ss;
    ss << "0.0.";
    
    // Use first 8 bytes of hash as account number
    uint64_t accountNum = 0;
    for (int i = 0; i < 8; ++i) {
        accountNum = (accountNum << 8) | hash[i];
    }
    
    ss << (accountNum % 1000000000);
    
    return ss.str();
}
