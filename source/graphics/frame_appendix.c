#include <tonc_core.h>
#include <stdio.h>
#include "frame_appendix.h"
#include "DWedit/debug.h"

void load_frameblocks_into_base_mem(u16 length, struct FrameBlock *frameblocks){
    for(u16 i = 0; i<length; i++){
        char *buff[128];
        sprintf(buff, " index: %d, starting index: %d, size %d\n",i,frameblocks[i].starting_index, frameblocks[i].size);
        vbaprint(buff);
        dma3_cpy(&tile8_mem[0][frameblocks[i].starting_index], frameblocks[i].tiles, 256);
    }
}


const unsigned short broo_append0_0[32] __attribute__((aligned(4))) = {0x2100, 0x0000, 0x0000, 0x0000, 0x1821, 0xC500, 0x0021, 0x2100, 0x7F0C, 0x187F, 0x4F00, 0x0010, 0x1818, 0x7F0C, 0x1800, 0x8B00, 0x7F7F, 0x7F4F, 0x007F, 0x0000, 0x0C7F, 0x007F, 0x3F18, 0x7F4F, 0x0D00, 0x7F00, 0x007F, 0x7F18, 0x760C, 0x2100, 0x0000, 0x007F};
const struct FrameBlock broo_frame_block_0_0 = {  .starting_index=35, .size=32,.tiles=&broo_append0_0[0],};
const struct FrameBlock *broo_frameblocks[1] = {&broo_frame_block_0_0};
//const struct FrameAppendix broo_frame_appendix_0 = {.frame_blocks = frameblocks, .length=28};

// write functions in each image that apply a callback function to all blocks in a frame (and delete FrameBlock and FrameAppendix)
//like do_frame_0 and undo_frame_0
// also change pixel thing to export decimal instead of hex bc it's smaller when you factor in the 0x