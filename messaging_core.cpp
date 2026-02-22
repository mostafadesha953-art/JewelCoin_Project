#include <iostream>
#include <string>
#include "crypto/ecdh.h"   // ·· »«œ· «·¬„‰ ··„›« ÌÕ
#include "crypto/aes_gcm.h" // ·· ‘›Ì— «·„ ‰«Ÿ— 256-» 

class JewelCoinMessenger {
public:
    //  Ê·Ìœ —”«·… „‘›—… „ÊÃÂ… ·„Ã›Ÿ… „⁄Ì‰…
    std::string encryptMessage(std::string plainText, std::string recipientPubKey, std::string myPrivKey) {
        // 1. «‘ ﬁ«ﬁ „› «Õ ”—¯Ì „‘ —ﬂ (Shared Secret) »Ì‰ «·„Õ›Ÿ Ì‰
        std::string sharedSecret = ECDH::derive(myPrivKey, recipientPubKey);

        // 2.  ‘›Ì— «·—”«·… »«” Œœ«„ «·„› «Õ «·„‘ —ﬂ
        return AES_GCM::encrypt(plainText, sharedSecret);
    }

    // ›ﬂ  ‘›Ì— «·—”«·… «·„” ﬁ»·…
    std::string decryptMessage(std::string cipherText, std::string senderPubKey, std::string myPrivKey) {
        std::string sharedSecret = ECDH::derive(myPrivKey, senderPubKey);
        return AES_GCM::decrypt(cipherText, sharedSecret);
    }
};