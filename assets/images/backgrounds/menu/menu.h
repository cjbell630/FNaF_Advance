
//{{BLOCK(menu)

//======================================================================
//
//	menu, 512x512@4, 
//	+ palette 16 entries, not compressed
//	+ 814 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 64x64 
//	Total size: 32 + 26048 + 8192 = 34272
//
//	Time-stamp: 2021-01-22, 02:29:18
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_MENU_H
#define GRIT_MENU_H

#define menuTilesLen 26048
extern const unsigned short menuTiles[13024];

#define menuMapLen 8192
extern const unsigned short menuMap[4096];

#define menuPalLen 32
extern const unsigned short menuPal[16];

#endif // GRIT_MENU_H

//}}BLOCK(menu)
