#include "crypto/keypair.h"
#include <openssl/evp.h>
#include <openssl/ec.h>
#include <openssl/rand.h>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <algorithm>

// BIP39 word list (abbreviated for demonstration)
static const std::vector<std::string> BIP39_WORDS = {
    "abandon", "ability", "able", "about", "above", "absent", "absorb", "abstract",
    "absurd", "abuse", "access", "accident", "account", "accuse", "achieve", "acid",
    // ... (full 2048 word list would be here)
};

KeyPair::KeyPair()
{
}

KeyPair::KeyPair(const std::string& publicKey, const std::string& privateKey)
    : publicKey(hexToBytes(publicKey))
    , privateKey(hexToBytes(privateKey))
{
}

KeyPair KeyPair::generate()
{
    KeyPair keyPair;
    
    // Generate ED25519 keypair
    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_ED25519, NULL);
    if (!ctx) {
        throw std::runtime_error("Failed to create context");
    }
    
    EVP_PKEY* pkey = NULL;
    if (EVP_PKEY_keygen_init(ctx) <= 0 ||
        EVP_PKEY_keygen(ctx, &pkey) <= 0) {
        EVP_PKEY_CTX_free(ctx);
        throw std::runtime_error("Failed to generate keypair");
    }
    
    // Extract keys
    size_t pubKeyLen = 32;
    size_t privKeyLen = 32;
    keyPair.publicKey.resize(pubKeyLen);
    keyPair.privateKey.resize(privKeyLen);
    
    EVP_PKEY_get_raw_public_key(pkey, keyPair.publicKey.data(), &pubKeyLen);
    EVP_PKEY_get_raw_private_key(pkey, keyPair.privateKey.data(), &privKeyLen);
    
    EVP_PKEY_free(pkey);
    EVP_PKEY_CTX_free(ctx);
    
    return keyPair;
}

KeyPair KeyPair::fromPrivateKey(const std::string& privateKey)
{
    KeyPair keyPair;
    keyPair.privateKey = hexToBytes(privateKey);
    
    // Derive public key from private key
    EVP_PKEY* pkey = EVP_PKEY_new_raw_private_key(
        EVP_PKEY_ED25519, NULL, 
        keyPair.privateKey.data(), 
        keyPair.privateKey.size());
    
    if (!pkey) {
        throw std::runtime_error("Failed to create key from private key");
    }
    
    size_t pubKeyLen = 32;
    keyPair.publicKey.resize(pubKeyLen);
    EVP_PKEY_get_raw_public_key(pkey, keyPair.publicKey.data(), &pubKeyLen);
    
    EVP_PKEY_free(pkey);
    
    return keyPair;
}

KeyPair KeyPair::fromMnemonic(const std::string& mnemonic, size_t index)
{
    if (!validateMnemonic(mnemonic)) {
        throw std::runtime_error("Invalid mnemonic");
    }
    
    // In a real implementation, this would use BIP32/BIP44 derivation
    // For now, we'll use a simple hash-based approach
    std::string seed = mnemonic + std::to_string(index);
    
    unsigned char hash[32];
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(ctx, EVP_sha256(), NULL);
    EVP_DigestUpdate(ctx, seed.c_str(), seed.length());
    EVP_DigestFinal_ex(ctx, hash, NULL);
    EVP_MD_CTX_free(ctx);
    
    std::string privateKeyHex = bytesToHex(std::vector<uint8_t>(hash, hash + 32));
    
    return fromPrivateKey(privateKeyHex);
}

std::string KeyPair::generateMnemonic(int wordCount)
{
    if (wordCount != 12 && wordCount != 24) {
        throw std::runtime_error("Word count must be 12 or 24");
    }
    
    std::vector<uint8_t> entropy(wordCount == 12 ? 16 : 32);
    if (RAND_bytes(entropy.data(), entropy.size()) != 1) {
        throw std::runtime_error("Failed to generate random bytes");
    }
    
    // Convert entropy to mnemonic words
    std::vector<std::string> words;
    for (size_t i = 0; i < static_cast<size_t>(wordCount); ++i) {
        size_t index = entropy[i % entropy.size()] % BIP39_WORDS.size();
        words.push_back(BIP39_WORDS[index]);
    }
    
    std::string mnemonic;
    for (size_t i = 0; i < words.size(); ++i) {
        if (i > 0) mnemonic += " ";
        mnemonic += words[i];
    }
    
    return mnemonic;
}

