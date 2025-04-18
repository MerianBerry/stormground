local tick = 0
function onTick()
  x,y=stormground.getCursor()
  if stormground.getKey("space") == "pressed" then
    print "hello"
  end
  if stormground.getScroll() ~= 0 then
    print(stormground.getScroll())
  end
  for u = 0, 95 do
    for v = 0, 95 do
      stormground.setColor(u, v, 0)
      stormground.drawRectangle(u, v, 1, 1)
    end
  end
  tick = tick+1
end