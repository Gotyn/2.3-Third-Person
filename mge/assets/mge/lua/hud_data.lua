module("hud_data", package.seeall)
local HUD = {}
alignment = { LEFT_TOP = 1, LEFT_CENTER = 2, LEFT_BOTTOM = 3, CENTER_TOP = 4, CENTER_CENTER = 5, CENTER_BOTTOM = 6, RIGHT_TOP = 7, RIGHT_CENTER = 8, RIGHT_BOTTOM = 9 }

-- BUTTONS AND BOXES PARAMETERS START --
display_riddle_at_start = 20

--Progressbar
progress_bar_xOffset = 0
progress_bar_yOffset = 50 
progress_bar_sprite_width = 672   	-- to change: do scale the actual picture and set this value to be the same size
progress_bar_sprite_height = 768	-- to change: do scale the actual picture and set this value to be the same size
progress_bar_sprite_rows = 8
progress_bar_scaleX = 0.5
progress_bar_scaley = 0.5
progress_bar_alignment = alignment.CENTER_TOP
progress_bar_texture = "Progress_256.png"

--Button for Riddle / Hints
help_button_xOffset = 20
help_button_yOffset = 20
help_button_width = 512				-- spriteWidth / columns
help_button_height = 512
help_button_scaleX = 0.14
help_button_scaleY = 0.14
help_button_alignment = alignment.RIGHT_TOP
help_button_texture = "Hint_Button_Shinx_Sprite.png"

--Button for first hint
hint_button1_xOffset = 30
hint_button1_yOffset = 92
hint_button1_width = 512			-- spriteWidth / columns
hint_button1_height = 512
hint_button1_scaleX = 0.1
hint_button1_scaleY = 0.1
hint_button1_alignment = alignment.RIGHT_TOP
hint_button1_texture = "Hint_Button_1_Sprite.png"

--Button for second hint
hint_button2_xOffset = 30
hint_button2_yOffset = 140
hint_button2_width = 512			-- spriteWidth / columns
hint_button2_height = 512
hint_button2_scaleX = 0.1
hint_button2_scaleY = 0.1
hint_button2_alignment = alignment.RIGHT_TOP
hint_button2_texture = "Hint_Button_2_Sprite.png"

--Button for third hint
hint_button3_xOffset = 30
hint_button3_yOffset = 188
hint_button3_width = 512			-- spriteWidth / columns
hint_button3_height = 512
hint_button3_scaleX = 0.1
hint_button3_scaleY = 0.1
hint_button3_alignment = alignment.RIGHT_TOP
hint_button3_texture = "Hint_Button_3_Sprite.png"

--Label that shows menu container
menu_box_xOffset = 0
menu_box_yOffset = 0
menu_box_width = 500
menu_box_height = 500
menu_box_scaleX = 1
menu_box_scaleY = 1
menu_box_alignment = alignment.LEFT_CENTER
menu_box_texture = "bricks.jpg"

--Label that shows storybook container
story_book_xOffset = 0
story_book_yOffset = 0
story_book_width = 300
story_book_height = 250
story_book_scaleX = 1
story_book_scaleY = 1
story_book_alignment = alignment.RIGHT_CENTER
story_book_texture = "bricks.jpg"

--Continue button in storybook container
story_book_button_xOffset = 0
story_book_button_yOffset = 0
story_book_button_width = 100
story_book_button_height = 75
story_book_button_scaleX = 1
story_book_button_scaleY = 1
story_book_button_alignment = alignment.RIGHT_CENTER
story_book_button_texture = "land.jpg"

--Start button in menu
start_button_xOffset = 50
start_button_yOffset = 0
start_button_width = 100			    -- spriteWidth / columns
start_button_height = 50
start_button_scaleX = 1
start_button_scaleY = 1
start_button_alignment = alignment.LEFT_CENTER
start_button_texture = "land.jpg"

--Resume button in menu
resume_button_xOffset = 170
resume_button_yOffset = 120
resume_button_width = 100	        -- spriteWidth / columns
resume_button_height = 50
resume_button_scaleX = 1
resume_button_scaleY = 1
resume_button_alignment = alignment.LEFT_CENTER
resume_button_texture = "land.jpg"

--Exit button in menu
exit_button_xOffset = 290
exit_button_yOffset = 240
exit_button_width = 100		    -- spriteWidth / columns
exit_button_height = 50
exit_button_scaleX = 1
exit_button_scaleY = 1
exit_button_alignment = alignment.LEFT_CENTER
exit_button_texture = "land.jpg"

