# Basic Bignum

Basic Bignum package with slow performance and limited performance optimization. The library only uses C++17 STL with little to no focus on performance.

## Usage (without profiler)

- Compile using provided shell script
    - compile.sh

- Basic Timed Encrypt/Decrypt 
    - time echo "The quick brown fox jumps over the lazy dog" | bignum e | bignum d

- Separate Timed Encrypt/Decrypt
    - time bignum e < one-liners > encoded
    - time bignum d < encoded

- Total Timed Encrypt/Decrypt
    - time bignum e < one-liners | bignum d

## Usage (with profiler)

- Compile using provided shell script
    - compile-pg.sh

- Generate performance profiles
    - bignum e < one-liners > encoded
    - gprof bignum > analysis_encrypt.txt

    - bignum d < encoded
    - gprof bignum > analysis_decrypt.txt

- Basic timed Encrypt/Decrypt
    - time echo "The quick brown fox jumps over the lazy dog" | bignum e | bignum d

- Separate timed Encrypt + Decrypt
    - time bignum e < one-liners > encoded
    - time bignum d < encoded

- Total timed Encrypt + Decrypt
    - time bignum e < one-liners | bignum d

## TODO

- RSA Key generation (2048 bits)
- RSA InitLoadServer(server_public, server_private, client_public)
- RSA encrypt(public_key, message)
- RSA decrypt(private_key, message)
- AES Key generation (256 bits)
- AES encrypt(key, iv, text)
- AES decrypt(key, text)
- AES createmessage(key, message)
- Add Unit Testing
