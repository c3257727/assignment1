/* Jamie McKay c3257727, ENGG1003 2019 Assignment 1*/

/*
The following program works as an enigma machine; that can both encode and decode messages via a rotation or a substitution cipher.
Any method may be chosen by the user via the welcome page when the program is run. All messages and the rotation key must be written in files
message.txt and Rotation_Cipher.txt to be read by the propgram. Once read from file, the message is put through either the roatation cipher with or without key,
or the substition cipher, with key only. Descriptions of each cipher function can be seen before their definitions.
 */


#include <stdio.h>
#include <stdlib.h>

void Lowercase_Capital (char *str);                                             //Function to turn lowercase letters to capitals
void Encryption_rotation (char *str, int rotation);                             //Function to encrypt via rotation cipher with key given
void Decryption_rotation (char *str, int rotation);                             //Function to decrypt via rotation cipher with key given
void Encryption_substitution (char *message, char *alphabet, char *key);        //Function to encrypt via substutution cipher with key given
void Decryption_substitution (char *message, char *alphabet, char *key);        //Function to decrypt via substitution cipher with key given
void Decryption_rotation_NoKey(char *message);                                  //Function to decrypt via rotation cipher with no key given

int main()
{
    //int rotation = 1;
    int i = 0;                                                  // The array index, initializing at 0.
    int key;                                                    // Rotation key, given from file.
    char message[1024];                                         // A string containing the message to be encrypted or decrypted.
    char message_out[1024];                                     // A string containing the meesage output.
    char alphabet [] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";            // A string containing the alphabet for substitution comparisons.
    char sub_key [26];                                          // A string containing 26 chars; i.e. the number of letters in the alphabet.

    FILE *input;
    input = fopen("Message.txt", "r");          // Opening the file containing the message.
    if (input == NULL)                          // IF the folder is empty, send a perror message for message.txt.
    {
        perror("Message.txt");
        return 1;                               // End the program.
    }

    while (feof(input) == 0)                    //WHILE there is an input in the file, read each character.
    {
        fscanf(input, "%c", &message[i]);       //Scaning in each char then i++ to move onto the next one.
        i++;
    }

    FILE *number;
    number = fopen("Rotation_Cipher.txt", "r");     // Opening the file stating the number of rotations, i.e. the key, for the rotation cipher.
    if (number == NULL)                             // IF the folder is empty send a perror message for Rotation_Cipher.txt.
    {
        perror("Rotation_Cipher.txt");
        return 1;                                   // End the program.
    }
    i = 0;                                          // Initializing the counter at 0.
    while (feof(number) == 0)                       //WHILE there is an input in the file, read each character.
    {
        fscanf(number, "%d", &key);                 // Scaning in the number to rotate each letter by, i.e. the key.
        i++;
    }

    FILE *sub;
    sub = fopen("Substitution_Cipher.txt", "r");        // Opening the file containing the substitution cipher. i.e. the jumbled alphabet.
    if (sub == NULL)                                    //IF the folder is empty send a perror message for Substitution_Cipher.txt
    {
        perror("Substitution_Cipher.txt");
        return 1;                                       // End the program.
    }

    while (feof(sub) == 0)                              // WHILE there is an input in the file, read each character.
    {
        fscanf(sub, "%c", &sub_key[i]);                 // Scan in the characters of the jubled apphabet from the file and replace.
        i++;                                            // Move on to the next character.
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
        scanf("%d", &selection);                                // Scan in an int from user as a choice.

        if (selection < 1 || selection > 5)                     // If the selection is not one avaliable, print an error message to user.
        {
            printf("Invalid selection, please try again.\n");
        }

    }
    while (selection < 1 || selection > 5);                     // WHILE it is a correct selection...

    Lowercase_Capital (message);                                //converting every case into capitals before performing any tasks.


/*This is a SWITCH. Once the user gives an approproate input, the program will run accordingly.
i.e. it will run the choice in the switch associated with the selection. */

    switch (selection)
    {
    case 1:                                     // For selection 1.
        Encryption_rotation (message, key);     // Calling encryption_rotation function.
        printf("%s\n", message);                // Print the encoded message.
        break;                                  // End the program.


    case 2:                                     // For selection 2.
        Decryption_rotation (message, key);     // Calling decryption_rotation function.
        printf("%s\n", message);                // Print the decoded message.
        break;                                  // End the program.

    case 3:                                     // For selection 3.
        Decryption_rotation_NoKey(message);     // Calling Decryption via rotation function with no key.
        break;                                  // End the program.

    case 4:                                                     // For selection 4.
        Encryption_substitution(message, alphabet, sub_key);    // Calling Encryption_substitution function.
        printf("%s\n", message);                                // Print the encrypted message.
        break;                                                  // End the program.

    case 5:                                                     // For selection 5.
        Decryption_substitution (message, alphabet, sub_key);   // Calling Decryption_substitution function.
        printf("%s\n", message);                                // Print the decoded message.
        break;                                                  // End the program.

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
    while (message[i] != '\0')                              // Continue the loop until NULL character is reached at end of string.
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
    while (message[i] != '\0')                                              // Initializing encryption loop, NULL will end the loop.
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
    while (message[i] != '\0')                                              // Initializing encryption loop, NULL will end the loop.
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
        for ( count2 = 0; count2 < 26; count2++)         // Comparing the letter to each position in the alphabet string.
        {
            if (message[i] == key[count2])              //Using counter to read each letter after the other then compare it to the alphabet positioning.
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
     while (i < 25)                     //While the counter is less than 26 (the amount of key rotations)
    {
        Encryption_rotation (message, 1);
        printf("Rotation %d: %s\n\n", i+1, message);
        i++;
    }
    return;
}

