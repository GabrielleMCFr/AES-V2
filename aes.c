#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <ctype.h>

typedef uint8_t BYTE;

// SBOX look up table.
BYTE SBOX [256] =
{
    0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
    0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
    0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
    0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
    0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
    0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
    0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
    0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
    0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
    0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
    0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
    0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
    0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
    0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
    0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
    0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
};

// inverse SBOX loop up table
BYTE inv_SBOX[256] =
{
    0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
    0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
    0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
    0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
    0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
    0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
    0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
    0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
    0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
    0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
    0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
    0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
    0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
    0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
    0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
};

// round constant
BYTE RCON[11] = {0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36};

// prototypes
void process_key_schedule(const char *keystr, BYTE key[][4][4], int key_size, int mc);
void handle_file_input(const char *input_filename, BYTE bytearray[][4][4], int nb, int s);
void write_output_file(const char *output_filename, BYTE outputarray[][4][4], int nb);
void print_hex_output(BYTE outputarray[][4][4], int nb);
void keyschedule128(BYTE key128[11][4][4], const char *keystr);
void keyschedule192(BYTE key192[13][4][4], const char *keystr);
void keyschedule256(BYTE key256[15][4][4], const char *keystr);
void encrypt(int mc, int nb, int lk, BYTE key[][4][4], BYTE bytearray[][4][4], BYTE outputarray[][4][4], FILE *output);
void decrypt(int mc, int nb, int lk, BYTE key[][4][4], BYTE bytearray[][4][4], BYTE outputarray[][4][4], FILE *output);
BYTE galois_multiply(BYTE a, BYTE b);

