-- hud = {}

-- function hud.draw()
--     -- if Hud.button(50, 50, "lua button") == true then
--     --     print("lua button clicked!")
--     -- end
--     print("hud module test")
-- end

-- return Hud;

module("hud", package.seeall)

hint = "this is the next hint"
progress = "0" 											-- update this in the levels update function!

function draw()
    --Hint Button--
	if Hud.button(50, 50, "show hint") == true then
        print("lua button clicked!")
        hint = "now showing tip 2 biatch!"
    end

    Hud.label(50, 350, hint)
	
	--Progress Bar--
	Hud.label(50,100, progress)
end