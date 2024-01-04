<h1>
  <center>
  Stormground manual (beta.0.1)
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

## Command line options

`-h`: Help : Gives a list of the command line options and what they do.

`-d <directory>`: Directory : Gives a relative path to the project directory. If `-d` is not used, Stormground will assume it's current working directory is the project directory.

`-v`: Version : Prints the current version of the program.

## Project settings

You are able to set some settings for the program using `project.json`, which is in the root of the project directory.

Your settings available is:

`monitorWidth`: 1 < integer < 1080 : Defines the width of the "monitor", or the emulated display for the program.

`monitorHeight`: 1 < integer < 1080 : Defines the height of the "monitor", or the emulated display for the program.

`name`: string : Defines the name of the project. Isn't used for anything despite the name of the window created.

## Lua API

```lua
stormground.getDelta()
```
Returns the number of milliseconds spent on the last frame. This number will typically be around 16.7 milliseconds.

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
