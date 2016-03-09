module("hud", package.seeall)

-- BUTTONS AND BOXES PARAMETERS START --
hud_textures =
{
    "land",     -- riddle_button_texture
    "bricks",   -- hints_button_texture
    "land",     -- riddle_box_texture
    "bricks"    -- hints_box_texture
}

hud_progress_sprites =
{
	1, 2, 3, 4, 5, 6, 7
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

showRiddleBox = false
showHintsBox = false

progress = 0

function draw()
	-- Progress Label --
	Hud.label(50, 50, 300, 30, hints_box_font, progress, hud_textures[4])
	
	-- Progress Labels --
	updateProgressBar()
	
	-- Test Label --
	Hud.label(100,100,100,100, 20, "123", hud_textures[1])
    
	
	
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
    end
end

function handleHintsButtonClick()
    if Hud.hintsButton(hints_button_x, hints_button_y, hints_button_width, hints_button_height, hints_button_font, hints_button_text, hud_textures[2]) == true then
        print("clicked hints!")
        if showHintsBox == false then showHintsBox = true
        elseif showHintsBox == true then showHintsBox = false
        end
    end
end

function updateProgressBar()
	-- Using TextLabels for now
	if (progress > 0.10) then Hud.textLabel(50 ,400, "||  1") end
	if (progress > 0.20) then Hud.textLabel(80,400, "| 2") end
	if (progress > 0.35) then Hud.textLabel(105,400, "| 3") end
	if (progress > 0.50) then Hud.textLabel(130,400, "| 4") end
	if (progress > 0.65) then Hud.textLabel(155,400, "| 5") end
	if (progress > 0.80) then Hud.textLabel(180,400, "| 6") end
	if (progress > 0.90) then Hud.textLabel(205,400, "| 7  ||") end
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
end