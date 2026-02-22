#include "crow.h" // „ﬂ »… «·—»ÿ «·”—Ì⁄ ·⁄«„ 2026
#include "blockchain.cpp" // „·› «·‰Ê«… «·”«»ﬁ

int main() {
    crow::SimpleApp app;
    JewelCoinBlockchain JWL; // «” œ⁄«¡ «·»·Êﬂ‘Ì‰

    // [1] „”«—  ÕœÌÀ «·—’Ìœ Ê«·»Ì«‰« 
    CROW_ROUTE(app, "/get_status")
    ([&](){
        crow::json::wvalue res;
        res["balance"] = "150.00";
        res["reserve"] = "7,000,000";
        res["height"] = jwl.getLastBlock().index;
        return res;
    });

    // [2] „”«— ≈—”«· «·⁄„·«  Ê«·—”«∆· «·„‘›—…
    CROW_ROUTE(app, "/send_tx").methods("POST"_method)
    ([&](const crow::request& req){
        auto x = crow::json::load(req.body);
        if (!x) return crow::response(400);

        //  ‰›Ì– «· ‘›Ì— (SHA-3 + RandomX)
        jwl.createBlock(jwl.getLastBlock().index + 1, x["message"].s(), jwl.getLastBlock().hash);
        
        return crow::response(200, "{\"status\"??"success\"}");
    });

    //  ‘€Ì· «·—»ÿ ⁄·Ï «·„‰›– 18081
    app.port(18081).multithreaded().run();
}