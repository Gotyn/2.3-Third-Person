piece1 = Game.PuzzleBlock("cube_flat.obj", "land.jpg")
piece2 = Game.PuzzleBlock("teapot_smooth.obj", "bricks.jpg")
piece3 = Game.PuzzleBlock("teapot_smooth.obj", "land.jpg")

piece1:setPosition(0,-1,0)
piece2:setPosition(0,1,0)
piece3:setPosition(0,3,0)

activePiece = piece2

function update()
    handleControl()

    handleSelection()

    checkProgress()
end

function checkProgress()
    totalProgress = (piece1:getProgress() + piece2:getProgress() + piece3:getProgress()) / 3

    print(totalProgress)
end

function handleControl()
    if Game.getKey(KeyCode.W) == true then
        activePiece:pitch(1.5) 
    end
    if Game.getKey(KeyCode.S) == true then
        activePiece:pitch(-1.5) 
    end

    if Game.getKey(KeyCode.D) == true then
        activePiece:roll(1.5) 
    end
    if Game.getKey(KeyCode.A) == true then
        activePiece:roll(-1.5) 
    end
end 

function handleSelection()
    if Game.getKey(KeyCode.Num1) == true then
        activePiece = piece1
    end

    if Game.getKey(KeyCode.Num2) == true then
        activePiece = piece2
    end

    if Game.getKey(KeyCode.Num3) == true then
        activePiece = piece3
    end
end 