//
// bignum.hpp
//
// This class represents the Bignum class that supports RSA, AES encryption and 
// decrypytion. The file contains only the basic interface without any 
// performance optimizations.
//

#ifndef __BIGNUM_H__
#define __BIGNUM_H__
#include <iostream> 
#include <algorithm> 
#include <vector> 


class Bignum 
{

	public:
		Bignum();
		Bignum(const Bignum&);
		Bignum(int);
		Bignum(std::string);
		std::string to_string();
		void check(std::string);
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
		Bignum encrypt(std::string, std::string);
		Bignum decrypt(std::string, std::string);
		std::vector<int> as_vec();
	private:
		std::vector<int> digits;
		void append_digit(int);
};

#endif /* __BIGNUM_H__ */
