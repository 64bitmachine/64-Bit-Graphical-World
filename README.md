Intro:

    This code base was created as part of my undergraduate course 
    Computer Graphics (CS475) - https://www.cse.iitb.ac.in/~paragc/teaching/2017/cs475/

Notes:

    1. OpenGL is a large state machine
    2. Macro view of working:
        (create context -> change options -> render the context)

Dependencies:

    sudo apt install libglew2.1
    sudo apt install mesa-utils
    sudo apt install freeglut3-dev
    sudo ln -f -s /usr/lib/x86_64-linux-gnu/libGLEW.so.2.1 /usr/lib/libGLEW.so.2.0
    sudo apt install libglfw3-dev
    sudo apt install libglew-dev

x, y, z direction are assumed same as opengl x, y, z direction convention<br/>
Keys binding:
        
    space	-	toggle lights
    left control	-	open sliding door
    right control	-	close sliding door
    left shift	-	open door
    right shift	-	close door
    right alt	-	toggle lamp lights
    left alt	-	save screenshot
    tab			-	saving key frame
    
    l 	-	start camera animation
    p   - 	draw control points for beizer curve
    t	-	open the lid of music box
    y	-	close the lid of music box
    w	-	camera forward movement
    a	-	camera left movement
    s	-	camera backward	movement
    d	-	camera right movement
    z	-	camera moving upwards
    x	-	camera moving downwards
    q	-	camera rotating clockwise to right
    e	-	camera rotating anti-clockwise to left

    j	-	open keyframe file for writing
    k 	-	save keyframe
    esc	-	close the program

Video preview : https://youtu.be/rVoDl_9Dk74

Reference:

    1. LearnOpenGl.com
