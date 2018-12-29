#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        string key = argv[1];

        int keyNum;

        int exitprogram;

        // place holder variable that skips when plaintext has a nonalphabetical char
        int k = 0;

        for (int i=0; i<strlen(key); i++)
        {
            // checking if entered key has any nonalphabetical chars
            int errCheck = (int)(key[i]);
            if (errCheck <64 || (errCheck > 90 && errCheck < 97) || errCheck > 123 )
            {
                printf("error\n");
                exit(1);
            }
        }

        /*if (exitprogram == 1) // exits if it does have nonalphabetical chars
        {
            printf("error\n");
            return 1;
        }*/

        string plaintext = get_string("plaintext: ");


        printf("ciphertext: ");

        for (int i=0; i<strlen(plaintext); i++)
        {
            int j = (i-k) - (i-k)/strlen(key)* strlen(key);

            // number corresponding to key before it is primed for use
            int preKeyNum = (int)key[j];

            if (preKeyNum > 96 && preKeyNum < 123)
            {
                keyNum = preKeyNum - 97;
            }

            else if (preKeyNum > 64 && preKeyNum < 91)
            {
                keyNum = preKeyNum - 65;
            }


            int intChar = (int)plaintext[i];

            int cipherChar = intChar + keyNum;

            if (cipherChar > 122 || ( cipherChar > 90 && (intChar < 91 && intChar > 64)))
            {
                cipherChar = cipherChar - 26;
            }

            else if(intChar < 65 || (intChar > 90 && intChar <97) || intChar > 122)
            {
                cipherChar =  intChar;
                k = k+1;

            }

            printf ("%c", (char)cipherChar);
        }
        printf ("\n");
    }

    else
    {
        printf("error\n");
        return 1;
    }
}

