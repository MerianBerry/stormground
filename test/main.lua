function deadzone(x)
  return math.abs(x) > 0.05 and x or 0
end

stormground.setColor(255, 255, 255)
local notset = true
local off = 0
function onTick() 
  off = off + stormground.getScroll() * 2
  stormground.setColor(0, 0, 255)
  stormground.drawTriangle(0, 0 + off, 10, 10 + off, 20, 0 + off)
  stormground.setColor(255, 0, 0)
  x, y = stormground.getCursor()
  if stormground.getInputMethod() == "gamepad" then
    local gp = stormground.getGamepad(1)
    local rx, ry = stormground.getRealCursor()
    rx = rx + deadzone(gp.axes.leftX) * 10;
    ry = ry + deadzone(gp.axes.leftY) * 10
    stormground.setCursor(rx, ry)
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
