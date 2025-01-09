
function onTick()
  stormground.setColor(255,255,255)
  x,y=stormground.getCursor()
  stormground.drawLine(50,50,x,y)
end