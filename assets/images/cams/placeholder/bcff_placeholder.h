
//{{BLOCK(bcff_placeholder)

//======================================================================
//
//	bcff_placeholder, 512x256@4, 
//	+ palette 16 entries, not compressed
//	+ 282 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 64x32 
//	Total size: 32 + 9024 + 4096 = 13152
//
//	Time-stamp: 2021-01-27, 11:48:14
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_BCFF_PLACEHOLDER_H
#define GRIT_BCFF_PLACEHOLDER_H

#define bcff_placeholderTilesLen 9024
extern const unsigned short bcff_placeholderTiles[4512];

#define bcff_placeholderMapLen 4096
extern const unsigned short bcff_placeholderMap[2048];

#define bcff_placeholderPalLen 32
extern const unsigned short bcff_placeholderPal[16];

#endif // GRIT_BCFF_PLACEHOLDER_H

//}}BLOCK(bcff_placeholder)
