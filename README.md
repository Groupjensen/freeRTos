My FreeRTOS Journey

Description

This project explores the functionality of the FreeRTOS real-time operating system (RTOS) on Arduino platforms. Through a series of practical examples, you'll learn how to manage tasks, synchronize execution, and handle data in real-time embedded systems.

Getting Started

To get started with this project, ensure you have Visual Studio Code (VS Code) and the PlatformIO extension installed. You can download VS Code from [https://code.visualstudio.com/](https://code.visualstudio.com/) and install the PlatformIO extension within VS Code.

Prerequisites

VS Code with the PlatformIO extension

Basic understanding of Arduino programming and C++

Installation

1. VS Code: Download and install Visual Studio Code.

2. PlatformIO extension: Install the PlatformIO extension from the VS Code marketplace.

3. Clone the repository: Clone this GitHub repository to your local machine.

4. Open the project: Open the cloned directory in VS Code.

5. PlatformIO handles FreeRTOS: PlatformIO will automatically manage the FreeRTOS library dependency, so you don't need to add it manually.

Usage

After setting up the environment, open the provided examples in VS Code. Each example is designed to illustrate a specific FreeRTOS concept. Explore the code, experiment with it, and observe the behavior of the RTOS.

Examples

Here's a breakdown of the examples, linking FreeRTOS concepts to the code:

Task Management:

    Demonstrates creating and managing tasks with xTaskCreate().

    See examples in:

        freeRTos/experiment2/src/main.cpp (Task creation, basic queue usage)

        freeRTos/resumingTask/src/main.cpp (Suspending and resuming tasks)

        freeRTos/queus/QueuSet/src/main.cpp (Tasks interacting with Queue Sets)

    Key FreeRTOS functions: xTaskCreate(), vTaskDelay(), vTaskSuspend(), vTaskResume()

Inter-Task Communication:

     Illustrates communication between tasks using queues and semaphores.

     See examples in:

         freeRTos/queu1/src/main.cpp (Basic queue send and receive)

         freeRTos/queus/QueuSet/src/main.cpp (Queue Sets for managing multiple queues)

         freeRTos/semaforesIntro/src/main.cpp (Binary semaphore for task synchronization)

         freeRTos/semaphoreCounting/src/main.cpp (Counting semaphore for resource management)

         freeRTos/sendingStructToQueue/src/main.cpp (Sending structured data via queues)

         freeRTos/mutex/src/main.cpp (Mutex for protecting shared resources like Serial output)

    Key FreeRTOS functions: xQueueCreate(), xQueueSend(), xQueueReceive(), xSemaphoreCreateBinary(), xSemaphoreCreateCounting(), xSemaphoreTake(), xSemaphoreGive(), xSemaphoreCreateMutex()

Real-Time Timing:

    Explores FreeRTOS timers for scheduling events.

    See examples in:

         freeRTos/SoftwareTimeManagement/src/main.cpp (One-shot and auto-reload timers)

         freeRTos/Interacting_whit_multiples_timer/src/main.cpp (Multiple interacting timers)

    Key FreeRTOS functions: xTimerCreate(), xTimerStart(), xTimerStop()

Advanced Concepts:

 freeRTos/mesuringTicks/src/main.cpp (Measuring FreeRTOS ticks)

Detailed Example Explanations:

(Here, provide more in-depth explanations for selected examples, drawing from our previous conversations. For instance:)

Queue Sets (freeRTos/queus/QueuSet/src/main.cpp):

     This example demonstrates how a Queue Set allows a task to monitor multiple queues. As discussed, this is more efficient than having a task block on each queue individually. The receiverTask uses xQueueSelectFromSet() to wait until data is available in either queue1 or queue2.

     The senderTask1 and senderTask2 send messages to their respective queues, and the LEDs indicate which task is currently sending data.

Counting Semaphores (freeRTos/semaphoreCounting/src/main.cpp):

    This example shows how counting semaphores can be used to control access to a shared resource. Although the resource here is conceptual (LED control and serial output), the semaphore ensures that only one task modifies the LEDs and prints to the serial monitor at any given time.

    The semaphore is created with a maximum count of 1 and an initial count of 0, effectively making it behave like a mutex. Each task must xSemaphoreTake() the semaphore before accessing the 'resource' and xSemaphoreGive() it afterward.

Sending Structures (freeRTos/sendingStructToQueue/src/main.cpp):

 This example demonstrates how to send complex data between tasks by using structures. The Data_t structure bundles a value and a sender identifier, allowing the receiver task to differentiate between data from Sender1 and Sender2.

Mutex (freeRTos/mutex/src/main.cpp):

    This example highlights the importance of using mutexes to protect shared resources in a multitasking environment. In this specific case, two tasks (`outputTask` instances) attempt to print messages to the Serial monitor. Without a mutex, their outputs could become interleaved and unreadable. The mutex (`xMutex`) ensures that only one task can access `Serial.println()` at a time, by requiring each task to `xSemaphoreTake()` the mutex before printing and `xSemaphoreGive()` it afterward. This demonstrates how mutexes prevent race conditions and ensure data integrity when multiple tasks interact with a common resource.

(Continue providing these detailed explanations for a few key examples)

Contributing

Contributions are welcome! Feel free to submit pull requests for improvements, bug fixes, or new examples.

License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.

Acknowledgments

Special thanks to Jensen Yrkeshögskolan and the FreeRTOS community for the resources and support that made this project possible.
