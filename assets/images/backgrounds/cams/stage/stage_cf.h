
//{{BLOCK(stage_cf)

//======================================================================
//
//	stage_cf, 512x256@8, 
//	+ palette 202 entries, not compressed
//	+ 573 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 64x32 
//	Total size: 404 + 36672 + 4096 = 41172
//
//	Time-stamp: 2024-10-14, 18:36:51
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_STAGE_CF_H
#define GRIT_STAGE_CF_H

#define stage_cfTilesLen 36672
extern const unsigned short stage_cfTiles[18336];

#define stage_cfMapLen 4096
extern const unsigned short stage_cfMap[2048];

#define stage_cfPalLen 404
extern const unsigned short stage_cfPal[202];

#endif // GRIT_STAGE_CF_H

//}}BLOCK(stage_cf)
