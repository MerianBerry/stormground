
function onTick()
  x,y=stormground.getCursor()
  if stormground.getKey("space") == "pressed" then
    print "hello"
  end
  if stormground.getScroll() ~= 0 then
    print(stormground.getScroll())
  end
end