bool KeyPair::validateMnemonic(const std::string& mnemonic)
{
    std::istringstream iss(mnemonic);
    std::vector<std::string> words;
    std::string word;
    
    while (iss >> word) {
        words.push_back(word);
    }
    
    if (words.size() != 12 && words.size() != 24) {
        return false;
    }
    
    // Validate each word is in dictionary
    for (const auto& w : words) {
        if (std::find(BIP39_WORDS.begin(), BIP39_WORDS.end(), w) == BIP39_WORDS.end()) {
            return false;
        }
    }
    
    return true;
}

std::string KeyPair::getPublicKey() const
{
    return bytesToHex(publicKey);
}

std::string KeyPair::getPrivateKey() const
{
    return bytesToHex(privateKey);
}

std::string KeyPair::getPublicKeyHex() const
{
    return bytesToHex(publicKey);
}

std::string KeyPair::getPrivateKeyHex() const
{
    return bytesToHex(privateKey);
}

std::string KeyPair::sign(const std::string& message) const
{
    EVP_PKEY* pkey = EVP_PKEY_new_raw_private_key(
        EVP_PKEY_ED25519, NULL, 
        privateKey.data(), 
        privateKey.size());
    
    if (!pkey) {
        throw std::runtime_error("Failed to create key for signing");
    }
    
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    if (EVP_DigestSignInit(ctx, NULL, NULL, NULL, pkey) <= 0) {
        EVP_PKEY_free(pkey);
        EVP_MD_CTX_free(ctx);
        throw std::runtime_error("Failed to init signing");
    }
    
    size_t sigLen = 0;
    EVP_DigestSign(ctx, NULL, &sigLen, 
                  reinterpret_cast<const unsigned char*>(message.data()), 
                  message.length());
    
    std::vector<uint8_t> signature(sigLen);
    EVP_DigestSign(ctx, signature.data(), &sigLen, 
                  reinterpret_cast<const unsigned char*>(message.data()), 
                  message.length());
    
    EVP_MD_CTX_free(ctx);
    EVP_PKEY_free(pkey);
    
    return bytesToHex(signature);
}

bool KeyPair::verify(const std::string& message, const std::string& signature) const
{
    auto sigBytes = hexToBytes(signature);
    
    EVP_PKEY* pkey = EVP_PKEY_new_raw_public_key(
        EVP_PKEY_ED25519, NULL, 
        publicKey.data(), 
        publicKey.size());
    
    if (!pkey) {
        return false;
    }
    
    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    if (EVP_DigestVerifyInit(ctx, NULL, NULL, NULL, pkey) <= 0) {
        EVP_PKEY_free(pkey);
        EVP_MD_CTX_free(ctx);
        return false;
    }
    
    int result = EVP_DigestVerify(ctx, sigBytes.data(), sigBytes.size(),
                                 reinterpret_cast<const unsigned char*>(message.data()), 
                                 message.length());
    
    EVP_MD_CTX_free(ctx);
    EVP_PKEY_free(pkey);
    
    return result == 1;
}

std::vector<uint8_t> KeyPair::hexToBytes(const std::string& hex)
{
    std::vector<uint8_t> bytes;
    for (size_t i = 0; i < hex.length(); i += 2) {
        std::string byteString = hex.substr(i, 2);
        uint8_t byte = static_cast<uint8_t>(strtol(byteString.c_str(), NULL, 16));
        bytes.push_back(byte);
    }
    return bytes;
}

std::string KeyPair::bytesToHex(const std::vector<uint8_t>& bytes)
{
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for (const auto& byte : bytes) {
        ss << std::setw(2) << static_cast<int>(byte);
    }
    return ss.str();
}
