game.testFunction("hello from my own lua script")
newGO = game.createProp("teapot_smooth.obj", "colorMaterial", "test prop")

name = newGO:getName()
print(name)

camera = {
	{
		componentName = "Transform",
		x = 0;
		y = 0;
		z = 5;
	},
    {
        componentName = "Camera"
    }
}

gameObject = {
	{
		componentName = "Transform",
		x = 0;
		y = 0;
		z = -2;
	},
    {
        componentName = "MeshRenderer",
        modelname = "teapot_smooth.obj"
    },
    {
        componentName = "RotatingBehaviour",
        speed = 5
    }
}

-- showCaster = {
--     MeshRenderer = {
--         modelname = "teapot_smooth.obj"
--     },
--     Rotator = {
--         speed = 5
--     }
-- }