module("hud", package.seeall)
local data = require("mge/lua/hud_data")

MODE = { MENU = 1, BOOK = 2, LEVEL = 3 }
game_state = MODE.LEVEL
showHintsBox1 = false
showHintsBox2 = false
showHintsBox3 = false
showRiddleBox = true
showHelpBox = true           -- NOTE: SHOULD BE TRUE UPON START OF THE LEVEL FOR INITIAL RIDDLE SHOW-UP
initialRiddleCheck = false   -- NOTE: SHOULD BE FALSE FOR INITIAL RIDDLE SHOW-UP
firstMenuShown = false
firstBookShown = false
continueToNextPuzzle = false
showFinalMenu = false
restartGame = false
hint_1 = "hint_1"
hint_2 = "hint_2"
hint_3 = "hint_3"
riddle_text = "riddle text"

progress = 0

hint1_spriteID = 2 
hint2_spriteID = 4 
hint3_spriteID = 6
exit_spriteID = 2 
resume_spriteID = 6 
start_spriteID = 0
story_book_button_spriteID = 0

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
    popStoryBook()
    handleStoryBookButtonClick()
end

function updateMenu()
    if Game.getKeyDown(KeyCode.M) == true and firstMenuShown == true then
        game_state = MODE.LEVEL
    end
	popMenu()
    handleMenuButtonsClick()
end

function updateLevel()
    updateHelpBox()
    updateHintsBox()
	
	if (showHelpBox) then handleHelpButtonClick(1) 	-- show pressed
	else handleHelpButtonClick(0) end				-- show unpressed
	
    inintialRiddleDisplay()
	
	updateProgressBar(data.progress_bar_xOffset, data.progress_bar_yOffset, data.progress_bar_alignment, data.progress_bar_scaleX, data.progress_bar_scaleY)
    if Game.getKeyDown(KeyCode.M) == true then
        game_state = MODE.MENU
    end
end

function handleHelpButtonClick(spriteID)
	--HelpButton
	if Hud.hintsButton(data.help_button_xOffset, data.help_button_yOffset, spriteID, 
				       data.help_button_alignment, data.help_button_scaleX, data.help_button_scaleY) == true then					
        if showHelpBox == false then
            showHelpBox = true
            showRiddleBox = true
        else
            showHelpBox = false
			hint1_spriteID = 2 --off
			hint2_spriteID = 4 --off
			hint3_spriteID = 6 --off
        end
        
		showHintsBox1 = false
        showHintsBox2 = false
        showHintsBox3 = false
    end
end

function handleHintButtonsClick()
    --HintButton1
	if Hud.hintsButton(data.hint_button1_xOffset, data.hint_button1_yOffset, 
        hint1_spriteID, data.hint_button1_alignment, data.hint_button1_scaleX, data.hint_button1_scaleY) == true then
        if showHintsBox1 == false then
            showHintsBox1 = true
			hint1_spriteID = 3 --on
			hint2_spriteID = 4 --off
			hint3_spriteID = 6 --off
			
            showHintsBox2 = false
            showHintsBox3 = false
            showRiddleBox = false
        else
            showHintsBox1 = false
			showRiddleBox = true
			hint1_spriteID = 2 --off
        end
    end
    
	--HintButton2
	if Hud.hintsButton(data.hint_button2_xOffset, data.hint_button2_yOffset,
        hint2_spriteID, data.hint_button2_alignment, data.hint_button2_scaleX, data.hint_button2_scaleY) == true then
        if showHintsBox2 == false then
            showHintsBox2 = true
			hint1_spriteID = 2 --off
			hint2_spriteID = 5 --on
			hint3_spriteID = 6 --off
			
            showHintsBox1 = false
            showHintsBox3 = false
            showRiddleBox = false
        else
            showHintsBox2 = false
			showRiddleBox = true
			hint2_spriteID = 4 --off
        end
    end
    
    --HintButton3
	if Hud.hintsButton(data.hint_button3_xOffset, data.hint_button3_yOffset, 
        hint3_spriteID, data.hint_button3_alignment, data.hint_button3_scaleX, data.hint_button3_scaleY) == true then
        if showHintsBox3 == false then
            showHintsBox3 = true
			hint1_spriteID = 2 --off
			hint2_spriteID = 4 --off
			hint3_spriteID = 7 --on
			
            showHintsBox2 = false
            showHintsBox1 = false
            showRiddleBox = false
        elseif showHintsBox3 == true then
            showHintsBox3 = false
			showRiddleBox = true
			hint3_spriteID = 6 --off
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
        Hud.helpBox	 (data.help_box_xOffset, data.help_box_yOffset, data.help_box_alignment, data.help_box_scaleX, data.help_box_scaleY)
		if showRiddleBox == true then
            Hud.riddleBox(data.riddle_box_xOffset, data.riddle_box_yOffset, data.riddle_box_font, riddle_text, data.riddle_box_alignment, data.riddle_box_scaleX, data.riddle_box_scaleY)
        end
        handleHintButtonsClick()
    else
        showHintsBox1 = false
        showHintsBox2 = false
        showHintsBox3 = false
        showRiddleBox = false
    end
