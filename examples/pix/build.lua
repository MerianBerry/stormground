
--[[sg.addBuilder('*.hlsl', function(file)
  local spv = sg.compShader(file)
  local out string.gsub(file, ".hlsl", ".spv")
  local f = io.open(out, "wb")
  if f ~= nil then
    f:write(spv)
    f:close()
  end
  return out
end, true)]]

return {
  build = function()
    print("im buildiiiiiing")
  end
}
