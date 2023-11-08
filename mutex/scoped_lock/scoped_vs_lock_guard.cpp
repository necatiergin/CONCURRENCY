friend void swap(X& lhs, X& rhs)
{
    if (&lhs == &rhs)
        return;
    std::lock(lhs.m, rhs.m);
    std::lock_guard<std::mutex> lock_a(lhs.m, std::adopt_lock);
    std::lock_guard<std::mutex> lock_b(rhs.m, std::adopt_lock);
    swap(lhs.some_detail, rhs.some_detail);
}

friend void swap(X& lhs, X& rhs)
{
    if (&lhs == &rhs)
        return;
    std::scoped_lock guard(lhs.m, rhs.m);
    swap(lhs.some_detail, rhs.some_detail);
}
