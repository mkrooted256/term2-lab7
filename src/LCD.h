#ifndef LAB7_LCD_H
#define LAB7_LCD_H

#include <string>
#include <ostream>
#include "ObservableBuffer.h"

class LCD : public ObservableBuffer<std::string, std::string>{
    size_t pos;
public:
    static const size_t LINE_LEN = 32;

    LCD();

    LCD& put(const std::string &str);
    friend LCD& operator<<(LCD& lcd, const std::string &str);

    const std::string get_buffer() {
        return buffer;
    }

    friend std::ostream &operator<<(std::ostream &os, const LCD &lcd);

    LCD& setpos(size_t pos) {
        pos = pos;
        return *this;
    }
    LCD& clear();
};

LCD& operator<<(LCD& lcd, const std::string &str) {
    lcd.put(str);
    return lcd;
}

LCD& LCD::put(const std::string &str) {
    buffer = buffer.substr(0,pos) + str;
    pos += str.length();
    notify_listeners(str);
    return *this;
}

LCD::LCD() {
    pos = 0;
    for (int i=0; i<LINE_LEN; i++)
        buffer += ' ';
}

std::ostream &operator<<(std::ostream &os, const LCD &lcd) {
    os << "buffer: " << lcd.buffer;
    return os;
}

LCD &LCD::clear() {
    buffer.clear();
    notify_listeners("");
    pos = 0;
    return *this;
}


#endif //LAB7_LCD_H
