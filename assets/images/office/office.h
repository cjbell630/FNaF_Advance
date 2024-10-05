#ifndef OFFICE_H
#define OFFICE_H

#define office_palette_size 496
extern const unsigned short office_palette[248];
#define office_tiles_size 57600
extern const unsigned short office_tiles[28800];
#define office_tilemap_size 4096
extern const unsigned short office_tilemap[2048];

void do_office_llight_empty();
void undo_office_llight_empty();
void do_office_llight_bonnie();
void undo_office_llight_bonnie();
void do_office_rlight_empty();
void undo_office_rlight_empty();
void do_office_rlight_chica();
void undo_office_rlight_chica();
#endif