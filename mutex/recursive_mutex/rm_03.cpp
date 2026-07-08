class Stack {
public:
    void push(int x)
    {
        std::lock_guard<std::mutex> lock{mtx_};
        push_impl(x);
    }

    void push_many(const std::vector<int>& values)
    {
        std::lock_guard<std::mutex> lock{mtx_};

        for (int x : values) {
            push_impl(x);
        }
    }

private:
    void push_impl(int x)
    {
        data_.push_back(x);
    }

    std::vector<int> data_;
    std::mutex mtx_;
};
