//
// bignum.hpp
// Basic Bignum
//
// This class represents the Bignum class that supports RSA, AES encryption and
// decrypytion. The file contains only the basic interface without any
// performance optimizations.
//

#ifndef _BIGNUM_H
#define _BIGNUM_H
#include <algorithm>
#include <iostream>
#include <vector>

/**
 * Bignum class representing a large integer number with support for 
 * RSA and AES encryption and decryption.
 * 
 * Capable of generating public and private keys for RSA (2048 bits) and 
 * AES (256 bits). 
 */
class Bignum {
private:
    /** The vector of numerical digits making up a Bignum. */
    std::vector<int> _digits;

    // operators
    // +, -, *, /, %, <, ==, >, !=, <=, >=, []
    // expmod
    // gcd
    // >>, <<

    bool operator<(Bignum);
    bool operator>(Bignum);
    bool operator==(Bignum);
    bool operator<=(Bignum);
    bool operator>=(Bignum);
    bool operator!=(Bignum);
    Bignum operator+(Bignum);
    Bignum operator-(Bignum);
    Bignum operator*(int);
    Bignum operator*(Bignum);
    Bignum operator/(Bignum);
    Bignum operator%(Bignum);

    Bignum expmod(Bignum, Bignum);
    Bignum gcd(Bignum);

public:
    /**
     * Creates a Bignum number with the default values.
     */
    Bignum() {}

    /** 
     * Creates a Bignum number with a reference to existing Bignum.
     * 
     * @param bnum   The ref to existing Bignum
     */
    Bignum(const Bignum& bnum) {
        _digits = bnum._digits;
    }

    /**
     * Creates a Bignum number with the provided integer value.
     * 
     * @param num   The integer value for Bignum
     */
    Bignum(int num) {
        _digits.push_back(num);
    }

    /**
     * Creates a Bignum number with the provided string of integer number.
     * 
     * @param num   The string of integer number for Bignum
     */
    Bignum(std::string num) {
        for (auto c : num) {
            _digits.push_back(c - '0');
        }
    }

    /**
     * Returns the digits vector of the Bignum number.
     * 
     * @return vector<int>  digits vector of Bignum number
     */
    std::vector<int> as_vec() {
        return _digits;
    }

    /**
     * Returns the string representation of the Bignum number.
     * 
     * @return string   String representation of Bignum number
     */
    std::string to_string() {
        std::string s;
        for (auto d : digits) {
            s += std::to_string(d);
        }
        return s;
    }

    /**
     * Generates a Bignum number from handling RSA encryption 
     * using the specified key values.
     * 
     * @param rsa_n RSA N key value
     * @param rsa_e RSA E key value
     */
    Bignum rsa_encrypt(std::string rsa_n, std::string rsa_e) {
        return expmod(Bignum(rsa_e), Bignum(rsa_n)).to_string();
    }

    /**
     * Generates an Bignum number from handling RSA decryption
     * using the specified key values.
     * 
     * @param rsa_n RSA N key value 
     * @param rsa_d RSA D key value
     */
    Bignum rsa_decrypt(std::string rsa_n, std::string rsa_d) {
        return expmod(Bignum(rsa_d), Bignum(rsa_n));
    }
};

#endif /* _BIGNUM_H */
