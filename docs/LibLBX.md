
The palette_info_offset and palette_info
  may the equivalent of the FliLib FLI_COLOR Chunk(s).
If the count of colors to change is zero, it is interpreted to mean 256.
Some arrangement like this would have allowed them to share the palette across /frame_raw/.

Also, this would further suggest that the did indeed use Autodesk Animator (Pro)
  and the FLI/FLC format (i.e., not CEL/PIC) for all of the images. 

Also, if I am imagining this correctly,
  given that they dropped the individual color chunk packets,
  they would seem to have had to have designated a portion of the (default) palette
  as available for custom colors.

Somewhere in here, it does actually seem difficult to imagine the amount of
  coding they would have had to go through for the sake of saving on the bytes
  of required storage space by reducing the headers and consolidating the palettes
  into standard palettes and custom colors per image.
As yet, I have not seen anything in FliLib or ANI and its source code or documentation
  that would have facilitated this arrangement.
I suppose they could simply have started, at some point, with a standardized palette
  and then simply post-processed all the images to capture any custom colors.



FLI_COLOR Chunks -
The first byte says how many packets are in this chunk.
This is followed directly by the packets.
The first byte of a packet says how many colors to skip.
The next byte says how many colors to change.
If this byte is zero it is interpreted to mean 256.
Next follows 3 bytes  for each color to change (one each for red green blue).

...

PJFILES.DOC

256 Color Chunks - FLI_COLOR256 (4)

The data following this chunk is organized in packets. The first word
following the chunks header is a count of the number of packets in
the chunk. Each packet consists of a single byte color index skip
count, a single byte color count and three bytes of color information
for each color defined.

At the start of the chunk, the color index is initialized to 0.
Before processing any colors in a packet, the color index skip count
is added to the current color index. The number of colors defined in
the packet is retrieved. A zero in this byte indicates 256 colors
are to be defined. The three bytes used to define each color define
the red, green, and blue components of the color in that order. Each
component can range from 0 (off) to 255 (full on). It is the players
responsbility to convert these colors to the correct values for the
device being used to play the animation.


64 Color Chunks - FLI_COLOR (11)

This chunks is almost identical to the 256 Color Chunk. The only
difference is the range of values for the red, green and blue
components of defined colors. In this chunks these values can range
from 0 (off) to 63 (full on).

