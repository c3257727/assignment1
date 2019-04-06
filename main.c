/* Jamie McKay c3257727 
ENGG1003 2019 Assignment 1*/

#include <stdio.h>
#include <stdlib.h>

void Lowercase_Capital (char *str);
void Encryption (char *str);
void Decryption (char *str);


int main()
{
    int k; // This is the 'key' for the rotation cipher, and will be between 0 and 25.
    //char m; // This is the message letter i.e the letter being encrypted.
    //char c; 
    int i = 0; //The array index. 
    
    
    
    //------------------------------------
    // get a message (string)
    //------------------------------------
    
    char str[] = "abcdefghijklmnopAAAA";                    // A string containing the message to be encrypted or decrypted.
    
    
    //------------------------------------
    // do some encryption/decryption on the message (do me last)
    //------------------------------------
 
    Lowercase_Capital(str);
  /* This is the ENCRYPTION section */                                          
    
  /*  while (str[i] != '\0')   
                                                                                // Initializing encryption loop, NULL will end the loop.
    {
       
        if (str[i] > 64 && str[i] < 91)
        {
            //str[i] = str[i] + 1;
            str[i] = 'A' + ((str[i] - 'A' + 4) % 26);                           // Implememtning the given function and keeping it within the constrains of (0-25)
           
        }
        
        i++;
    } */
    
    /* this is the DECRYPTION section*/
    
    while (str[i] != '\0')
    {
      
        if (str[i] > 64 && str[i] < 91)
        {
           
            str[i] = 'A' + ((str[i] - 'A' - 1 + 26) % 26);
           
        }
    
        i++;
    }
    
    
    
    printf("%s", str);          // Printing the message.
    

    return 0;
}


/* DESCRIPTION/LIMITATIONS: The function takes a string and changes the lowercase characters to uppercase. 
 * INPUTS: The string of characters i.e. the message.
 * OUTPUTS: The output is of the modified string.
 * RETURN VALUE: None.
 */

void Lowercase_Capital (char *str)
{
    int i = 0;
    while (str[i] != '\0')                      // Continue the loop until NULL character is reached at end of string.
    {
        if (str[i] > 96 && str[i] < 123)        // IF the string message is within the lowercase letter assignment in the ASCII table.
        {
            str[i] = str[i] - 32;               // Minus 32 from the string value to bring back into the capital letter assignment in the ASCII table.
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
void Encryption (char *str)
{
    
while (str[i] != '\0')   
                                                                                // Initializing encryption loop, NULL will end the loop.
    {
       
        if (str[i] > 64 && str[i] < 91)
        {
            //str[i] = str[i] + 1;
            str[i] = 'A' + ((str[i] - 'A' + 4) % 26);                           // Implememtning the given function and keeping it within the constrains of (0-25)
           
        }
        
        i++;
    } 
}

/* DESCRIPTION/LIMITATIONS: The function takes the message and decrypts it by moving each letter a set number of places back in the alphabet. 
 * INPUTS: The string of characters i.e. the encoded message.
 * OUTPUTS: The output is of the modified string, i.e. the decrypted message.
 * RETURN VALUE: None.
 */
void Decryption (char *str)
   while (str[i] != '\0')
    {
      
        if (str[i] > 64 && str[i] < 91)
        {
           
            str[i] = 'A' + ((str[i] - 'A' - 1 + 26) % 26);
           
        }
    
        i++;
    }
    
