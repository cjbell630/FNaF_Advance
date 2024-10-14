
//{{BLOCK(stage_bf)

//======================================================================
//
//	stage_bf, 512x256@8, 
//	+ palette 176 entries, not compressed
//	+ 700 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 64x32 
//	Total size: 352 + 44800 + 4096 = 49248
//
//	Time-stamp: 2024-10-13, 15:14:35
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_STAGE_BF_H
#define GRIT_STAGE_BF_H

#define stage_bfTilesLen 44800
extern const unsigned short stage_bfTiles[22400];

#define stage_bfMapLen 4096
extern const unsigned short stage_bfMap[2048];

#define stage_bfPalLen 352
extern const unsigned short stage_bfPal[176];

#endif // GRIT_STAGE_BF_H

//}}BLOCK(stage_bf)
