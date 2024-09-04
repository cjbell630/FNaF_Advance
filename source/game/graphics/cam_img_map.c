#include "cam_img_map.h"

#include "images/backgrounds/error/error.h"
#include "images/cams/stage_empty.h"
#include "images/cams/stage_bcf_s.h"

#include "images/cams/placeholder/b_placeholder.h"
#include "images/cams/placeholder/bcf_placeholder.h"
#include "images/cams/placeholder/bcff_placeholder.h"
#include "images/cams/placeholder/bf_placeholder.h"
#include "images/cams/placeholder/c_placeholder.h"
#include "images/cams/placeholder/cf_placeholder.h"
#include "images/cams/placeholder/fo_placeholder.h"
#include "images/cams/placeholder/fr_placeholder.h"
#include "images/cams/placeholder/empty_placeholder.h"
#include "game/control/cameras/room_names.h"
#include "game/control/cameras/spooky_effects.h"
#include "game/control/ai/ai.h"


CAM_IMG_DATA get_cam_img_data(enum RoomNames room) {
    return CAM_IMG_MAP[room][Animatronics.get_room_occupants(room)][SpookyEffects.get_effects(room)];
}

const CAM_IMG_DATA CAM_IMG_MAP[12][16][2] = {
        { /* STAGE (0) */
                { // Empty
                        { // Std
                                &stage_emptyTiles,      stage_emptyTilesLen,
                                &stage_emptyPal,       stage_emptyPalLen,
                                &stage_emptyMap,      stage_emptyMapLen
                        }
                },
                { /*Foxy*/},
                { //Freddy
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &fr_placeholderPal, fr_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Freddy Foxy*/},
                { /*Chica*/},
                { /*Chica Foxy*/},
                { //Chica Freddy
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &cf_placeholderPal, cf_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Chica Freddy Foxy*/},
                { /*Bonnie*/},
                { /*Bonnie Foxy*/},
                { // Bonnie Freddy
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &bf_placeholderPal, bf_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Bonnie Freddy Foxy*/},
                { /*Bonnie Chica*/},
                { /*Bonnie Chica Foxy*/},
                { // Bonnie Chica Freddy
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &bcf_placeholderPal, bcf_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        },
                        { // Spec
                                &stage_bcf_sTiles, stage_bcf_sTilesLen,
                                &stage_bcf_sPal, stage_bcf_sPalLen,
                                &stage_bcf_sMap, stage_bcf_sMapLen
                        },
                }
        },
        {/*Dining Area (1)*/
                { //Empty
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &empty_placeholderPal, empty_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Foxy*/},
                { //Freddy
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &fr_placeholderPal, fr_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Freddy Foxy*/},
                { //Chica
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &c_placeholderPal, c_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Chica Foxy*/},
                { /*Chica Freddy*/},
                { /*Chica Freddy Foxy*/},
                { //Bonnie
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &b_placeholderPal, b_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Bonnie Foxy*/},
                { /*Bonnie Freddy*/},
                { /*Bonnie Freddy Foxy*/},
                { /*Bonnie Chica*/},
                { /*Bonnie Chica Foxy*/},
                { /*Bonnie Chica Freddy*/},
                { /*Bonnie Chica Freddy Foxy*/}
        },
        {/*Pirate's Cove (2)*/
                { //Empty
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &empty_placeholderPal, empty_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { //Foxy
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &fo_placeholderPal, fo_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Freddy*/ },
                { /*Freddy Foxy*/},
                { /*Chica*/},
                { /*Chica Foxy*/},
                { /*Chica Freddy*/},
                { /*Chica Freddy Foxy*/},
                { /*Bonnie*/},
                { /*Bonnie Foxy*/},
                { /*Bonnie Freddy*/},
                { /*Bonnie Freddy Foxy*/},
                { /*Bonnie Chica*/},
                { /*Bonnie Chica Foxy*/},
                { /*Bonnie Chica Freddy*/},
                { /*Bonnie Chica Freddy Foxy*/}
        },
        {/*West Hall A (3)*/
                { //Empty
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &empty_placeholderPal, empty_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { //Foxy
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &fo_placeholderPal, fo_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Freddy*/ },
                { /*Freddy Foxy*/},
                { /*Chica*/},
                { /*Chica Foxy*/},
                { /*Chica Freddy*/},
                { /*Chica Freddy Foxy*/},
                { //Bonnie
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &b_placeholderPal, b_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Bonnie Foxy*/},
                { /*Bonnie Freddy*/},
                { /*Bonnie Freddy Foxy*/},
                { /*Bonnie Chica*/},
                { /*Bonnie Chica Foxy*/},
                { /*Bonnie Chica Freddy*/},
                { /*Bonnie Chica Freddy Foxy*/}
        },
        {/*West Hall B (Corner) (4)*/
                { //Empty
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &empty_placeholderPal, empty_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Foxy*/},
                { /*Freddy*/ },
                { /*Freddy Foxy*/},
                { /*Chica*/},
                { /*Chica Foxy*/},
                { /*Chica Freddy*/},
                { /*Chica Freddy Foxy*/},
                { //Bonnie
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &b_placeholderPal, b_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Bonnie Foxy*/},
                { /*Bonnie Freddy*/},
                { /*Bonnie Freddy Foxy*/},
                { /*Bonnie Chica*/},
                { /*Bonnie Chica Foxy*/},
                { /*Bonnie Chica Freddy*/},
                { /*Bonnie Chica Freddy Foxy*/}
        },
        {/*Supply Closet (5)*/
                { //Empty
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &empty_placeholderPal, empty_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Foxy*/},
                { /*Freddy*/ },
                { /*Freddy Foxy*/},
                { /*Chica*/},
                { /*Chica Foxy*/},
                { /*Chica Freddy*/},
                { /*Chica Freddy Foxy*/},
                { //Bonnie
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &b_placeholderPal, b_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Bonnie Foxy*/},
                { /*Bonnie Freddy*/},
                { /*Bonnie Freddy Foxy*/},
                { /*Bonnie Chica*/},
                { /*Bonnie Chica Foxy*/},
                { /*Bonnie Chica Freddy*/},
                { /*Bonnie Chica Freddy Foxy*/}
        },
        {/*East Hall A (6)*/
                { //Empty
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &empty_placeholderPal, empty_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Foxy*/},
                { //Freddy
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &fr_placeholderPal, fr_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Freddy Foxy*/},
                { //Chica
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &c_placeholderPal, c_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Chica Foxy*/},
                { /*Chica Freddy*/},
                { /*Chica Freddy Foxy*/},
                { /*Bonnie*/},
                { /*Bonnie Foxy*/},
                { /*Bonnie Freddy*/},
                { /*Bonnie Freddy Foxy*/},
                { /*Bonnie Chica*/},
                { /*Bonnie Chica Foxy*/},
                { /*Bonnie Chica Freddy*/},
                { /*Bonnie Chica Freddy Foxy*/}
        },
        {/*East Hall B (Corner) (7)*/
                { //Empty
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &empty_placeholderPal, empty_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Foxy*/},
                { //Freddy
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &fr_placeholderPal, fr_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Freddy Foxy*/},
                { //Chica
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &c_placeholderPal, c_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Chica Foxy*/},
                { /*Chica Freddy*/},
                { /*Chica Freddy Foxy*/},
                { /*Bonnie*/},
                { /*Bonnie Foxy*/},
                { /*Bonnie Freddy*/},
                { /*Bonnie Freddy Foxy*/},
                { /*Bonnie Chica*/},
                { /*Bonnie Chica Foxy*/},
                { /*Bonnie Chica Freddy*/},
                { /*Bonnie Chica Freddy Foxy*/}
        },
        {/*Backstage (8)*/
                { //Empty
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &empty_placeholderPal, empty_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Foxy*/},
                { /*Freddy*/ },
                { /*Freddy Foxy*/},
                { /*Chica*/},
                { /*Chica Foxy*/},
                { /*Chica Freddy*/},
                { /*Chica Freddy Foxy*/},
                { //Bonnie
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &b_placeholderPal, b_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Bonnie Foxy*/},
                { /*Bonnie Freddy*/},
                { /*Bonnie Freddy Foxy*/},
                { /*Bonnie Chica*/},
                { /*Bonnie Chica Foxy*/},
                { /*Bonnie Chica Freddy*/},
                { /*Bonnie Chica Freddy Foxy*/}
        },
        {/*Kitchen (9)*/
                { //Empty
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &empty_placeholderPal, empty_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Foxy*/},
                { //Freddy
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &fr_placeholderPal, fr_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Freddy Foxy*/},
                { //Chica
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &c_placeholderPal, c_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Chica Foxy*/},
                { /*Chica Freddy*/},
                { /*Chica Freddy Foxy*/},
                { /*Bonnie*/},
                { /*Bonnie Foxy*/},
                { /*Bonnie Freddy*/},
                { /*Bonnie Freddy Foxy*/},
                { /*Bonnie Chica*/},
                { /*Bonnie Chica Foxy*/},
                { /*Bonnie Chica Freddy*/},
                { /*Bonnie Chica Freddy Foxy*/}
        },
        {/*Restrooms (10)*/
                { //Empty
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &empty_placeholderPal, empty_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Foxy*/},
                { //Freddy
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &fr_placeholderPal, fr_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Freddy Foxy*/},
                { //Chica
                        { // Std //TODO: remove
                                &bcff_placeholderTiles, bcff_placeholderTilesLen,
                                &c_placeholderPal, c_placeholderPalLen,
                                &bcff_placeholderMap, bcff_placeholderMapLen
                        }},
                { /*Chica Foxy*/},
                { /*Chica Freddy*/},
                { /*Chica Freddy Foxy*/},
                { /*Bonnie*/},
                { /*Bonnie Foxy*/},
                { /*Bonnie Freddy*/},
                { /*Bonnie Freddy Foxy*/},
                { /*Bonnie Chica*/},
                { /*Bonnie Chica Foxy*/},
                { /*Bonnie Chica Freddy*/},
                { /*Bonnie Chica Freddy Foxy*/}
        }
};