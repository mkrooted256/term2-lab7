#include "Lab7.cpp"

int main() {
    CandyMachine CM = CandyMachine();
    UI ui(&CM);

    ui.startup();
    ui.update();

    while (not ui.exit_flag()) {
        system("cls");
        ui.update();
    }

    return 0;
}