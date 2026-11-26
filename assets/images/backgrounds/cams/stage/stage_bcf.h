
//{{BLOCK(stage_bcf)

//======================================================================
//
//	stage_bcf, 512x256@8, 
//	+ palette 204 entries, not compressed
//	+ 752 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 64x32 
//	Total size: 408 + 48128 + 4096 = 52632
//
//	Time-stamp: 2024-10-13, 15:44:31
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_STAGE_BCF_H
#define GRIT_STAGE_BCF_H

#define stage_bcfTilesLen 48128
extern const unsigned short stage_bcfTiles[24064];

#define stage_bcfMapLen 4096
extern const unsigned short stage_bcfMap[2048];

#define stage_bcfPalLen 408
extern const unsigned short stage_bcfPal[204];

#endif // GRIT_STAGE_BCF_H

//}}BLOCK(stage_bcf)
