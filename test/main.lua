local tick = 0

stormground.setScreen(512, 256)
local w, h = stormground.getScreen()
local wsize = 5
function onTick()
  x,y=stormground.getCursor()
  wsize = math.max(wsize + stormground.getScroll()*1.5, 0)
  --wsize = tick

  if stormground.getKey("lshift") == "pressed" then
    print("\x1b[1;92mHIIII!! :)")
  end

  stormground.setColor(255,255,255)
  stormground.drawCircle(x, y, wsize, wsize-1)
  
  tick = tick+1
end
