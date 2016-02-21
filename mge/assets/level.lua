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
  -- print(piece1:getProgress())
  -- print("update from lua")
end

-- TODO:: if GetKeyDown