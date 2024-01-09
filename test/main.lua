stormground.setColor(0, 255, 0)
function onTick()

    
    if stormground.getKey("space") == "held" then
        stormground.drawText(5, 1, 1, "Yippee!")
    end

end
