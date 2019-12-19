# MatrixGame-Atari-Breakout

#### HARDWARE: 
- 1 x Arduino Uno
- 1 x 8x8 LED Matrix 
- 1 x MAX7219 Driver 
- 1 x LCD Screen 
- 2 x Potentiometers
- 1 x Joystick 
- 2 x Breadboards 
- Wires 
 
#### HOW TO PLAY: 

1. Select "Start Game" in the menu by pressing down on the joystick 
2. The ball will leave the paddle in a random direction towards the bricks and destroy each one it touches. Each brick is worth 5 points.
3. You have completed the level once every brick is destroyed. As you advance through the levels, the game speed will increase.   
4. You have 3 lives at the start of the game. If you did not catch the ball with your paddle, you will lose 1 life. 







##### INITIAL DETAILS: 

My game will simulate the famous game Atari Breakout, or as a more general name that's been adopted by other developers, Brick Breaker. We will use a 8x8 led matrix, of course representing the game elements, the paddle, the ball and the wall of bricks. The point of the game is to destroy all the bricks using the ball and also not letting the ball fall by catching it with the paddle. 

The game will be rewarding the user by score, having it increase by a certain amount of points each time it destroys a brick. Also, each time the user will level up, the score will increase, along with the speed of the ball, as to account for variable difficulty. The user will start with 3 lives and will lose 1 each time the ball slips past the paddle. 

The high-score will be saved and displayed in the menu. 
