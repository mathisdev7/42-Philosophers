# Philosophers

![Final Score](https://i.ibb.co/DCtw70t/image.png)

## Project Description
The `Philosophers` project is a multithreading and synchronization exercise developed as part of the 42 School curriculum. It simulates the famous "Dining Philosophers" problem, where multiple philosophers alternately think, eat, and try to pick up shared forks without causing deadlocks or starvation. The project emphasizes understanding concurrency, thread synchronization, and resource management.

## Journey
This project was an insightful dive into parallel programming and thread synchronization. Initially, I faced challenges in preventing deadlocks and ensuring that all philosophers had a fair chance to eat. My first attempt was unsuccessful due to inefficient food distribution, leading to starvation issues. However, through careful debugging, mutex implementation, and condition variables, I was able to refine the algorithm and create a balanced and efficient simulation on my second attempt.

## Key Learnings
- Understanding multithreading and parallel programming
- Implementing mutexes and avoiding race conditions
- Preventing deadlocks and starvation in concurrent environments
- Managing shared resources efficiently
- Debugging synchronization issues

## Technical Details
- The program simulates philosophers sitting at a table, following these rules:
  - A philosopher must pick up both forks to eat.
  - Philosophers cannot communicate directly.
  - The simulation must prevent deadlocks and starvation.
- Implemented using:
  - Threads for concurrent execution.
  - Mutexes to protect shared resources.
  - Timers to track philosopher activity and avoid starvation.

## Project Status
- **First Attempt**: Unsuccessful (Inefficient food distribution led to starvation)
- **Second Attempt**: Success (Functional simulation with proper synchronization)
- **Completion Time**: ~10 days

## Challenges Faced
The most complex parts of this project included:
- Ensuring that philosophers do not starve while preventing deadlocks.
- Properly handling thread synchronization with minimal performance overhead.
- Debugging race conditions and unexpected behaviors in concurrent execution.
- Optimizing the algorithm to maintain fairness and efficiency.

## Reflection
This project provided a deep understanding of multithreading and the importance of careful resource management in concurrent systems. It strengthened my debugging skills and my ability to analyze synchronization issues, making it one of the most technically enriching projects at 42.

## Skills Developed
- Multithreading and synchronization
- Mutex management and race condition prevention
- Deadlock avoidance strategies
- Debugging concurrent programs
- Performance optimization in parallel computing

