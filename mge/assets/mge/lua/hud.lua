module("hud", package.seeall)
local data = require("mge/lua/hud_data")

MODE = { MENU = 1, BOOK = 2, LEVEL = 3 }
game_state = MODE.LEVEL
showHintsBox1 = false
showHintsBox2 = false
showHintsBox3 = false
showHelpBox = true
initialRiddleCheck = false
hintText = ""

progress = 0

hint1_spriteID = 0 
hint2_spriteID = 0 
hint3_spriteID = 0
exit_spriteID = 0 
resume_spriteID = 0 
start_spriteID = 0

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
    if Game.getKeyDown(KeyCode.M) == true then
        game_state = MODE.LEVEL
    end
	popMenu()
end

function updateLevel()
    updateHelpBox()
    updateHintsBox()
	
	if (showHelpBox) then handleHelpButtonClick(1) 	-- show pressed
	else handleHelpButtonClick(0) end				-- show unpressed
	
    inintialRiddleDisplay()
	
	-- Update ProgressBar: --
	updateProgressBar(data.progress_bar_xOffset, data.progress_bar_yOffset, data.progress_bar_alignment,
					  data.progress_bar_scaleX,  data.progress_bar_scaleY
					  )
    if Game.getKeyDown(KeyCode.M) == true then
        game_state = MODE.MENU
    end
end

function handleHelpButtonClick(spriteID)
    if Hud.helpButton(data.help_button_xOffset, data.help_button_yOffset, spriteID, 
				      data.help_button_alignment, data.help_button_scaleX, data.help_button_scaleY) == true then
        if showHelpBox == false then
            showHelpBox = true
        else
            showHelpBox = false
			hint1_spriteID = 0 
			hint2_spriteID = 0 
			hint3_spriteID = 0
        end
        
		showHintsBox1 = false
        showHintsBox2 = false
        showHintsBox3 = false
    end
end

function handleHintButtonsClick()
    if Hud.hintButton1(data.hint_button1_xOffset, data.hint_button1_yOffset, 
        hint1_spriteID, data.hint_button1_alignment, data.hint_button1_scaleX, data.hint_button1_scaleY) == true then
        if showHintsBox1 == false then
            showHintsBox1 = true
			hint1_spriteID = 1
			hint2_spriteID = 0
			hint3_spriteID = 0
			
            showHintsBox2 = false
            showHintsBox3 = false
        else
            showHintsBox1 = false
			hint1_spriteID = 0
        end
    end
     
    if Hud.hintButton2(data.hint_button2_xOffset, data.hint_button2_yOffset,
        hint2_spriteID, data.hint_button2_alignment, data.hint_button2_scaleX, data.hint_button2_scaleY) == true then
        if showHintsBox2 == false then
            showHintsBox2 = true
			hint1_spriteID = 0
			hint2_spriteID = 1
			hint3_spriteID = 0
			
            showHintsBox1 = false
            showHintsBox3 = false
        elseif showHintsBox2 == true then
            showHintsBox2 = false
			hint2_spriteID = 0

        end
    end
    
    if Hud.hintButton3(data.hint_button3_xOffset, data.hint_button3_yOffset, 
        hint3_spriteID, data.hint_button3_alignment, data.hint_button3_scaleX, data.hint_button3_scaleY) == true then
        if showHintsBox3 == false then
            showHintsBox3 = true
			hint1_spriteID = 0
			hint2_spriteID = 0
			hint3_spriteID = 1
			
            showHintsBox2 = false
            showHintsBox1 = false
        elseif showHintsBox3 == true then
            showHintsBox3 = false
			hint3_spriteID = 0
        end
    end
end

function updateProgressBar(xOffset, yOffset, alignment, scaleX, scaleY)
	if 	   (progress > 0.90)  then Hud.progressBar(xOffset, yOffset, 7, alignment, scaleX, scaleY) -- show 7 
	elseif (progress > 0.80)  then Hud.progressBar(xOffset, yOffset, 6, alignment, scaleX, scaleY) -- show 6
	elseif (progress > 0.65)  then Hud.progressBar(xOffset, yOffset, 5, alignment, scaleX, scaleY) -- show 5
	elseif (progress > 0.50)  then Hud.progressBar(xOffset, yOffset, 4, alignment, scaleX, scaleY) -- show 4
	elseif (progress > 0.35)  then Hud.progressBar(xOffset, yOffset, 3, alignment, scaleX, scaleY) -- show 3
	elseif (progress > 0.20)  then Hud.progressBar(xOffset, yOffset, 2, alignment, scaleX, scaleY) -- show 2
	elseif (progress > 0.10)  then Hud.progressBar(xOffset, yOffset, 1, alignment, scaleX, scaleY) -- show 1
	elseif (progress <= 0.10) then Hud.progressBar(xOffset, yOffset, 0, alignment, scaleX, scaleY) -- show 0
	end
	
end

-- the box holding the hint buttons
function updateHelpBox()
    if showHelpBox == true then
        Hud.helpBox	 (data.help_box_xOffset, data.help_box_yOffset, data.help_box_width, data.help_box_height, 
					  data.help_box_alignment, data.help_box_scaleX, data.help_box_scaleY)
		Hud.riddleBox(data.riddle_box_xOffset, data.riddle_box_yOffset, data.riddle_box_width, data.riddle_box_height, data.riddle_box_font, 
				      data.riddle_box_text, data.riddle_box_alignment, data.riddle_box_scaleX, data.riddle_box_scaleY)
        handleHintButtonsClick()
    else
        showHintsBox1 = false
        showHintsBox2 = false
        showHintsBox3 = false
    end
end

-- the box showing the actual hint
function updateHintsBox()
    if showHintsBox1 == true or showHintsBox2 == true or showHintsBox3 == true then
        Hud.hintsBox(data.hints_box_xOffset, data.hints_box_yOffset, data.hints_box_width, data.hints_box_height, data.hints_box_font, 
					 hintText, data.hints_box_alignment, data.hints_box_scaleX, data.hints_box_scaleY)
    end
end

function inintialRiddleDisplay()
    if Hud.displayRiddleAtStart() == true and initialRiddleCheck == false then 
        showHelpBox = false
        hint1_spriteID = 0
        hint2_spriteID = 0
        hint3_spriteID = 0
        initialRiddleCheck = true
    end
end

function popMenu()
    Hud.menuBox(data.menu_box_xOffset, data.menu_box_yOffset, data.menu_box_width, data.menu_box_height, data.menu_box_alignment, data.menu_box_scaleX, data.menu_box_scaleY)
    Hud.startButton(data.start_button_xOffset, data.start_button_yOffset, data.start_button_width, 
        data.start_button_height, start_spriteID, data.start_button_alignment, data.start_button_scaleX, data.start_button_scaleY)
    Hud.resumeButton(data.resume_button_xOffset, data.resume_button_yOffset, data.resume_button_width, 
        data.resume_button_height, resume_spriteID, data.resume_button_alignment, data.resume_button_scaleX, data.resume_button_scaleY)
    Hud.exitButton(data.exit_button_xOffset, data.exit_button_yOffset, data.exit_button_width, 
        data.exit_button_height, exit_spriteID, data.exit_button_alignment, data.exit_button_scaleX, data.exit_button_scaleY)
end