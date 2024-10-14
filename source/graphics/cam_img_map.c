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


#include "game/room_names.h"
#include "components/spooky_effects.h"
#include "components/animatronics.h"

const Frame CAM_IMG_MAP[12][16][5] = {
        { /* STAGE (0) */
                { // Empty
                        { // Std
                                &stage_emptyTiles, stage_emptyTilesLen,
                                &stage_emptyPal, stage_emptyPalLen,
                                &stage_emptyMap, stage_emptyMapLen
                        }
                },
                { /* Foxy */ },
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
                { /* Freddy Foxy */ }, { /* Chica */ }, { /* Chica Foxy */ },
                { // Chica Freddy
                        { // Std
                                &stage_cfTiles, stage_cfTilesLen,
                                &stage_cfPal, stage_cfPalLen,
                                &stage_cfMap, stage_cfMapLen
                        }
                },
                { /* Chica Freddy Foxy */ }, { /* Bonnie */ }, { /* Bonnie Foxy */ },
                { // Bonnie Freddy
                        { // Std
                                &stage_bfTiles, stage_bfTilesLen,
                                &stage_bfPal, stage_bfPalLen,
                                &stage_bfMap, stage_bfMapLen
                        }
                },
                { /* Bonnie Freddy Foxy */ }, { /* Bonnie Chica */ }, { /* Bonnie Chica Foxy */ },
                { // Bonnie Chica Freddy
                        { // Std
                                &stage_bcfTiles, stage_bcfTilesLen,
                                &stage_bcfPal, stage_bcfPalLen,
                                &stage_bcfMap, stage_bcfMapLen
                        }
                }
        },
        { /* Dining Area (1) */
                { // Empty
                        { // Std // TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &empty_placeholderPal, empty_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }
                },
                { /* Foxy */ },
                { // Freddy
                        { // Std // TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &fr_placeholderPal, fr_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }
                },
                { /* Freddy Foxy */ },
                { // Chica
                        { // Std // TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &c_placeholderPal, c_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }
                },
                { /* Chica Foxy */ },
                { /* Chica Freddy */ },
                { /* Chica Freddy Foxy */ },
                { // Bonnie
                        { // Std // TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &b_placeholderPal, b_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }
                }
        },
        {/*Pirate's Cove (2)*/
                { //Empty
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &empty_placeholderPal, empty_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }
                },
                { //Foxy
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &fo_placeholderPal, fo_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }
                }
        },
        {/*West Hall A (3)*/
                { //Empty
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &empty_placeholderPal, empty_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }
                },
                { //Foxy
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &fo_placeholderPal, fo_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }
                },
                { /*Freddy*/ }, { /*Freddy Foxy*/}, { /*Chica*/}, { /*Chica Foxy*/},
                { /*Chica Freddy*/}, { /*Chica Freddy Foxy*/},
                { //Bonnie
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &b_placeholderPal, b_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }
                }
        },
        {/*West Hall B (Corner) (4)*/
                { //Empty
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &empty_placeholderPal, empty_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }
                },
                { /*Foxy*/}, { /*Freddy*/ }, { /*Freddy Foxy*/}, { /*Chica*/}, { /*Chica Foxy*/},
                { /*Chica Freddy*/}, { /*Chica Freddy Foxy*/},
                { //Bonnie
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &b_placeholderPal, b_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }
                }
        },
        {/*Supply Closet (5)*/
                { //Empty
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &empty_placeholderPal, empty_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }
                },
                { /*Foxy*/}, { /*Freddy*/ }, { /*Freddy Foxy*/}, { /*Chica*/},
                { /*Chica Foxy*/}, { /*Chica Freddy*/}, { /*Chica Freddy Foxy*/},
                { //Bonnie
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &b_placeholderPal, b_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }
                }
        },
        {/*East Hall A (6)*/
                { //Empty
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &empty_placeholderPal, empty_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }
                },
                { /*Foxy*/},
                { //Freddy
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &fr_placeholderPal, fr_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }
                },
                { /*Freddy Foxy*/},
                { //Chica
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &c_placeholderPal, c_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
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
                { /*Foxy*/},
                { //Freddy
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &fr_placeholderPal, fr_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }
                },
                { /*Freddy Foxy*/},
                { //Chica
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &c_placeholderPal, c_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }
                }
        },
        {/*Backstage (8)*/
                { //Empty
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &empty_placeholderPal, empty_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }
                },
                { /*Foxy*/}, { /*Freddy*/ }, { /*Freddy Foxy*/}, { /*Chica*/}, { /*Chica Foxy*/},
                { /*Chica Freddy*/}, { /*Chica Freddy Foxy*/},
                { //Bonnie
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &b_placeholderPal, b_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }
                }
        },
        {/*Kitchen (9)*/
                { //Empty
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &empty_placeholderPal, empty_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }
                },
                { /*Foxy*/},
                { //Freddy
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &fr_placeholderPal, fr_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }
                },
                { /*Freddy Foxy*/},
                { //Chica
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &c_placeholderPal, c_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }
                }
        },
        {/*Restrooms (10)*/
                { //Empty
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &empty_placeholderPal, empty_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }
                },
                { /*Foxy*/},
                { //Freddy
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &fr_placeholderPal, fr_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }
                },
                { /*Freddy Foxy*/},
                { //Chica
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &c_placeholderPal, c_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
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
        occupants = (occupants & 1) ? 1 : // Foxy in room
                (occupants & (1 << 2)) ? 4 : // Chica in room
                (occupants & (1 << 3)) ? 8 : // Bonnie in room
                2; // Freddy in room
        // TODO might cause issues for foxy in west hall
    }
    return CAM_IMG_MAP[room][occupants][SpookyEffects.get_effects(room)];
}