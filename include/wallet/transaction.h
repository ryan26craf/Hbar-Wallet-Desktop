#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <ctime>

struct Transaction
{
    std::string txId;
    std::string from;
    std::string to;
    double amount;
    std::string memo;
    std::time_t timestamp;
    std::string status; // pending, confirmed, failed
    double fee;
    
    Transaction()
        : amount(0.0)
        , timestamp(0)
        , fee(0.0)
    {
    }
};

#endif // TRANSACTION_H
