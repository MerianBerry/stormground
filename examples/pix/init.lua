--[[sg.renderPass({
  render = function(self)

  end
})]]

sg.onTick(function ()
  local x, y = sg.getCursor()
  if sg.getKey("a") == "pressed" or sg.getKey("space") == "pressed" then
    print("Hello")
  end
end)

