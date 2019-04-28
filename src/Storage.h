#ifndef LAB7_STORAGE_H
#define LAB7_STORAGE_H


#include <vector>
#include <map>
#include "ObservableBuffer.h"


struct StorageCell {
    unsigned int cost;
    unsigned int capacity;
    std::string content;
};

class Storage : public ObservableBuffer<
        std::pair<std::string,StorageCell>,
        std::map<std::string, StorageCell>>
{
    static const unsigned int CANDY_TYPES_NUM = 8;
    const std::string CANDIES[CANDY_TYPES_NUM] {
        "Chervony Mak",
        "Zeleny Hai",
        "Smachny Zefir",
        "Zvychayny Zefir",
        "Zhovty Liodianyk",
        "Zoriane Siaivo",
        "Iryska",
        "Ptashyne Moloko",
    };

    void populate_storage();
public:
    static const unsigned int CELL_NUM = 4;
    static const unsigned int CODE_LEN = 4;
    static const unsigned int MAX_CAPACITY = 5;

    Storage() {
        populate_storage();
    }

    const StorageCell * get_cell(const std::string &c) const {
        auto cell = buffer.find(c);
        if (cell != buffer.end()) {
            return &cell->second;
        }
        return nullptr;
    }

    const StorageCell * giveout(const std::string& c) {
        auto cell = buffer.find(c);
        if (cell != buffer.end()) {
            cell->second.capacity--;
            notify_listeners(*cell);
            return & cell->second;
        }
        return nullptr;
    }

    const std::map<std::string, StorageCell> get_storage() {
        return buffer;
    }
};

void Storage::populate_storage() {
    for(unsigned int i=0; i<CELL_NUM; i++) {
        std::string code;
        for (int j=0; j<CODE_LEN; j++) {
            code += '0' + rand()%10;
        }
        buffer[code] = StorageCell{
                (unsigned int) (rand() % 250),
                (unsigned int) rand()%MAX_CAPACITY + 1,
                CANDIES[rand()%CANDY_TYPES_NUM]
        };
    }
}

#endif //LAB7_STORAGE_H
