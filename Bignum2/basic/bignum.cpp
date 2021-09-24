#include "bignum.hpp"

#include <algorithm>
#include <iostream>
#include <vector>

Bignum::Bignum() {
}

Bignum::Bignum(const Bignum& b) {
    digits = b.digits;
}

Bignum::Bignum(int d) {
    digits.push_back(d);
}

const Bignum BZero(0);
const Bignum BOne(1);

Bignum::Bignum(std::string s) {
    for (auto c : s)
        digits.push_back(c - '0');
}

std::vector<int> Bignum::as_vec() {
    return digits;
}

std::string Bignum::to_string() {
    std::string s;
    for (auto d : digits) {
        s += std::to_string(d);
    }
    return s;
}

bool Bignum::operator<(Bignum b) {
    int alen = digits.size();
    int blen = b.digits.size();
    int aindex = 0, bindex = 0;
    if (alen > blen) {
        return false;
    }
    if (blen > alen) {
        return true;
    }
    while (alen-- > 0) {
        if (digits[aindex] > b.digits[bindex]) {
            return false;
        }
        if (digits[aindex++] < b.digits[bindex++]) {
            return true;
        }
    }
    return false;
}

bool Bignum::operator>(Bignum b) {
    return b < *this;
}

bool Bignum::operator==(Bignum b) {
    return !(*this < b || b < *this);
}

bool Bignum::operator<=(Bignum b) {
    return !(*this > b);
}

bool Bignum::operator>=(Bignum b) {
    return !(*this < b);
}

bool Bignum::operator!=(Bignum b) {
    return !(*this == b);
}

Bignum Bignum::operator+(Bignum b) {
    Bignum res;
    int alen = digits.size();
    int blen = b.digits.size();
    int aindex = 0, bindex = 0;
    while (alen > blen) {
        res.digits.push_back(digits[aindex++]);
        --alen;
    }
    while (blen > alen) {
        res.digits.push_back(b.digits[bindex++]);
        --blen;
    }
    while (alen-- > 0) {
        res.digits.push_back(digits[aindex++] + b.digits[bindex++]);
    }
    int rlen = res.digits.size();
    int carry = 0;
    while (rlen > 0) {
        carry += res.digits[--rlen];
        res.digits[rlen] = carry % 10;
        carry /= 10;
    }
    while (carry > 0) {
        res.digits.emplace(res.digits.begin(), carry % 10);
        carry /= 10;
    }
    return res;
}

Bignum Bignum::operator-(Bignum b) {
    Bignum res;
    int alen = digits.size();
    int blen = b.digits.size();
    if (*this < b) {
        return BZero;
    }
    int borrow = 0;
    int zeros = 0;
    while (alen > 0 && blen > 0) {
        int d = digits[--alen] - b.digits[--blen] - borrow;
        borrow = 0;
        if (d < 0) {
            d += 10;
            borrow = 1;
        }
        if (d == 0) {
            ++zeros;
        } else {
            while (zeros--) {
                res.digits.emplace(res.digits.begin(), 0);
            }
            zeros = 0;
            res.digits.emplace(res.digits.begin(), d);
        }
    }
    while (alen > 0) {
        int d = digits[--alen] - borrow;
        borrow = 0;
        if (d < 0) {
            d += 10;
            borrow = 1;
        }
        if (d == 0) {
            ++zeros;
        } else {
            while (zeros--) {
                res.digits.emplace(res.digits.begin(), 0);
            }
            zeros = 0;
            res.digits.emplace(res.digits.begin(), d);
        }
    }
    if (res.digits.size() == 0) {
        return BZero;
    }
    return res;
}

// Helper procedure to multiple a Bignum by an integer.  This could be just a single
// digit, but in fact it will sometimes be 10 in my code.  We multiple all the digits
// first, then sweep from low to high digit applying the carries.
Bignum Bignum::operator*(int d) {
    if (d == 0) {
        return BZero;
    }
    if (d == 1) {
        return *this;
    }
    Bignum res;
    int alen = digits.size();
    int aindex = 0;
    while (alen--) {
        res.digits.push_back(digits[aindex++] * d);
    }
    int carry = 0;
    while (aindex-- > 0) {
        carry += res.digits[aindex];
        res.digits[aindex] = carry % 10;
        carry /= 10;
    }
    while (carry > 0) {
        res.digits.emplace(res.digits.begin(), carry % 10);
        carry /= 10;
    }
    return res;
}

Bignum Bignum::operator*(Bignum b) {
    int blen = b.digits.size();
    Bignum tmp = *this;
    Bignum res = BZero;
    while (blen > 0) {
        int d = b.digits[--blen];
        if (d == 1) {
            res = res + tmp;
        } else if (d != 0) {
            res = res + tmp * d;
        }
        if (blen > 0) {
            tmp = tmp * 10;
        }
    }
    return res;
}

Bignum Bignum::operator/(Bignum b) {
    if (b > *this) {
        return BZero;
    }
    if (b == *this) {
        return BOne;
    }
    if (b == BZero) {
        std::cout << "Error: Divide by 0" << std::endl;
        exit(1);
    }
    Bignum res;
    Bignum tmp;
    int alen = digits.size();
    int blen = b.digits.size();
    int aindex = 0;
    bool placed_first = false;
    while (aindex < blen) {
        int d = digits[aindex++];
        if (d != 0 || placed_first) {
            tmp.digits.push_back(d);
            placed_first = true;
        }
    }
    if (!placed_first) {
        tmp = BZero;
    }
    bool first = true;
    do {
        int d = 0;
        if (b > tmp && aindex < alen) {
            d = digits[aindex++];
            if (d != 0 || tmp != BZero) {
                if (tmp == BZero) {
                    tmp.digits[0] = d;
                } else {
                    tmp.digits.push_back(d);
                }
            }
        }
        d = 0;
        while (b <= tmp) {
            ++d;
            tmp = tmp - b;
        }
        if (d != 0 || !first) {
            first = false;
            res.digits.push_back(d);
        }
    } while (aindex < alen);
    if (res.digits.size() == 0) {
        return BZero;
    }
    return res;
}

Bignum Bignum::operator%(Bignum b) {
    return *this - (*this / b) * b;
}

Bignum Bignum::expmod(Bignum exp, Bignum mod) {
    if (exp == BZero) {
        return BOne;
    }
    Bignum two = Bignum(2);
    Bignum res = BOne;
    Bignum tmp = *this;
    while (exp > 0) {
        if (exp % two == BOne) {
            res = res * tmp;
            res = res % mod;
        }
        tmp = tmp * tmp % mod;
        exp = exp / two;
    }
    return res;
}

Bignum Bignum::gcd(Bignum b) {
    if (b == BZero)
        return *this;
    return b.gcd(*this % b);
}

Bignum Bignum::encrypt(std::string rsa_n, std::string rsa_e) {
    return expmod(Bignum(rsa_e), Bignum(rsa_n)).to_string();
}

Bignum Bignum::decrypt(std::string rsa_n, std::string rsa_d) {
    return expmod(Bignum(rsa_d), Bignum(rsa_n));
}
