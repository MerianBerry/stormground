local tick = 0
--stormground.setScreen(160, 96)
local w, h = stormground.getScreen()
function onTick()
  x,y=stormground.getCursor()
  if stormground.getKey("space") == "pressed" then
    print "hello"
  end
  if stormground.getScroll() ~= 0 then
    print(stormground.getScroll())
  end
  local x, y = stormground.getCursor()
  stormground.setColor(255,255,255)
  local r =math.sqrt((x-w/2)^2 + (y-h/2)^2)
  local th = math.atan((y-h/2), (x-w/2))
  stormground.drawLine(w/2,h/2,x,y)
  stormground.setColor(255, 0, 0, 128)
  stormground.drawCircle(w/2,h/2, r/3, r, -th)
  
  tick = tick+1
end