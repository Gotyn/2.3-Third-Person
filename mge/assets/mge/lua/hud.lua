module("hud", package.seeall)

-- BUTTONS AND BOXES PARAMETERS START --
hud_textures =
{
    "land",     -- riddle_button_texture
    "bricks",   -- hints_button_texture
    "land",     -- riddle_box_texture
    "bricks"    -- hints_box_texture
}

riddle_button_x = 600
riddle_button_y = 30
riddle_button_width = 80
riddle_button_height = 40
riddle_button_font = 15
riddle_button_text = "show riddle"

hints_button_x = 700
hints_button_y = 30
hints_button_width = 80
hints_button_height = 40
hints_button_font = 15
hints_button_text = "show hints"

riddle_box_x = 250
riddle_box_y = 480
riddle_box_width = 300
riddle_box_height = 100
riddle_box_font = 30
riddle_box_text = "this is riddle"

<<<<<<< HEAD
hint = "this is the next hint"
progress = "0" 											-- update this in the levels update function!

function draw()
    --Hint Button--
	if Hud.button(50, 50, "show hint") == true then
        print("lua button clicked!")
        hint = "now showing tip 2 biatch!"
=======
hints_box_x = 280
hints_box_y = 150
hints_box_width = 250
hints_box_height = 300
hints_box_font = 30
hints_box_text = "this is hint"
-- BUTTONS AND BOXES PARAMETERS START --

showRiddleBox = false
showHintsBox = false

function draw()
    handleRiddleButtonClick()
    handleHintsButtonClick()
    updateRiddleBox()
    updateHintsBox()
end

function handleRiddleButtonClick()
    if Hud.riddleButton(riddle_button_x, riddle_button_y, riddle_button_width, riddle_button_height, riddle_button_font, riddle_button_text, hud_textures[1]) == true then
        print("clicked riddle!")
        if showRiddleBox == false then showRiddleBox = true
        elseif showRiddleBox == true then showRiddleBox = false
        end
>>>>>>> refs/remotes/origin/hud2
    end
end

<<<<<<< HEAD
    Hud.label(50, 350, hint)
	
	--Progress Bar--
	Hud.label(50,100, progress) 
=======
function handleHintsButtonClick()
    if Hud.hintsButton(hints_button_x, hints_button_y, hints_button_width,hints_button_height, hints_button_font, hints_button_text, hud_textures[2]) == true then
        print("clicked hints!")
        if showHintsBox == false then showHintsBox = true
        elseif showHintsBox == true then showHintsBox = false
        end
    end
end

function updateRiddleBox()
    if showRiddleBox == true then
        Hud.riddleBox(riddle_box_x, riddle_box_y, riddle_box_width, riddle_box_height, riddle_box_font, riddle_button_text, hud_textures[3])
    end
end

function updateHintsBox()
    if showHintsBox == true then
        Hud.hintsBox(hints_box_x, hints_box_y, hints_box_width, hints_box_height, hints_box_font, hints_button_text, hud_textures[4])
    end
>>>>>>> refs/remotes/origin/hud2
end