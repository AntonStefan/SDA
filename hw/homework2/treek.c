#include <string.h>
#include <stdlib.h>

#include "ppm.h"

int main(int argc, char** argv)
{
    if (argc < 4)
        return 0;

    if (!strcmp(argv[1], "-c"))
        ppm_compress(argv[3], argv[4], atoi(argv[2]));
    else if (!strcmp(argv[1], "-d"))
        ppm_decompress(argv[2], argv[3]);
}