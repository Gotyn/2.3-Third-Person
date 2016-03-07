-- hud = {}

-- function hud.draw()
--     -- if Hud.button(50, 50, "lua button") == true then
--     --     print("lua button clicked!")
--     -- end
--     print("hud module test")
-- end

-- return Hud;

module("hud", package.seeall)

tip = "this is the next tip"
hintsToggled = false
riddleToggled = false

function draw()
<<<<<<< HEAD
    --print("test")
    if Hud.button(50, 50, "show tip") == true then
        print("lua button clicked!")
        tip = "now showing tip 2 biatch!"
    end
    
    displayButtons()
=======
    -- if Hud.button(50, 50, "show tip") == true then
    --     print("lua button clicked!")
    --     tip = "now showing tip 2 biatch!"
    -- end
>>>>>>> refs/remotes/origin/master

    updateButtonsStatus()
    
    Hud.label(50, 350, tip)
end

function updateButtonsStatus()
    if(hintsToggled == true) then 
        Hud.hints()
    end
    
    if(riddleToggled == true) then 
        Hud.riddle()
    end
end

function displayButtons()
    if Hud.button(50, 50, "show hints") == true then
        hintsToggled = true
    else then hintsToggled = false
    end
    
    if Hud.button(50, 50, "show riddle") == true then
        riddleToggled = true
    else then riddleToggled = false
    end
end