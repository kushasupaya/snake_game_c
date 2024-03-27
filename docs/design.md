# Design Document

My process for this would be similar to that of the other assignments which is reading the handout properly. Then after receiving the stencil getting the feel for each program on it would be and planning the next move.

Since there are lot of files and tons of test cases my approach would be **prototype first approach**. I would make some changes try the test case; fix if needed; test again and then move on to the next task.

Before getting started I would definitely revisit the C-primers to improve my skills and knowledge. Additionally concepts such as memory allocation and ASCII vs Unicode representations is another thing to learn about.

## Part 1

There are three sub sections for part 1. This section is just the basic part of the snake game which consists of starting the game, making the snake move, creating the board, updating the game.

Starting off I need to figure out the global variables that represents the snake. The global variables could be the score, snakes position, length and direction. Then after this I would move over to initializing my default board. I know I need to do something with `malloc` which allocates the memory dynamically but we need to free the memory at the end.

For second section I need to update the game. My strategy here would be to study the `update` function properly. I would need to change my snake depending on the input key. The snakes global variable containing position and direction would be then updated depending on the key. This will help me with the `game loop` as this is the part of it. Furthermore I need to make sure all the user inputs are handled in this `update` function then make the snake data update accordingly.

Board decompression might be a obstacle. Need to do some research on `C string library` more specifically `strtok_r`. Furthermore converting strings to integers with function like `atoi` would be helpful.

## Part 2

The concept of `structs` is familiar to me. In this part we would use `structs` to represent snakes data instead of global variables. The concept of a growing snake after eating food is core to the snake game. So definitely making changes to the snake struct to handle this case is needed. How do you allocate memory to accomodate your snake is the bigger challenge here. Concepts of `malloc` and `free` might be useful here but I need to dig deeper. Rendering the game over screen would be another fun challenge here. Furthermore taking the user name from the input wouldn't be much of a hassle.

Handling error for all the strategies that I have mentioned is something I need to work on. Since it is a prototype approach I would change a small thing check it and I would immediately know if I need to handle error for such case.

## Part 3

This part is all about the challenges of ASCII vs Unicode (UTF-8 encoding). I have some experience working with forms were the input is not English language and storing the user input as it is in the database. Thankfully most databases have utf-8 encoding on the columns if you mention it. But managing it in the frontend is a different hassle. Doing some research on how to handle it in `C` would be a good starting point I guess.

## Extra Credit

To be honest, I don't know what I would want to do for extra credit. Changing the food icon to a `Bell` character sound interesting and achievable. I would definitely try this if I have time.
