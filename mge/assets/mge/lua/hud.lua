module("hud", package.seeall)

local data = require("mge/lua/hud_data")
showHintsBox = false
showHelpBox = true
initialRiddleCheck = false

progress = 0

function draw()
	--Hud.hintsBox(data.hints_box_x, data.hints_box_y, data.hints_box_width, data.hints_box_height, data.hints_box_font, progress)
	Hud.label(50, 50, 300, 30, data.hints_box_font, progress)
	--Hud.textLabel(100, 100, "yer a wizard Harry!")
	Hud.label(100,100,100,100, 20, "123")
    handleHelpButtonClick()
    updateHelpBox()
    updateHintsBox()
    inintialRiddleDisplay()
end

function handleHelpButtonClick()
    if Hud.helpButton(data.help_button_x, data.help_button_y, data.help_button_width, data.help_button_height, data.help_button_font, data.help_button_text) == true then
        if showHelpBox == false then
            showHelpBox = true
        elseif showHelpBox == true then
            showHelpBox = false
        end
        if showHintsBox == true then
            showHintsBox = false
        end
    end
end

function handleHintButtonsClick()
    if Hud.hintButton1(data.hint_button1_x, data.hint_button1_y, data.hint_button1_width, data.hint_button1_height, data.hint_button1_font, data.hint_button1_text) == true then
        if showHintsBox == false then showHintsBox = true
        elseif showHintsBox == true then showHintsBox = false
        end
    end
    
    if Hud.hintButton2(data.hint_button2_x, data.hint_button2_y, data.hint_button2_width, data.hint_button2_height, data.hint_button2_font, data.hint_button2_text) == true then
        if showHintsBox == false then showHintsBox = true
        elseif showHintsBox == true then showHintsBox = false
        end
    end
    
    if Hud.hintButton3(data.hint_button3_x, data.hint_button3_y, data.hint_button3_width, data.hint_button3_height, data.hint_button3_font, data.hint_button3_text) == true then
        if showHintsBox == false then showHintsBox = true
        elseif showHintsBox == true then showHintsBox = false
        end
    end
end

function updateHelpBox()
    if showHelpBox == true then
        Hud.helpBox(data.help_box_x, data.help_box_y, data.help_box_width, data.help_box_height, data.help_box_font, data.help_box_text)
        Hud.riddleBox(data.riddle_box_x, data.riddle_box_y, data.riddle_box_width, data.riddle_box_height, data.riddle_box_font, data.riddle_box_text)
        handleHintButtonsClick()
    end
end

function updateHintsBox()
    if showHintsBox == true then
        Hud.hintsBox(data.hints_box_x, data.hints_box_y, data.hints_box_width, data.hints_box_height, data.hints_box_font, data.hints_box_text2)
    end
end

function inintialRiddleDisplay()
    if Hud.displayRiddleAtStart() == true and initialRiddleCheck == false then 
        showHelpBox = false
        initialRiddleCheck = true
    end
end
