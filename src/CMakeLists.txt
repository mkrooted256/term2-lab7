set(LAB7LIB
        ObservableBuffer.h
        BanknoteReader.h
        LCD.h
        Keypad.h
        Storage.h
        CandyMachine.h
        DebugUI.h
        Lab7.cpp)

add_library(lab7lib ${LAB7LIB})

add_executable(lab7 main.cpp)
target_link_libraries(lab7 lab7lib)