#ifndef HEDERA_CLIENT_H
#define HEDERA_CLIENT_H

#include <string>

class HederaClient
{
public:
    HederaClient();
    
    std::string sendTransaction(const std::string& from,
                                const std::string& to,
                                double amount,
                                const std::string& memo,
                                const std::string& privateKey);
    
    double getBalance(const std::string& accountId);
    bool checkTransactionStatus(const std::string& txId);
    
private:
    std::string network;
};

#endif // HEDERA_CLIENT_H
