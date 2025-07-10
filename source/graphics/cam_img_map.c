#include "cam_img_map.h"

/* PLACEHOLDER IMG DATA */
#include "images/cams/placeholder/bcff_placeholder.h"

/* STAGE IMG DATA */
#include "images/cams/stage/stage_empty.h"
#include "images/cams/stage/stage_bcf.h"
#include "images/cams/stage/stage_bf.h"
#include "images/cams/stage/stage_cf.h"
#include "images/cams/stage/stage_f.h"
#include "images/cams/stage/stage_f_s.h"

/* BACKSTAGE IMG DATA */
#include "images/cams/backstage/backstage_empty.h"
#include "images/cams/backstage/backstage_empty_s.h"
#include "images/cams/backstage/backstage_bonnie.h"
#include "images/cams/backstage/backstage_bonnie_s.h"

/* PIRATE IMG DATA */
#include "images/cams/pirate/pirate_empty.h"
#include "images/cams/pirate/pirate_empty_s.h"
#include "images/cams/pirate/pirate_foxy_0.h"
#include "images/cams/pirate/pirate_foxy_1.h"
#include "images/cams/pirate/pirate_foxy_2.h"

/* DINING IMG DATA */
#include "images/cams/dining/dining_empty.h"
#include "images/cams/dining/dining_f.h"
#include "images/cams/dining/dining_b.h"
#include "images/cams/dining/dining_b_s.h"
#include "images/cams/dining/dining_c.h"
#include "images/cams/dining/dining_c_s.h"

/* EAST HALL IMG DATA */
#include  "images/cams/east/east_empty.h"
#include  "images/cams/east/east_empty_s0.h"
#include  "images/cams/east/east_empty_s1.h"
#include  "images/cams/east/east_freddy.h"
#include  "images/cams/east/east_chica.h"
#include  "images/cams/east/east_chica_s.h"


#include "game/room_names.h"
#include "components/spooky_effects.h"
#include "components/animatronics.h"
#include "images/cams/closet/closet_empty.h"
#include "images/cams/closet/closet_b.h"
#include "images/cams/restroom/restrooms_c_s.h"
#include "images/cams/restroom/restrooms_c.h"
#include "images/cams/restroom/restrooms_fr.h"
#include "images/cams/restroom/restrooms_empty.h"
// 0  0  0  0
// Fo C  B  Fr

