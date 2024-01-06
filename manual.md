<h1>
  <center>
  Stormground manual (beta.0.2)
  </center>
</h1>

- [Welcome](#welcome-to-stormground)
- [Command line options](#command-line-options)
- [Project settings](#project-settings)
- [API reference](#lua-api)

### Welcome to Stormground!

A project created to use a Stormworks-ish lua API to run as a playground on your PC instead of the game!

The lua API that Stormground indends to imitate is specifically the drawing API, used to draw to monitors in the game. For the purposes of making the API easier to work with however, some new functions are added, and some are not, and some are changed.

Stormground uses "projects" (directories/folders) as its organization method, and requires `project.json` and `main.lua` to be present in the given project directory.

## Some stuff

The "virtual display" is a term describing the display that your lua code is drawing to, not the physical display of your computer. This virtual display sits inside of the Stormground window, and has the resolution defined in your project settings.

Note that the coordinate system of Stormground originates in the bottom left corner of the virtual display, with positive Y going up, and positive X going right.

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
Returns the X and Y of the cursor relative to the bottom left of the virtual display.

```lua
stormground.getKey(name)
```
Returns a string of the press state of the `name` key. State can be `pressed`, `released`, `held`, `not pressed`. See the [list of key names](#api-key-names) for... a list of valid key names. If input name is invalid, or something went wrong internally, this function will return `nil`.

```lua
stormground.getButton(name)
```
Returns a string of the press state of the `name` mouse button. State can be `pressed`, `released`, `held`, `not pressed`. See the [list of button names](#api-button-names) for... a list of valid button names. If input name is invalid, or something went wrong internally, this function will return `nil`.

```lua
stormground.setColor(r, g, b)
```
Sets the draw color of any shapes from the call of the function, and then on. If any shapes were drawn before the call of this function, those shapes will retain their draw color.

```lua
stormground.drawRectangle(x, y, width, height)
```
Draws a filled rectangle, starting at (`x`,`y`), and extending for `width` and `height`.

```lua
stormground.drawTriangle(x1, y1, x2, y2, x3, y3)
```
Draws a filled triangle, with the points (`x1`,`y1`), (`x2`,`y2`), (`x3`,`y3`).
NOTE: may not be perfectly accurate.


### API key names

`0-9` zero to nine

`A-Z` OR `a-z`, a to z returns the same thing

`lshift` left shift

`rshift` right shift

`lcontrol` left control

`lalt` left alt

`ralt` right alt

`lbracket` left bracket

`rbracket` right bracket

`space` space

`backspace` backspace

`tab` tab

`enter` enter

`minus` minus sign

`equal` equals sign

`up` up arrow

`down` down arrow

`left` left arrow

`right` right arrow

`comma` comma

`period` period

`escape` escape

`slash` slash

`backslash` backslash

`semicolon` semicolon

`delete` delete

`page up` page up

`page down` page down

`home` home

`end` end

`insert` insert

### API button names

`left` left mouse button

`right` right mouse button

`middle` middle mouse button

`button1` mouse button 1

`button2` mouse button 2

`button3` mouse button 3

`button4` mouse button 4

`button5` mouse button 5

`button6` mouse button 6

`button7` mouse button 7

`button8` mouse button 8

