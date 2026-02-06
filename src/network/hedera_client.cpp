#include "network/hedera_client.h"
#include <ctime>
#include <sstream>

HederaClient::HederaClient() : network("mainnet")
{
}

std::string HederaClient::sendTransaction(const std::string& from,
                                         const std::string& to,
                                         double amount,
                                         const std::string& memo,
                                         const std::string& privateKey)
{
    // Stub implementation - returns mock transaction ID
    std::stringstream ss;
    ss << "0.0." << std::time(nullptr);
    return ss.str();
}

double HederaClient::getBalance(const std::string& accountId)
{
    // Stub - returns mock balance
    return 100.0;
}

bool HederaClient::checkTransactionStatus(const std::string& txId)
{
    // Stub - returns success
    return true;
}
