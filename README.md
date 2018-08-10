"make all" to compile gui program
"./RUNME" to run it
"make test" to compile a* testing program (runs 5 a* solutions for k=5-20)
Files
===========
* gearball.h:	class structure for gear, side, and ball
* astar.h:	aStar search structure (that works although inefficient)
* astar2.h:	my first attempt at using astar (compiles but does not really work, seg faults at depth = 2)
* astar3.h:	a tertiary attempt at using astar (not finished as I realized the method I was using didn't work out)
* gearball.cpp:	class function definitions
* Makefile:	used to compile the program
* main.cpp:	GUI structure
* README.md:	This file
* graph1.png	graph of results 1-6
* graph2.png	graph of results 5-20

The AStar Algorithm & What I learned in Program 2
----------------------------------------------------
As you can see from the 3 different astar.h files, I had some difficulty implementing this algorithm.
My first attempt can be seen in astar2.h. This attempt is what I believe to be the "proper" method, using priority_queues and
(at least originally) sets and maps. However, in my first iteration of this file, the program would loop infinitely after reaching a depth of 3.
For solves involving only 1 or 2 rotations, it worked fine. After several hours of messing around with this, I realized the issue was with
how maps compare two objects. I explained my issue on the discussion board, quoted here:

	"I attempted to implement a* using maps of my GearBall class to integers representing the gScore and aScore. 
	However this ended up not working because the map data structure uses the '<' operator to compare elements. 
	I could not for the life of me think of a way to make two balls compare in such a way except using the heuristic. 
	But doing so means two balls that have the same heuristic would be identified as the same despite being different states.
	I have since switched to just using vectors, but I still feel that maps would offer a significant time improvement.
	Does anyone have an idea of how I could compare Ball structures in such a manner?"

Unable to find an solution to my issue, I switched to using a vector based version of the algorithm. For detail in my implementation, please see
comments in astar.h

Dr. Goldsmith was kind enough to reply to my query, and although I had already begun testing of my version of a*, I was eager to try and implement
her suggestions. What you now see in astar2.h, is the results of how I interpreted her help. However, I was still unable to make signifigant progress
with maps. After research into other implementations of a* such as these:
	http://www.redblobgames.com/pathfinding/a-star/introduction.html
	https://stackoverflow.com/questions/41558850/a-star-algorithm-in-c
	http://www.geeksforgeeks.org/a-search-algorithm/
I arrived at a conclusion. A* works best when you can map out every possible state of game, or every position you can end up in. This is why it is
particularly good at path finding. A grid can be represented as a graph or array, and you can initialize every gScore or fScore on this structure.
Thus, lookUps via maps or simple array accesses are much more feasible. The key issue I had with similar structures in this project, is that I had
to continually iterate through the sets of objects to see if I had already found the ball, as every state could not be pre-mapped. 
Data structures like maps and priority_queues use the '<' operator for this, and since more than one ball can have the same fScore but different
values, I could not find a way to implement them.

In fact, each of these implementations linked above have initialized maps or arrays containing g and f scores. A feat impossible as every possible
combination of the gearball is unknown.

The third attempt of a* is taken from the approach in the stack overflow link, using nodes and pointers. This however did not pan out either, as
it also required initialization of every possible node.

I know that proper use of priority queue's and maps would make this algorithm run faster. 
However with this many iterations (especially with 20 turns) this program can be expected to take a long amount of time to run regardless.
With my vector implementation, solving a ball to 5 levels can take between 30min-1hr.
With 75 neccessary tests, getting exponentially difficult, at BEST case this will take 75 hrs to complete. While I did not leave this project to 
the last minute, I may not have 75 hours of testing time (or memory to handle it available). So please forgive me if my graphs are not up to par.
In testing. Solving a gearball with depth > 6 took > 8hrs... As such, my graph only goes up to 6 as that is all I could
do before my computer locked up and would not complete the tests overnight.

I have included graphs from 1-6 and an additional graph from 5-20 using predictive methods (an exponential regression formula).

One might assume that at high solves (ie 20) the number of necessary moves would fall back down. While this may be the
case for some solves, it may not be true for the majority. If we compare to the rubix's cube for a minute:

"God's number" is the number of turns in which every rubix's cube can be solved. Right now, for the quarter turn method,
this number is 26 for the cube. See link:
	http://www.cube20.org/

While the gearball may be less complex than the cube, I'd take an educated guess that god's number for our cube is somewhere
in the 15-20 range, thus requiring solves involving 15-20 turns to take a* to a depth of 15-20 forgiving some lucky coincidence
where the moves tend to solve the ball itself. This however is also unlikely as there are built in protections against that
in the randomizer.
_________________________________________

BELOW IS A REPEAT OF PROJ 1 INFORMATION
_________________________________________

GUI
--------
GUI prints out representation in the following manner

                        P|G

                        GGG
                Y|G     GGG     G|O
                        GGG

                        G|R

        YYY             RRR             OOO
P|Y     YYY     Y|R     RRR     R|O     OOO     O|P
        YYY             RRR             OOO

                        R|B

                        BBB
                Y|B     BBB     B|O
                        BBB

                        B|P

                        PPP
        P|Y             PPP             O|P
                        PPP

                        P|G

Data Structures
----------------
Gear:
	represented by 2 colors (for each side) and number of rotations
	in correct orientation when mod 6 = 0
	different positions shown below with colors 1 and 2

	functions to print rotate gears left and right are in this class

1       1       2       2       2       1       1
- ->    \ ->    / ->    - ->    \ ->    / ->    -
2       2       1       1       1       2       2

0       1       2       3       4       5       6

1|2     1/2     2\1     2|1     2/1     1\2     1|2


Side:
	represented by a 3x3 grid and pointers to connected gears and faces
	Face structure and its rotations shown below

	functions to print and rotate face left and right are included

                G

        1       2       3
  G     4       5       6    G
        7       8       9

                G

258     012     630
147  <- 345 ->  741
036     678     852

Ball:
	Contains 8 side objects for each face
	Contains 12 gear objects that each face points too
	functions to rotate each face and print the ball are included
	the randMoves function exists in this class


Randomizer (defined in gearball.cpp)
------------
The randomizer function takes in an integer, then generates that many moves
works by using the srand() function to generate a number between 1 and 6 and preform the necessary rotation
also includes protections to make sure the moves arent repeated more than 12 times 
	and the move does not undo the one immediately previous to it


Heuristic
-----------
As discussed in class, the key thing to determine how solved a gearball 
	is is to determine the number tiles out of place. However, it is
	important to normalize this by the maximum number of tiles that can
	be displaced in a single rotation. 
	If you rotate the top and bottom sides, you displace the top and 
	bottom layers of the front, left, right, and rear sides. If you 
	include all the gears + the faces you rotated, this brings the
	total number of moves is 52.
	So the heuristic is calculated by counting the number of misplaced
	tiles and dividing by 52.

What I learned (project 1)
---------------

I learned a lot about what goes into a heuristic and modeling a moving puzzle
Knowing how all peices interact and move is much more difficult than
originally thought and led to a large number of errors in judgement.
The heuristic was additionally difficult as finding a lowerbound was 
more challenging than anticipated as many heuristics that are first
thought of dont work well. I am very excited to get a-star to work on
solving it.
