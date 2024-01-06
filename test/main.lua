
stormground.setColor(255, 255, 255)

function onTick() 
  stormground.setColor(0, 0, 255)
  stormground.drawTriangle(0, 0, 10, 10, 20, 0)
  stormground.setColor(255, 0, 0)
  x, y = stormground.getCursor()
  if stormground.getButton("left") == "pressed" then
    print "YIPPEE!!!"
  end
  stormground.drawRectangle(x, y, 2, 2)
end
