#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string>
#include <vector>

class Encryption
{
public:
    Encryption();
    ~Encryption();
    
    void initialize(const std::string& password);
    void clear();
    
    std::vector<uint8_t> encrypt(const std::vector<uint8_t>& data) const;
    std::vector<uint8_t> decrypt(const std::vector<uint8_t>& data) const;
    
private:
    std::vector<uint8_t> key;
    std::vector<uint8_t> salt;
};

#endif // ENCRYPTION_H
