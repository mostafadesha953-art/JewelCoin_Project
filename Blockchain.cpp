#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <fstream> // [÷—Ê—Ì] ··—»ÿ »«·Â«—œ œ”ﬂ
#include <sstream>

// ÂÌﬂ· «·ﬂ ·… (Block Structure)
struct Block {
    int index;
    long long timestamp;
    std::string data;        
    std::string previousHash;
    std::string hash;
    uint32_t nonce;          

    std::string calculateHash() const {
        //  „  »”Ìÿ «·Â«‘ Â‰« ·÷„«‰ ⁄„·Â ›Ì ﬂ· »Ì∆«  CMD Ê GitHub œÊ‰ „ﬂ »«  Œ«—ÃÌ… „⁄ﬁœ…
        std::string record = std::to_string(index) + std::to_string(timestamp) + data + previousHash + std::to_string(nonce);
        size_t h = std::hash<std::string>{}(record);
        return std::to_string(h);
    }
};

classJewelCoinBlockchain {
private:
    std::vector<Block> chain;
    uint32_t difficulty = 4;
    std::string dbPath = "jewel_ledger.dat"; // [«”„ „·› «·Â«—œ œ”ﬂ]

public:
    JewelCoinBlockchain() {
        // [1] „Õ«Ê·… «” ⁄«œ… «·⁄„·«  „‰ «·Â«—œ œ”ﬂ ⁄‰œ  ‘€Ì· «·”Ì” „
        if (!loadFromDisk()) {
            std::cout << "[!] «·”Ã· ›«—€.  ⁄œÌ‰ ﬂ ·… «· ﬂÊÌ‰ (Genesis)..." << std::endl;
            createBlock(0, "JewelCoin Genesis - 2026", "0");
        }
    }

    // [2] ÊŸÌ›… «·Õ›Ÿ «·›Ì“Ì«∆Ì ⁄·Ï «·Â«—œ œ”ﬂ
    void saveToDisk(const Block& b) {
        std::ofstream file(dbPath, std::ios::app); // › Õ «·„·› ›Ì Ê÷⁄ "«·≈÷«›…" (Append)
        if (file.is_open()) {
            file << b.index << "|" << b.timestamp << "|" << b.data << "|" << b.previousHash << "|" << b.hash << "|" << b.nonce << "\n";
            file.close();
            std::cout << "[??]  „  ”ÃÌ· «·ﬂ ·… »‰Ã«Õ ⁄·Ï «·ﬁ—’ «·’·»." << std::endl;
        }
    }

    // [3] ÊŸÌ›… «” ⁄«œ… «·»Ì«‰«  „‰ «·Â«—œ œ”ﬂ ( „‰⁄ ÷Ì«⁄ «· ⁄œÌ‰)
    bool loadFromDisk() {
        std::ifstream file(dbPath);
        if (!file) return false;

        std::string line;
        while (std::getline(file, line)) {
            // „‰ÿﬁ »”Ìÿ ·ﬁ—«¡… «·»Ì«‰«  Ê≈⁄«œ… »‰«¡ «·”·”·… ›Ì «·–«ﬂ—…
            // (Ì„ﬂ‰ﬂ  ÿÊÌ—Â ·«Õﬁ« ·ﬁ—«¡… ﬂ· »«—«„ — ⁄·Ï Õœ…)
        }
        return true;
    }

    void createBlock(int idx, std::string data, std::string prevHash) {
        Block newBlock;
        newBlock.index = idx;
        newBlock.timestamp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        newBlock.data = data;
        newBlock.previousHash = prevHash;
        newBlock.nonce = 0;
        
        std::cout << "Mining Block " << idx << "..." << std::endl;
        do {
            newBlock.nonce++;
            newBlock.hash = newBlock.calculateHash();
        } while (newBlock.hash.substr(0, difficulty) != "0000");

        std::cout << "Block Mined! Hash: " << newBlock.hash << std::endl;
        chain.push_back(newBlock);

        // [«·Õ›Ÿ «·›Ê—Ì]
        saveToDisk(newBlock);
    }

    Block getLastBlock() { return chain.back(); }
};