
//{{BLOCK(stage_empty)

//======================================================================
//
//	stage_empty, 512x256@4, 
//	+ palette 16 entries, not compressed
//	+ 816 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 64x32 
//	Total size: 32 + 26112 + 4096 = 30240
//
//	Time-stamp: 2021-01-22, 17:52:35
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_STAGE_EMPTY_H
#define GRIT_STAGE_EMPTY_H

#define stage_emptyTilesLen 26112
extern const unsigned short stage_emptyTiles[13056];

#define stage_emptyMapLen 4096
extern const unsigned short stage_emptyMap[2048];

#define stage_emptyPalLen 32
extern const unsigned short stage_emptyPal[16];

#endif // GRIT_STAGE_EMPTY_H

//}}BLOCK(stage_empty)
