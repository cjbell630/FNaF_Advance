
//{{BLOCK(stage_bcf)

//======================================================================
//
//	stage_bcf, 512x256@8, 
//	+ palette 256 entries, not compressed
//	+ 755 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 64x32 
//	Total size: 512 + 48320 + 4096 = 52928
//
//	Time-stamp: 2024-09-08, 22:29:01
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_STAGE_BCF_H
#define GRIT_STAGE_BCF_H

#define stage_bcfTilesLen 48320
extern const unsigned short stage_bcfTiles[24160];

#define stage_bcfMapLen 4096
extern const unsigned short stage_bcfMap[2048];

#define stage_bcfPalLen 512
extern const unsigned short stage_bcfPal[256];

#endif // GRIT_STAGE_BCF_H

//}}BLOCK(stage_bcf)