int main(int argc, char *argv[])
{
if (argc != 3) {
        fprintf(stderr, "Usage: %s <encrypt|decrypt> <128|192|256>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "encrypt") != 0 && strcmp(argv[1], "decrypt") != 0) {
        fprintf(stderr, "Invalid operation. Use 'encrypt' or 'decrypt'.\n");
        return 2;
    }

    if (strcmp(argv[2], "128") != 0 && strcmp(argv[2], "192") != 0 && strcmp(argv[2], "256") != 0) {
        fprintf(stderr, "Invalid key size. Use 128, 192, or 256.\n");
        return 3;
    }

    int lk = 0, mc = 0;
    if (strcmp(argv[2], "128") == 0) {
        lk = 16;
        mc = 10;
    } else if (strcmp(argv[2], "192") == 0) {
        lk = 24;
        mc = 12;
    } else if (strcmp(argv[2], "256") == 0) {
        lk = 32;
        mc = 14;
    }

    BYTE key[15][4][4] = {0}; // Maximum size for any key schedule

    char keystr[33];
    printf("Enter your key (string): ");
    scanf("%32s", keystr);

    if ((strlen(keystr) != lk)) {
        fprintf(stderr, "Invalid key size. Expected %d characters.\n", lk);
        return 4;
    }

    process_key_schedule(keystr, key, lk, mc);

    char input_filename[50];
    printf("Input file: ");
    scanf("%49s", input_filename);

    FILE *file = fopen(input_filename, "rb");
    if (!file) {
        perror("Error opening input file");
        return 5;
    }

    // Find out the file length
    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fseek(file, 0, SEEK_SET);
    fclose(file);

    // need to separate it into 16B parts
    int s = size;
    while (size % 16 != 0) size++;
    int nb = size / 16;

    BYTE (*bytearray)[4][4] = malloc(nb * sizeof(*bytearray));
    BYTE (*outputarray)[4][4] = malloc(nb * sizeof(*outputarray));
    if (!bytearray || !outputarray) {
        perror("Memory allocation failed");
        free(bytearray);
        free(outputarray);
        return 6;
    }
    memset(bytearray, 0x00, nb * sizeof(*bytearray));
    memset(outputarray, 0x00, nb * sizeof(*outputarray));

    handle_file_input(input_filename, bytearray, nb, s);

    char output_filename[50];
    printf("Output file: ");
    scanf("%49s", output_filename);

    FILE *output = fopen(output_filename, "wb");
    if (!output) {
        perror("Error opening output file");
        fclose(file);
        return 7;
    }

    if (strcmp(argv[1], "encrypt") == 0) {
        encrypt(mc, nb, lk, key, bytearray, outputarray, output);
    } else {
        decrypt(mc, nb, lk, key, bytearray, outputarray, output);
    }

    write_output_file(output_filename, outputarray, nb);

    char answer;
    printf("Do you want to print the output in hex values? (y/n): ");
    scanf(" %c", &answer);

    if (tolower(answer) == 'y') {
        print_hex_output(outputarray, nb);
    }

    fclose(output);
    free(bytearray);
    free(outputarray);

    return 0;
}


void keyschedule128(BYTE key128[11][4][4], const char *keystr) {
    for (int rd = 1; rd < 11; rd++) {
        BYTE RotWord[4];
        BYTE subword[4];

        // rotate and SubBytes transformation
        for (int m = 0; m < 4; m++) {
            RotWord[m] = key128[rd - 1][3][m];
        }
        BYTE tmp = RotWord[0];
        for (int m = 0; m < 3; m++) {
            RotWord[m] = RotWord[m + 1];
        }
        RotWord[3] = tmp;
        for (int m = 0; m < 4; m++) {
            subword[m] = SBOX[RotWord[m]];
        }
        subword[0] ^= RCON[rd];

        // generate new key
        for (int i = 0; i < 4; i++) {
            key128[rd][0][i] = key128[rd - 1][0][i] ^ subword[i];
        }
        for (int t = 1; t < 4; t++) {
            for (int i = 0; i < 4; i++) {
                key128[rd][t][i] = key128[rd][t - 1][i] ^ key128[rd - 1][t][i];
            }
        }
    }
}

void keyschedule192(BYTE key192[13][4][4], const char *keystr) {
    BYTE words[54][4] = {0};

    int count = 0;
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            words[i][j] = keystr[count++];
        }
    }

    int rdc = 1;
    for (int i = 6; i < 54; i += 6, rdc++) {
        BYTE rotword[4], subword[4];

        for (int m = 0; m < 4; m++) {
            rotword[m] = words[i - 1][m];
        }
        BYTE tmp = rotword[0];
        for (int m = 0; m < 3; m++) {
            rotword[m] = rotword[m + 1];
        }
        rotword[3] = tmp;

        for (int m = 0; m < 4; m++) {
            subword[m] = SBOX[rotword[m]];
        }
        subword[0] ^= RCON[rdc];

        for (int m = 0; m < 4; m++) {
            words[i][m] = words[i - 6][m] ^ subword[m];
        }
        for (int w = i + 1; w < i + 6; w++) {
            for (int m = 0; m < 4; m++) {
                words[w][m] = words[w - 6][m] ^ words[w - 1][m];
            }
        }
    }

    for (int w = 0, k = 0; w < 13; w++) {
        for (int v = 0; v < 4; v++) {
            for (int j = 0; j < 4; j++) {
                key192[w][v][j] = words[k][j];
            }
            k++;
        }
    }
}


void keyschedule256(BYTE key256[15][4][4], const char *keystr)
{
    BYTE words[60][4] = {0};

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            words[i][j] = keystr[i * 4 + j];
        }
    }

    int rdc = 1;
    for (int i = 8; i < 60; i++) {
        BYTE rotword[4], subword[4];

        if (i % 8 == 0) {
            for (int m = 0; m < 4; m++) {
                rotword[m] = words[i - 1][m];
            }
            BYTE tmp = rotword[0];
            for (int m = 0; m < 3; m++) {
                rotword[m] = rotword[m + 1];
            }
            rotword[3] = tmp;

            for (int m = 0; m < 4; m++) {
                subword[m] = SBOX[rotword[m]];
            }
            subword[0] ^= RCON[rdc++];
        } else if (i % 8 == 4) {
            for (int m = 0; m < 4; m++) {
                subword[m] = SBOX[words[i - 1][m]];
            }
        }
        for (int m = 0; m < 4; m++) {
            words[i][m] = words[i - 8][m] ^ subword[m];
        }
    }

    for (int rd = 0, k = 0; rd < 15; rd++) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                key256[rd][i][j] = words[k][j];
            }
            k++;
        }
    }
}

