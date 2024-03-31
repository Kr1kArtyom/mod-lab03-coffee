// Copyright 2024 Kr1kArtyom

#include <../include/Automata.h>

Automata::Automata() {
        cash = 0;
        state = States::OFF;
        menu = {
            { 0, { "Espresso", 100 } },
            { 1, { "Americano", 120 } },
            { 2, { "Doppio", 150 } },
            { 3, { "Cappuccino", 200 } },
            { 4, { "Flat-white", 170 } },
            { 5, { "Latte", 200 } },
            { 6, { "Raf", 190 } }
        };
}

void Automata::on() {
    if (state == States::OFF) {
        state = States::WAIT;
        std::cout << "Automata is on" << std::endl;
    } else {
        throw std::logic_error("Automata is already on");
    }
}

void Automata::off() {
    if (state == States::WAIT) {
        state = States::OFF;
        std::cout << "Automata is off" << std::endl;
    } else {
        throw std::logic_error("Wait for automata to complete");
    }
}

void Automata::coin(int value) {
    if (state == States::WAIT || state == States::ACCEPT) {
        if (value <= 0) {
            throw std::invalid_argument("Incorrect deposit value");
        }
        cash += value;
        state = States::ACCEPT;
        std::cout << "The balance has been successfully replenished"
        << std::endl
        << "The current balance is " << cash << " rubles"
        << std::endl;
    } else {
        throw std::logic_error("Wait for automata to complete");
    }
}

void Automata::choice(int coffee) {
    if (state == States::ACCEPT) {
        if (menu.find(coffee) == menu.end()) {
            throw std::out_of_range("Incorrect menu item");
        }
        curItem = menu[coffee];
        state = States::CHECK;
        std::cout << "You have chosen " << curItem.coffee << std::endl
        << "Price: " << curItem.price << std::endl;
        check();
    } else {
        throw std::logic_error("Wait for automata to complete");
    }
}

void Automata::check() {
    if (state == States::CHECK) {
        if (cash < curItem.price) {
            std::cout << "Insufficient funds" << std::endl;
            cancel();
        } else {
            std::cout << "Ready to cook" << std::endl;
        }
    } else {
        throw std::logic_error("Wait for automata to complete");
    }
}

void Automata::cook() {
    if (state == States::CHECK) {
        cash -= curItem.price;
        state = States::COOK;
        std::cout << "Start cooking" << std::endl;
    } else {
        throw std::logic_error("Wait for automata to complete");
    }
}

void Automata::finish() {
    if (state == States::COOK) {
        std::cout << "Your " << curItem.coffee << " is ready" << std::endl
        << "Your change is " << cash << " rubles";
        cash = 0;
        state = States::WAIT;
    } else {
        throw std::logic_error("Wait for automata to complete");
    }
}

void Automata::cancel() {
    if (state == States::ACCEPT || state == States::CHECK) {
        std::cout << "The current session has been cancelled" << std::endl
        << "Your change is " << cash << " rubles";
        cash = 0;
        state = States::WAIT;
    } else {
        throw std::logic_error("It can't cancel the service session");
    }
}

void Automata::getMenu() {
    for (const auto& item : menu) {
        std::cout << "ID: " << item.first
        << " Name: " << item.second.coffee
        << " Price: " << item.second.price
        << std::endl;
    }
}

int Automata::getState() {
    return state;
}
