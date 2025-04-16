| Feature                      | `lock_guard` | `unique_lock` | `scoped_lock` | `shared_lock`         |
|-----------------------------|--------------|----------------|----------------|------------------------|
| Timeout support (`try_lock_for`) | ❌           | ✅             | ❌             | ✅                      |
| `defer_lock`, `adopt_lock` support | ❌       | ✅             | ❌             | ✅                      |
| Ownership transfer (movable) | ❌           | ✅             | ❌             | ✅                      |
| Multiple mutex locking       | ❌           | ❌             | ✅             | ❌                      |
| Shared (read) locking        | ❌           | ❌             | ❌             | ✅                      |
| Supported mutex types        | `mutex`      | any mutex type | any mutex type | `shared_mutex`         |
