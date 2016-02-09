require "constructor";

-- FUNCTION TO GET VALUE OF WHETHER KEY IS PRESSED OR NOT
function getKeyDown()
    return keyIsPressed;
end

-- FUNCTION TO GET VALUE OF WHETHER KEY IS RELEASED OR NOT
function getKeyUp()
    return keyIsReleased;
end

-- FUNCTION TO GET ACTUAL TIME FROM THE GAME START
function getGameTime()
    return gameTime;
end

-- FUNCTION THAT AS AN EXAMPLE RETURNS STRING WITH IDs OF TWO OBJECTS THAT COLLIDE
function getColliders()
    return "Obj ID " .. collider_1 .. " collides with Obj ID " .. collider_2;
end

-- UPDATE LOOP IS TRIGGERED EVERY FRAME
function Update()
    if (getKeyDown() == 1 and getGameTime() % 2 == 0) then moveObject(objID.car);  
    --elseif (getKeyDown() == 1 and getGameTime() % 2 == 1) then
    --else
    end
end

-- TEST METHOD TO VIEW LUA FUNCTIONALITY LOGS IN CONSOLE
function test()
    print("time from start in sec: " .. getGameTime());
    if( keyIsPressed ~= nil) then print("Key Up (1 true | 0 false): " .. getKeyUp()); end
    if( keyIsPressed ~= nil) then print("Key Down (1 true | 0 false): " .. getKeyDown()); end
    x, y, z = getObjectPositionLua (objID.teapot);
    print("Obj cur pos: x -> " .. x .. " | y -> " .. y .. " | z -> " .. z);
    if( collider_1 ~= nil and collider_2 ~= nil) then print(getColliders()); end
    print('\n');
end

objID = {
    teapot = 0,
    monkey = 1,
    car = 2,
    plane = 3
};

--Objects types
objects = {
    "teapot",   --obj 1
    "monkey",   --obj 2
    "car",      --obj 3
    "plane"     --obj 4
};

--Positions: SETS OF 3 VALUES - x, y, z per object
positions = { 
    0, 1, 0,    --obj 1
    2, 1, 1,    --obj 2
    -3, 1, -3,  --obj 3
    0, 0, 0     --obj 4
};

--Rotations: SETS OF 4 VALUES - angle in degrees, x-axis, y-axis, z-axis
rotations = {
    90, 0, 1, 0,    --obj 1
    180, 0, 1, 0,   --obj 2
    90, 0, 1, 0,    --obj 3
    0, 0, 0, 0      --obj 4
};

--Scalings: value per object (tegelijk scaling)
scalings = {
    3,  --obj 1
    1,  --obj 2
    1,  --obj 3
    5   --obj 4
};

--Textures: file name per object
textures = {
    "teapot_smooth",    --obj 1
    "suzanna_flat",     --obj 2
    "cylinder_smooth",  --obj 3
    "plane"             --obj 4
};

--Materials: file name per object
materials = {
    "bricks",   --obj 1
    "yellow",   --obj 2
    "green",    --obj 3
    "land"      --obj 4
};

-- CAMERA IS A SEPARATE OBJECT, THUS IT GOES HERE
--Camera: position (x, y, z), target object #, rotation (angle, x-, y-, z-axis)
camera = { 
    0, 6, 7, --position (x, y, z)
    1, --target object #
    90, 0, 1, 0 --rotation (angle, x-, y-, z-axis)
};

    