--Label behind the hint buttons (helpbox)
help_box_xOffset = 27
help_box_yOffset = 25
help_box_width = 512
help_box_height = 2048
help_box_scaleX = 0.11
help_box_scaleY = 0.11
help_box_alignment = alignment.RIGHT_TOP
help_box_texture = "Dropdown_Box.png"

--Label that shows the riddle
riddle_box_xOffset = 0
riddle_box_yOffset = 15
riddle_box_width = 900
riddle_box_height = 100
riddle_box_font = 30
riddle_box_scaleX = 1
riddle_box_scaleY = 1
riddle_box_text = "What two things can you\nnever eat for breakfast?"
riddle_box_alignment = alignment.CENTER_BOTTOM
riddle_box_texture = "bricks.jpg"

--Label that shows the actual hint
hints_box_xOffset = 250
hints_box_yOffset = 480
hints_box_width = 300
hints_box_height = 100
hints_box_font = 30
hints_box_scaleX = 1
hints_box_scaleY = 1
hints_box_text1 = "this is hint #1"
hints_box_text2 = "this is hint #2"
hints_box_text3 = "this is hint #3"
hints_box_alignment = alignment.CENTER_BOTTOM
hints_box_texture = "bricks.jpg"
-- BUTTONS AND BOXES PARAMETERS START --

--------------------------------------------------------------------------------
---||\--||--|||||||--|||||||--|||||||--|||||||--|||||||--|||||||--|||||||---------
---||\\-||--||---||--||---||--||---||--||---||--||---||--||---||--||---||-------
---||-\\||--|||||||--|||||||--|||||||--|||||||--|||||||--|||||||--|||||||---------
--------------------------------------------------------------------------------

-- THIS PART SHOULD NOT BE TOUCHED --
HUD.alignment = alignment
HUD.display_riddle_at_start = display_riddle_at_start

HUD.progress_bar_xOffset = progress_bar_xOffset
HUD.progress_bar_yOffset = progress_bar_yOffset
HUD.progress_bar_sprite_width = progress_bar_sprite_width 
HUD.progress_bar_sprite_height = progress_bar_sprite_height
HUD.progress_bar_sprite_rows = progress_bar_sprite_rows
HUD.progress_bar_scaleX = progress_bar_scaleX
HUD.progress_bar_scaleY = progress_bar_scaleY
HUD.progress_bar_alignment = progress_bar_alignment
HUD.progress_bar_texture = progress_bar_texture

-- riddle / hint / help button
HUD.help_button_xOffset = help_button_xOffset
HUD.help_button_yOffset = help_button_yOffset
HUD.help_button_width = help_button_width
HUD.help_button_height = help_button_height
HUD.help_button_scaleX = help_button_scaleX
HUD.help_button_scaleY = help_button_scaleY
HUD.help_button_alignment = help_button_alignment
HUD.help_button_texture = help_button_texture

--Button for first hint
HUD.hint_button1_xOffset = hint_button1_xOffset
HUD.hint_button1_yOffset = hint_button1_yOffset
HUD.hint_button1_width = hint_button1_width
HUD.hint_button1_height = hint_button1_height
HUD.hint_button1_scaleX = hint_button1_scaleX
HUD.hint_button1_scaleY = hint_button1_scaleY
HUD.hint_button1_alignment = hint_button1_alignment
HUD.hint_button1_texture = hint_button1_texture

--Button for second hint
HUD.hint_button2_xOffset = hint_button2_xOffset
HUD.hint_button2_yOffset = hint_button2_yOffset
HUD.hint_button2_width = hint_button2_width
HUD.hint_button2_height = hint_button2_height
HUD.hint_button2_scaleX = hint_button2_scaleX
HUD.hint_button2_scaleY = hint_button2_scaleY
HUD.hint_button2_alignment = hint_button2_alignment
HUD.hint_button2_texture = hint_button2_texture

--Button for third hint
HUD.hint_button3_xOffset = hint_button3_xOffset
HUD.hint_button3_yOffset = hint_button3_yOffset
HUD.hint_button3_width = hint_button3_width
HUD.hint_button3_height = hint_button3_height
HUD.hint_button3_scaleX = hint_button3_scaleX
HUD.hint_button3_scaleY = hint_button3_scaleY
HUD.hint_button3_alignment = hint_button3_alignment
HUD.hint_button3_texture = hint_button3_texture

