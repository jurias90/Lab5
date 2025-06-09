//There was an additional constructor that was added to the header file that is a copy constructor.
//This was added to create a copy currency of the correct type from the SinglyLinkedList.

/**
    Lab #2
    Group CPP2
    Team Memebers: Jesus Urias, Nhung Vo
    Purpose: The purpose of this lab is to properly impolement inheritance and polymorphism as needed.
**/
#pragma once

#include "Currency.h"

class DrachmaCurrency : public Currency {
public:
    //Constructors
    DrachmaCurrency() {};
    DrachmaCurrency(double value) :Currency(value) {};

    DrachmaCurrency(Currency* newCurrency) :Currency(*newCurrency) {};
    /**
    Method getValue()
        -The point of this method is to safely retrieve the private of the class
        Pre:
        Post:
        Return: string coinName
    **/
    std::string getCoinName() { return coinName; }
    /**
    Method setValue(newValue)
        -The point of this method is to safely save into the private of the class
        Pre: newValue - the value
        Post: value - newValue is saved into value
        Return:
    **/
    void setCoinName(std::string newCoinName) { coinName = newCoinName; };
    //Ovverridden Methods
    /**
    Method toString()
        -THis method will stringify the currency by formatting it into 'xx.yy' format and adding the currency name after
        Pre:
        Post:
        Return: string value- with the formated value and the name of currency
    **/
    std::string toString() const override {
        return Currency::toString() + " " + coinName;
    };

    void addCurrency(Currency* currency) override;

    void subtractCurrency(Currency* currency) override;
    /**
    Method print()
        -THis method will call toString to get the formated information and print it out to the console.
        Pre:
        Post: string value - currencies values and name will be formated and printed to the console
        Return:
    **/
    void print() const override {
        std::cout << toString();
    };


private:
    std::string coinName = "Drachma";
};
/**
Method addCurrency(otherCurrency) overriden
    -This method is adds the otherCurrency values to the invoked
     but checks to make sure the otherCrrency is of the same type as Drachma
    Pre:otherCurrency - a currency object for comparison
    Post: currencyWholeValue - Will be added by the otherCurrencyWholeValue. It will add 1 to this value if fractionValue goes above or equals 100
          currencyFractionalValue - Will be added by the otherCurrencyFractionalValue. It will subtract 100 from it if it goes above or equals 100
    Return:
    Throws: std::string if the otherCurrency type does not match the Drachma currency type
**/
inline void DrachmaCurrency::addCurrency(Currency* other) {
    //The purpose of dynamic casting here is to check and see if this currency belongs to Peso Currency. If not
    //it will return undefined which is false to the if statement.
    if (DrachmaCurrency* otherDrachmaCurrency = dynamic_cast<DrachmaCurrency*>(other)) {
        Currency::addCurrency(otherDrachmaCurrency);
    }
    else {
        throw std::string("Invalid Addition of Currency Type");
    }
}
/**
Method subtractCurrency(otherCurrency) overriden
    -This method  adds the otherCurrency values to the invoked and makes sure currency does not go negative
    but checks to make sure the otherCurrency is of the same type as Drachma
    Pre:otherCurrency - a currency object for comparison
    Post: currencyWholeValue - Will be added by the otherCurrencyWholeValue. It will add 1 to this value if fractionValue goes above or equals 100
          currencyFractionalValue - Will be added by the otherCurrencyFractionalValue. It will subtract 100 from it if it goes above or equals 100
    Return:
    Throws: std::string if otherCurrency is greater than the invoked currency
            std::string if the otherCurrency type does not match the Drachma currency type
**/
inline void DrachmaCurrency::subtractCurrency(Currency* other) {
    //The purpose of dynamic casting here is to check and see if this currency belongs to Peso Currency. If not
    //it will return undefined which is false to the if statement.
    if (DrachmaCurrency* otherDrachmaCurrency = dynamic_cast<DrachmaCurrency*>(other)) {
        Currency::subtractCurrency(otherDrachmaCurrency);
    }
    else {
        throw std::string("Invalid Subtraction of Currency Type");
    }
}

