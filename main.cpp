#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include "config.h"
#include "crow.h" // ãßÊÈÉ ÇáÜ API áÑÈØ ÇáæÇÌåÉ

// [1] åíßá ÇáßÊáÉ (Block Structure)
struct Block {
    int index;
    std::string prevHash;
    std::string data;
    uint32_t nonce;
    std::string hash;
};

// [2] ßáÇÓ ÇáÈáæßÔíä ãÚ ãÍÑß ÇáÊÚÏíä ÇáĞßí
class Blockchain {
public:
    std::vector<Block> chain;
    double walletBalance = 0.0;

    Blockchain() {
        // ÚäÏ ÊÔÛíá ÇáäÙÇã¡ äÈÏÃ İæÑÇğ ÈÊÚÏíä Ãæá ÚãáÉ (Genesis)
        mineFirstBlock();
    }

    // ÏÇáÉ ÍÓÇÈ ÇáåÇÔ ÇáåÌíä (SHA3 + RandomX ÇáÊÎíáí)
    std::string calculateHybridHash(Block& b) {
        std::string record = std::to_string(b.index) + b.prevHash + b.data + std::to_string(b.nonce);
        // ãÍÇßÇÉ ááÊÔİíÑ ÇáÚÇáí - İí ÇáäÓÎÉ ÇáİÚáíÉ ÊõÓÊÏÚì ãßÊÈÉ SHA3
        return std::to_string(std::hash<std::string>{}(record)); 
    }

    // ãÑÍáÉ ÅØáÇŞ Ãæá ÚãáÉ X-Hybrid (Genesis Mining)
    void mineFirstBlock() {
        Block genesis;
        genesis.index = 0;
        genesis.data = "X-Hybrid Genesis Block - Private Era 2026";
        genesis.prevHash = "00000000000000000000000000000000";
        genesis.nonce = 0;

        std::cout << "[!] ÌÇÑí ÇáÈÍË Úä Ãæá ÚãáÉ... (ÊÚÏíä CPU Ğßí äÔØ)" << std::endl;

        while (true) {
            genesis.hash = calculateHybridHash(genesis);
            
            // ÔÑØ ÇáÕÚæÈÉ: ÇáåÇÔ íÈÏÃ ÈÜ "0000" (ßãÇ åæ ãÍÏÏ İí config.h)
            if (genesis.hash.substr(0, 4) == "0000") {
                std::cout << "? äÌÇÍ! Êã ÊÚÏíä Ãæá ßÊáÉ ÓíÇÏíÉ." << std::endl;
                std::cout << "?? ÇáåÇÔ: " << genesis.hash << std::endl;
                std::cout << "?? ÇáãßÇİÃÉ ÇáÃæáì ÇáãÖÇİÉ ááãÍİÙÉ: 50 XHB" << std::endl;
                
                walletBalance += 50.0; // ÅÖÇİÉ ÇáãßÇİÃÉ ááÑÕíÏ
                chain.push_back(genesis);
                break;
            }
            genesis.nonce++;

            // ãíÒÉ ÇáÜ AI: ãäÚ ÊÌãíÏ ÇáÌåÇÒ (ÊåÏÆÉ ÇáÃäæíÉ ßá 1000 ãÍÇæáÉ)
            if (genesis.nonce % 1000 == 0) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        }
    }

    // ÅÖÇİÉ ßÊá ÌÏíÏÉ (ááãÚÇãáÇÊ ÇáÚÇÏíÉ Ãæ ÊÍÑíÑ ÇáÇÍÊíÇØí)
    void addBlock(std::string data) {
        Block newBlock;
        newBlock.index = chain.size();
        newBlock.data = data;
        newBlock.prevHash = chain.back().hash;
        newBlock.nonce = 0;

        while (true) {
            newBlock.hash = calculateHybridHash(newBlock);
            if (newBlock.hash.substr(0, 4) == "0000") {
                chain.push_back(newBlock);
                break;
            }
            newBlock.nonce++;
        }
    }
};

// [3] ÊÔÛíá ÇáÓíÑİÑ æÇáÑÈØ ÈÇáæÇÌåÉ
int main() {
    Blockchain xhb; // ÓíŞæã ÊáŞÇÆíÇğ ÈÊÚÏíä Ãæá ßÊáÉ ÚäÏ ÇáÈÏÁ
    crow::SimpleApp app;

    // ãÓÇÑ ÌáÈ ÇáÈíÇäÇÊ ÇáãÍÏËÉ ááãÍİÙÉ (ÇáÑÕíÏ æÇáÇÍÊíÇØí)
    CROW_ROUTE(app, "/status")([&](){
        crow::json::wvalue res;
        res["balance"] = std::to_string(xhb.walletBalance);
        res["reserve"] = "7000000"; // ÇáÜ 7 ãáíæä ÇÍÊíÇØí ËÇÈÊÉ ÈÑãÌíÇğ
        res["height"] = xhb.chain.size();
        return res;
    });

    // ãÓÇÑ ÇáÊÍßã ÇáÓíÇÏí İí ÇáÇÍÊíÇØí (Admin Only)
    CROW_ROUTE(app, "/admin_release").methods("POST"_method)([&](const crow::request& req){
        auto x = crow::json::load(req.body);
        if (x["auth"].s() == XHybrid::MASTER_KEY) {
            xhb.addBlock("Reserve Release: " + std::to_string(x["amount"].d()));
            return crow::response(200, "Success");
        }
        return crow::response(403, "Unauthorized");
    });

    std::cout << "------------------------------------------" << std::endl;
    std::cout << "X-Hybrid Node is Live on Port 18081" << std::endl;
    std::cout << "Open index.html to control your assets." << std::endl;
    std::cout << "------------------------------------------" << std::endl;

    app.port(18081).multithreaded().run();
    return 0;
}