void encrypt(int mc, int nb, int lk, BYTE key[lk][4][4], BYTE bytearray[nb][4][4], BYTE outputarray[nb][4][4], FILE *output) {
    // ROUND 0 : add roundkey
    for (int w = 0; w < nb; w++) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                outputarray[w][i][j] = (bytearray[w][i][j] ^ key[0][i][j]);
            }
        }
    }

    for (int w = 0; w < nb; w++) {
        int rds = mc + 1;
        for (int rd = 1; rd < rds; rd++) {
            // sub bytes step
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    outputarray[w][i][j] = SBOX[outputarray[w][i][j]];
                }
            }

            // shift rows step
            int temp;
            temp = outputarray[w][0][1];
            for (int i = 0; i < 3; i++) {
                outputarray[w][i][1] = outputarray[w][i + 1][1];
            }
            outputarray[w][3][1] = temp;

            temp = outputarray[w][0][2];
            int temp2 = outputarray[w][1][2];
            for (int i = 0; i < 2; i++) {
                outputarray[w][i][2] = outputarray[w][i + 2][2];
            }
            outputarray[w][2][2] = temp;
            outputarray[w][3][2] = temp2;

            temp = outputarray[w][3][3];
            for (int i = 3; i > 0; i--) {
                outputarray[w][i][3] = outputarray[w][i - 1][3];
            }
            outputarray[w][0][3] = temp;

            // mix columns step (if not the last round)
            if (rd != mc) {
                BYTE temp[4][4];
                memset(temp, 0, sizeof(temp));
                for (int i = 0; i < 4; i++) {
                    temp[i][0] = galois_multiply(2, outputarray[w][i][0]) ^ galois_multiply(3, outputarray[w][i][1]) ^ outputarray[w][i][2] ^ outputarray[w][i][3];
                    temp[i][1] = outputarray[w][i][0] ^ galois_multiply(2, outputarray[w][i][1]) ^ galois_multiply(3, outputarray[w][i][2]) ^ outputarray[w][i][3];
                    temp[i][2] = outputarray[w][i][0] ^ outputarray[w][i][1] ^ galois_multiply(2, outputarray[w][i][2]) ^ galois_multiply(3, outputarray[w][i][3]);
                    temp[i][3] = galois_multiply(3, outputarray[w][i][0]) ^ outputarray[w][i][1] ^ outputarray[w][i][2] ^ galois_multiply(2, outputarray[w][i][3]);
                }
                memcpy(outputarray[w], temp, sizeof(temp));
            }

            // add roundkey step
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    outputarray[w][i][j] ^= key[rd][i][j];
                }
            }
        }
    }
}

