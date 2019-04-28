#ifndef LAB7_BANKNOTEREADER_H
#define LAB7_BANKNOTEREADER_H

#include "ObservableBuffer.h"

enum Banknote {
    BN_1 = 1,
    BN_2 = 2,
    BN_5 = 5,
    BN_10 = 10,
    BN_20 = 20,
    BN_50 = 50,
    BN_100 = 100,
    BN_200 = 200,
    BN_500 = 500,
};

class BanknoteReader : public ObservableBuffer<int, unsigned int> {
public:
    BanknoteReader() {
        buffer = 0;
    }

    unsigned int get_credit() {
        return buffer;
    }
    void withdraw(unsigned int amount) {
        if (amount <= buffer)
            buffer -= amount;
        notify_listeners(-amount);
    }
    void emulate_input(Banknote banknote) {
        buffer += (unsigned int) banknote;
        notify_listeners(banknote);
    }
};


#endif //LAB7_BANKNOTEREADER_H
