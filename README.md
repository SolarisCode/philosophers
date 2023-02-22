# philosophers
This C application demonstrates a solution to the dining philosophers problem using multithreading and mutual exclusion.
The program simulates multiple philosophers sitting at a table, each with a plate of spaghetti and two forks.
Philosophers alternate between thinking and eating, but must acquire both forks to eat.
To avoid deadlocks, forks are shared and protected by mutex locks.
