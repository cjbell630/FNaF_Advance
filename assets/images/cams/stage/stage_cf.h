
//{{BLOCK(stage_cf)

//======================================================================
//
//	stage_cf, 512x256@8, 
//	+ palette 200 entries, not compressed
//	+ 569 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 64x32 
//	Total size: 400 + 36416 + 4096 = 40912
//
//	Time-stamp: 2024-10-13, 15:13:45
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_STAGE_CF_H
#define GRIT_STAGE_CF_H

#define stage_cfTilesLen 36416
extern const unsigned short stage_cfTiles[18208];

#define stage_cfMapLen 4096
extern const unsigned short stage_cfMap[2048];

#define stage_cfPalLen 400
extern const unsigned short stage_cfPal[200];

#endif // GRIT_STAGE_CF_H

//}}BLOCK(stage_cf)
