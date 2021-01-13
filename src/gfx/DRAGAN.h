#ifndef DRAGAN_appvar_include_file
#define DRAGAN_appvar_include_file

#ifdef __cplusplus
extern "C" {
#endif

#define sizeof_global_palette 512
#define globale_palette (DRAGAN_appvar[0])
#define tileset_palette_offset 0
#define image1_tile_width 80
#define image1_tile_height 80
#define image1_compressed DRAGAN_appvar[1]
#define image1_tiles_num 12
extern unsigned char *image1_tiles_compressed[12];
#define image1_tile_0_compressed image_tiles_compressed[0]
#define image1_tile_1_compressed image_tiles_compressed[1]
#define image1_tile_2_compressed image_tiles_compressed[2]
#define image1_tile_3_compressed image_tiles_compressed[3]
#define image1_tile_4_compressed image_tiles_compressed[4]
#define image1_tile_5_compressed image_tiles_compressed[5]
#define image1_tile_6_compressed image_tiles_compressed[6]
#define image1_tile_7_compressed image_tiles_compressed[7]
#define image1_tile_8_compressed image_tiles_compressed[8]
#define image1_tile_9_compressed image_tiles_compressed[9]
#define image1_tile_10_compressed image_tiles_compressed[10]
#define image1_tile_11_compressed image_tiles_compressed[11]
#define DRAGAN_entries_num 2
extern unsigned char *DRAGAN_appvar[2];
unsigned char DRAGAN_init(void);

#ifdef __cplusplus
}
#endif

#endif
