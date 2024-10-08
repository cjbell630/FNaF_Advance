import os
import sys

from PIL import Image
from sympy import ceiling

from gba_exporter import get_screenblock_index, get_pixels_from_tile, convert_palette, write_to_c_files, convert_tiles
from io_util import get_lambda

TOLERANCE = 1720
AVG_TOLERANCE = 27
NUM_DIFF_TOLERANCE = 9

REPLACE_SKIPPED_WITH_ORIGINAL = False

"""
should be considered same (return True): 20,8
Diff: 1306
average diff: 20.40625
Num diff: 8 (at avg diff = 1 and also 25)

should not be considered same (return False): 13,12
Diff: 1730
average diff: 27.03125
Num diff: 7

would be great if they weren't considered the same: 6,19
Diff: 1058
average diff: 16.53125
Num over: 9
"""


def images_are_basically_same(img1: Image, img2: Image, palette: list[int], to_print=False):
    if img1.size != img2.size:
        # throw error
        print("Images are not the same size")
        exit(1)
    diff = 0
    num_over = 0
    for y in range(0, 8):
        for x in range(0, 8):
            pixel1_index = img1.getpixel((x, y))
            pixel1 = (palette[pixel1_index], palette[pixel1_index + 1], palette[pixel1_index + 2])
            pixel2_index = img2.getpixel((x, y))
            pixel2 = (palette[pixel2_index], palette[pixel2_index + 1], palette[pixel2_index + 2])
            this_diff = 0
            for i in range(0, 3):
                this_diff += abs(pixel1[i] - pixel2[i])
            diff += this_diff
            if this_diff > 0:
                num_over += 1
    average_diff = diff / 64
    pass1 = diff < TOLERANCE
    pass2 = average_diff < AVG_TOLERANCE
    pass3 = num_over < NUM_DIFF_TOLERANCE
    if to_print:  # pass3 != pass2:
        print(f"Diff: {diff}")
        print(f"average diff: {diff / 64}")
        print(f"Num over: {num_over}")
    return (pass1 or pass2) and pass3


def process_image(filename):
    img = Image.open(filename)
    width, height = img.size
    print(f"Image size: {width}x{height}")

    palette = img.getpalette()
    # for i in range(0, len(palette), 3):
    # r, g, b = palette[i], palette[i + 1], palette[i + 2]
    # print the colors in their 5 bit binary representation
    # print(f"R: {r:05b} G: {g:05b} B: {b:05b}")
    # print(f"Palette: {palette}")
    print(f"Image mode: {img.mode}")
    num_colors = int(get_lambda("How many colors? ", lambda response: response.isnumeric()))

    num_frames = int(height / 160)
    frame_width_in_tiles = int(ceiling(width / 8))
    frame_height_in_tiles = int(ceiling(height / (8 * num_frames)))
    print(f"Number of frames: {num_frames}")

    frames = [[] for i in range(num_frames)]

    # iterate through 8x8 tiles
    for y in range(0, frame_height_in_tiles):
        y_coord = y * 8
        row = []
        for x in range(0, frame_width_in_tiles):
            x_coord = x * 8
            row.append(img.crop((x_coord, y_coord, x_coord + 8, y_coord + 8)))
        frames[0].append(row)
    #print(len(frames[0][0]))

    blank_tile = Image.new("P", (8, 8))

    for frame in range(1, num_frames):
        for y in range(0, frame_height_in_tiles):
            y_coord = y * 8
            row = []
            for x in range(0, frame_width_in_tiles):
                x_coord = x * 8
                tile = img.crop((x_coord, y_coord + frame * 160, x_coord + 8, y_coord + 8 + frame * 160))
                # print(f"Frame Y: {y} X: {x}")
                if images_are_basically_same(tile, frames[0][y][x], palette,
                                             # (x==13 and y==12) or (x == 20 and y == 8)or (x == 6 and y == 19)
                                             ):  # tile is the same as the first frame
                    row.append(frames[0][y][x] if REPLACE_SKIPPED_WITH_ORIGINAL else None)
                else:
                    row.append(tile)
            frames[frame].append(row)

    # export image
    new_img = Image.new("P", (width, height))
    new_img.putpalette(palette)

    converted_pal = convert_palette(palette, num_colors)


    tilemap=[0 for i in range(64*32)]
    base_tiles = []
    for y in range(frame_height_in_tiles):
        y_coord = y * 8
        for x in range(frame_width_in_tiles):
            x_coord = x * 8

            tilemap[get_screenblock_index(x, y, frame_width_in_tiles)] = x + y * frame_width_in_tiles
            base_tiles = get_pixels_from_tile(base_tiles, frames[0][y][x])

            new_img.paste(blank_tile if frames[0][y][x] is None else frames[0][y][x], (x_coord, y_coord))
    #print(tilemap)
    #print(base_tiles)

    appendices = []

    for frame in range(1, num_frames):
        #tilemap = [0 for i in range(64*32)]
        tiles = []
        appendices.append([{}]) # appendix for frame is a list of dicts
        for y in range(frame_height_in_tiles):
            y_coord = y * 8
            if len(appendices[frame-1][-1]) != 0:
                appendices[frame-1].append({})
            for x in range(frame_width_in_tiles):
                x_coord = x * 8
                curr_tile = frames[frame][y][x]
                if curr_tile is None:
                    if len(appendices[frame-1][-1]) != 0:
                        appendices[frame-1].append({})
                else:
                    if len(appendices[frame-1][-1]) == 0:
                        #appendices[frame-1].append({"start": get_screenblock_index(x, y, frame_width_in_tiles), "pixels": []})
                        appendices[frame-1].append({"start":  2*(x + y * frame_width_in_tiles), "pixels": []})
                    #tilemap[get_screenblock_index(x, y, frame_width_in_tiles)] = x + y * frame_width_in_tiles
                    appendices[frame-1][-1]["pixels"] = get_pixels_from_tile(appendices[frame-1][-1]["pixels"], frames[frame][y][x])

                new_img.paste(blank_tile if curr_tile is None else curr_tile, (x_coord, y_coord + frame * 160))
        #print(tilemap)
        #print(tiles)
        #write_to_c_files(converted_pal, convert_tiles(tiles), tilemap)
    #print(appendices)
    print("Finished processing! Saving image as output.bmp...")
    new_img.save("output.bmp")
    print("Image saved! Writing to C files...")
    write_to_c_files(converted_pal, convert_tiles(base_tiles), tilemap, appendices)


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python script.py <image_file>")
        sys.exit(1)

    filename = sys.argv[1]
    if not os.path.isfile(filename):
        print("File not found!")
        sys.exit(1)

    process_image(filename)
