module("hud", package.seeall)

local data = require("mge/lua/hud_data")

showHintsBox1 = false
showHintsBox2 = false
showHintsBox3 = false
showHelpBox = true
initialRiddleCheck = false
hintText = ""

progress = 0

function draw()
	Hud.textLabel(50, 50, progress)

    handleHelpButtonClick()
    updateHelpBox()
    updateHintsBox()
    inintialRiddleDisplay()
	-- Progress Labels --
	updateProgressBar()
end

function handleHelpButtonClick()
    if Hud.helpButton(data.help_button_x, data.help_button_y, data.help_button_width, 
        data.help_button_height, data.help_button_font, data.help_button_text, data.help_button_alignment) == true then
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
    if Hud.hintButton1(data.hint_button1_x, data.hint_button1_y, data.hint_button1_width, 
        data.hint_button1_height, data.hint_button1_font, data.hint_button1_text, data.hint_button1_alignment) == true then
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
     
    if Hud.hintButton2(data.hint_button2_x, data.hint_button2_y, data.hint_button2_width, 
        data.hint_button2_height, data.hint_button2_font, data.hint_button2_text, data.hint_button2_alignment) == true then
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
    
    if Hud.hintButton3(data.hint_button3_x, data.hint_button3_y, data.hint_button3_width, 
        data.hint_button3_height, data.hint_button3_font, data.hint_button3_text, data.hint_button3_alignment) == true then
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
	if 	   (progress > 0.90)  then Hud.progressBar(600,500, 224, 32, 224, 0, "", 1) -- show all 
	elseif (progress > 0.80)  then Hud.progressBar(600,500, 224, 32, 196, 0, "", 1) -- show 6
	elseif (progress > 0.65)  then Hud.progressBar(600,500, 224, 32, 160, 0, "", 1) -- show 5
	elseif (progress > 0.50)  then Hud.progressBar(600,500, 224, 32, 128, 0, "", 1) -- show 4
	elseif (progress > 0.35)  then Hud.progressBar(600,500, 224, 32,  96, 0, "", 1) -- show 3
	elseif (progress > 0.20)  then Hud.progressBar(600,500, 224, 32,  64, 0, "", 1) -- show 2
	elseif (progress > 0.10)  then Hud.progressBar(600,500, 224, 32,  32, 0, "", 1) -- show 1
	elseif (progress <= 0.10) then Hud.progressBar(600,500, 224, 32,  0, 0,  "", 1) -- show none
	end
end

function updateHelpBox()
    if showHelpBox == true then
        Hud.helpBox(data.help_box_x, data.help_box_y, data.help_box_width, data.help_box_height, data.help_box_font, data.help_box_text, data.help_box_alignment)
        Hud.riddleBox(data.riddle_box_x, data.riddle_box_y, data.riddle_box_width, 
            data.riddle_box_height, data.riddle_box_font, data.riddle_box_text, data.riddle_box_alignment)
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
        Hud.hintsBox(data.hints_box_x, data.hints_box_y, data.hints_box_width, data.hints_box_height, data.hints_box_font, hintText, data.hints_box_alignment)
    end
end

function inintialRiddleDisplay()
    if Hud.displayRiddleAtStart() == true and initialRiddleCheck == false then 
        showHelpBox = false
        initialRiddleCheck = true
    end
end
