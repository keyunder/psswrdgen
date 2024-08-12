#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
#include <wincrypt.h>

//region Prototypes
char* pwgen(int length);
int ask_read_length(int argc, char* argv[]);
int ask_actually(void);
char randomChar(const char* chars);
int randomInt(int max);
//endregion

//region Constants
const int MIN_PASSWORD_LENGTH = 4;
const int MAX_PASSWORD_LENGTH = 64;

const char LOWER_CASE[] = "abcdefghijklmnopqrstuvwxyz";
const char UPPER_CASE[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char NUMBERS[] = "0123456789";
const char SPECIAL_CHARS[] = "!@#$%^&*()_+?[].";
const char ALL_CHARS[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_+?[].";
//endregion

int main(int argc, char* argv[]) {
    int length = ask_read_length(argc, argv);
    char* psswrd = pwgen(length);
    printf("Generated password: %s\n", psswrd);
    printf("Password length: %d\n", length);
    free(psswrd);
    return 0;
}

char* pwgen(int length) {
    if(length > MAX_PASSWORD_LENGTH) {
        printf("Number too high. Defaulting to %d\n", MAX_PASSWORD_LENGTH);
        length = MAX_PASSWORD_LENGTH;
    }
    char* response;
    response = malloc(sizeof(char) * (length + 1));
    if (response == NULL) {
        fprintf(stderr, "Error mallocating memory\n");
        exit(1);
    }
    response[0] = randomChar(LOWER_CASE);
    response[1] = randomChar(UPPER_CASE);
    response[2] = randomChar(NUMBERS);
    response[3] = randomChar(SPECIAL_CHARS);

    for(int i = 4; i < length; i++) {
        response[i] = randomChar(ALL_CHARS);
    }
    for(int i = 0; i < length; i++) {
        int j = randomInt(length);
        char temp = response[i];
        response[i] = response[j];
        response[j] = temp;
    }
    response[length] = '\0';

    return response;
}

int ask_read_length(int argc, char* argv[]) {
    if (argc > 1) {
        int length = atoi(argv[1]);
        if (length >= MIN_PASSWORD_LENGTH) {
            return length;
        }
        printf("Invalid input. Defaulting to interactive mode.\n");
    }
    return ask_actually();
}

int ask_actually(void) {
    int response;
    while (true) {
        printf("Input length:\n");
        if( scanf("%d", &response) != 1 ) {
            printf("Invalid input. Please enter an integer.\n");
            while(getchar() != '\n');
        } else if ( response >= MIN_PASSWORD_LENGTH) {
            break;
        } else {
            printf("Invalid number. Enter %d or greater.\n", MIN_PASSWORD_LENGTH);
        }
    }
    return response;
}

int randomInt(int max) {
    HCRYPTPROV hCryptProv;
    BYTE random[4];
    if (!CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL, 0)) {
        fprintf(stderr, "Error acquiring context\n");
        exit(1);
    }
    if (!CryptGenRandom(hCryptProv, 4, random)) {
        fprintf(stderr, "Error generating random\n");
        exit(1);
    }
    CryptReleaseContext(hCryptProv, 0);
    int random_int = (random[0] << 24)
                    | (random[1] << 16)
                    | (random[2] << 8)
                    | random[3];

    return abs(random_int % max);
}

char randomChar(const char* chars) {
    if(chars == NULL) {
        fprintf(stderr, "Null pointer passed to randomChar\n");
        exit(1);
    }
    int len = strlen(chars);
    if(len == 0) {
        fprintf(stderr, "Empty string passed to randomChar\n");
        exit(1);
    }
    int index = randomInt(len);
    return chars[index];
}
