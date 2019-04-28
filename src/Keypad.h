#ifndef LAB7_KEYPAD_H
#define LAB7_KEYPAD_H

#include <vector>
#include "ObservableBuffer.h"

enum Key {
    KEY_0 = '0', KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_OK, KEY_RESET
};

class Keypad : public ObservableBuffer<Key, std::vector<Key>> {
public:
    static bool isnum(Key k) {
        return (k >= KEY_0) and (k <= KEY_9);
    }

    void emulate_keypress(Key key) {
        buffer.push_back(key);
        notify_listeners(key);
    }

    std::vector<Key> &get_buffer() {
        return buffer;
    }
};

#endif //LAB7_KEYPAD_H
