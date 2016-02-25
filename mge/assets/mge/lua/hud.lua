-- hud = {}

-- function hud.draw()
--     -- if Hud.button(50, 50, "lua button") == true then
--     --     print("lua button clicked!")
--     -- end
--     print("hud module test")
-- end

-- return Hud;

module("hud", package.seeall)

function draw()
    if Hud.button(50, 50, "show tip") == true then
        print("lua button clicked!")
    end

    Hud.label(50, 350, "this is a test tip")
end