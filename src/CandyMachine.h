#ifndef LAB7_CANDYMACHINE_H
#define LAB7_CANDYMACHINE_H

#include "BanknoteReader.h"
#include "Storage.h"
#include "LCD.h"
#include "Keypad.h"

class CandyMachine :
        public BanknoteReader::Listener,
        public Keypad::Listener
{
    BanknoteReader banknoteReader;
    Storage        storage;
    LCD            lcd;
    Keypad         keypad;

    bool money_input = false;
    bool reset_flag = false;
    void reset() {
        keypad.get_buffer().clear();
        lcd.clear() << "Enter code: ";
        reset_flag = false;
    }
public:

    CandyMachine();

    BanknoteReader& get_banknote_reader() {
        return banknoteReader;
    }
    Storage& get_storage() {
        return storage;
    }
    LCD& get_lcd() {
        return lcd;
    }
    Keypad& get_keypad() {
        return keypad;
    }

    // BanknoteReader listener
    void handle(const int &last_input, const unsigned int &buffer) override;
    // Keypad listener
    void handle(const Key &last_input, const std::vector<Key> &buffer) override;

    static std::string keys_to_string(std::vector<Key>);
};

std::string CandyMachine::keys_to_string(std::vector<Key> keys) {
    std::string str;
    for (Key& k : keys) {
        if (Keypad::isnum(k))
            str += (char) k;
        else
            str += ( (k == Key::KEY_OK) ? 'K' : 'R' );
    }
    return str;
}

CandyMachine::CandyMachine()
{
    banknoteReader.attach_listener(this);
    keypad.attach_listener(this);
    lcd << "Enter code: ";
}

//BanknoteReader
void CandyMachine::handle(const int &last_input, const unsigned int &buffer) {
    keypad.get_buffer().clear();
    lcd << "Credit: " << std::to_string(buffer);
    money_input = true;
}

// Keypad
void CandyMachine::handle(const Key &last_input, const std::vector<Key> &buffer) {
    if (money_input) {
        lcd.clear();
        money_input = false;
    }
    if (reset_flag and last_input != Key::KEY_RESET)
        return;
    switch (last_input)
    {
        case Key::KEY_RESET:
            reset();
            break;
        case Key::KEY_OK:
        {
            lcd.clear();
            if (!buffer.empty()) {
                std::string code = keys_to_string(buffer).substr(0, 4);
                const StorageCell * cell = storage.get_cell(code);

                if (cell) {
                    if (cell->capacity != 0) {
                        if (cell->cost <= banknoteReader.get_credit()) {
                            banknoteReader.withdraw(cell->cost);
                            storage.giveout(code);
                        } else {
                            lcd << "Insufficient credit. Press RESET";
                            reset_flag = true;
                        }
                    } else {
                        lcd << "Out of stock. Press RESET";
                        reset_flag = true;
                    }
                } else {
                    lcd << "Invalid code. Press RESET";
                    reset_flag = true;
                }
            }
            break;
        }
        default:
            lcd << std::string() + (char)last_input;
    }
}

#endif //LAB7_CANDYMACHINE_H
