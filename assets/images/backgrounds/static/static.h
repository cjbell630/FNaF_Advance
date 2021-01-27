
//{{BLOCK(static)

//======================================================================
//
//	static, 128x128@8, 
//	+ palette 256 entries, not compressed
//	+ 146 tiles (t|f|p reduced) not compressed
//	+ affine map, not compressed, 16x16 
//	Total size: 512 + 9344 + 256 = 10112
//
//	Time-stamp: 2021-01-26, 20:20:39
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_STATIC_H
#define GRIT_STATIC_H

#define staticTilesLen 9344
extern const unsigned short staticTiles[4672];

#define staticMapLen 256
extern const unsigned short staticMap[128];

#define staticPalLen 512
extern const unsigned short staticPal[256];

#endif // GRIT_STATIC_H

//}}BLOCK(static)
