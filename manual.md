<h1>
  <center>
  Stormground manual (beta.0.3)
  </center>
</h1>

- [Welcome](#welcome-to-stormground)
- [Some stuff](#some-stuff)
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

The Lua API that Stormground indends to imitate is specifically the drawing API, used to draw to monitors in the game. For the purposes of making the API easier to work with however, some new functions are added, and some are not, and some are changed.

If you are familiar with Stormworks' Lua API, chances are you wont have much trouble learning Stormground's Lua API.

Stormground uses "projects" (directories/folders) as its organization method, and requires `project.json` and `main.lua` to be present in the given project directory.

## Some stuff

The "virtual display" is a term describing the display that your Lua code is drawing to, not the physical display of your computer. This virtual display sits inside of the Stormground window, and has the resolution defined in your project settings.

Note that the coordinate system of Stormground originates in the bottom left corner of the virtual display, with positive Y going up, and positive X going right.

Stormground uses a "virtual cursor" method for cursor usage. Stormground will NEVER move the system cursor, but the user script is able to move the virtual cursor. If the current input method for Stormground is a gamepad, the virtual cursor will not be bound to the system cursor until the input method is deemed to be mouse and keyboard again.

`stormground.getCursor`'s location in the virtual display is based off of the virtual cursor, instead of the system cursor.

## Command line options

`-h`: Help : Gives a list of the command line options and what they do.

`-d <directory>`: Directory : Gives a relative path to the project directory. If `-d` is not used, Stormground will assume it's current working directory is the project directory.

`-v`: Version : Prints the current version of the program.

## Project settings

You are able to set some settings for the program using `project.json`, which is in the root of the project directory.

Your settings available is:

`monitorWidth`: 1 < integer < 960 : Defines the width of the "monitor", or the emulated display for the program.

`monitorHeight`: 1 < integer < 540 : Defines the height of the "monitor", or the emulated display for the program.

`name`: string : Defines the name of the project. Isn't used for anything despite the name of the window created.

## Lua API

The Lua API was made to be much less restrictive than Stormworks.

You are able to have a script with a size above 4KB, able to `require` other lua scripts, and have access to the entire standard Lua library (except for `assert`, `os.exit` and `os.execute`)

- [Input](#input)
- [Output](#output)
- [Drawing](#drawing)

### Input

```lua
stormground.getDelta()
```
Returns the number of milliseconds spent on the last frame. This number will typically be around 16.7 milliseconds.

```lua
stormground.getTime()
```
Returns the number of seconds since the start of the program. Yes it is a float.

```lua
stormground.getCursor()
```
Returns the X and Y (two return values) of the cursor relative to the top left of the virtual display.

```lua
stormground.getRealCursor()
```
Returns the X and Y (two return values) of the system cursor relative to the top left of the window.

```lua
stormground.getScroll()
```
Returns the change in the Y scroll axis since the last frame.

```lua
stormground.getScreen()
```
Returns the width and height (two return values) of the virtual display.

```lua
stormground.getKey(name)
```
Returns a string of the press state of the `name` key. State can be `pressed`, `released`, `held`, `not pressed`, `repeated`. If input name is invalid, or something went wrong internally, this function will return `nil`.

```lua
stormground.keyIsTyped(name)
```
Returns a boolean that is true if the state of the `name` key is `pressed` or `repeated`. If the input name is invalid, or something went wrong internally, this function will return `nil`.

```lua
stormground.keyIsDown(name)
```
Returns a boolean that is true if the state of the `name` key is `pressed`, `repeated` or `held`. If the input name is invalid, or something went wrong internally, this function will return `nil`.

See the [list of key names](#api-key-names) for... a list of valid key names.

```lua
stormground.getButton(name)
```
Returns a string of the press state of the `name` mouse button. State can be `pressed`, `released`, `held`, `not pressed`. If input name is invalid, or something went wrong internally, this function will return `nil`.

See the [list of button names](#api-button-names) for... a list of valid button names.

```lua
stormground.getGamepad(id)
```
Returns a gamepad state table for the gamepad specified by `id`. Passing a value of `1` for `id` returns the state table for the last detected gamepad. If `id` is invalid for some reason, this function will still return the full state table, but `.name` will be `nil`.

See the [gamepad table reference](#api-gamepad-table) to see its fields.

```lua
stormground.getInputMethod()
```
Returns a string of the last active imput method. `m&k` for mouse and keyboard, or `gamepad` if gamepad. If an error happens internally, this result will be `nil`.

### Output

```lua
stormground.close()
```
Calling this function will tell Stormground to stop runtime. Stormground will close on its own time, but usually on the start of processing the next frame.

```lua
stormground.setScreen(w, h)
```
Sets a new size of the virtual display. `w` will be clamped to between `6` and `960`. `h` will be clamped to be between `6` and `540`. The change in display size will take place the same frame that this function was called. `stormground.getScreen` will return the new virtual display size.

```lua
stormground.setCursor(x, y)
```
Sets the position of the virtual cursor, relative to the top left of the window. `x` and `y` represents physical pixel coordinates instead of virtual display coordinates.


### Drawing

```lua
stormground.drawText(x, y, size, text)
```
Draws `text` at (`x`, `y`), with `size` being the size scaling of the text. Default letter size is 3 by 5 pixels.

```lua
stormground.drawLine(x1, y1, x2, y2)
```
Draws a 1 pixel wide line from (`x1`, `y1`) to (`x2`, `y2`).

```lua
stormground.drawCircle(x, y, outerDiam, innerDiam)
```
Draws a circle centered around (`x`, `y`), with an outer diameter of `outerDiam`, and an inner diameter of `innerDiam`. `innerDiam` can be undefined or `nil`, and will be determined to be `0`.


```lua
stormground.drawRectangle(x, y, width, height, isHollow)
```
Draws a filled rectangle, starting at (`x`,`y`), and extending for `width` and `height`. If `isHollow` is true, the rectangle will be drawn as hollow with a `1` pixel wide shell. `isHollow` can be undefined or `nil`, and will be determined to be `false`.

```lua
stormground.drawTriangle(x1, y1, x2, y2, x3, y3)
```
Draws a filled triangle, with the points (`x1`,`y1`), (`x2`,`y2`), (`x3`,`y3`).

*NOTE: may not be perfectly accurate.*

```lua
stormground.setColor(r, g, b)
```
Sets the draw color of any shapes from the call of the function, and then on. If any shapes were drawn before the call of this function, those shapes will retain their draw color.


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

### API button name

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

  - `rightTrigger` field (number): Right trigger axis.
  - `leftTrigger` field (number): Left trigger axis.
  - `leftX` field (number): Left joystick X axis.
  - `leftY` field (number): Left joystick Y axis.
  - `rightX` field (number): Right joystick X axis.
  - `rightY` field (number): Right joystick Y axis.

- `buttons` field (table): Table with the accessable buttons.

  - `a` field (string): A/Cross button.
  - `b` field (string): B/Circle button.
  - `x` field (string): X/Square button.
  - `y` field (string): Y/Triangle button.
  - `leftBumper` field (string): Left bumper button.
  - `rightBumber` field (string): Right bumper button.
  - `back` field (string): Back/Share button.
  - `start` field (string): Start/Options button.
  - `guide` field (string): Guide/PS button.
  - `leftThumb` field (string): Left Joystick/Thumbstick button.
  - `rightThumb` field (string): Right Joystick/Thumbstick button.
  - `dpadUp` field (string): DPAD up button.
  - `dpadRight` field (string): DPAD right button.
  - `dpadDown` field (string): DPAD down button.
  - `dpadLeft` field (string): DPAD left button.

Button fields hold `pressed`, `released`, `held` or `not pressed`, just like return values of the `getButton` function.
