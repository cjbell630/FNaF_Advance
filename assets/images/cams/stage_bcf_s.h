
//{{BLOCK(stage_bcf_s)

//======================================================================
//
//	stage_bcf_s, 512x256@4, 
//	+ palette 16 entries, not compressed
//	+ 719 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 64x32 
//	Total size: 32 + 23008 + 4096 = 27136
//
//	Time-stamp: 2021-01-22, 18:54:23
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_STAGE_BCF_S_H
#define GRIT_STAGE_BCF_S_H

#define stage_bcf_sTilesLen 23008
extern const unsigned short stage_bcf_sTiles[11504];

#define stage_bcf_sMapLen 4096
extern const unsigned short stage_bcf_sMap[2048];

#define stage_bcf_sPalLen 32
extern const unsigned short stage_bcf_sPal[16];

#endif // GRIT_STAGE_BCF_S_H

//}}BLOCK(stage_bcf_s)
