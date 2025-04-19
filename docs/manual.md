<h1>
  <center>
  Stormground manual (v1.4)
  </center>
</h1>

- [Welcome](#welcome-to-stormground)
- [Terminology](#some-terminology)
- [Command line options](#command-line-options)
- [Project settings](#project-settings)
- [API reference](#lua-api)
  - [Input](#input)
  - [Output](#output)
  - [Drawing](#drawing)
  - [Key names](#api-key-names)
  - [Button names](#api-button-names)
  - [Gamepad table](#api-gamepad-table)

### Welcome to Stormground!

A project created to use a Stormworks-ish lua API to run as a playground on your PC instead of the game!

This manual includes everything that has to do with using Stormground.

## Some Terminology

Because of the nature of drawing to a "screen" that isn't Stormgrounds' window, the term "Virtual Screen" or "Virtual Display" is used to represent the screen that you actual draw to, and can manage.

A similar treament is applied to the system cursor, with the "Virtual Cursor" representing the system cursor in virtual pixel space.

## Command line options

`help [-h] <command>`: Prints a list of commands, and how to use the program.

`run [-r] [<dir>]`: Runs stormground in a directory. `<dir>` is optional.

`version [-v]`: Prints version info.

## Project settings

Stormground uses "projects" (directories/folders) as its organization method, and requires a `main.lua` to be present in the given project directory.

You are able to set some optional settings for Stormground using `sgproject.json`, which is in the root of the project directory.

The settings available are:

`monitorWidth`: 6 < integer < 1280 : Defines the width of the "monitor" / virtual screen.

`monitorHeight`: 6 < integer < 720 : Defines the height of the "monitor" / virtual screen

`name`: string : Defines the name of the project. Isn't used for anything despite the name of the window created.

## Lua API

The Lua API was made to be much less restrictive than Stormworks.

You are able to have a script with a size above 4KB, able to `require` other lua scripts, and have access to the entire standard Lua library (except for `os.execute`)

**NOTE**: All pixel coordinates are relative to the top left of the virtual screen. With +y pointing down.

- [Input](#input)
- [Output](#output)
- [Drawing](#drawing)

### Input

`getDelta()`

- Returns the number of milliseconds spent on the last frame.
- This number will typically be around 16.7 milliseconds.

`getTime()`

- Returns the number of seconds since the start of the program.

`getCursor()`

- Returns the X and Y (two return values) of the cursor relative to the top left of the virtual display.

`getRealCursor()`

- Returns the X and Y (two return values) of the system cursor relative to the top left of the window.

`getScroll()`

- Returns the change in the Y scroll axis since the last frame.

`getScreen()`

- Returns the width and height (two return values) of the virtual display.

`getKey(name)`

- Returns a string of the press state of the `name` key.
- State can be `pressed`, `released`, `held`, `not pressed`, `repeated`.
- If input name is invalid, or something went wrong internally, this function will return `nil`.

`keyIsTyped(name)`

- Returns a boolean that is true if the state of the `name` key is `pressed` or `repeated`.
- If the input name is invalid, or something went wrong internally, this function will return `nil`.

`keyIsDown(name)`

- Returns a boolean that is true if the state of the `name` key is `pressed`, `repeated` or `held`.
- If the input name is invalid, or something went wrong internally, this function will return `nil`.

See the [list of key names](#api-key-names) for a list of valid key names.

`getButton(name)`

- Returns a string of the press state of the `name` mouse button. State can be `pressed`, `released`, `held`, `not pressed`.
- If input name is invalid, or something went wrong internally, this function will return `nil`.

See the [list of button names](#api-button-names) for a list of valid button names.

`getGamepad(id)`

- Returns a gamepad state table for the gamepad specified by `id`. Passing a value of `1` for `id` returns the state table for the last detected gamepad.
- If `id` is invalid for some reason, this function will still return the full state table, but `.name` will be `nil`.

See the [gamepad table reference](#api-gamepad-table) to see its fields.

`getInputMethod()`

- Returns a string of the last active imput method. `m&k` for mouse and keyboard, or `gamepad` if gamepad.
- If an error happens internally, this result will be `nil`.

### Output

`close()`

- Calling this function will cause stormground to exit at the start of the next frame.

`setScreen(w, h)`

- Sets a new size of the virtual display.
- `w` will be clamped to between `6` and `1280`.
- `h` will be clamped to be between `6` and `720`.
- The change in display size will take effect immediately.

`setCursor(x, y)`

- Sets the position of the virtual cursor, relative to the top left of the window.
- `x` and `y` represents physical pixel coordinates instead of virtual display coordinates.

### Drawing

`setColor(r, g, b, a)`

- Sets the color for drawing. Take effect immediately.
- All arguments are in a range of 0-255.
- `a` is optional, defaulting to 255.

`drawTriangle(x0, y0, x1, y1, x2, y2, fill)`

- Draws a triangle with the given points as vertices.
- `fill` is optional, defaulting to `true`.

`drawRectangle(x, y, w, h, fill)`

- Draws a rectangle at `(x,y)` with the size `(w,h)`.
- `fill` is optional, defaulting to `true`.

`drawLine(x0, y0, x1, y1)`

- Draws a one pixel wide line between the given points.

`drawCircle(x, y, outerRad, innerRad, arc, offset, step)`

- Draws a circle/arc around `(x, y)`, starting at `θ`, traveling counter clockwise.
- `innerRad` is optional, defaulting to `0`.
- `arc` is how long the arc is (can be negative). And is optional, defaulting `2pi`.
- `off` is how far the arc starts (can be negative). And is optional, defaulting to `0`.
- `step` is how many quads are used to draw the circle. It is also optional.

`drawText(x, y, text, scale)`

- Draws `text` at `(x,y)`, `(x,y)` being the top left of the text.
- `scale` is the size each pixel in the drawn text. And is optiona, defaulting to `1`.
- Default letter size is 3x5 pixels.

### API key names

- `0-9` zero to nine
- `A-Z` OR `a-z` (can be upper or lower case), a to z
- `lshift` left shift
- `rshift` right shift
- `lcontrol` left control
- `lalt` left alt
- `ralt` right alt
- `lbracket` left bracket
- `rbracket` right bracket
- `space` space
- `backspace` backspace
- `tab` tab
- `enter` enter
- `minus` minus sign
- `equal` equals sign
- `up` up arrow
- `down` down arrow
- `left` left arrow
- `right` right arrow
- `comma` comma
- `period` period
- `escape` escape
- `slash` slash
- `backslash` backslash
- `semicolon` semicolon
- `delete` delete
- `page up` page up
- `page down` page down
- `home` home
- `end` end
- `insert` insert

### API button names

- `left` left mouse button
- `right` right mouse button
- `middle` middle mouse button
- `button1` mouse button 1
- `button2` mouse button 2
- `button3` mouse button 3
- `button4` mouse button 4
- `button5` mouse button 5
- `button6` mouse button 6
- `button7` mouse button 7
- `button8` mouse button 8

### API gamepad table

- `name` field (string): Name of the gamepad (will be `nil` if error occurs).

- `axes` field (table): Table with the accessable axes.

  - `lx` field (number): Left joystick X axis.
  - `ly` field (number): Left joystick Y axis.
  - `rx` field (number): Right joystick X axis.
  - `ry` field (number): Right joystick Y axis.
  - `ltrigger` field (number): Left trigger axis.
  - `rtrigger` field (number): Right trigger axis.

- `buttons` field (table): Table with the accessable buttons.

  - `a` field (string): A/Cross button.
  - `b` field (string): B/Circle button.
  - `x` field (string): X/Square button.
  - `y` field (string): Y/Triangle button.
  - `lbumper` field (string): Left bumper button.
  - `rbumper` field (string): Right bumper button.
  - `back` field (string): Back/Share button.
  - `start` field (string): Start/Options button.
  - `guide` field (string): Guide/PS button.
  - `lstick` field (string): Left Joystick/Thumbstick button.
  - `rstick` field (string): Right Joystick/Thumbstick button.
  - `up` field (string): DPAD up button.
  - `right` field (string): DPAD right button.
  - `down` field (string): DPAD down button.
  - `left` field (string): DPAD left button.

Button fields hold `pressed`, `released`, `held` or `not pressed`, just like return values of the `getButton` function.
