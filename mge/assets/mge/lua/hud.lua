module("hud", package.seeall)
local data = require("mge/lua/hud_data")

MODE = { MENU = 1, BOOK = 2, LEVEL = 3 }
game_state = MODE.LEVEL
showHintsBox1 = false
showHintsBox2 = false
showHintsBox3 = false
showHelpBox = true
initialRiddleCheck = false
menuPressed = false
hintText = ""

progress = 0

function draw()
	if game_state == MODE.LEVEL then
        updateLevel()
    elseif game_state == MODE.BOOK then
        updateBook()
    elseif game_state == MODE.MENU then
        updateMenu()
    end
end

function updateBook()

end

function updateMenu()
    popMenu()
    if Game.getKeyDown(KeyCode.M) == true then
        game_state = MODE.LEVEL
    end
end

function updateLevel()    
    handleHelpButtonClick()
    updateHelpBox()
    updateHintsBox()
    inintialRiddleDisplay()
    
	-- Update ProgressBar: --
	--	int: xOffset, yOffset, spriteWidth, spriteHeight, spriteRows, alignment --
	updateProgressBar(data.progress_bar_xOffset, 
					  data.progress_bar_yOffset,  
					  data.progress_bar_sprite_width, 
					  data.progress_bar_sprite_height, 
					  data.progress_bar_sprite_rows,
					  data.progress_bar_alignment)
    if Game.getKeyDown(KeyCode.M) == true then
        game_state = MODE.MENU
    end
end

function handleHelpButtonClick()
    if Hud.helpButton(data.help_button_xOffset, data.help_button_yOffset, data.help_button_width, 
        data.help_button_height, data.help_button_alignment) == true then
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
    if Hud.hintButton1(data.hint_button1_xOffset, data.hint_button1_yOffset, data.hint_button1_width, 
        data.hint_button1_height, data.hint_button1_alignment) == true then
        if showHintsBox1 == false then
            showHintsBox1 = true
            showHintsBox2 = false
            showHintsBox3 = false
        elseif showHintsBox1 == true then
            showHintsBox1 = false
        end
    end
     
    if Hud.hintButton2(data.hint_button2_xOffset, data.hint_button2_yOffset, data.hint_button2_width, 
        data.hint_button2_height, data.hint_button2_alignment) == true then
        if showHintsBox2 == false then
            showHintsBox2 = true
            showHintsBox1 = false
            showHintsBox3 = false
        elseif showHintsBox2 == true then
            showHintsBox2 = false
        end
    end
    
    if Hud.hintButton3(data.hint_button3_xOffset, data.hint_button3_yOffset, data.hint_button3_width, 
        data.hint_button3_height, data.hint_button3_alignment) == true then
        if showHintsBox3 == false then
            showHintsBox3 = true
            showHintsBox2 = false
            showHintsBox1 = false
        elseif showHintsBox3 == true then
            showHintsBox3 = false
        end
    end
end

function updateProgressBar(xOffset, yOffset, spriteWidth, spriteHeight, spriteRows, alignment)
	rowHeight = spriteHeight / spriteRows
		
	if 	   (progress > 0.90)  then Hud.progressBar(xOffset, yOffset, spriteWidth, rowHeight, rowHeight * 7, alignment) -- show all 
	elseif (progress > 0.80)  then Hud.progressBar(xOffset, yOffset, spriteWidth, rowHeight, rowHeight * 6, alignment) -- show 6
	elseif (progress > 0.65)  then Hud.progressBar(xOffset, yOffset, spriteWidth, rowHeight, rowHeight * 5, alignment) -- show 5
	elseif (progress > 0.50)  then Hud.progressBar(xOffset, yOffset, spriteWidth, rowHeight, rowHeight * 4, alignment) -- show 4
	elseif (progress > 0.35)  then Hud.progressBar(xOffset, yOffset, spriteWidth, rowHeight, rowHeight * 3, alignment) -- show 3
	elseif (progress > 0.20)  then Hud.progressBar(xOffset, yOffset, spriteWidth, rowHeight, rowHeight * 2, alignment) -- show 2
	elseif (progress > 0.10)  then Hud.progressBar(xOffset, yOffset, spriteWidth, rowHeight, rowHeight * 1, alignment) -- show 1
	elseif (progress <= 0.10) then Hud.progressBar(xOffset, yOffset, spriteWidth, rowHeight, rowHeight * 0, alignment) -- show none
	end
	
end

-- the box holding the hint buttons
function updateHelpBox()
    if showHelpBox == true then
        Hud.helpBox(data.help_box_xOffset, data.help_box_yOffset, data.help_box_width, data.help_box_height, data.help_box_alignment)
        Hud.riddleBox(data.riddle_box_xOffset, data.riddle_box_yOffset, data.riddle_box_width, 
            data.riddle_box_height, data.riddle_box_font, data.riddle_box_text, data.riddle_box_alignment)
        handleHintButtonsClick()
    end
    if showHelpBox == false then
        showHintsBox1 = false
        showHintsBox2 = false
        showHintsBox3 = false
    end
end

-- the box showing the actual hint
function updateHintsBox()
    if showHintsBox1 == true or showHintsBox2 == true or showHintsBox3 == true then
        Hud.hintsBox(data.hints_box_xOffset, data.hints_box_yOffset, data.hints_box_width, data.hints_box_height, data.hints_box_font, hintText, data.hints_box_alignment)
    end
end

function inintialRiddleDisplay()
    if Hud.displayRiddleAtStart() == true and initialRiddleCheck == false then 
        showHelpBox = false
        initialRiddleCheck = true
    end
end

function popMenu()
    Hud.tutorialBox(0, 0, 500, 500, 40, "MENU", 5)
end