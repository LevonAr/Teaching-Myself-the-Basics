#include <stdint.h>

typedef uint8_t  BYTE;

typedef struct
{
   unsigned int nibble1 : 4;
   unsigned int nibble2 : 4;
} nib;

typedef struct
{

    unsigned int first_bytes : 24;
    BYTE rest_of_JPEG[509];

} block;
