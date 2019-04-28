#ifndef LAB7_LAB7_H
#define LAB7_LAB7_H

#include "CandyMachine.h"
#include "DebugUI.h"
#include <iostream>
#include <iomanip>
using namespace std;

class UI :
        public DebugUI,
        public LCD::Listener,
        public Storage::Listener
{
    string message;
    string lcd;
    bool exit;

    void show_storage();
    void show_msgs();
    void show_lcd();
public:
    explicit UI(CandyMachine *candyMachine);

    void handle(const string &last_input, const string &buffer) override;
    void handle(const pair<string, StorageCell> &output, const map<string, StorageCell> &storage) override;

    void startup() override;

    void update() override;

    bool exit_flag() { return exit; }
};

UI::UI(CandyMachine * candyMachine) : DebugUI(candyMachine) {
    candyMachine->get_lcd().attach_listener(this);
    candyMachine->get_storage().attach_listener(this);
    exit = false;
}

void UI::show_storage() {
    for (const auto &cell_pair : candyMachine->get_storage().get_storage()) {
        StorageCell cell = cell_pair.second;
        cout << "#" << cell_pair.first << " \"" << setw(16) << left << cell.content << "\" [" << setw(3) << cell.cost << "c] (" << cell.capacity << " left)" << endl;
    }
}

void UI::show_msgs() {
    if (!message.empty()) {
        cout << "[[ " << message << " ]]";
        message.clear();
    }
    cout << endl;
}

void UI::show_lcd() {
    cout << "LCD: [" << lcd << "]" << endl;
}

void UI::startup() {
    cout << "Starting up." << endl;
}

void UI::update() {
    string delim = string(36, '=');
    cout << string(delim).replace(13, 9, " Storage ") << endl;
    show_storage();
    cout << delim << endl;
    show_lcd();
    cout << delim << endl;
    show_msgs();
    cout << delim << endl;
    cout << "Enter key ([0-9], R or K) or 'B_#' (banknote input) or X (exit): ";
    string input;
    cin >> input;
    char key = input[0];
    if (tolower(key) == 'x') {
        exit = true;
    } if (tolower(key) == 'b' and input[1] == '_') {
        unsigned int banknote = 0;
        for (char &d : input.substr(2)) {
            if (isdigit(d)) {
                banknote = banknote*10 + d - '0';
            } else {
                message += "Invalid input; ";
                return;
            }
        }
        candyMachine->get_banknote_reader().emulate_input((Banknote) (banknote));
    } else if (key >= '0' and key <= '9') {
        candyMachine->get_keypad().emulate_keypress((Key) (key) );
    } else if (tolower(key) == 'r') {
        candyMachine->get_keypad().emulate_keypress(Key::KEY_RESET);
    } else if (tolower(key) == 'k') {
        candyMachine->get_keypad().emulate_keypress(Key::KEY_OK);
    } else {
        message += "Invalid key; ";
    }
}

// LCD Listener
void UI::handle(const string &last_input, const string &buffer) {
    lcd = buffer;
}

// Storage Listener
void UI::handle(const pair<string, StorageCell> &output, const map<string, StorageCell> &storage) {
    message += string("Candy! (") + output.second.content + "); It cost " + to_string(output.second.cost) + "; ";
}

#endif //LAB7_LAB7_H
