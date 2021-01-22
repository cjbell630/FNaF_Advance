
//{{BLOCK(office)

//======================================================================
//
//	office, 512x512@4, 
//	+ palette 16 entries, not compressed
//	+ 512 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 64x64 
//	Total size: 32 + 16384 + 8192 = 24608
//
//	Time-stamp: 2021-01-22, 00:47:36
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_OFFICE_H
#define GRIT_OFFICE_H

#define officeTilesLen 16384
extern const unsigned short officeTiles[8192];

#define officeMapLen 8192
extern const unsigned short officeMap[4096];

#define officePalLen 32
extern const unsigned short officePal[16];

#endif // GRIT_OFFICE_H

//}}BLOCK(office)
