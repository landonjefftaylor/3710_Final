#include "stm32l476xx.h"
#include "TASK.h"

uint8_t** inputs = {
	"inpt1",
	"inpt2",
	"inpt3"
};

// READ 27.3 Random Number Genrateor RNG

/* PSEUDOCODE FOR MASTER

Randomly pick two tasks, one in task[0] and one in task[1]
Send task[] to the slave module
Send task[0] to COM (slave will send task[1] to COM)
Wait for ok[] to come back
If ok[0] or ok[1] is 'n':
	Give a task-appropriate penalty
	Update either one or both tasks
If ok[0] is 'y':
	Give a task-appropriate reward
	Update task[0] to a new random task
	Send task[new_task, '\0'] to slave module
If ok[1] is 'y'
	Give a task-appropriate reward
	Update task[1] to a new random task
	Send task['\0', new_task] to slave module
Else:
	

*/

/* PSEUDOCODE FOR SLAVE

*/

/* TASK LIST
A:
B:
C:
D:
E:
F:
G:
H:
I:
J:
K:
L:
M:
N:
O:
P:
Q:
R:
S:
T:
U:
V:
W:
X:
Y:
Z:

*/
