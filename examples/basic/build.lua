
--[[
  WARNING: build time functions will not have
  this global state, and will instead be blank, with the
  build system already required.

  So you will need to aqcuire external data manually,
  however the global state does persist between build function calls.
  so using `require` in build time functions will not have significant impace.
]]

return {
  "merianberry/blahblah",
  builders = {{
    -- A pattern for source files to compile
    -- rules cannot share source patterns, or overlap
    from = "*.hlsl",
    -- A list of possible output patterns to check
    -- different rules can share the same output pattern
    to = {"*.bin"},
    -- A build function that respects the given constraints.
    -- This function is not required to output a file.
    -- but if a given input should be skipped for this rule, return nil.
    build = function(from)
      local spv = amp.compShader(file)
      local out string.gsub(file, ".hlsl", ".bin")
      local f = io.open(out, "wb")
      if f ~= nil then
        f:write(spv)
        f:close()
      end
    end
  }},
  config = function()

  end,
  build = function()

  end
}