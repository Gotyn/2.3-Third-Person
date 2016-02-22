require "keyCodes"

-- print("hello from level")

-- game.preloadSounds();

-- game.playSound("door.wav")

-- modelViewer = game.ModelViewer()

piece1 = game.PuzzleBlock("cube_flat.obj", "land.jpg")
piece2 = game.PuzzleBlock("teapot_smooth.obj", "bricks.jpg")
piece3 = game.PuzzleBlock("teapot_smooth.obj", "land.jpg")

piece1:setPosition(0,-1,0)
piece2:setPosition(0,1,0)
piece3:setPosition(0,3,0)

activePiece = piece2

-- print("lua gameObject name: " .. piece1:getName())

function update ()
  -- print(piece2:getProgress())
  
  -- print(game.getKeyDown(0))

    if game.getKey(KeyCode.W) == true then
        activePiece:pitch(1.5) 
    end
    if game.getKey(KeyCode.S) == true then
        activePiece:pitch(-1.5) 
    end

    if game.getKey(KeyCode.D) == true then
        activePiece:roll(1.5) 
    end
    if game.getKey(KeyCode.A) == true then
        activePiece:roll(-1.5) 
    end
end