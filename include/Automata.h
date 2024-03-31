// Copyright 2024 Kr1kArtyom

#pragma once
#include <map>
#include <iostream>
#include <string>

struct AutomataItem {
    std::string coffee;
    int price;
};

class Automata {
 private:
    enum States{
        OFF = 0,
        WAIT = 1,
        ACCEPT = 2,
        CHECK = 3,
        COOK = 4,
    };

    int cash;
    States state;
    std::map<int, AutomataItem> menu;
    AutomataItem curItem;

 public:
    Automata();
    void on();
    void off();
    void coin(int value);
    void getMenu();
    int getState();
    void choice(int coffee);
    void check();
    void cancel();
    void cook();
    void finish();
};
