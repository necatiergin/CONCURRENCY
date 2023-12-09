template<class InIter, class T>
constexpr // since C++20
T accumulate(InIter first, InIter last, T init)
{
    for (; first != last; ++first)
        init = std::move(init) + *first; // std::move since C++20

    return init;
}
