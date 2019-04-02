#include <stdint.h>

typedef uint8_t  BYTE;


typedef struct
{

    unsigned int first_bytes : 24;
    BYTE rest_of_JPEG[509];

} block;
