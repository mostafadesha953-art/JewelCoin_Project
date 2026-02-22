#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "crypto/sha256.h"

class JewelCoinRecovery {
private:
    // ﬁ«∆„… «·ﬂ·„«  (ﬁ«„Ê” BIP-39 «·„»”ÿ ·⁄«„ 2026)
    std::vector<std::string> wordList = {
        "alpha", "bravo", "cyber", "digital", "echo", "flame", "galaxy", 
        "Jewel", "iron", "jump", "knight", "lunar", "matrix", "noble", 
        "ocean", "privacy", "quantum", "reserve", "sovereign", "titan"
    };

public:
    // 1.  Ê·Ìœ 12 ﬂ·„… ⁄‘Ê«∆Ì… „— »ÿ… »„› «Õ «·‹ 7 „·ÌÊ‰ «Õ Ì«ÿÌ
    std::vector<std::string> generateMnemonic() {
        std::vector<std::string> mnemonic;
        for(int i=0; i<12; i++) {
            int randomIndex = rand() % wordList.size();
            mnemonic.push_back(wordList[randomIndex]);
        }
        return mnemonic;
    }

    // 2.  ÕÊÌ· «·ﬂ·„«  ≈·Ï "„› «Õ ”Ì«œÌ" ·· Õﬂ„ »«·«Õ Ì«ÿÌ
    std::string recoverMasterKey(std::vector<std::string> words) {
        std::string combined;
        for(const auto& w : words) combined += w;
        
        //  ‘›Ì— SHA-256 (»Ì ﬂÊÌ‰) „œ„Ã „⁄ Keccak (≈À—ÌÊ„)
        return "x_master_" + sha256(combined).substr(0, 32);
    }
};

int main() {
    JewelRecovery recovery;
    auto myWords = recovery.generateMnemonic();

    std::cout << "?? Â«„ Ãœ«: «Õ›Ÿ Â–Â «·ﬂ·„«  «·‹ 12 ›Ì Ê—ﬁ… Œ«—ÃÌ…! ??" << std::endl;
    std::cout << "Â–Â «·ﬂ·„«   „‰Õﬂ «·Ê’Ê· ·‹ 21 „·ÌÊ‰ ⁄„·… Ê«·«Õ Ì«ÿÌ «·Œ«’ »ﬂ:" << std::endl;
    
    for(int i=0; i<12; i++) {
        std::cout << i+1 << ". " << myWords[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}