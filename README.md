# AES Bench Generator
A simple program to create test vectors for the Digital Design (BIL264) AES project.
Utilizes both OpenSSL and a homebrew AES adaptation of tiny-aes-c for failure-control. It is recommended that you
run the internal test at all times.

## Usage
```
aes_benchgen - generate test vectors
Usage: aes_benchgen [OPTION] ...
Options:
  -[-i]nternal: check openssl and self aes consistency
  -[-k]eyexpand: generate key expansion vectors
  -[-a]ddroundkey: generate AddRoundKey vectors
  -[-s]ubbytes: generate SubBytes vectors
  -[-S]hiftrows: generate ShiftColumns vectors
  -[-m]ixcolumns: generate MixColumns vectors
  -[-c]ipher: generate high-level test vector
  -[-h]elp: display this message and exit
No arguments run all tests
```

## License
This repository is licenced under BSD-3-Clause. Refer to
LICENSE.md for more details.

## Credits
* OpenSSL project team for the [OpenSSL](https://github.com/openssl/openssl) library.
* kokko for the [tiny-AES-c](https://github.com/kokke/tiny-AES-c) file.
* Chris Wellons for the [optparse](https://github.com/skeeto/optparse) header.
