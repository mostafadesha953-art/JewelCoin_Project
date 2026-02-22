#include <openssl/evp.h>
#include <openssl/aes.h>
#include <fstream>
#include <iostream>

class WalletEncryptor {
public:
    // œ«·…  ‘›Ì— „·› «·„Õ›Ÿ…
    void encryptWalletFile(std::string filename, std::string password) {
        std::ifstream inFile(filename, std::ios::binary);
        std::ofstream outFile(filename + ".enc", std::ios::binary);

        //  Ê·Ìœ „› «Õ (Key) Ê‰«ﬁ· (IV) „‰ ﬂ·„… «·„—Ê— »«” Œœ«„ PBKDF2
        unsigned char key[32], iv[16];
        PKCS5_PBKDF2_HMAC(password.c_str(), password.length(), NULL, 0, 10000, EVP_sha256(), 32, key);

        // »œ¡ ⁄„·Ì… «· ‘›Ì— »‹ AES-256
        EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
        EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);

        //  ‘›Ì— „Õ ÊÌ«  «·„·› ÊÕ›ŸÂ«
        // ... (⁄„·Ì… „⁄«·Ã… «·»Ì«‰« ) ...
        
        std::cout << "?  „  Õ„«Ì… «·„Õ›Ÿ… Ê ‘›Ì— «·„·› »‰Ã«Õ." << std::endl;
        EVP_CIPHER_CTX_free(ctx);
    }
};
