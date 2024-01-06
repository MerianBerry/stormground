
stormground.setColor(255, 255, 255)
local notset = true
function onTick() 
  stormground.setColor(0, 0, 255)
  stormground.drawTriangle(0, 0, 10, 10, 20, 0)
  stormground.setColor(255, 0, 0)
  x, y = stormground.getCursor()
  local gp = stormground.getGamepad(1)
  if gp.buttons.a == "pressed" then
    print "YIPPEE!!!"
  end
  if stormground.getKey("escape") == "released" then
    stormground.close()
  end
  stormground.drawRectangle(x, y, 2, 2)
  w, h = stormground.getScreen()
  stormground.drawRectangle(w-1, h-1, 1, 1)
  --[[if notset and stormground.getTime() > 5 then
    stormground.setScreen(288, 160)
  end]]
end
