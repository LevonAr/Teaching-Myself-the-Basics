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
        // K before modulus
        int preK= atoi(argv[1]);

        // modulus strips any number larger than 26 to a functional number
        int k = preK%26;

        int caeser;

        string s = get_string("plaintext: ");

        printf("ciphertext: ");

        for(int i=0; i<strlen(s); i++)
        {
            // corresponding ASCII #
            int num = (int)s[i];
            if ((num > 64 && num < 91) || (num > 96 && num <123))
                {
                    // in the case that k takes ASCII assignmtent over the corresponding lowercase alphabet
                    caeser = num + k;
                    if (caeser > 122)
                        {caeser = caeser - 26;}
                    // in the case that k takes ASCII assignmtent over the corresponding uppercase alphabet
                    else if (num > 64 && num < 91 && caeser > 90 )
                        {caeser = caeser - 26;}
                }
            else
                {
                    caeser = num;
                }
        printf("%c", (char)caeser);
        }

        printf("\n");
    }

    else
    {
        printf ("error\n");
        return 1;
    }
}
