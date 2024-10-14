
//{{BLOCK(stage_empty)

//======================================================================
//
//	stage_empty, 512x256@8, 
//	+ palette 73 entries, not compressed
//	+ 256 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 64x32 
//	Total size: 146 + 16384 + 4096 = 20626
//
//	Time-stamp: 2024-10-13, 15:11:13
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_STAGE_EMPTY_H
#define GRIT_STAGE_EMPTY_H

#define stage_emptyTilesLen 16384
extern const unsigned short stage_emptyTiles[8192];

#define stage_emptyMapLen 4096
extern const unsigned short stage_emptyMap[2048];

#define stage_emptyPalLen 146
extern const unsigned short stage_emptyPal[74];

#endif // GRIT_STAGE_EMPTY_H

//}}BLOCK(stage_empty)