end

-- the box showing the actual hint
function updateHintsBox()
    if showHintsBox1 == true then
        Hud.hintsBox(data.hints_box_xOffset, data.hints_box_yOffset, data.hints_box_font, hint_1, data.hints_box_alignment, data.hints_box_scaleX, data.hints_box_scaleY)
    elseif showHintsBox2 == true then
        Hud.hintsBox(data.hints_box_xOffset, data.hints_box_yOffset, data.hints_box_font, hint_2, data.hints_box_alignment, data.hints_box_scaleX, data.hints_box_scaleY)
    elseif showHintsBox3 == true then
        Hud.hintsBox(data.hints_box_xOffset, data.hints_box_yOffset, data.hints_box_font, hint_3, data.hints_box_alignment, data.hints_box_scaleX, data.hints_box_scaleY)
    end
end

function inintialRiddleDisplay()
    if Hud.displayRiddleAtStart() == true and initialRiddleCheck == false then 
        showHelpBox = false
        showRiddleBox = false
        hint1_spriteID = 0
        hint2_spriteID = 0
        hint3_spriteID = 0
        initialRiddleCheck = true
    end
end

function popMenu()
    Hud.menuBox(data.menu_box_xOffset, data.menu_box_yOffset, data.menu_box_alignment, data.menu_box_scaleX, data.menu_box_scaleY)
end

function handleMenuButtonsClick()

    if firstMenuShown == false then
		--StartButton
		if Hud.menuButton(data.start_button_xOffset, data.start_button_yOffset, start_spriteID, 
						   data.start_button_alignment, data.start_button_scaleX, data.start_button_scaleY) == true then
            game_state = MODE.BOOK
            firstMenuShown = true
			start_spriteID = 4 --Switch to RestartButtonSprite
        end
    end
    
    if firstMenuShown == true then
        --RestartButton
		if Hud.menuButton(data.start_button_xOffset, data.start_button_yOffset, start_spriteID, 
						   data.start_button_alignment, data.start_button_scaleX, data.start_button_scaleY) == true then
            restartGame = true
            print("RESTART!")
        end

		if showFinalMenu == false then 
		--ResumeButton
			if Hud.menuButton(data.resume_button_xOffset, data.resume_button_yOffset, resume_spriteID, 
							data.resume_button_alignment, data.resume_button_scaleX, data.resume_button_scaleY) == true then
				game_state = MODE.LEVEL
			end
		end
    end
	--ExitButton
	if Hud.menuButton(data.exit_button_xOffset, data.exit_button_yOffset, exit_spriteID, 
				  data.exit_button_alignment, data.exit_button_scaleX, data.exit_button_scaleY) == true then
		Hud.handleExit()
	end
end
	
function popStoryBook()
    Hud.storyBook(data.story_book_xOffset, data.story_book_yOffset, data.story_book_alignment, data.story_book_scaleX, data.story_book_scaleY)
end

function handleStoryBookButtonClick()
    if firstBookShown == false then
        if Hud.storyBookButton(data.story_book_button_xOffset, data.story_book_button_yOffset, story_book_button_spriteID, 
            data.story_book_button_alignment, data.story_book_button_scaleX, data.story_book_button_scaleY) == true then
            game_state = MODE.LEVEL
            firstBookShown = true
        end
    else
        if Hud.storyBookButton(data.story_book_button_xOffset, data.story_book_button_yOffset, story_book_button_spriteID, 
            data.story_book_button_alignment, data.story_book_button_scaleX, data.story_book_button_scaleY) == true then
            game_state = MODE.LEVEL
            continueToNextPuzzle = true
        end
    end
end
