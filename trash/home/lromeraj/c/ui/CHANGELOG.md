## v1.1.2
`[NEW]`
- Implemented format caching.

`[IMPROVEMENTS]`
- Improved `ui` speed.

## v0.4.6
`[FIXES]`
	- Minor bug fixes.

`[NEW]`
	- Implemented scroll boxes.

## v0.4.5
`[FIXES]`
  - Fixed memory leaks.

`[NEW]`
  - Implemented `ui_box_seek()`, move the cursor of a box to a given position.

`[IMPROVEMENTS]`
  - Improved destroy functions.

## v0.4.2
`[FIXES]`
  - Fixed issue that allowed to add new boxes with the same id.
  - Fixed issue with indented tabs.

`[IMPROVEMENTS]`
  - Improved `ui_pix_ovf()` function.

`[NEW]`
  - All UI public functions were documented.

## v0.4.0
`[FIXES]`
  - Fixed default initialization parameters.
  - Fixed an issue that caused a bad insertion of carriage returns when calling `ui_put_box()`.
  - Fixed box overflowing.

`[IMPROVEMENTS]`
  - Improved `ui_box_put()` performance.
  - If you put a string inside a box using `ui_box_put()` and the last char is a new line `\n`, the remaining chub of the line will be filled with the last remembered format parameters.
  - Improved `ui` stability such as pixels `getters` and `setters` ( avoiding overflows ).

`[NEW]`
  - `ui_dump_box()` dumps the data of a box inside the `ui` buffer.
  - `ui_box_pad()` sets the padding of a box ( internal margin ).
    the correct padding format is "<top> <right> <bottom> <left>",for example: "1 2 1 2".
    NOTE: when you call this function the box buffer is cleared, so make sure to call it before any `ui_put_box()` call.
  - `ui_draw()` will print a FATAL ERROR message if a pixel could not be printed.
  - Removed `ui_txt_bg()`, `ui_txt_fg()`, `ui_txt_frm()`, all of them have been fusioned into `ui_frm()`. which can set multiple formats like color, background, ..., at the same time.
  - Renamed `ui_txt_rs()` to `ui_rs()`, this function now resets temporary parameters to default.
