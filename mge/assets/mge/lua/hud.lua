module("hud", package.seeall)

local data = require("mge/lua/hud_data")

hud_progress_sprites =
{
	1, 2, 3, 4, 5, 6, 7
}

showHintsBox1 = false
showHintsBox2 = false
showHintsBox3 = false
showHelpBox = true
initialRiddleCheck = false
hintText = ""

progress = 0

function draw()
	Hud.label(50, 50, 300, 30, data.hints_box_font, progress)
	Hud.label(100,100,100,100, 20, "123")
    
    handleHelpButtonClick()
    updateHelpBox()
    updateHintsBox()
    inintialRiddleDisplay()
    
    -- Progress Label --
	Hud.label(50, 50, 300, 30, hints_box_font, progress, hud_textures[4])
	
	-- Progress Labels --
	updateProgressBar()
	
	-- Test Label --
	Hud.label(100,100,100,100, 20, "123", hud_textures[1])
end

function handleHelpButtonClick()
    if Hud.helpButton(data.help_button_x, data.help_button_y, data.help_button_width, data.help_button_height, data.help_button_font, data.help_button_text) == true then
        if showHelpBox == false then
            showHelpBox = true
        elseif showHelpBox == true then
            showHelpBox = false
        end
        if showHintsBox1 == true then
            showHintsBox1 = false
        end
        if showHintsBox2 == true then
            showHintsBox2 = false
        end
        if showHintsBox3 == true then
            showHintsBox3 = false
        end
    end
end

function handleHintButtonsClick()
    if Hud.hintButton1(data.hint_button1_x, data.hint_button1_y, data.hint_button1_width, data.hint_button1_height, data.hint_button1_font, data.hint_button1_text) == true then
        if showHintsBox1 == false then
            showHintsBox1 = true
            showHintsBox2 = false
            showHintsBox3 = false
            hintText = data.hints_box_text1
        elseif showHintsBox1 == true then
            showHintsBox1 = false
            hintText = ""
        end
    end
     
    if Hud.hintButton2(data.hint_button2_x, data.hint_button2_y, data.hint_button2_width, data.hint_button2_height, data.hint_button2_font, data.hint_button2_text) == true then
        if showHintsBox2 == false then
            showHintsBox2 = true
            showHintsBox1 = false
            showHintsBox3 = false
            hintText = data.hints_box_text2
        elseif showHintsBox2 == true then
            showHintsBox2 = false
            hintText = ""
        end
    end
    
    if Hud.hintButton3(data.hint_button3_x, data.hint_button3_y, data.hint_button3_width, data.hint_button3_height, data.hint_button3_font, data.hint_button3_text) == true then
        if showHintsBox3 == false then
            showHintsBox3 = true
            showHintsBox2 = false
            showHintsBox1 = false
            hintText = data.hints_box_text3
        elseif showHintsBox3 == true then
            showHintsBox3 = false
            hintText = ""
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

function updateHelpBox()
    if showHelpBox == true then
        Hud.helpBox(data.help_box_x, data.help_box_y, data.help_box_width, data.help_box_height, data.help_box_font, data.help_box_text)
        Hud.riddleBox(data.riddle_box_x, data.riddle_box_y, data.riddle_box_width, data.riddle_box_height, data.riddle_box_font, data.riddle_box_text)
        handleHintButtonsClick()
    end
    if showHelpBox == false then
        showHintsBox1 = false
        showHintsBox2 = false
        showHintsBox3 = false
    end
end

function updateHintsBox()
    if showHintsBox1 == true or showHintsBox2 == true or showHintsBox3 == true then
        Hud.hintsBox(data.hints_box_x, data.hints_box_y, data.hints_box_width, data.hints_box_height, data.hints_box_font, hintText)
    end
end

function inintialRiddleDisplay()
    if Hud.displayRiddleAtStart() == true and initialRiddleCheck == false then 
        showHelpBox = false
        initialRiddleCheck = true
    end
end
