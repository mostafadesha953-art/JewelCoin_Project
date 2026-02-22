#include <iostream>
#include <string>
#include <ctime>
#include "crypto/hash.h" // гя »… «б ‘Ён— «бќ«’… »«бЏгб…

// яжѕ ≈д‘«Ѕ я б… «б яжнд бЏгб… JewelCoin
void CreateGenesisBlock() {
    // 1. "—”«б… «бЏ’—" (гЋб »н яжнд) -  ÷Џ ќ»—«р гд  «—нќ «бнжг б÷г«д Џѕг «б б«Џ»
    std::string timestamp_msg = "Feb 08 2026: JewelCoin Privacy Era Begins with CPU Mining";

    // 2. ≈Џѕ«ѕ«  «бгя«Ё√… «б√жбн… (»н яжнд/б«н яжнд)
    uint64_t genesis_reward = 50 * 100000000; // 50 Џгб…

    // 3. Ў«»Џ «бжё  (Timestamp) бЏ«г 2026
    uint32_t nTime = 1739019300; // нгЋб  «—нќ «бнжг » жён  Unix

    // 4. джд’ «б Џѕнд (Nonce) - «б—ёг «б–н ”н»ЌЋ Џде «бгЏ«бћ
    uint32_t nNonce = 0;

    std::cout << " жбнѕ я б… «б яжнд... н—ћм «б«д ў«— ( Џѕнд CPU ћ«—н)" << std::endl;

    // Џгбн… " Џѕнд" «бя б… «б√жбм бѕгћ «б ‘Ён— (RandomX + SHA3)
    while (true) {
        std::string block_data = timestamp_msg + std::to_string(nTime) + std::to_string(nNonce);
        std::string hash = CalculateJewelCoinHash(block_data); // ѕ«б…  ‘Ён— гѕгћ…

        // ‘—Ў «б’Џж»… ббя б… «б√жбм (нћ» √д н»ѕ√ «бе«‘ »√’Ё«— гЏнд…)
        if (hash.substr(0, 4) == "0000") {
            std::cout << " г «бЏЋж— Џбм я б… «б яжнд!" << std::endl;
            std::cout << "«бе«‘ (Hash): " << hash << std::endl;
            std::cout << "«бджд’ (Nonce): " << nNonce << std::endl;
            break;
        }
        nNonce++;
    }
}