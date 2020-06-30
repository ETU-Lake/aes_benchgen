#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <openssl/crypto.h>

#include "optparse.h"
#include "constants.h"
#include "test.h"

static void help(void) {
    puts("aes_benchgen - generate test vectors\n"
         "Usage: aes_benchgen [OPTION] ...\n"
         "Options:\n"
         "  -[-i]nternal: check openssl and self aes consistency\n"
         "  -[-k]eyexpand: generate key expansion vectors\n"
         "  -[-a]ddroundkey: generate AddRoundKey vectors\n"
         "  -[-s]ubbytes: generate SubBytes vectors\n"
         "  -[-S]hiftrows: generate ShiftColumns vectors\n"
         "  -[-m]ixcolumns: generate MixColumns vectors\n"
         "  -[-c]ipher: generate high-level test vector\n"
         "  -[-h]elp: display this message and exit\n"
         "No arguments run all tests"
        );
}


int main(int argc, char **argv) {
    uint8_t mode = 0;
    int option;
    struct optparse opts;
    struct optparse_long longopts[] = {
        { "internal",    'i', OPTPARSE_NONE },
        { "keyexpand",   'k', OPTPARSE_NONE },
        { "addroundkey", 'a', OPTPARSE_NONE },
        { "subbytes",    's', OPTPARSE_NONE },
        { "Shiftrows",   'S', OPTPARSE_NONE },
        { "mixcolumns",  'm', OPTPARSE_NONE },
        { "cipher",      'c', OPTPARSE_NONE },
        { "help",        'h', OPTPARSE_NONE },
        {0}
    };

    optparse_init(&opts, argv);

    while ((option = optparse_long(&opts, longopts, NULL)) != -1) {
        switch (option) {
        case 'i':
            mode |= INTERNAL;
            break;
        case 'k':
            mode |= KEYEXPAND;
            break;
        case 'a':
            mode |= ADDROUNDKEY;
            break;
        case 's':
            mode |= SUBBYTES;
            break;
        case 'S':
            mode |= SHIFTROWS;
            break;
        case 'm':
            mode |= MIXCOLUMNS;
            break;
        case 'c':
            mode |= CIPHER;
            break;
        case '?':
            fprintf(stderr, "%s: %s\n", *argv, opts.errmsg);
        case 'h':
            help();
            exit(EXIT_SUCCESS);
        }
    }

    if (!mode || argc == 1) {
        mode = 0xFF;
    }

    test_eval(mode);
}
