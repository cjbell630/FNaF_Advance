
//{{BLOCK(night)

//======================================================================
//
//	night, 256x256@8, 
//	+ palette 256 entries, not compressed
//	+ 47 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 32x32 
//	Total size: 512 + 3008 + 2048 = 5568
//
//	Time-stamp: 2026-11-21, 13:30:16
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_NIGHT_H
#define GRIT_NIGHT_H

#define nightTilesLen 3008
extern const unsigned short nightTiles[1504];

#define nightMapLen 2048
extern const unsigned short nightMap[1024];

#define nightPalLen 512
extern const unsigned short nightPal[256];

#endif // GRIT_NIGHT_H

//}}BLOCK(night)
