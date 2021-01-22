
//{{BLOCK(newspaper)

//======================================================================
//
//	newspaper, 256x256@4, 
//	+ palette 16 entries, not compressed
//	+ 1024 tiles not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 32 + 32768 + 2048 = 34848
//
//	Time-stamp: 2021-01-22, 01:28:28
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_NEWSPAPER_H
#define GRIT_NEWSPAPER_H

#define newspaperTilesLen 32768
extern const unsigned short newspaperTiles[16384];

#define newspaperMapLen 2048
extern const unsigned short newspaperMap[1024];

#define newspaperPalLen 32
extern const unsigned short newspaperPal[16];

#endif // GRIT_NEWSPAPER_H

//}}BLOCK(newspaper)
