#include <iterator>

template<class InIter>
typename std::iterator_traits<InIter>::value_type reduce(InIter beg, InIter end);

template<class ExecutionPolicy, class ForIter>
typename std::iterator_traits<ForIter>::value_type reduce(ExecutionPolicy&& policy, ForIter beg, ForIter end);

template<class InIter, class T>
T reduce(InIter beg, InIter end, T init);

template<class ExecutionPolicy, class ForIter, class T>
T reduce(ExecutionPolicy&& policy, ForIter beg, ForIter end, T init);

template<class InIter, class T, class BinaryOp>
T reduce(InIter beg, InIter end, T init, BinaryOp binary_op);

template<class ExecutionPolicy, class ForIter, class T, class BinaryOp>
T reduce(ExecutionPolicy&& policy, ForIter beg, ForIter end, T init, BinaryOp binary_op);
