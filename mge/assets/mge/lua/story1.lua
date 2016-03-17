story = {
    {
        wallImage = "1_MainWall_Base_Color.png",    --SHIPS (done)
        blocks = {  
            Game.PuzzleBlock("Ship.obj", "Ship_Base_Color.png", "piece1", -1.325238, 4.995407, 4.780406)
            --Game.PuzzleBlock("sphere_smooth.obj", "bricks.jpg", "piece2", 2, 0, 0)
        },
        tips = {
            "puzzle 1, tip1",
            "puzzle 1, tip2"
        },
        camPosition = {-5.809093, 3.296122, 6.267358},
        lightPosition = {-1.325238, 4.995407, 13.4},
        wallPosition = {4.169649, 0.326027, 5.563453}
    },
    {
        wallImage = "2_MainWall_Base_Color.png",    --EAGLE (done)
        blocks = {  
            Game.PuzzleBlock("Eagle.obj", "Eagle_Base_Color.png", "piece1", -1.620447, 1.626915, 5.364659)
            --Game.PuzzleBlock("sphere_smooth.obj", "bricks.jpg", "piece2", 6, 0, 0)
        },
        tips = {
            "puzzle 2, tip1",
            "puzzle 2, tip2"
        },
        camPosition = {-5.974538, 1.666161, 6.152138},
        lightPosition = {-1.847859, 1.815444, 9.814968},
        wallPosition = {5.442980, 3.081979, 5.682520}
    },
    {
        wallImage = "3_MainWall_Base_Color.png",    --KNIFE (done)
        blocks = {  
            Game.PuzzleBlock("Knife.obj", "Knife_Base_Color.png", "piece1", 0.843153, 0.834008, 5.276042)
            --Game.PuzzleBlock("sphere_smooth.obj", "bricks.jpg", "piece2", 2, 0, 0)
        },
        tips = {
            "puzzle 3, tip1",
            "puzzle 3, tip2"
        },
        camPosition = {-2.434961, 0.555908, 6.144196},
        lightPosition = {0.843153, 1.088349, 13.4},
        wallPosition = {1.148681, 4.441195, 4.885514}
    },
    -- {
    --     wallImage = "4_MainWall_Base_Color.png",    --STAR (done)
    --     blocks = {  
    --         Game.PuzzleBlock("Star_Piece_1.obj", "Star1_Base_Color.png", "piece1", -0.693387, 2.375158, 7.263427),
    --         Game.PuzzleBlock("Star_Piece_2.obj", "Star2_Base_Color.png", "piece2", -0.693387, 2.375158, 6.297121)
    --     },
    --     tips = {
    --         "puzzle 5, tip1",
    --         "puzzle 5, tip2"
    --     },
    --     camPosition = {-4.253707, 2.660000, 7.026434},
    --     lightPosition = {-0.693387, 2.375158, 11.252758},
    --     wallPosition = {-0.888751, 2.354517, 4.053206}
    -- },
    {
        wallImage = "5_MainWall_Base_Color.png",    --PYRAMIDE (done)
        blocks = {  
            Game.PuzzleBlock("Piramide_Base.obj", "Piramide_Base_Base_Color.png", "piece1", 3.800427, 1.652600, 6.775362),
            Game.PuzzleBlock("Piramide_Peak.obj", "Piramide_Peak_Base_Color.png", "piece2", 3.865358, 1.794074, 6.345235)
        },
        tips = {
            "puzzle 5, tip1",
            "puzzle 5, tip2"
        },
        camPosition = {-0.270552, 2.220431, 6.825822},
        lightPosition = {3.067473, 1.827167, 11.252758},
        wallPosition = {-0.893377, 3.392399, 4.224762}
    },
    {
        wallImage = "6_MainWall_Base_Color.png",    --SCROLL (done)
        blocks = {  
            Game.PuzzleBlock("scroll_Piece_1.obj", "Scroll1_Base_Color.png", "piece1", -0.765814, 2.388417, 6.728118),
            Game.PuzzleBlock("scroll_Piece_2.obj", "Scroll2_Base_Color.png", "piece2", -0.964263, 2.766296, 6.073485)
        },
        tips = {
            "puzzle 6, tip1",
            "puzzle 6, tip2"
        },
        camPosition = {-1.812449, 2.336787, 6.410395},
        lightPosition = {-1.438703, 2.400000, 11.904770},
        wallPosition = {0.647556, 2.089863, 4.580250}
    }
    -- {
    --     wallImage = "7_MainWall_Base_Color.png",    --LIPS (done)
    --     blocks = {  
    --         Game.PuzzleBlock("Lips_Top.obj", "LipsTop_Base_Color.png", "piece1", -0.731242, 2.409929, 5.689291),
    --         Game.PuzzleBlock("Lips_Bottom.obj", "LipsLow_Base_Color.png", "piece2", -0.841410, 2.121926, 6.893439)
    --     },
    --     tips = {
    --         "puzzle 7, tip1",
    --         "puzzle 7, tip2"
    --     },
    --     camPosition = {-5.53, 2.66, 7.02},
    --     lightPosition = {-1.6, 2.4, 13.4},
    --     wallPosition = {0.654102, 3.237490, 4.120658}
    -- },
    -- {
    --     wallImage = "8_MainWall_Base_Color.png",    --SKULL (done)
    --     blocks = {  
    --         Game.PuzzleBlock("Skull_Top.obj", "Skill_TOP_Base_Color.png", "piece1", -0.506487, 2.752661, 6.262687),
    --         Game.PuzzleBlock("Skull_Jaw.obj", "Skull_JAW_Base_Color.png", "piece2", -0.523324, 1.884991, 7.142652)
    --     },
    --     tips = {
    --         "puzzle 8, tip1",
    --         "puzzle 8, tip2"
    --     },
    --     camPosition = {-5.048825, 2.660000, 6.819078},
    --     lightPosition = {-0.506487, 2.752661, 11.988092},
    --     wallPosition = {0.810955, 0.927196, 4.518479}
    -- },
    -- {
    --     wallImage = "9_MainWall_Base_Color.png",    --CAMEL (done)
    --     blocks = {  
    --         Game.PuzzleBlock("Camal_Body_1.obj", "CamelBody_Base_Color.png", "piece1", -0.695431, 2.460062, 6.407862),
    --         Game.PuzzleBlock("Camal_Body_2.obj", "CamelBody2_Base_Color.png", "piece2", -0.769944, 2.431351, 7.053287)
    --     },
    --     tips = {
    --         "puzzle 9, tip1",
    --         "puzzle 9, tip2"
    --     },
    --     camPosition = {-3.449792, 2.660000, 7.062323},
    --     lightPosition = {-1.323179, 2.400000, 11.600792},
    --     wallPosition = {-0.835359, 0.731956, 3.084598}
    -- },
    -- {
    --     wallImage = "10_MainWall_Base_Color.png",   --POTION (done)
    --     blocks = {  
    --         Game.PuzzleBlock("Potion_Base.obj", "Potion_Base_Color.png", "piece1", -0.132431, 1.943297, 5.910479),
    --         Game.PuzzleBlock("Potion_Top.obj", "PotionTop_Base_Color.png", "piece2", -0.171941, 2.459845, 6.288596)
    --     },
    --     tips = {
    --         "puzzle 10, tip1",
    --         "puzzle 10, tip2"
    --     },
    --     camPosition = {-3.308889, 2.099800, 6.048161},
    --     lightPosition = {-1.6, 2.4, 13.4},
    --     wallPosition = {-2.482606, 2.089347, 1.852979}
    -- },
    -- {
    --     wallImage = "11_MainWall_Base_Color.png",   --ARKH (done)
    --     blocks = {  
    --         Game.PuzzleBlock("Ankh_Block.obj", "Ankh_Block_Base_Color.png", "piece1", -0.037408, 1.879630, 5.375822),
    --         Game.PuzzleBlock("Ankh_Smooth.obj", "Ankh_Smooth_Base_Color.png", "piece2", -0.385306, 2.647555, 5.986688)
    --     },
    --     tips = {
    --         "puzzle 10, tip1",
    --         "puzzle 10, tip2"
    --     },
    --     camPosition = {-3.587104, 2.380138, 5.942830},
    --     lightPosition = {-1.286625, 2.400000, 11.972546},
    --     wallPosition = {-3.612379, 3.936397, 1.054261}
    -- },
    -- {
    --     wallImage = "12_MainWall_Base_Color.png",   --UFO 
    --     blocks = {  
    --         Game.PuzzleBlock("UFO_Part1.obj", "UFO1_Base_Color.png", "piece1", -0.214553, 1.577794, 6.050745),
    --         Game.PuzzleBlock("UFO_Part2.obj", "UFO2_Base_Color.png", "piece2", -0.539950, 2.046320, 5.558316),
    --         Game.PuzzleBlock("UFO_Part3.obj", "UFO3_Base_Color.png", "piece3", 0.003840, 1.904312, 5.260504),
    --         Game.PuzzleBlock("UFO_Part4.obj", "UFO4_Base_Color.png", "piece4", 0.087823, 1.932990, 5.673162)
    --     },
    --     tips = {
    --         "puzzle 12, tip1",
    --         "puzzle 12, tip2"
    --     },
    --     camPosition = {-4.454628, 2.860016, 5.957380},
    --     lightPosition = {-1.6, 2.4, 13.4},
    --     wallPosition = {-4.099431, 0.326027, 1.404314}
    -- }
}