--Exit button in menu
HUD.exit_button_xOffset = exit_button_xOffset
HUD.exit_button_yOffset = exit_button_yOffset
HUD.exit_button_width = exit_button_width
HUD.exit_button_height = exit_button_height
HUD.exit_button_scaleX = exit_button_scaleX
HUD.exit_button_scaleY = exit_button_scaleY
HUD.exit_button_alignment = exit_button_alignment
HUD.exit_button_texture = exit_button_texture

--Resume button in menu
HUD.resume_button_xOffset = resume_button_xOffset
HUD.resume_button_yOffset = resume_button_yOffset
HUD.resume_button_width = resume_button_width
HUD.resume_button_height = resume_button_height
HUD.resume_button_scaleX = resume_button_scaleX
HUD.resume_button_scaleY = resume_button_scaleY
HUD.resume_button_alignment = resume_button_alignment
HUD.resume_button_texture = resume_button_texture

--Start button in menu
HUD.start_button_xOffset = start_button_xOffset
HUD.start_button_yOffset = start_button_yOffset
HUD.start_button_width = start_button_width
HUD.start_button_height = start_button_height
HUD.start_button_scaleX = start_button_scaleX
HUD.start_button_scaleY = start_button_scaleY
HUD.start_button_alignment = start_button_alignment
HUD.start_button_texture = start_button_texture

--Continue button in storybook container
HUD.story_book_button_xOffset = story_book_button_xOffset
HUD.story_book_button_yOffset = story_book_button_yOffset
HUD.story_book_button_width = story_book_button_width
HUD.story_book_button_height = story_book_button_height
HUD.story_book_button_scaleX = story_book_button_scaleX
HUD.story_book_button_scaleY = story_book_button_scaleY
HUD.story_book_button_alignment = story_book_button_alignment
HUD.story_book_button_texture = story_book_button_texture

-- background of the hintbuttons
HUD.help_box_xOffset = help_box_xOffset
HUD.help_box_yOffset = help_box_yOffset
HUD.help_box_width = help_box_width
HUD.help_box_height = help_box_height
HUD.help_box_scaleX = help_box_scaleX
HUD.help_box_scaleY = help_box_scaleY
HUD.help_box_alignment = help_box_alignment
HUD.help_box_texture = help_box_texture

-- actual riddle
HUD.riddle_box_xOffset = riddle_box_xOffset
HUD.riddle_box_yOffset = riddle_box_yOffset
HUD.riddle_box_width = riddle_box_width
HUD.riddle_box_height = riddle_box_height
HUD.riddle_box_font = riddle_box_font
HUD.riddle_box_text = riddle_box_text
HUD.riddle_box_scaleX = riddle_box_scaleX
HUD.riddle_box_scaleY = riddle_box_scaleY
HUD.riddle_box_alignment = riddle_box_alignment
HUD.riddle_box_texture = riddle_box_texture

-- actual menu container
HUD.menu_box_xOffset = menu_box_xOffset
HUD.menu_box_yOffset = menu_box_yOffset
HUD.menu_box_width = menu_box_width
HUD.menu_box_height = menu_box_height
HUD.menu_box_alignment = menu_box_alignment
HUD.menu_box_texture = menu_box_texture
HUD.menu_box_scaleX = menu_box_scaleX
HUD.menu_box_scaleY = menu_box_scaleY

-- actual story book container
HUD.story_book_xOffset = story_book_xOffset
HUD.story_book_yOffset = story_book_yOffset
HUD.story_book_width = story_book_width
HUD.story_book_height = story_book_height
HUD.story_book_scaleX = story_book_scaleX
HUD.story_book_scaleY = story_book_scaleY
HUD.story_book_alignment = story_book_alignment
HUD.story_book_texture = story_book_texture

-- actual hint
HUD.hints_box_xOffset = hints_box_xOffset
HUD.hints_box_yOffset = hints_box_yOffset
HUD.hints_box_width = hints_box_width
HUD.hints_box_height = hints_box_height
HUD.hints_box_font = hints_box_font
HUD.hints_box_text1 = hints_box_text1
HUD.hints_box_text2 = hints_box_text2
HUD.hints_box_text3 = hints_box_text3
HUD.hints_box_scaleX = hints_box_scaleX
HUD.hints_box_scaleY = hints_box_scaleY
HUD.hints_box_alignment = hints_box_alignment
HUD.hints_box_texture = hints_box_texture

return HUD