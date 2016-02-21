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

-- print("lua gameObject name: " .. piece1:getName())

function update ()
  -- print(piece2:getProgress())
  
  -- print(game.getKeyDown(0))

    if game.getKey(22) == true then
        piece2:pitch(1.5) 
    end
    if game.getKey(18) == true then
        piece2:pitch(-1.5) 
    end

    if game.getKey(3) == true then
        piece2:roll(1.5) 
    end
    if game.getKey(0) == true then
        piece2:roll(-1.5) 
    end
end

-- TODO:: if GetKeyDown