module("hud_data", package.seeall)
local HUD = {}
alignment = { LEFT_TOP = 1, LEFT_CENTER = 2, LEFT_BOTTOM = 3, CENTER_TOP = 4, CENTER_CENTER = 5, CENTER_BOTTOM = 6, RIGHT_TOP = 7, RIGHT_CENTER = 8, RIGHT_BOTTOM = 9 }

-- BUTTONS AND BOXES PARAMETERS START --
display_riddle_at_start = 30

--Progressbar
progress_bar_xOffset = 0
progress_bar_yOffset = 50 
progress_bar_sprite_width = 672   	-- to change: do scale the actual picture and set this value to be the same size
progress_bar_sprite_height = 768	-- to change: do scale the actual picture and set this value to be the same size
progress_bar_sprite_rows = 8
progress_bar_alignment = alignment.CENTER_TOP

--Button for Riddle / Hints
help_button_xOffset = 25
help_button_yOffset = 30
help_button_width = 60
help_button_height = 40
help_button_alignment = alignment.RIGHT_TOP
help_button_texture = "bricks.jpg"

--Button for first hint
hint_button1_xOffset = 30
hint_button1_yOffset = 75
hint_button1_width = 50
hint_button1_height = 40
hint_button1_alignment = alignment.RIGHT_TOP
hint_button1_texture = "bricks.jpg"

--Button for second hint
hint_button2_xOffset = 30
hint_button2_yOffset = 120
hint_button2_width = 50
hint_button2_height = 40
hint_button2_alignment = alignment.RIGHT_TOP
hint_button2_texture = "bricks.jpg"

--Button for third hint
hint_button3_xOffset = 30
hint_button3_yOffset = 165
hint_button3_width = 50
hint_button3_height = 40
hint_button3_alignment = alignment.RIGHT_TOP
hint_button3_texture = "bricks.jpg"

--Label behind the hint buttons
help_box_xOffset = 28
help_box_yOffset = 70
help_box_width = 54
help_box_height = 140
help_box_alignment = alignment.RIGHT_TOP
help_box_texture = "bricks.jpg"

--Label that shows the riddle
riddle_box_xOffset = 0
riddle_box_yOffset = 15
riddle_box_width = 900
riddle_box_height = 100
riddle_box_font = 30
riddle_box_text = "What two things can you\nnever eat for breakfast?"
riddle_box_alignment = alignment.CENTER_BOTTOM
riddle_box_texture = "bricks.jpg"

--Label that shows the actual hint
hints_box_xOffset = 250
hints_box_yOffset = 480
hints_box_width = 300
hints_box_height = 100
hints_box_font = 30
hints_box_text1 = "this is hint #1"
hints_box_text2 = "this is hint #2"
hints_box_text3 = "this is hint #3"
hints_box_alignment = alignment.CENTER_BOTTOM
hints_box_texture = "bricks.jpg"
-- BUTTONS AND BOXES PARAMETERS START --

-- THIS PART SHOULD NOT BE TOUCHED --
HUD.alignment = alignment
HUD.display_riddle_at_start = display_riddle_at_start

HUD.progress_bar_xOffset = progress_bar_xOffset
HUD.progress_bar_yOffset = progress_bar_yOffset
HUD.progress_bar_sprite_width = progress_bar_sprite_width 
HUD.progress_bar_sprite_height = progress_bar_sprite_height
HUD.progress_bar_sprite_rows = progress_bar_sprite_rows
HUD.progress_bar_alignment = progress_bar_alignment

-- riddle / hint / help button
HUD.help_button_xOffset = help_button_xOffset
HUD.help_button_yOffset = help_button_yOffset
HUD.help_button_width = help_button_width
HUD.help_button_height = help_button_height
HUD.help_button_alignment = help_button_alignment
HUD.help_button_texture = help_button_texture

--Button for first hint
HUD.hint_button1_xOffset = hint_button1_xOffset
HUD.hint_button1_yOffset = hint_button1_yOffset
HUD.hint_button1_width = hint_button1_width
HUD.hint_button1_height = hint_button1_height
HUD.hint_button1_alignment = hint_button1_alignment
HUD.hint_button1_texture = hint_button1_texture

--Button for second hint
HUD.hint_button2_xOffset = hint_button2_xOffset
HUD.hint_button2_yOffset = hint_button2_yOffset
HUD.hint_button2_width = hint_button2_width
HUD.hint_button2_height = hint_button2_height
HUD.hint_button2_alignment = hint_button2_alignment
HUD.hint_button2_texture = hint_button2_texture

--Button for third hint
HUD.hint_button3_xOffset = hint_button3_xOffset
HUD.hint_button3_yOffset = hint_button3_yOffset
HUD.hint_button3_width = hint_button3_width
HUD.hint_button3_height = hint_button3_height
HUD.hint_button3_alignment = hint_button3_alignment
HUD.hint_button3_texture = hint_button3_texture

-- background of the hintbuttons
HUD.help_box_xOffset = help_box_xOffset
HUD.help_box_yOffset = help_box_yOffset
HUD.help_box_width = help_box_width
HUD.help_box_height = help_box_height
HUD.help_box_alignment = help_box_alignment
HUD.help_box_texture = help_box_texture

-- actual riddle
HUD.riddle_box_xOffset = riddle_box_xOffset
HUD.riddle_box_yOffset = riddle_box_yOffset
HUD.riddle_box_width = riddle_box_width
HUD.riddle_box_height = riddle_box_height
HUD.riddle_box_font = riddle_box_font
HUD.riddle_box_text = riddle_box_text
HUD.riddle_box_alignment = riddle_box_alignment
HUD.riddle_box_texture = riddle_box_texture

-- actual hint
HUD.hints_box_xOffset = hints_box_xOffset
HUD.hints_box_yOffset = hints_box_yOffset
HUD.hints_box_width = hints_box_width
HUD.hints_box_height = hints_box_height
HUD.hints_box_font = hints_box_font
HUD.hints_box_text1 = hints_box_text1
HUD.hints_box_text2 = hints_box_text2
HUD.hints_box_text3 = hints_box_text3
HUD.hints_box_alignment = hints_box_alignment
HUD.hints_box_texture = hints_box_texture

return HUD