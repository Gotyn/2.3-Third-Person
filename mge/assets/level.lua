print("hello from level")

modelViewer = game.ModelViewer()
piece1 = game.PuzzleBlock()
piece2 = game.PuzzleBlock()
piece1:setPosition(0,3,0)

print("lua gameObject name: " .. piece1:getName())

function update ()
  -- print(piece1:getProgress())
  -- print("update from lua")
end