-- hud = {}

-- function hud.draw()
--     -- if Hud.button(50, 50, "lua button") == true then
--     --     print("lua button clicked!")
--     -- end
--     print("hud module test")
-- end

-- return Hud;

module("hud", package.seeall)

tips = {
    "tip 1 placeholder text to be put in later",
    "tip 2 text",
}

tipText = "tip text"

function draw()
    if Hud.button(50, 50, "show tip") == true then
        tipText = tips[1]
    end

    Hud.label(50, 350, tipText)
end