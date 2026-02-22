#include <iostream>
#include <string>
#include <vector>
#include "crypto/secp256k1.h" // ãßÊÈÉ ÊÔİíÑ ÅËÑíæã æÈíÊßæíä
#include "crypto/ed25519.h"   // ãßÊÈÉ ÊÔİíÑ ãæäíÑæ ááÎÕæÕíÉ

class JewelWallet {
private:
    std::string privateKey; // ÇáãİÊÇÍ ÇáÓÑí (áÇ íÙåÑ áÃÍÏ)
    std::string publicKey;  // ÇáãİÊÇÍ ÇáÚÇã (ÇáåæíÉ)
    std::string stealthAddress; // ÇáÚäæÇä ÇáãÊÎİí (ááÇÓÊáÇã ÈÎÕæÕíÉ)

public:
    JewelWallet() {
        generateKeys();
    }

    // ÊæáíÏ ãİÇÊíÍ ãÏãÌÉ (ÚÇáíÉ ÇáÊÔİíÑ)
    void generateKeys() {
        // 1. ÊæáíÏ ãİÊÇÍ ÎÇÕ ÚÔæÇÆí Şæí ÌÏÇğ
        privateKey = Crypto::generateRandomSeed(32); 

        // 2. ÇÔÊŞÇŞ ÇáãİÊÇÍ ÇáÚÇã (ØÑíŞÉ ÈíÊßæíä/ÅËÑíæã)
        publicKey = Crypto::derivePublicKey(privateKey);

        // 3. ÅäÔÇÁ "ÇáÚäæÇä ÇáãÊÎİí" (ØÑíŞÉ ãæäíÑæ)
        // åĞÇ ÇáÚäæÇä íÊÛíÑ İí ßá ãÚÇãáÉ áÅÎİÇÁ åæíÉ ÇáãÓÊáã
        stealthAddress = "jwl_" + Crypto::sha3_256(publicKey + std::to_string(time(0)));
    }

    void displayWalletInfo() {
        std::cout << "--- ãÍİÙÉ JewelCoin ÇáÌÇåÒÉ ---" << std::endl;
        std::cout << "Public Key: " << publicKey << std::endl;
        std::cout << "Stealth Address (Privacy): " << stealthAddress << std::endl;
        std::cout << "-------------------------------" << std::endl;
        std::cout << "!! ÊÍĞíÑ: ÇÍİÙ ãİÊÇÍß ÇáÎÇÕ İí ãßÇä Âãä !!" << std::endl;
    }

    // æÙíİÉ ÊæŞíÚ ÇáãÚÇãáÉ (ãËá ÈíÊßæíä)
    std::string signTransaction(std::string txData) {
        return Crypto::sign(txData, privateKey);
    }
};

int main() {
    JewelWallet myWallet;
    myWallet.displayWalletInfo();
    return 0;
}