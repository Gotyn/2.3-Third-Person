pieces = {  
    Game.PuzzleBlock("cube_flat.obj", "land.jpg", "piece1"),
    Game.PuzzleBlock("teapot_smooth.obj", "bricks.jpg", "piece2"),
    Game.PuzzleBlock("teapot_smooth.obj", "land.jpg", "piece3")
}

pieces[1]:setPosition(0,-1,0)
pieces[2]:setPosition(0,1,0)
pieces[3]:setPosition(0,3,0)

-- props / scenery
prop1 = Game.Prop("OfficeChair.obj", "bricks.jpg", "prop1")
prop1:setPosition(2, 0.5, 0)

activePiece = 1

function update()
    handleControl(pieces[activePiece])

    -- test placement for placing prop
    handleControl(prop1)

    handleSelection()
    -- print(pieces[activePiece]:getName())
    -- print(checkProgress())

    -- test lookAt
    -- pieces[2]:lookAt(pieces[1])
    -- print(pieces[2]:printStatus())

    if Game.getKeyDown(KeyCode.P) == true then
        printPuzzleBlocksStates() 
    end
end

function updateGUI()
    -- -- button test
    -- if Hud.button(50, 50, "lua button") == true then
    --     print("lua button clicked!")
    -- end 
    require "mge/lua/hud"
    hud.draw()
end

function printPuzzleBlocksStates()
    for i, v in ipairs(pieces) do 
        v:printStatus() 
    end

    -- file = io.open("snapshot.txt", "w")
    -- io.output(file)
    -- io.write("-- End of the test.lua file")
    -- io.close(file)
end

-- checks the total progress of the puzzle between 0 and 1
function checkProgress()
    totalProgress = 0
    for i, v in ipairs(pieces) do 
        totalProgress = totalProgress + v:getProgress() 
    end   
    return totalProgress / #pieces
end

function handleControl(gameObject)
    -- rotation
    if Game.getKey(KeyCode.W) == true then
        gameObject:pitch(1.5) 
    end
    if Game.getKey(KeyCode.S) == true then
        gameObject:pitch(-1.5) 
    end
    if Game.getKey(KeyCode.D) == true then
        gameObject:roll(1.5) 
    end
    if Game.getKey(KeyCode.A) == true then
        gameObject:roll(-1.5) 
    end
    if Game.getKey(KeyCode.Q) == true then
        gameObject:yaw(1.5) 
    end
    if Game.getKey(KeyCode.E) == true then
        gameObject:yaw(-1.5) 
    end

    -- movement
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