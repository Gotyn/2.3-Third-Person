pieces = {  
    Game.PuzzleBlock("cube_flat.obj", "land.jpg", "piece1"),
    Game.PuzzleBlock("teapot_smooth.obj", "bricks.jpg", "piece2"),
    Game.PuzzleBlock("teapot_smooth.obj", "land.jpg", "piece3")
}

pieces[1]:setPosition(0,-1,0)
pieces[2]:setPosition(0,1,0)
pieces[3]:setPosition(0,3,0)

activePiece = 1

function update()
    handleControl()

    handleSelection()
    -- print(pieces[activePiece]:getName())
    -- print(checkProgress())

    -- test lookAt
    pieces[2]:lookAt(pieces[2])
    print(pieces[2]:printStatus())

    if Game.getKeyDown(KeyCode.P) == true then
        printPuzzleBlocksStates() 
    end
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

function handleControl()
    -- rotation
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

    -- movement
    if Game.getKey(KeyCode.Up) == true then
        pieces[activePiece]:move(0, 0, -1)
    end  
    if Game.getKey(KeyCode.Down) == true then
        pieces[activePiece]:move(0, 0, 1) 
    end
    if Game.getKey(KeyCode.Left) == true then
        pieces[activePiece]:move(-1, 0, 0) 
    end
    if Game.getKey(KeyCode.Right) == true then
        pieces[activePiece]:move(1, 0, 0) 
    end
    if Game.getKey(KeyCode.RShift) == true then
        pieces[activePiece]:move(0, 1, 0) 
    end
    if Game.getKey(KeyCode.RControl) == true then
        pieces[activePiece]:move(0, -1, 0) 
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