#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>
#include "transaction.h"

class Account
{
public:
    Account(const std::string& publicKey, 
            const std::string& privateKey,
            const std::string& name);
    
    // Getters
    std::string getAccountId() const;
    std::string getPublicKey() const;
    std::string getPrivateKey() const;
    std::string getName() const;
    double getBalance() const;
    
    // Setters
    void setName(const std::string& name);
    void setBalance(double balance);
    
    // Transactions
    std::vector<Transaction> getTransactions() const;
    void addTransaction(const Transaction& tx);
    
    // Actions
    bool send(const std::string& toAddress, double amount, const std::string& memo = "");
    
private:
    std::string accountId;
    std::string publicKey;
    std::string privateKey;
    std::string name;
    double balance;
    std::vector<Transaction> transactions;
    
    std::string generateAccountId(const std::string& pubKey) const;
};

#endif // ACCOUNT_H
