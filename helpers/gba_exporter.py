from math import floor

from PIL.Image import Image

from io_util import get_lambda

def get_screenblock_index(tile_x, tile_y, screenblock_width):
    screenblock_num = int(floor(tile_y/32)) * int(floor(screenblock_width/32)) + int(floor(tile_x/32))
    return screenblock_num*1024 + (tile_y%32)*32 + (tile_x%32)

def convert_tiles(tiles:list[int]):
    # treat each entry in the list as an 8bit number, and combine it with each adjacent number to make a 16 bit number,
    # then add it to the new as a hex string
    new_tiles = []
    for i in range(0, len(tiles), 2):
        new_value = tiles[i+1] << 8 | tiles[i]
        new_tiles.append(f"0x{new_value:04X}")
    return new_tiles

def get_pixels_from_tile(tiles:list[int], tile:Image):
    for y in range(8):
        for x in range(8):
            tiles.append(tile.getpixel((x, y)))
    return tiles

def convert_palette(palette: list[int]):
    new_palette = []
    for i in range(0, len(palette), 3):
        # convert each r g b to 0,32 then combine them like this: xrrrrrgggggbbbbb
        r = palette[i] >> 3
        g = palette[i + 1] >> 3
        b = palette[i + 2] >> 3
        rgb = b << 10 | g << 5 | r
        new_palette.append(rgb)
        # print r g and b as ints and then RGB as hex
        #print(f"R: {r} G: {g} B: {b} RGB: {hex(rgb)}")
    return new_palette

def write_to_c_files(palette: list[int], tiles: list[str], tilemap: list[int], appendices: list[list[dict]]):
    img_name = get_lambda("Enter the desired image name: ", lambda x: x.isalnum())
    charblock = int(get_lambda("Enter the desired charblock: ", lambda x: x.isnumeric()))
    name_frames = input("Would you like to name the frames? (y/n): ").lower() == "y"
    append_h = ""
    with open(f"{img_name}.c", "w") as f:
        f.write(f"#include \"{img_name}.h\"\n#include \"tonc.h\"\n#include <string.h>")

        f.write(f"const unsigned short {img_name}_palette[{len(palette)}] __attribute__((aligned(4))) = {{{str(palette)[1:-1]}}};\n")
        f.write(f"const unsigned short {img_name}_tiles[{len(tiles)}] __attribute__((aligned(4))) = {{{str(tiles)[1:-1].replace("'","")}}};\n")
        f.write(f"const unsigned short {img_name}_tilemap[{len(tilemap)}] __attribute__((aligned(4))) = {{{str(tilemap)[1:-1]}}};\n")
        for frame_num, frame_append in enumerate(appendices):
            frame_name = get_lambda(f"Enter the name of frame {frame_num+1}: ", lambda x: " " not in x) if name_frames else f"frame_{frame_num+1}"

            do_func_name = f"do_{img_name}_{frame_name}"

            do_string = f"void {do_func_name}(){{\n"
            undo_string = f"void un{do_func_name}(){{\n"
            num_blocks = 0
            for block_num, block in enumerate(block for block in frame_append if len(block) != 0):
                #print(block)
                block["pixels"] = convert_tiles(block["pixels"])
                block_len = len(block["pixels"])
                block_size = 2*block_len
                f.write(f"const unsigned short {img_name}_append_{frame_name}_{block_num}[{block_len}] __attribute__((aligned(4))) = {{{str(block["pixels"])[1:-1].replace("'","")}}};\n")
                do_string += f"    memcpy(&tile_mem[{charblock}][{block['start']}], &{img_name}_append_{frame_name}_{block_num}, {block_size});\n"
                undo_string += f"    memcpy(&tile_mem[{charblock}][{block['start']}], &{img_name}_tiles[{int(block['start']*16)}], {block_size});\n"
                num_blocks += 1
            do_string += "}\n"
            undo_string += "}\n"
            f.write(do_string)
            f.write(undo_string)
            append_h += f"void {do_func_name}();\nvoid un{do_func_name}();\n"

    with open(f"{img_name}.h", "w") as f:
        f.write(f"#ifndef {img_name.upper()}_H\n")
        f.write(f"#define {img_name.upper()}_H\n\n")
        f.write(f"#define {img_name}_palette_size {len(palette)*2}\n")
        f.write(f"extern const unsigned short {img_name}_palette[{len(palette)}];\n")
        f.write(f"#define {img_name}_tiles_size {len(tiles)*2}\n")
        f.write(f"extern const unsigned short {img_name}_tiles[{len(tiles)}];\n")
        f.write(f"#define {img_name}_tilemap_size {len(tilemap)*2}\n")
        f.write(f"extern const unsigned short {img_name}_tilemap[{len(tilemap)}];\n\n")
        f.write(append_h)
        f.write(f"#endif")
