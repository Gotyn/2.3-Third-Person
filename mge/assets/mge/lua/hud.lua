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

hints_box_x = 280
hints_box_y = 150
hints_box_width = 250
hints_box_height = 300
hints_box_font = 30
hints_box_text = "this is hint"
-- BUTTONS AND BOXES PARAMETERS START --

showRiddleBox = true
showHintsBox = false
initialRiddleCheck = false

progress = 0

function draw()
	--Hud.hintsBox(hints_box_x, hints_box_y, hints_box_width, hints_box_height, hints_box_font, progress, hud_textures[4])
	Hud.label(50, 50, 300, 30, hints_box_font, progress)
	--Hud.textLabel(100, 100, "yer a wizard Harry!")
	Hud.label(100,100,100,100, 20, "123")
    handleRiddleButtonClick()
    handleHintsButtonClick()
    updateRiddleBox()
    updateHintsBox()
    inintialRiddleDisplay()
end

function handleRiddleButtonClick()
    if Hud.riddleButton(riddle_button_x, riddle_button_y, riddle_button_width, riddle_button_height, riddle_button_font, riddle_button_text) == true then
        if showRiddleBox == false then showRiddleBox = true
        elseif showRiddleBox == true then showRiddleBox = false
        end
    end
end

function handleHintsButtonClick()
    if Hud.hintsButton(hints_button_x, hints_button_y, hints_button_width, hints_button_height, hints_button_font, hints_button_text) == true then
        if showHintsBox == false then showHintsBox = true
        elseif showHintsBox == true then showHintsBox = false
        end
    end
end

function updateRiddleBox()
    if showRiddleBox == true then
        Hud.riddleBox(riddle_box_x, riddle_box_y, riddle_box_width, riddle_box_height, riddle_box_font, riddle_button_text)
    end
end

function updateHintsBox()
    if showHintsBox == true then
        Hud.hintsBox(hints_box_x, hints_box_y, hints_box_width, hints_box_height, hints_box_font, hints_button_text)
    end
end

function inintialRiddleDisplay()
    if Hud.displayRiddleAtStart() == true and initialRiddleCheck == false then 
        showRiddleBox = false
        initialRiddleCheck = true
    end
end