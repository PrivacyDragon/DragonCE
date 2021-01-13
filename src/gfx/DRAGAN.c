#include "DRAGAN.h"
#include <fileioc.h>

#define DRAGAN_HEADER_SIZE 6

unsigned char *DRAGAN_appvar[2] =
{
    (unsigned char*)6,
    (unsigned char*)518,
};

unsigned char *image1_tiles_compressed[12] =
{
    (unsigned char*)0,
    (unsigned char*)4259,
    (unsigned char*)8404,
    (unsigned char*)12288,
    (unsigned char*)15601,
    (unsigned char*)20056,
    (unsigned char*)23862,
    (unsigned char*)27276,
    (unsigned char*)31549,
    (unsigned char*)36205,
    (unsigned char*)40511,
    (unsigned char*)44502,
};

unsigned char DRAGAN_init(void)
{
    unsigned int data, i;
    ti_var_t appvar;

    ti_CloseAll();

    appvar = ti_Open("DRAGAN", "r");
    if (appvar == 0)
    {
        return 0;
    }

    data = (unsigned int)ti_GetDataPtr(appvar) - (unsigned int)DRAGAN_appvar[0] + DRAGAN_HEADER_SIZE;
    for (i = 0; i < 2; i++)
    {
        DRAGAN_appvar[i] += data;
    }

    ti_CloseAll();

    data = (unsigned int)DRAGAN_appvar[1] - (unsigned int)image1_tiles_compressed[0];
    for (i = 0; i < image1_tiles_num; i++)
    {
        image1_tiles_compressed[i] += data;
    }

    return 1;
}

