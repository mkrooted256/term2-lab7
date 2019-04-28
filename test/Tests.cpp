#include "gtest/gtest.h"
#include "../src/Lab7.cpp"


TEST(Listeners_BR, input) {
    #define init 42
    #define add 73

    BanknoteReader br;
    br.emulate_input(static_cast<Banknote>(init));

    class BRL : public BanknoteReader::Listener {
    public:
        void handle(const int &last_input, const unsigned int &buffer) override {
            ASSERT_EQ(buffer, init + add);
            ASSERT_EQ(last_input, add);
        }
    } brl;

    br.attach_listener(&brl);
    br.emulate_input(static_cast<Banknote>(add));
}

TEST(Listeners_BR, withdraw) {
    #define sub 37

    BanknoteReader br;
    br.emulate_input(static_cast<Banknote>(init));

    class BRL : public BanknoteReader::Listener {
    public:
        void handle(const int &last_input, const unsigned int &buffer) override {
            ASSERT_EQ(buffer, init - sub);
            ASSERT_EQ(last_input, -sub);
        }
    } brl;

    br.attach_listener(&brl);
    br.withdraw(sub);
}


TEST(Keypad, EmulateKeypress) {
    Keypad kp;
    class KPL1 : public Keypad::Listener {
        bool fired = false;
    public:
        void handle(const Key &last_input, const vector<Key> &buffer) override {
            if (!fired) {
                ASSERT_EQ(buffer.size(), 1);
                ASSERT_EQ(buffer[0], '1');
                fired = true;
            }
        };
    } kpl1;
    class KPL2 : public Keypad::Listener {
        bool fired = false;
    public:
        void handle(const Key &last_input, const vector<Key> &buffer) override {
            if (!fired) {
                ASSERT_EQ(buffer.size(), 2);
                ASSERT_EQ(buffer[0], '1');
                ASSERT_EQ(buffer[1], '2');
                fired = true;
            }
        };
    } kpl2;
    
    auto buf = kp.get_buffer();
    ASSERT_EQ(buf.size(), 0);
    
    kp.attach_listener(&kpl1);
    kp.emulate_keypress(Key::KEY_1);
    kp.attach_listener(&kpl2);
    kp.emulate_keypress(Key::KEY_2);
}