const Frame CAM_IMG_MAP[12][16][5] = {
        { /* STAGE (0) */
                { // Empty
                        { // Std
                                &stage_emptyTiles, stage_emptyTilesLen,
                                &stage_emptyPal, stage_emptyPalLen,
                                &stage_emptyMap, stage_emptyMapLen
                        }
                },
                { // Freddy
                        { // Std
                                &stage_fTiles, stage_fTilesLen,
                                &stage_fPal, stage_fPalLen,
                                &stage_fMap, stage_fMapLen
                        },
                        { // Staring at cam
                                &stage_f_sTiles, stage_f_sTilesLen,
                                &stage_f_sPal, stage_f_sPalLen,
                                &stage_f_sMap, stage_f_sMapLen
                        }
                },
                { /* Bonnie */ },
                { // Bonnie Freddy
                        { // Std
                                &stage_bfTiles, stage_bfTilesLen,
                                &stage_bfPal, stage_bfPalLen,
                                &stage_bfMap, stage_bfMapLen
                        }
                },
                { /* Chica */ },
                { // Chica Freddy
                        { // Std
                                &stage_cfTiles, stage_cfTilesLen,
                                &stage_cfPal, stage_cfPalLen,
                                &stage_cfMap, stage_cfMapLen
                        }
                },
                { /* Chica Bonnie */ },
                { // Chica Bonnie Freddy
                        { // Std
                                &stage_bcfTiles, stage_bcfTilesLen,
                                &stage_bcfPal, stage_bcfPalLen,
                                &stage_bcfMap, stage_bcfMapLen
                        }
                }
        },
        { /* Dining Area (1) */
                { // Empty
                        { // Std
                                &dining_emptyTiles, dining_emptyTilesLen,
                                &dining_emptyPal, dining_emptyPalLen,
                                &dining_emptyMap, dining_emptyMapLen
                        }
                },
                { // Freddy
                        { // Std
                                &dining_fTiles, dining_fTilesLen,
                                &dining_fPal, dining_fPalLen,
                                &dining_fMap, dining_fMapLen
                        }
                },
                { // Bonnie
                        { // Far
                                &dining_bTiles, dining_bTilesLen,
                                &dining_bPal, dining_bPalLen,
                                &dining_bMap, dining_bMapLen
                        },
                        { // Close
                                &dining_b_sTiles, dining_b_sTilesLen,
                                &dining_b_sPal, dining_b_sPalLen,
                                &dining_b_sMap, dining_b_sMapLen
                        }
                },
                { /* Freddy Bonnie */ },
                { // Chica
                        { // Far
                                &dining_cTiles, dining_cTilesLen,
                                &dining_cPal, dining_cPalLen,
                                &dining_cMap, dining_cMapLen
                        },
                        { // Close
                                &dining_c_sTiles, dining_c_sTilesLen,
                                &dining_c_sPal, dining_c_sPalLen,
                                &dining_c_sMap, dining_c_sMapLen
                        }
                }
        },
        { /* Pirate's Cove (2) */
                { // Empty
                        { // Std
                                &pirate_emptyTiles, pirate_emptyTilesLen,
                                &pirate_emptyPal, pirate_emptyPalLen,
                                &pirate_emptyMap, pirate_emptyMapLen
                        },
                        { // it's me
                                &pirate_empty_sTiles, pirate_empty_sTilesLen,
                                &pirate_empty_sPal, pirate_empty_sPalLen,
                                &pirate_empty_sMap, pirate_empty_sMapLen
                        }
                },
                { /* Freddy */ },{ /* Bonnie */ },{ /* Freddy Bonnie */ },{ /* Chica */ },
                { /* Chica Freddy */ },{ /* Chica Bonnie */ },{ /* Chica Bonnie Freddy */ },
                { // Foxy
                        { // Hiding
                                &pirate_foxy_0Tiles, pirate_foxy_0TilesLen,
                                &pirate_foxy_0Pal, pirate_foxy_0PalLen,
                                &pirate_foxy_0Map, pirate_foxy_0MapLen
                        },
                        { // Peeking
                                &pirate_foxy_1Tiles, pirate_foxy_1TilesLen,
                                &pirate_foxy_1Pal, pirate_foxy_1PalLen,
                                &pirate_foxy_1Map, pirate_foxy_1MapLen
                        },
                        { // Out
                                &pirate_foxy_2Tiles, pirate_foxy_2TilesLen,
                                &pirate_foxy_2Pal, pirate_foxy_2PalLen,
                                &pirate_foxy_2Map, pirate_foxy_2MapLen
                        }
                }
        },
        { /* West Hall A (3) */
                { // Empty
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &empty_placeholderPal, empty_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }
                },
                { /* Freddy */ },
                { // Bonnie
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &b_placeholderPal, b_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }
                },
                { /* Freddy Bonnie */ },{ /* Chica */ },
                { /* Chica Freddy */ },{ /* Chica Bonnie */ },{ /* Chica Bonnie Freddy */ },
                { // Foxy
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &fo_placeholderPal, fo_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }
                }
        },
        {/* West Hall B (Corner) (4) */
                { //Empty
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &empty_placeholderPal, empty_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }
                },
                { /*Freddy*/ },
                { //Bonnie
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &b_placeholderPal, b_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }
                }
        },
        {/* Supply Closet (5) */
                { //Empty
                        { // Std
                                &closet_emptyTiles, closet_emptyTilesLen,
                                &closet_emptyPal, closet_emptyPalLen,
                                &closet_emptyMap, closet_emptyMapLen
                        }
                },
                { /* Freddy */ },
                { //Bonnie
                        { // Std
                                &closet_bTiles, closet_bTilesLen,
                                &closet_bPal, closet_bPalLen,
                                &closet_bMap, closet_bMapLen
                        }
                }
        },
        {/* East Hall A (6) */
                { // Empty
                        { // Std
                                &east_emptyTiles, east_emptyTilesLen,
                                &east_emptyPal, east_emptyPalLen,
                                &east_emptyMap, east_emptyMapLen
                        },
                        { // Crying children poster
                                &east_empty_s0Tiles, east_empty_s0TilesLen,
                                &east_empty_s0Pal, east_empty_s0PalLen,
                                &east_empty_s0Map, east_empty_s0MapLen
                        },
                        { // it's me
                                &east_empty_s1Tiles, east_empty_s1TilesLen,
                                &east_empty_s1Pal, east_empty_s1PalLen,
                                &east_empty_s1Map, east_empty_s1MapLen
                        }
                },
                { // Freddy
                        { // Std 
                                &east_freddyTiles, east_freddyTilesLen,
                                &east_freddyPal, east_freddyPalLen,
                                &east_freddyMap, east_freddyMapLen
                        }
                },
                { /* Bonnie */ },{ /* Freddy Bonnie */ },
                { //Chica
                        { // Far
                                &east_chicaTiles, east_chicaTilesLen,
                                &east_chicaPal, east_chicaPalLen,
                                &east_chicaMap, east_chicaMapLen
                        },
                        { // Close
                                &east_chica_sTiles, east_chica_sTilesLen,
                                &east_chica_sPal, east_chica_sPalLen,
                                &east_chica_sMap, east_chica_sMapLen
                        }
                }
        },
        {/*East Hall B (Corner) (7)*/
                { //Empty
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &empty_placeholderPal, empty_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }
                },
                { // Freddy
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &fr_placeholderPal, fr_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }
                },
                { /* Bonnie */ },{ /* Freddy Bonnie */ },
                { // Chica
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &c_placeholderPal, c_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }
                }
        },
        {/* Backstage (8) */
                { //Empty
                        { // Std
                                &backstage_emptyTiles, backstage_emptyTilesLen,
                                &backstage_emptyPal, backstage_emptyPalLen,
                                &backstage_emptyMap, backstage_emptyMapLen
                        },
                        { // Suits facing camera
                                &backstage_empty_sTiles, backstage_empty_sTilesLen,
                                &backstage_empty_sPal, backstage_empty_sPalLen,
                                &backstage_empty_sMap, backstage_empty_sMapLen
                        }
                },
                { /*Freddy*/ },
                { // Bonnie
                        { // Std
                                &backstage_bonnieTiles, backstage_bonnieTilesLen,
                                &backstage_bonniePal, backstage_bonniePalLen,
                                &backstage_bonnieMap, backstage_bonnieMapLen
                        },
                        { // Bonnie staring into camera
                                &backstage_bonnie_sTiles, backstage_bonnie_sTilesLen,
                                &backstage_bonnie_sPal, backstage_bonnie_sPalLen,
                                &backstage_bonnie_sMap, backstage_bonnie_sMapLen
                        }
                }
        },
        {/* Kitchen (9) */
                { //Empty
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &empty_placeholderPal, empty_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }
                },
                { //Freddy
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &fr_placeholderPal, fr_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }
                },
                { /* Bonnie */ },{ /* Freddy Bonnie */ },
                { // Chica
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &c_placeholderPal, c_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }
                }
        },
        {/*Restrooms (10)*/
                { //Empty
                        { // Std
                                &restrooms_emptyTiles, restrooms_emptyTilesLen,
                                &restrooms_emptyPal, restrooms_emptyPalLen,
                                &restrooms_emptyMap, restrooms_emptyMapLen
                        }
                },
                { //Freddy
                        { // Std
                                &restrooms_frTiles, restrooms_frTilesLen,
                                &restrooms_frPal, restrooms_frPalLen,
                                &restrooms_frMap, restrooms_frMapLen
                        }
                },
                { /* Bonnie */ },{ /* Freddy Bonnie */ },
                { // Chica
                        { // Std
                                &restrooms_cTiles, restrooms_cTilesLen,
                                &restrooms_cPal, restrooms_cPalLen,
                                &restrooms_cMap, restrooms_cMapLen
                        },
                        { // Close up
                                &restrooms_c_sTiles, restrooms_c_sTilesLen,
                                &restrooms_c_sPal, restrooms_c_sPalLen,
                                &restrooms_c_sMap, restrooms_c_sMapLen
                        }
                }
        }
};



// when multiple animatronics are in the same room (excluding the stage), the display order is:
// Foxy > Chica > Bonnie > Freddy
Frame get_cam_img_data(enum RoomNames room) {
    u8 occupants = Animatronics.get_room_occupants(room);
    // if the room is not stage and there are multiple animatronics in room
    if ((occupants & (occupants - 1)) && (room != ROOM_STAGE)) {
        occupants = (occupants > 0b1000) ?  0b1000: // Foxy in room
                (occupants > 0b0100) ? 0b0100 : // Chica in room
                0b0010; // Bonnie in room
        // TODO might cause issues for foxy in west hall
    }
    return CAM_IMG_MAP[room][occupants][SpookyEffects.get_effects(room)];
}