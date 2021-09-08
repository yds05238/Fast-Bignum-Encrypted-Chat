# Basic Bignum

Basic Bignum package with slow performance and limited performance optimization. The library only uses C++17 STL with little to no focus on performance.

## Pre-requisites

- Linux(Ubuntu 18.04/20.04/Debian)
- g++
- C++ 17
- gprof

## Usage

- Compile using provided shell script
    - compile.sh

- Generate performance profiles
    - bigint e < one-liners > encoded
    - gprof bigint > analysis_encrypt.txt

    - bigint d < encoded
    - gprof bigint > analysis_decrypt.txt

- Basic timed Encrypt/Decrypt
    - time echo "The quick brown fox jumps over the lazy dog" | bigint e | bigint d

- Separate timed Encrypt + Decrypt
    - time bigint e < one-liners > encoded
    - time bigint d < encoded

- Total timed Encrypt + Decrypt
    - time bigint e < one-liners | bigint d

## TODO

- Add AES Encryption/Decryption
- Add Unit Testing
