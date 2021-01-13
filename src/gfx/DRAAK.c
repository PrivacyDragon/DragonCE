#include "DRAAK.h"
#include <fileioc.h>

#define DRAAK_HEADER_SIZE 6

unsigned char *DRAAK_appvar[2] =
{
    (unsigned char*)6,
    (unsigned char*)518,
};

unsigned char *image_tiles_compressed[12] =
{
    (unsigned char*)0,
    (unsigned char*)10,
    (unsigned char*)1274,
    (unsigned char*)3020,
    (unsigned char*)3030,
    (unsigned char*)3040,
    (unsigned char*)5934,
    (unsigned char*)8944,
    (unsigned char*)8954,
    (unsigned char*)8964,
    (unsigned char*)10079,
    (unsigned char*)11183,
};

unsigned char DRAAK_init(void)
{
    unsigned int data, i;
    ti_var_t appvar;

    ti_CloseAll();

    appvar = ti_Open("DRAAK", "r");
    if (appvar == 0)
    {
        return 0;
    }

    data = (unsigned int)ti_GetDataPtr(appvar) - (unsigned int)DRAAK_appvar[0] + DRAAK_HEADER_SIZE;
    for (i = 0; i < 2; i++)
    {
        DRAAK_appvar[i] += data;
    }

    ti_CloseAll();

    data = (unsigned int)DRAAK_appvar[1] - (unsigned int)image_tiles_compressed[0];
    for (i = 0; i < image_tiles_num; i++)
    {
        image_tiles_compressed[i] += data;
    }

    return 1;
}

