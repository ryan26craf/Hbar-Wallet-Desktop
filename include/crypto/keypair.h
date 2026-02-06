#ifndef KEYPAIR_H
#define KEYPAIR_H

#include <string>
#include <vector>

class KeyPair
{
public:
    KeyPair();
    KeyPair(const std::string& publicKey, const std::string& privateKey);
    
    // Key generation
    static KeyPair generate();
    static KeyPair fromPrivateKey(const std::string& privateKey);
    static KeyPair fromMnemonic(const std::string& mnemonic, size_t index = 0);
    
    // Mnemonic (BIP39)
    static std::string generateMnemonic(int wordCount = 24);
    static bool validateMnemonic(const std::string& mnemonic);
    
    // Getters
    std::string getPublicKey() const;
    std::string getPrivateKey() const;
    std::string getPublicKeyHex() const;
    std::string getPrivateKeyHex() const;
    
    // Signing
    std::string sign(const std::string& message) const;
    bool verify(const std::string& message, const std::string& signature) const;
    
private:
    std::vector<uint8_t> publicKey;
    std::vector<uint8_t> privateKey;
    
    static std::vector<uint8_t> hexToBytes(const std::string& hex);
    static std::string bytesToHex(const std::vector<uint8_t>& bytes);
};

#endif // KEYPAIR_H
