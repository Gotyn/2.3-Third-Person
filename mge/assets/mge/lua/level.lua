gameHud = require "mge/lua/hud"
gameHud_Data = require "mge/lua/hud_data"

dofile("mge/lua/story1.lua")

game_state = 1
storyCompleted = false
activePuzzle = 1
activePiece = 1
solvedThreshold = 2

-- TEXTURE NAMES FOR C++ START --
display_riddle_at_start = gameHud_Data.display_riddle_at_start
help_button_texture = gameHud_Data.help_button_texture
hint_button1_texture = gameHud_Data.hint_button1_texture
hint_button2_texture = gameHud_Data.hint_button2_texture
hint_button3_texture = gameHud_Data.hint_button3_texture
exit_button_texture = gameHud_Data.exit_button_texture
resume_button_texture = gameHud_Data.resume_button_texture
start_button_texture = gameHud_Data.start_button_texture
help_box_texture = gameHud_Data.help_box_texture
riddle_box_texture = gameHud_Data.riddle_box_texture
hints_box_texture = gameHud_Data.hints_box_texture
menu_box_texture = gameHud_Data.menu_box_texture
progress_bar_texture = gameHud_Data.progress_bar_texture
story_book_texture = gameHud_Data.story_book_texture
story_book_button_texture = gameHud_Data.story_book_button_texture
-- TEXTURE NAMES FOR C++ END --

storyWall = Game.StoryWall("Main_wall_OBJ.obj", "1_MainWall_Base_Color.png", "StoryWall")
storyWall:rotateAroundAxis(240, 0, 1, 0)
storyWall:scale(0.7, 0.7, 0.7)
storyWall:setPosition (3.1, 2.3, 3.3)

spotlight = Game.getSpotlight()
camera = Game.getCameraObject()

camera:setPosition(-5.537027, 2.663034, 7.021962)
camera:rotateAroundAxis(-23, 0, 1, 0)

-- ambient lighting
-- Game.ambientLight(0, 1, 0)

print("spotlight name: " .. camera:getName())
print("spotlight name: " .. spotlight:getName())
print("spotlight intensity: " .. spotlight:getIntensity())
-- spotlight:setIntensity(0.30)
print("spotlight intensity: " .. spotlight:getIntensity())
print("spotlight innerCone: " .. spotlight:getInnerCone())
spotlight:setInnerCone(3)
print("spotlight innerCone: " .. spotlight:getInnerCone())
print("spotlight outerCone: " .. spotlight:getOuterCone())
spotlight:setOuterCone(13)
print("spotlight outerCone: " .. spotlight:getOuterCone())
-- spotlight:setColor(1, 0, 0)

-- (test) send active puzzleBlock to c++
function getActiveBlock()
    return story[activePuzzle].blocks[activePiece]
end

function puzzleSetActive(puzzleIndex, active)
    for i, v in ipairs(story[puzzleIndex].blocks) do 
        v:setActive(active)
    end   
end

function selectBlock(puzzleIndex, blockIndex)
    activePiece = blockIndex
    story[puzzleIndex].blocks[activePiece]:flash(1.8)
end

function selectPuzzle(puzzleIndex)
    counter = 1
    for i, v in ipairs(story) do 
        if counter == puzzleIndex then
            puzzleSetActive(counter, true)
        else
            puzzleSetActive(counter, false)
        end
        counter = counter + 1
    end

    activePuzzle = puzzleIndex
    storyWall:changeTexture(story[puzzleIndex].wallImage)
    selectBlock(activePuzzle, 1)
    print("Current Puzzel is: " .. activePuzzle) 
end

function nextPuzzle()
    nextPuzzleIndex = activePuzzle + 1
    if nextPuzzleIndex > #story then
        storyCompleted = true
        print("completed!!")
    else
        selectPuzzle(nextPuzzleIndex)
    end
end

function handlePlacement(gameObject)
    if Game.getKeyDown(KeyCode.P) == true then
        gameObject:printStatus(gameObject) 
    end
    if Game.getKey(KeyCode.Up) == true then
        gameObject:move(0, 0, -1) 
    end
    if Game.getKey(KeyCode.Down) == true then
        gameObject:move(0, 0, 1) 
    end
    if Game.getKey(KeyCode.Left) == true then
        gameObject:move(-1, 0, 0) 
    end
    if Game.getKey(KeyCode.Right) == true then
        gameObject:move(1, 0, 0) 
    end
    if Game.getKey(KeyCode.RShift) == true then
        gameObject:move(0, 1, 0) 
    end
    if Game.getKey(KeyCode.RControl) == true then
        gameObject:move(0, -1, 0) 
    end
end

selectPuzzle(activePuzzle)

function update()
    if game_state == hud.MODE.LEVEL then
        updateLevel()
    end
end

function updateLevel()
    if storyCompleted then
        return
    else
        if Game.getKeyDown(KeyCode.T) == true then
            handleSelection()
        end

        if Game.getKeyDown(KeyCode.Y) == true then
            nextPuzzle()
        end

        handleControl()
        handlePlacement(storyWall)
        --handlePlacement(camera)
        handlePlacement(story[activePuzzle].blocks[activePiece])

        if checkProgress() >= solvedThreshold then
            nextPuzzle()
        end
    end
end

function updateGUI()
    hud.progress = checkProgress()
    hud.draw()
    game_state = hud.game_state
end

function refreshHud()
    package.loaded["mge/lua/hud"] = nil
    gameHud = require "mge/lua/hud"
    print("hud reloaded!")
	package.loaded["mge/lua/hud_data"] = nil
	gameHud_Data = require "mge/lua/hud"
	print("hud_data reloaded!")
end

function printPuzzleBlocksStates()
    for i, v in ipairs(pieces) do 
        v:printStatus() 
    end
end

-- checks the total progress of the puzzle between 0 and 1
function checkProgress()
    totalProgress = 0
    for i, v in ipairs(story[activePuzzle].blocks) do 
        totalProgress = totalProgress + story[activePuzzle].blocks[i]:getProgress() 
    end   
    return totalProgress / #story[activePuzzle].blocks
end

function handleControl()
    if Game.getKey(KeyCode.W) == true then
        story[activePuzzle].blocks[activePiece]:pitch(1.5) 
    end
    if Game.getKey(KeyCode.S) == true then
        story[activePuzzle].blocks[activePiece]:pitch(-1.5) 
    end

    if Game.getKey(KeyCode.D) == true then
        story[activePuzzle].blocks[activePiece]:roll(1.5) 
    end
    if Game.getKey(KeyCode.A) == true then
        story[activePuzzle].blocks[activePiece]:roll(-1.5) 
    end
    if Game.getKey(KeyCode.Q) == true then
        story[activePuzzle].blocks[activePiece]:yaw(1.5) 
    end
    if Game.getKey(KeyCode.E) == true then
        story[activePuzzle].blocks[activePiece]:yaw(-1.5) 
    end
end 

function handleSelection()

    blockCount = #story[activePuzzle].blocks

    activePiece = activePiece + 1

    if activePiece > blockCount then
        activePiece = 1
    end

    story[activePuzzle].blocks[activePiece]:flash(1.8)
end
