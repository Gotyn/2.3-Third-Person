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

function draw()
    -- if Hud.button(50, 50, "show tip") == true then
    --     print("lua button clicked!")
    --     tip = "now showing tip 2 biatch!"
    -- end

    Hud.label(50, 350, tip)
end