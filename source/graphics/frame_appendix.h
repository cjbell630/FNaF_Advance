#ifndef FNAF_ADVANCE_FRAME_APPENDIX_H
#define FNAF_ADVANCE_FRAME_APPENDIX_H

#include <tonc_types.h>

typedef struct FrameBlock{
    u16 starting_index;
    u16 size;
    TILE *tiles;
} FrameBlock;

typedef struct FrameAppendix {
    u16 length;
    FrameBlock *frame_blocks[];
} FrameAppendix;

void load_frameblocks_into_base_mem(u16 length, struct FrameBlock *frameblocks);
extern const struct FrameBlock *broo_frameblocks[1];
#define broo_frameblocks_length 1



#endif //FNAF_ADVANCE_FRAME_APPENDIX_H
