gameHud = require "mge/lua/hud"

pieces = {  
    Game.PuzzleBlock("Ship.obj", "bricks.jpg", "piece1")
}

pieces[1]:setPosition(2,2,4)
pieces[1]:scale(0.3,0.3,0.3)

activePiece = 1
solved = false

pieces[activePiece]:flash(1.6)

storyWall = Game.StoryWall("Wall_side.obj", "bricks.jpg", "StoryWall")
storyWall:changeTexture("land.jpg")
-- wall:setPosition(0,1,-3)
-- wall:scale(5,5,1)

function update()
    -- updateGameStatus()
    handleControl()

    if checkProgress() > 0.9 then
        if solved == false then
            solved = true
            Audio.playSound("door.wav")
        end
    end

    -- handleControl(pieces[activePiece])

    -- -- test placement for placing prop
    -- handleControl(prop1)

    handleSelection()
    -- print(pieces[activePiece]:getName())
    -- if checkProgress() > 0.66 then print(checkProgress()) end

    -- if Game.getKeyDown(KeyCode.P) == true then
    --     printPuzzleBlocksStates()
    -- elseif Game.getKeyDown(KeyCode.H) == true then
    --     hints.showHint()
    -- end

    -- if Game.getKeyDown(KeyCode.F5) == true then
    --     refreshHud()
    -- end
end

function updateGUI()
    hud.draw()
end

function refreshHud()
    package.loaded["mge/lua/hud"] = nil
    gameHud = require "mge/lua/hud"
    print("hud reloaded!")
end

function printPuzzleBlocksStates()
    for i, v in ipairs(pieces) do 
        v:printStatus() 
    end
end

-- checks the total progress of the puzzle between 0 and 1
function checkProgress()
    totalProgress = 0
    for i, v in ipairs(pieces) do 
        totalProgress = totalProgress + v:getProgress() 
    end   
    return totalProgress / #pieces
end

function handleControl()
    if Game.getKey(KeyCode.W) == true then
        pieces[activePiece]:pitch(1.5) 
    end
    if Game.getKey(KeyCode.S) == true then
        pieces[activePiece]:pitch(-1.5) 
    end

    if Game.getKey(KeyCode.D) == true then
        pieces[activePiece]:roll(1.5) 
    end
    if Game.getKey(KeyCode.A) == true then
        pieces[activePiece]:roll(-1.5) 
    end
    if Game.getKey(KeyCode.Q) == true then
        pieces[activePiece]:yaw(1.5) 
    end
    if Game.getKey(KeyCode.E) == true then
        pieces[activePiece]:yaw(-1.5) 
    end
end 

function handleSelection()
    if Game.getKey(KeyCode.Num1) == true then
        activePiece = 1
    end

    if Game.getKey(KeyCode.Num2) == true then
        activePiece = 2
    end

    if Game.getKey(KeyCode.Num3) == true then
        activePiece = 3
    end
end

function updateGameStatus()
    if checkProgress() < 0.66 and testtt == true then 
        print("level completed! proceeding to next level...")
        -- os.execute("CHOICE /n /d: /c: /t:3")
        -- cleanLevel()
        testtt = false
    end
end
        