--Scales Puzzle pieces

story[1].blocks[1]:scale(0.08, 0.08, 0.08)

story[2].blocks[1]:scale(0.1, 0.1, 0.1)

story[3].blocks[1]:scale(0.08, 0.08, 0.08)

story[4].blocks[1]:scale(0.08, 0.08, 0.08)
story[4].blocks[2]:scale(0.08, 0.08, 0.08)

story[5].blocks[1]:scale(0.02, 0.02, 0.02)
story[5].blocks[2]:scale(0.02, 0.02, 0.02)

-- story[6].blocks[1]:scale(0.10, 0.10, 0.10)
-- story[6].blocks[2]:scale(0.10, 0.10, 0.10)

-- story[7].blocks[1]:scale(0.2, 0.2, 0.2)
-- story[7].blocks[2]:scale(0.15, 0.15, 0.15)

-- story[8].blocks[1]:scale(0.1, 0.1, 0.1)
-- story[8].blocks[2]:scale(0.085, 0.085, 0.085)


-- story[9].blocks[1]:scale(0.1, 0.1, 0.1)
-- story[9].blocks[2]:scale(0.09, 0.09, 0.09)

-- story[10].blocks[1]:scale(0.1, 0.1, 0.1)
-- story[10].blocks[2]:scale(0.09, 0.09, 0.09)

-- story[11].blocks[1]:scale(0.05,0.05, 0.05)
-- story[11].blocks[2]:scale(0.04, 0.04, 0.04)


-- story[12].blocks[1]:scale(0.1, 0.1, 0.1)
-- story[12].blocks[2]:scale(0.1, 0.1, 0.1)
-- story[12].blocks[3]:scale(0.1, 0.1, 0.1)
-- story[12].blocks[4]:scale(0.1, 0.1, 0.1)