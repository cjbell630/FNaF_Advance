#include "cam_img_map.h"

#include "images/backgrounds/error/error.h"
#include "images/cams/stage_empty.h"
#include "images/cams/stage_bcf_s.h"
#include "images/cams/stage_bcf.h"

#include "images/cams/placeholder/bcff_placeholder.h"
#include "game/room_names.h"
#include "components/spooky_effects.h"
#include "components/animatronics.h"


Frame get_cam_img_data(enum RoomNames room) {
    return CAM_IMG_MAP[room][Animatronics.get_room_occupants(room)][SpookyEffects.get_effects(room)];
}

const Frame CAM_IMG_MAP[12][16][32] = {
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
                                &stage_bcfTiles, stage_bcfTilesLen,
                                &stage_bcfPal, stage_bcfPalLen,
                                &stage_bcfMap, stage_bcfMapLen
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