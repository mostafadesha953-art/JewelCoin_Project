#include "crow.h" // „ﬂ »… Micro-framework ·‹ C++
#include "blockchain.cpp" // «” œ⁄«¡ ﬂÊœ «·»·Êﬂ‘Ì‰ «·”«»ﬁ

int main() {
    crow::SimpleApp app;
    JewelCoinBlockchain xhb; // ≈‰‘«¡ ‰”Œ… „‰ «·»·Êﬂ‘Ì‰

    // „”«— «·Õ’Ê· ⁄·Ï «·—’Ìœ (GET)
    CROW_ROUTE(app, "/get_balance")
    ([&](){
        // ›Ì «·Ê«ﬁ⁄ Ì „ Õ”«» «·—’Ìœ „‰ «·‹ UTXO
        return "{ \"balance\": \"150.50\", \"currency\": \"JWL\" }";
    });

    // „”«— ≈—”«· „⁄«„·… „‘›—… (POST)
    CROW_ROUTE(app, "/send_tx").methods("POST"_method)
    ([&](const crow::request& req){
        auto x = crow::json::load(req.body);
        if (!x) return crow::response(400);
        
        std::string to = x["to"].s();
        double amount = x["amount"].d();

        // «” œ⁄«¡ ÊŸÌ›… «· ⁄œÌ‰ Ê«·Œ’Ê’Ì… „‰ «·»·Êﬂ‘Ì‰
        JWL.createBlock(3, "Private TX to: " + to, jwl.getLastBlock().hash);

        return crow::response("{ \"status\": \"Success\", \"tx_hash\": \"0000abc...\" }");
    });

    app.port(18081).multithreaded().run();
}