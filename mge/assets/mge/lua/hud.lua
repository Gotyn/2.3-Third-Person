module("hud", package.seeall)

riddle = "this is riddle"
hint = "this is hint"
showRiddleBox = false
showHintsBox = false

function draw()
    handleRiddleButtonClick()
    handleHintsButtonClick()
    updateRiddleBox()
    updateHintsBox()
end

function handleRiddleButtonClick()
    if Hud.interactiveButton(600, 30, 80, 40, 15, "show riddle", "land") == true then
        print("clicked riddle!")
        if showRiddleBox == false then showRiddleBox = true
        elseif showRiddleBox == true then showRiddleBox = false
        end
    end
end

function handleHintsButtonClick()
    if Hud.interactiveButton(700, 30, 80, 40, 15, "show hint", "bricks") == true then
        print("clicked hints!")
        if showHintsBox == false then showHintsBox = true
        elseif showHintsBox == true then showHintsBox = false
        end
    end
end

function updateRiddleBox()
    if showRiddleBox == true then
        Hud.riddleBox(250, 480, 300, 100, 30, riddle, "bricks")
    end
end

function updateHintsBox()
    if showHintsBox == true then
        Hud.hintsBox(280, 150, 250, 300, 30, hint, "land")
    end
end