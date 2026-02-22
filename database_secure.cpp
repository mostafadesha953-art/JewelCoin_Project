#include <iostream>
#include <sqlite3.h> // „ﬂ »… ﬁ«⁄œ… «·»Ì«‰« 
#include "crypto/aes_512.h" //  ‘›Ì— „ ﬁœ„ 2026

class SecureDB {
public:
    sqlite3* db;

    // › Õ ﬁ«⁄œ… »Ì«‰«  «·„Õ›Ÿ… »ﬂ·„… „—Ê— „‘›—…
    bool openEncryptedWallet(std::string walletName, std::string password) {
        if (sqlite3_open(walletName.c_str(), &db) == SQLITE_OK) {
            //  ›⁄Ì· «· ‘›Ì— »«” Œœ«„ ﬂ·„… «·„—Ê— (AES-512)
            const char* key = password.c_str();
            sqlite3_key(db, key, strlen(key)); 

            if (sqlite3_exec(db, "SELECT count(*) FROM sqlite_master;", NULL, NULL, NULL) == SQLITE_OK) {
                std::cout << "?  „ ›ﬂ  ‘›Ì— ﬁ«⁄œ… «·»Ì«‰«  »‰Ã«Õ." << std::endl;
                return true;
            }
        }
        std::cout << "? ﬂ·„… „—Ê— «·„Õ›Ÿ… Œ«ÿ∆…!" << std::endl;
        return false;
    }

    // Õ›Ÿ „› «Õ ”Ì«œÌ „‘›— œ«Œ· «·ﬁ«⁄œ…
    void savePrivateData(std::string keyName, std::string encryptedData) {
        std::string query = "INSERT INTO secure_storage (key, value) VALUES ('" + keyName + "', '" + encryptedData + "');";
        sqlite3_exec(db, query.c_str(), NULL, NULL, NULL);
    }
};