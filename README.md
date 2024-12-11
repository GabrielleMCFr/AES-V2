# AES 128/192/256 (C)


## Description 

This program constitutes a C-based implementation of the Advanced Encryption Standard (AES) with support for 128-bit, 192-bit, and 256-bit key lengths. AES was selected due to its robust security attributes; notably, the 256-bit variant exhibits resistance against quantum computational threats. Its anticipated widespread adoption in the coming decades further underscores its relevance. The cipher operates in Electronic Codebook (ECB) mode.

### Command-Line Interface
The program requires two command-line arguments for execution:
Operation Mode: Specify either "encrypt" or "decrypt".
Key Length: Specify one of "128", "192", or "256" to define the key size.

### Key Schedule Generation

#### KeySchedule128
This routine generates 11 subkeys from a 128-bit master key. Subkey generation involves the following:
The final word of the previous round's key undergoes a leftward byte rotation.
A substitution operation (SubBytes) is applied to the rotated word.
The first byte of the substituted word is XORed with a round constant (RCON).
Subsequent words are derived by XORing the prior word with its corresponding position in the previous round.

#### KeySchedule192
For a 192-bit master key, this routine generates 13 subkeys. While it adheres to similar principles as KeySchedule128, the structure diverges:
The key schedule produces six words (24 bytes) per round, forming non-linear sequences.
Due to this organization, there are only 8 encryption rounds. Words are distributed across keys by segmenting them into groups of four bytes (e.g., word 0 spans bytes 0-5, word 1 spans bytes 6-11). Only 52 words are required, but the algorithm generates 54 for structural alignment.

#### KeySchedule256
The 256-bit master key variant generates 15 subkeys:
Each round produces eight words (32 bytes), sufficient for two keys.
An additional operation introduces non-linearity: between the third and fourth words of each round, a substituted version of the third word undergoes further transformation.
Seven rounds are sufficient to generate the requisite 60 words, although the process yields 64 for alignment.

#### Main Execution Flow
Upon execution, the user specifies:

An input file containing the plaintext or ciphertext.
An output file name for the processed data.
File contents are dynamically segmented into 16-byte blocks, with padding applied as necessary to align with the block size. Each block comprises four words, each four bytes long. When encrypting, output format selection is discretionary, as encrypted data is inherently non-readable. However, for decryption, the user must specify the plaintext format for compatibility.

#### Encryption and Decryption Functions
The core encrypt/decrypt routines dynamically adjust the number of rounds:

AES-128: 10 rounds
AES-192: 12 rounds
AES-256: 14 rounds
Each routine executes the following operations for each block:

Initial Key Addition: Perform XOR between the block and the initial round key.

Round Operations (1 through 10/12/14):

SubBytes: Byte substitution using S-Box (encryption) or inverse S-Box (decryption). For performance, a lookup table is employed. A more secure implementation could substitute this with a direct computation in 𝐺𝐹(2^8) to mitigate cache attacks.
ShiftRows: Circular byte shifts applied row-wise:
Encryption: Row 0 remains unchanged; subsequent rows shift left by 1, 2, and 3 bytes respectively.
Decryption: The pattern reverses, with rightward shifts.
MixColumns: Linear transformation applied to each column:
A temporary array stores the intermediate state.
Columns are multiplied by a fixed matrix, with results XORed to produce the output. Separate matrices are used for encryption and decryption, and lookup tables enhance computational efficiency.
AddRoundKey: XOR the round key with the block.
Finalization: After the final round, the transformed blocks are stored in memory for subsequent output.

### Lookup Table Optimization and Customization
The program leverages lookup tables for performance efficiency, particularly in the SubBytes and MixColumns transformations. These tables can be modified for experimental or specialized use cases:

Performance Tuning: Users can reduce the number of rows or adjust table dimensions to favor speed over security. For instance, using fewer rows simplifies transformations, accelerating computations but compromising cryptographic robustness.
Custom Implementations: Lookup tables can be tailored for specific use cases, allowing for novel or domain-specific variations of the AES standard.
This flexibility provides a balance between security and performance, accommodating scenarios where stringent security is unnecessary, and computational speed is paramount.

### Conclusion
The program’s design adheres to the structural rigor of AES while enabling customization for various performance and security trade-offs. Lookup tables expedite operations, and their modularity allows for flexible experimentation without compromising the core algorithmic structure.

### Note
We assume the keys are in ASCII chars.