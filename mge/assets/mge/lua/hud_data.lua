module("hud_data", package.seeall)
local HUD = {}
alignment = { LEFT_TOP = 1, LEFT_CENTER = 2, LEFT_BOTTOM = 3, CENTER_TOP = 4, CENTER_CENTER = 5, CENTER_BOTTOM = 6, RIGHT_TOP = 7, RIGHT_CENTER = 8, RIGHT_BOTTOM = 9 }

-- BUTTONS AND BOXES PARAMETERS START --
hud_textures =
{
    "land.jpg",     -- help_button_texture
    "bricks.jpg",   -- hint_button1_texture
    "bricks.jpg",   -- hint_button2_texture
    "bricks.jpg",   -- hint_button2_texture
    "land.jpg",     -- help_box_texture
    "bricks.jpg",   -- riddle_box_texture
    "bricks.jpg"    -- hints_box_texture
}

help_button_xOffset = 700
help_button_yOffset = 30
help_button_width = 80
help_button_height = 40
help_button_font = 15
help_button_text = "RIDDLE"
help_button_alignment = alignment.RIGHT_TOP

hint_button1_xOffset = 720
hint_button1_yOffset = 80
hint_button1_width = 40
hint_button1_height = 40
hint_button1_font = 15
hint_button1_text = "hint 1"
hint_button1_alignment = alignment.RIGHT_TOP

hint_button2_xOffset = 720
hint_button2_yOffset = 130
hint_button2_width = 40
hint_button2_height = 40
hint_button2_font = 15
hint_button2_text = "hint 2"
hint_button2_alignment = alignment.RIGHT_TOP

hint_button3_xOffset = 720
hint_button3_yOffset = 180
hint_button3_width = 40
hint_button3_height = 40
hint_button3_font = 15
hint_button3_text = "hint 3"
hint_button3_alignment = alignment.RIGHT_TOP

help_box_xOffset = 700
help_box_yOffset = 70
help_box_width = 80
help_box_height = 180
help_box_font = 30
help_box_text = ""
help_box_alignment = alignment.RIGHT_TOP

riddle_box_xOffset = 250
riddle_box_yOffset = 480
riddle_box_width = 300
riddle_box_height = 100
riddle_box_font = 30
riddle_box_text = "this is riddle"
riddle_box_alignment = alignment.CENTER_BOTTOM

hints_box_xOffset = 250
hints_box_yOffset = 480
hints_box_width = 300
hints_box_height = 100
hints_box_font = 30
hints_box_text1 = "this is hint #1"
hints_box_text2 = "this is hint #2"
hints_box_text3 = "this is hint #3"
hints_box_alignment = alignment.CENTER_BOTTOM
-- BUTTONS AND BOXES PARAMETERS START --

-- THIS PART SHOULD NOT BE TOUCHED --
HUD.hud_textures = hud_textures
HUD.alignment = alignment

HUD.help_button_xOffset = help_button_xOffset
HUD.help_button_yOffset = help_button_yOffset
HUD.help_button_width = help_button_width
HUD.help_button_height = help_button_height
HUD.help_button_font = help_button_font
HUD.help_button_text = help_button_text
HUD.help_button_alignment = help_button_alignment

HUD.hint_button1_xOffset = hint_button1_xOffset
HUD.hint_button1_yOffset = hint_button1_yOffset
HUD.hint_button1_width = hint_button1_width
HUD.hint_button1_height = hint_button1_height
HUD.hint_button1_font = hint_button1_font
HUD.hint_button1_text = hint_button1_text
HUD.hint_button1_alignment = hint_button1_alignment

HUD.hint_button2_xOffset = hint_button2_xOffset
HUD.hint_button2_yOffset = hint_button2_yOffset
HUD.hint_button2_width = hint_button2_width
HUD.hint_button2_height = hint_button2_height
HUD.hint_button2_font = hint_button2_font
HUD.hint_button2_text = hint_button2_text
HUD.hint_button2_alignment = hint_button2_alignment

HUD.hint_button3_xOffset = hint_button3_xOffset
HUD.hint_button3_yOffset = hint_button3_yOffset
HUD.hint_button3_width = hint_button3_width
HUD.hint_button3_height = hint_button3_height
HUD.hint_button3_font = hint_button3_font
HUD.hint_button3_text = hint_button3_text
HUD.hint_button3_alignment = hint_button3_alignment

HUD.help_box_xOffset = help_box_xOffset
HUD.help_box_yOffset = help_box_yOffset
HUD.help_box_width = help_box_width
HUD.help_box_height = help_box_height
HUD.help_box_font = help_box_font
HUD.help_box_text = help_box_text
HUD.help_box_alignment = help_box_alignment

HUD.riddle_box_xOffset = riddle_box_xOffset
HUD.riddle_box_yOffset = riddle_box_yOffset
HUD.riddle_box_width = riddle_box_width
HUD.riddle_box_height = riddle_box_height
HUD.riddle_box_font = riddle_box_font
HUD.riddle_box_text = riddle_box_text
HUD.riddle_box_alignment = riddle_box_alignment

HUD.hints_box_xOffset = hints_box_xOffset
HUD.hints_box_yOffset = hints_box_yOffset
HUD.hints_box_width = hints_box_width
HUD.hints_box_height = hints_box_height
HUD.hints_box_font = hints_box_font
HUD.hints_box_text1 = hints_box_text1
HUD.hints_box_text2 = hints_box_text2
HUD.hints_box_text3 = hints_box_text3
HUD.hints_box_alignment = hints_box_alignment

return HUD