
//{{BLOCK(loading)

//======================================================================
//
//	loading, 256x256@4, 
//	+ palette 16 entries, not compressed
//	+ 14 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 32 + 448 + 2048 = 2528
//
//	Time-stamp: 2021-01-22, 13:46:44
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_LOADING_H
#define GRIT_LOADING_H

#define loadingTilesLen 448
extern const unsigned short loadingTiles[224];

#define loadingMapLen 2048
extern const unsigned short loadingMap[1024];

#define loadingPalLen 32
extern const unsigned short loadingPal[16];

#endif // GRIT_LOADING_H

//}}BLOCK(loading)
