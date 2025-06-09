/**
    Lab #2
    Group CPP2
    Team Memebers: Jesus Urias, Nhung Vo
    Purpose: The purpose of this lab is to properly impolement inheritance and polymorphism as needed.
**/

#pragma once

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <cmath>

class Currency {
public:
    //Constructors
    Currency() : wholeValue(0), fractionalValue(0) {};

    Currency(const double value) {
        if (value < 0) {
            throw std::string("Invalid Currency value");
        }
        wholeValue = static_cast<unsigned int>(value);
        fractionalValue = static_cast<unsigned int>(round((value - wholeValue) * 100));
    };

    Currency(const Currency& other) : wholeValue(other.wholeValue), fractionalValue(other.fractionalValue) {};
    //Virtual Deconstructor
    virtual ~Currency() {};

    /**
    Method getValue()
        -The point of this method is to safely retrieve the private of the class
        Pre:
        Post:
        Return: unsigned int value
    **/
    unsigned int getWholeValue() const { return wholeValue; };
    unsigned int getFractionalValue() const { return fractionalValue; };

    /**
    Method setValue(newValue)
        -The point of this method is to safely save into the private of the class
        Pre: newValue - the value
        Post: value - newValue is saved into value
        Return:
    **/
    void setWholeValue(unsigned int newDollarValue) {
        wholeValue = newDollarValue;
    };
    void setFractionalValue(unsigned int newCentValue) {
        fractionalValue = newCentValue;
    };


    //Virtual Methods
    virtual void addCurrency(Currency* currency);
    virtual void subtractCurrency(Currency* currency);
    /**
    method isEqual(otherCurrency)
        -This Method is designed to check other currencies values and check if they equal to values of the
         currency that invoked this method.
        Pre:otherCurrency - a currency object for comparison
        Post:
        Return: true or false
    **/
    virtual bool isEqual(const Currency& other) const {
        return wholeValue == other.wholeValue && fractionalValue == other.fractionalValue;
    }
    /**
    Method isEqual(otherCurrency)
        -This method is designed to check other currencies values and check if they greater than  values of the
        currency that invoked this method.
        Pre:otherCurrency - a currency object for comparison
        Post:
        Return: true or false
    **/
    virtual bool isGreater(const Currency& other) const {
        if (wholeValue == other.wholeValue) { return fractionalValue > other.fractionalValue; }
        return wholeValue > other.wholeValue;
    }
    /**
    Method isEqual(otherCurrency)
        -This method is designed to check other currencies values and check if they greater than  values of the
        currency that invoked this method.
        Pre:otherCurrency - a currency object for comparison
        Post:
        Return: true or false
    **/
    virtual std::string toString() const {
        std::stringstream ss;
        ss << wholeValue << "." << std::setw(2) << std::setfill('0') << fractionalValue;
        return ss.str();
    };
    //Pure Virtual Method
    virtual void print() const = 0;

private:
    //I made these unsigned since these variables will never be negative anyway, 
    // extending the amount of values it can hold.
    unsigned int wholeValue;
    unsigned int fractionalValue;
};
/**
Method addCurrency(otherCurrency)
    -This method is adds the otherCurrency values to the invoked
    Pre:otherCurrency - a currency object for comparison
    Post: currencyWholeValue - Will be added by the otherCurrencyWholeValue. It will add 1 to this value if fractionValue goes above or equals 100
          currencyFractionalValue - Will be added by the otherCurrencyFractionalValue. It will subtract 100 from it if it goes above or equals 100
    Return:
**/
inline void Currency::addCurrency(Currency* other) {
    fractionalValue += other->fractionalValue;
    if (fractionalValue >= 100) {
        fractionalValue -= 100;
        ++wholeValue;
    }
    wholeValue += other->wholeValue;
};
/**
Method subtractCurrency(otherCurrency)
    -This method is adds the otherCurrency values to the invoked and makes sure currency does not go negative
    Pre:otherCurrency - a currency object for comparison
    Post: currencyWholeValue - Will be added by the otherCurrencyWholeValue. It will add 1 to this value if fractionValue goes above or equals 100
          currencyFractionalValue - Will be added by the otherCurrencyFractionalValue. It will subtract 100 from it if it goes above or equals 100
    Return:
    Throws: std::string if otherCurrency is greater than the invoked currency
**/
inline void Currency::subtractCurrency(Currency* other) {

    if (!isGreater(*other)) {
        throw std::string("Invalid Subtractions: Cannot be Negative Currency");
    }
    //Since we are using Unsinged int,  we had to make sure the subtraction doesnt go below zero
    //since that operation the unsigned int will underflow.
    if (fractionalValue < other->fractionalValue) {
        fractionalValue += 100;
        --wholeValue;
    }
    wholeValue -= other->wholeValue;
    fractionalValue -= other->fractionalValue;
};

