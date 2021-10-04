
Images / Animations AKA FLICs (FLIC Lib / VPaint / Autodesk Animator (Pro))


Test Scenarios:
* full screen image (320 x 200)
* non full screen image (<320 x <200)
* image with custom palette
* image with flag color
* single frame_raw image
* multiple frame_raw image
* animation (~=multiple frame_raw image)
* frame_type = 0
* frame_type = 1



Test-Bed:
* MAIN.LBX
  * MAIN000 () (320x200) (Main Game Screen) (LBX_RECORD_TYPE_FLIC) (No Custom Palette)
   * frame_count = 1
   * loop_frame = 0
   * unknown = 0
  * MAIN001 () (39x12) () (LBX_RECORD_TYPE_FLIC) (No Custom Palette)
   * frame_count = 2
   * loop_frame = 1
  * unknown = 1
 * MAIN039 () (9x9) () (LBX_RECORD_TYPE_FLIC) (No Custom Palette)
   * frame_count = 4
   * loop_frame = 0
   * unknown = 1

Scenario:
* deduce the significance of frame_count vs. loop_frame vs. unknown
 * e.g., in MAIN.LBX
 * every frame_count is {1, 2, 4}
 * every record with frame_count = 1 has loop_frame = 0 and unknown = 0
 * every record with frame_count = 2 has loop_frame = 1 and unknown = 1
 * every record with frame_count = 4 has loop_frame = 0 and unknown = 1
 * ?So, single-frame_raw has unknown = 0 and multi-frame_raw has unknown = 1?
 * ?But, why multi-frame_raw has loop_Frame = {0, 1}?

Scenario:
* What, if any, is the relationship between the FLIC Header and individual frame_raw?
 * frame_raw->frame_height = flic_header->frame_height
 * frame_raw->frame_width = flic_header->frame_width
