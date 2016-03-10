local HUD = {}

-- BUTTONS AND BOXES PARAMETERS START --
hud_textures =
{
    "land",     -- help_button_texture
    "bricks",   -- hint_button1_texture
    "bricks",   -- hint_button2_texture
    "bricks",   -- hint_button2_texture
    "land",     -- help_box_texture
    "bricks",   -- riddle_box_texture
    "bricks"    -- hints_box_texture
}

help_button_x = 700
help_button_y = 30
help_button_width = 80
help_button_height = 40
help_button_font = 15
help_button_text = "RIDDLE"

hint_button1_x = 720
hint_button1_y = 80
hint_button1_width = 40
hint_button1_height = 40
hint_button1_font = 15
hint_button1_text = "hint 1"

hint_button2_x = 720
hint_button2_y = 130
hint_button2_width = 40
hint_button2_height = 40
hint_button2_font = 15
hint_button2_text = "hint 2"

hint_button3_x = 720
hint_button3_y = 180
hint_button3_width = 40
hint_button3_height = 40
hint_button3_font = 15
hint_button3_text = "hint 3"

help_box_x = 700
help_box_y = 70
help_box_width = 80
help_box_height = 180
help_box_font = 30
help_box_text = ""

riddle_box_x = 250
riddle_box_y = 480
riddle_box_width = 300
riddle_box_height = 100
riddle_box_font = 30
riddle_box_text = "this is riddle"

hints_box_x = 250
hints_box_y = 480
hints_box_width = 300
hints_box_height = 100
hints_box_font = 30
hints_box_text1 = "this is hint #1"
hints_box_text2 = "this is hint #2"
hints_box_text3 = "this is hint #3"
-- BUTTONS AND BOXES PARAMETERS START --

-- THIS PART SHOULD NOT BE TOUCHED --
HUD.hud_textures = hud_textures

HUD.help_button_x = help_button_x
HUD.help_button_y = help_button_y
HUD.help_button_width = help_button_width
HUD.help_button_height = help_button_height
HUD.help_button_font = help_button_font
HUD.help_button_text = help_button_text

HUD.hint_button1_x = hint_button1_x
HUD.hint_button1_y = hint_button1_y
HUD.hint_button1_width = hint_button1_width
HUD.hint_button1_height = hint_button1_height
HUD.hint_button1_font = hint_button1_font
HUD.hint_button1_text = hint_button1_text

HUD.hint_button2_x = hint_button2_x
HUD.hint_button2_y = hint_button2_y
HUD.hint_button2_width = hint_button2_width
HUD.hint_button2_height = hint_button2_height
HUD.hint_button2_font = hint_button2_font
HUD.hint_button2_text = hint_button2_text

HUD.hint_button3_x = hint_button3_x
HUD.hint_button3_y = hint_button3_y
HUD.hint_button3_width = hint_button3_width
HUD.hint_button3_height = hint_button3_height
HUD.hint_button3_font = hint_button3_font
HUD.hint_button3_text = hint_button3_text

HUD.help_box_x = help_box_x
HUD.help_box_y = help_box_y
HUD.help_box_width = help_box_width
HUD.help_box_height = help_box_height
HUD.help_box_font = help_box_font
HUD.help_box_text = help_box_text

HUD.riddle_box_x = riddle_box_x
HUD.riddle_box_y = riddle_box_y
HUD.riddle_box_width = riddle_box_width
HUD.riddle_box_height = riddle_box_height
HUD.riddle_box_font = riddle_box_font
HUD.riddle_box_text = riddle_box_text

HUD.hints_box_x = hints_box_x
HUD.hints_box_y = hints_box_y
HUD.hints_box_width = hints_box_width
HUD.hints_box_height = hints_box_height
HUD.hints_box_font = hints_box_font
HUD.hints_box_text1 = hints_box_text1
HUD.hints_box_text2 = hints_box_text2
HUD.hints_box_text3 = hints_box_text3

return HUD