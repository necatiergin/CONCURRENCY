##### Scenarios where std::this_thread::yield() may be used

1) Waiting for a Condition to Change (Spin-Waiting)<br>
When a thread is waiting for a shared variable to change but does not want to block execution, yield() allows other threads to proceed.

2️) Avoiding Busy-Waiting (CPU-Friendly)<br>
Instead of continuously polling (which wastes CPU cycles), yield() lets other threads run and prevents excessive CPU usage.

3️) Improving Responsiveness in Multi-Threaded Systems<br>
When a thread has done some work and expects other threads to act, calling yield() gives them a chance to execute sooner.

4️) Reducing Lock Contention<br>
If a thread is waiting for a mutex or lock, yield() can help prevent excessive contention by allowing other threads to acquire the lock.

5️) Game Loop Optimization<br>
In game development, yield() is sometimes used when polling for user input or rendering updates to avoid high CPU consumption.
