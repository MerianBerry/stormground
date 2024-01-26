local w, h = stormground.getScreen()
local pix = {}
local mode = 1
local str = ""

function onTick()
    stormground.setColor(252, 186, 3)
    stormground.drawText(1, 1, 1, str)
    stormground.drawLine(1,1, 250 + 100 * math.cos(stormground.getTime()), 170 + 100 * math.sin(stormground.getTime()))
    if stormground.keyIsDown("space") then
        stormground.drawText(1, 1, 5, "YIPPEE!")
    end
end

function keypress() 
    for i = string.byte("a"), string.byte("z") do
        local char = string.char(i)
        if stormground.keyIsTyped(char) then
            str = str .. char
            return nil
        end
    end
    for i = string.byte("0"), string.byte("9") do
        local char = string.char(i)
        if stormground.keyIsTyped(char) then
            str = str .. char
            return nil
        end
    end
    if stormground.getKey("space") == "pressed" then
        str = str .. " "
        return nil
    end
    if stormground.getKey("backspace") == "pressed" then
        str = str:sub(0, str:len() - 1)
        return nil
    end
end