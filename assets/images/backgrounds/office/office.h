
//{{BLOCK(office)

//======================================================================
//
//	office, 512x256@4, 
//	+ palette 16 entries, not compressed
//	+ 501 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 64x32 
//	Total size: 32 + 16032 + 4096 = 20160
//
//	Time-stamp: 2021-01-22, 17:03:03
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_OFFICE_H
#define GRIT_OFFICE_H

#define officeTilesLen 16032
extern const unsigned short officeTiles[8016];

#define officeMapLen 4096
extern const unsigned short officeMap[2048];

#define officePalLen 32
extern const unsigned short officePal[16];

#endif // GRIT_OFFICE_H

//}}BLOCK(office)
