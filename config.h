// «”„ «·„·›: config.h
#ifndef XHYBRID_CONFIG_H
#define XHYBRID_CONFIG_H

#include <string>

namespace XHybrid {
    // «·ÂÊÌ… Ê«·√„«‰
    const char* const NAME = "JewelCoin";
    const char* const SYMBOL = "XHB";

    // «·«ﬁ ’«œ «·—ﬁ„Ì (Tokenomics 2026)
    const uint64_t MAX_SUPPLY = 21000000;    // «·„Ã„Ê⁄ «·ﬂ·Ì
    const uint64_t RESERVE_FUND = 7000000;   // «Õ Ì«ÿÌ ( Õﬂ„ ﬂ«„· ··„œÌ—)
    const uint64_t MINING_SUPPLY = 8400000;  // 60% „‰ «·‹ 14 „·ÌÊ‰ «·„ »ﬁÌ…
    const uint64_t AIRDROP_SUPPLY = 2800000; // 20% „‰ «·‹ 14 „·ÌÊ‰
    const uint64_t DEV_LIQUIDITY = 2800000;  // 20%  ÿÊÌ— Ê”ÌÊ·…

    // «·ŒÊ«—“„Ì… («·”—⁄… Ê«·Œ’Ê’Ì…)
    const int BLOCK_TIME = 60;               // ﬂ ·… ﬂ· œﬁÌﬁ… (”—⁄… ·«Ì ﬂÊÌ‰)
    const int DIFFICULTY = 4;                // ’⁄Ê»…  ⁄œÌ‰ „‰«”»… ··‹ CPU
    const char* const MASTER_KEY = "SECRET_ADMIN_2026"; // „› «Õ «· Õﬂ„ »«·«Õ Ì«ÿÌ
}

#endif