void decrypt(int mc, int nb, int lk, BYTE key[lk][4][4], BYTE bytearray[nb][4][4], BYTE outputarray[nb][4][4], FILE *output) {
    for (int w = 0; w < nb; w++) {
        for (int rd = mc; rd > 0; rd--) {
            // addRoundKey step
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    bytearray[w][i][j] ^= key[rd][i][j];
                }
            }

            // invMixColumns step (if not the last round)
            if (rd != mc) {
                BYTE temp[4][4];
                memset(temp, 0, sizeof(temp));
                for (int i = 0; i < 4; i++) {
                    temp[i][0] = galois_multiply(14, bytearray[w][i][0]) ^ galois_multiply(11, bytearray[w][i][1]) ^ galois_multiply(13, bytearray[w][i][2]) ^ galois_multiply(9, bytearray[w][i][3]);
                    temp[i][1] = galois_multiply(9, bytearray[w][i][0]) ^ galois_multiply(14, bytearray[w][i][1]) ^ galois_multiply(11, bytearray[w][i][2]) ^ galois_multiply(13, bytearray[w][i][3]);
                    temp[i][2] = galois_multiply(13, bytearray[w][i][0]) ^ galois_multiply(9, bytearray[w][i][1]) ^ galois_multiply(14, bytearray[w][i][2]) ^ galois_multiply(11, bytearray[w][i][3]);
                    temp[i][3] = galois_multiply(11, bytearray[w][i][0]) ^ galois_multiply(13, bytearray[w][i][1]) ^ galois_multiply(9, bytearray[w][i][2]) ^ galois_multiply(14, bytearray[w][i][3]);
                }
                memcpy(bytearray[w], temp, sizeof(temp));
            }

            // invShiftRows step
            int temp;
            temp = bytearray[w][3][1];
            for (int i = 3; i > 0; i--) {
                bytearray[w][i][1] = bytearray[w][i - 1][1];
            }
            bytearray[w][0][1] = temp;

            temp = bytearray[w][0][2];
            int temp2 = bytearray[w][1][2];
            for (int i = 0; i < 2; i++) {
                bytearray[w][i][2] = bytearray[w][i + 2][2];
            }
            bytearray[w][2][2] = temp;
            bytearray[w][3][2] = temp2;

            temp = bytearray[w][0][3];
            for (int i = 0; i < 3; i++) {
                bytearray[w][i][3] = bytearray[w][i + 1][3];
            }
            bytearray[w][3][3] = temp;

            // invSubBytes step
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    bytearray[w][i][j] = inv_SBOX[bytearray[w][i][j]];
                }
            }
        }

        // addRoundKey step for round 0
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                outputarray[w][i][j] = bytearray[w][i][j] ^ key[0][i][j];
            }
        }
    }
}

void write_output_file(const char *output_filename, BYTE outputarray[][4][4], int nb) {
    FILE *output = fopen(output_filename, "wb");
    if (!output) {
        perror("Error opening output file");
        exit(1);
    }

    fwrite(outputarray, sizeof(BYTE), nb * 16, output);
    fclose(output);
}

void print_hex_output(BYTE outputarray[][4][4], int nb) {
    printf("Output (hex):\n");
    for (int w = 0; w < nb; w++) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                printf("%02x ", outputarray[w][i][j]);
            }
        }
        printf("\n");
    }
}

void process_key_schedule(const char *keystr, BYTE key[][4][4], int key_size, int mc) {
    switch (key_size) {
        case 16:
            keyschedule128(key, keystr);
            break;
        case 24:
            keyschedule192(key, keystr);
            break;
        case 32:
            keyschedule256(key, keystr);
            break;
    }
}

void handle_file_input(const char *input_filename, BYTE bytearray[][4][4], int nb, int s) {
    FILE *file = fopen(input_filename, "rb");
    if (!file) {
        perror("Error opening input file");
        exit(1);
    }

    size_t bytesRead = fread(bytearray, sizeof(BYTE), s, file);
    if (bytesRead != s) {
        fprintf(stderr, "Warning: Expected %d bytes, but only %zu bytes were read.\n", s, bytesRead);
    }

    // Pad remaining bytes with spaces (if necessary)
    if (bytesRead < s) {
        memset((BYTE *)bytearray + bytesRead, 0x00, s - bytesRead);
    }

    fclose(file);
}

BYTE galois_multiply(BYTE a, BYTE b) {
    BYTE result = 0;
    while (b) {
        if (b & 1) {
            result ^= a;
        }
        BYTE hi_bit_set = a & 0x80;
        a <<= 1;
        if (hi_bit_set) {
            a ^= 0x1b; // AES irreducible polynomial
        }
        b >>= 1;
    }
    return result;
}