#include <ctime>
#include <atomic>

// payload
struct Message {
	std::clock_t tick;
	const char* str;
	void* param;
};

Message g_payload;
std::atomic g_guard{ 0 };

void SendTestMessage(void* param)
{
    // Copy to shared memory using non-atomic stores.
    g_payload.tick = clock();
    g_payload.str = "TestMessage";
    g_payload.param = param;

    // Perform an atomic write-release to indicate that the message is ready.
    g_guard.store(1, std::memory_order_release);
}


bool TryReceiveMessage(Message& result)
{
    // Perform an atomic read-acquire to check whether the message is ready.
    int ready = g_guard.load(std::memory_order_acquire);

    if (ready != 0)
    {
        // Yes. Copy from shared memory using non-atomic loads.
        result.tick = g_payload.tick;
        result.str = g_payload.str;
        result.param = g_payload.param;

        return true;
    }

    // No.
    return false;
}
