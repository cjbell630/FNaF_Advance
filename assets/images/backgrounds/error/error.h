
//{{BLOCK(error)

//======================================================================
//
//	error, 256x256@4, 
//	+ palette 16 entries, not compressed
//	+ 90 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 32 + 2880 + 2048 = 4960
//
//	Time-stamp: 2021-01-22, 14:45:25
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_ERROR_H
#define GRIT_ERROR_H

#define errorTilesLen 2880
extern const unsigned short errorTiles[1440];

#define errorMapLen 2048
extern const unsigned short errorMap[1024];

#define errorPalLen 32
extern const unsigned short errorPal[16];

#endif // GRIT_ERROR_H

//}}BLOCK(error)
