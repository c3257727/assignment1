/* Jamie McKay c3257727
ENGG1003 2019 Assignment 1*/

#include <stdio.h>
#include <stdlib.h>

void Lowercase_Capital (char *str);                                             //Function to turn lowercase letters to capitals
void Encryption_rotation (char *str, int rotation);                             //Function to encrypt via rotation cipher
void Decryption_rotation (char *str, int rotation);                             //Function to decrypt via rotation cipher
void Encryption_substitution (char *message, char *alphabet, char *key);        //Function to encrypt via substutution cipher
void Decryption_substitution (char *message, char *alphabet, char *key);        //Function to decrypt via substitution cipher
void Decryption_rotation_NoKey(char *message);                                  //Function to decrypt via rotation cipher with no key given

int main()
{
    int rotation = 1;
    int i = 0; //The array index, initializing at 0.
    int key;
    char message[1024];     // A string containing the message to be encrypted or decrypted.
    char message_out[1024];
    char alphabet [] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char sub_key [] = "QWERTYUIOPASDFGHJKLZXCVBNM";

    FILE *input;
    input = fopen("Message.txt", "r");
    if (input == NULL)
    {
        perror("Message.txt");
        return 1;
    }

    while (feof(input) == 0)
    {
        fscanf(input, "%c", &message[i]);
        i++;
    }

    FILE *number;
    number = fopen("Rotation_Cipher.txt", "r");
    if (number == NULL)
    {
        perror("Rotation_Cipher.txt");
        return 1;
    }
    i = 0;
    while (feof(number) == 0)
    {
        fscanf(number, "%d", &key);
        i++;
    }

    FILE *sub;
    input = fopen("Substitution_Cipher.txt", "r");
    if (input == NULL)
    {
        perror("Substitution_Cipher.txt");
        return 1;
    }

    printf("****************************************************\n");
    printf("           Welcome to the Enigma Machine\n");
    printf("****************************************************\n");
    printf("Please select an option:\n");
    printf("1) Encryption via Rotation, with key.\n");
    printf("2) Decryption via Rotation, with key.\n");
    printf("3) Decryption via Rotation, without key.\n");
    printf("4) Encryption via Substitution, with key.\n");
    printf("5) Decryption via Substitution, with key.\n");

    int selection;
    do
    {
        scanf("%d", &selection);

        if (selection < 1 || selection > 5)
        {
            printf("Invalid selection, please try again.\n");
        }

    }
    while (selection < 1 || selection > 5);

    Lowercase_Capital (message); //converting every case into capitals before performing any tasks.

    switch (selection)
    {
    case 1:
        Encryption_rotation (message, rotation);
        printf("%s\n", message);
        break;


    case 2:
        Decryption_rotation (message, rotation);
        printf("%s\n", message);
        break;

    case 3:
        Decryption_rotation_NoKey(message);
        break;

    case 4:
        Encryption_substitution(message, alphabet, sub_key);
        printf("%s\n", message);
        break;

    case 5:
        Decryption_substitution (message, alphabet, sub_key);
        printf("%s\n", message);
        break;

    }
    return 0;
}

/* DESCRIPTION/LIMITATIONS: The function takes a string and changes the lowercase characters to uppercase.
 * INPUTS: The string of characters i.e. the message.
 * OUTPUTS: The output is of the modified string.
 * RETURN VALUE: None.
 */

void Lowercase_Capital (char *message)
{
    int i = 0;
    while (message[i] != '\0')                           // Continue the loop until NULL character is reached at end of string.
    {
        if (message[i] >= 'a' && message[i] <= 'z')         // IF the string message is within the lowercase letter assignment in the ASCII table.
        {
            message[i] = message[i] - 32;                   // Minus 32 from the string value to bring back into the capital letter assignment in the ASCII table.
        }

        i++;
    }
    return;
}

/* DESCRIPTION/LIMITATIONS: The function takes the message and encrypts it by moving each letter a set number of places in the alphabet.
 * INPUTS: The string of characters i.e. the message.
 * OUTPUTS: The output is of the modified string, i.e. the encrypted message.
 * RETURN VALUE: None.
 */
void Encryption_rotation (char *message, int key)
{
    int i = 0;
    while (message[i] != '\0')                                          // Initializing encryption loop, NULL will end the loop.
    {
        if (message[i] >= 'A' && message[i] <= 'Z')                         // IF the string is between (inclusive) capital A and Z
        {
            message[i] = 'A' + ((message[i] - 'A' + key) % 26);             // Implememtning the given function (string)and keeping it within the constraints of (0-25)
        }
        i++;
    }
    return;
}

/* DESCRIPTION/LIMITATIONS: The function takes the message and decrypts it by moving each letter a set number of places back in the alphabet.
 * INPUTS: The string of characters i.e. the encoded message.
 * OUTPUTS: The output is of the modified string, i.e. the decrypted message.
 * RETURN VALUE: None.
 */
void Decryption_rotation (char *message, int key)
{
    int i = 0;
    while (message[i] != '\0')                                          // Initializing encryption loop, NULL will end the loop.
    {
        if (message[i] >= 'A' && message[i] <= 'Z')                         // IF the string is between (inclusive) capital A and Z
        {
            message[i] = 'A' + ((message[i] - 'A' - key + 26) % 26);        // Implememtning the given function (string) and keeping it within the constraints of (0-25).
        }
        i++;
    }
    return;
}

 /* DESCRIPTION/LIMITATIONS: The function takes the message and encrypts it by replacing each letter with the corresponding one in the key.
 * INPUTS: The string of characters i.e. the message.
 * OUTPUTS: The output is of the modified string, i.e. the encrypted message.
 * RETURN VALUE: None.
 */
void Encryption_substitution (char *message, char *alphabet, char *key)
{
    int count2;
    int i = 0;

    while (message[i] != '\0') //while the count is not NULL
    {
        for ( count2 = 0; count2 < 26; count2++) // Comparing the letter to each position in the alphabet string.
        {
            if (message[i] == alphabet[count2]) //Using counter to read each letter after the other then compare it to the alphabet positioning.
            {
                message[i] = key[count2];
            break;
            }
        }
        i++;
    }
    return;
}

/* DESCRIPTION/LIMITATIONS: The function takes the encrypted message and decrypts it by replacing each letter with the corresponding one in the alphabet.
 * INPUTS: The string of characters i.e. the encrypted message.
 * OUTPUTS: The output is of the modified string, i.e. the decrypted  message.
 * RETURN VALUE: None.
 */
void Decryption_substitution (char *message, char *alphabet, char *key)
{
    int i = 0;
    int count2;
    while (message[i] != '\0') //while the count is not NULL
    {
        for ( count2 = 0; count2 < 26; count2++) // Comparing the letter to each position in the alphabet string.
        {
            if (message[i] == key[count2]) //Using counter to read each letter after the other then compare it to the alphabet positioning.
            {
                message[i] = alphabet[count2];
            break;
            }
        }
        i++;
    }
    return;
}

/* DESCRIPTION/LIMITATIONS: The function takes the encrypted message and decrypts it by looping all posible rotations.
 * INPUTS: The string of characters i.e. the encrypted message.
 * OUTPUTS: The output is of the modified string, i.e. the decrypted  message.
 * RETURN VALUE: None.
 */
void Decryption_rotation_NoKey(char *message)
{
    int i = 0;
     while (i < 25)          //While the counter is less than 26 (the amount of key rotations)
    {
        Encryption_rotation (message, 1);
        printf("Rotation %d: %s\n\n", i+1, message);
        i++;
    }
    return;
}

