#include <stdint.h>

#include <stdint.h>

typedef uint8_t  BYTE;


typedef struct block
{

    unsigned int first_bytes : 24;
    BYTE rest_of_JPEG[509];

} bloc;
