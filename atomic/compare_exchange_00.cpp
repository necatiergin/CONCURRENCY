// from Fedor Picus CppCon talk
//CAS  compare-exchange-swap conceptually

bool compare_exchange_swap_strong(T &expected, T desired)
{
    //Lock is not a real mutex but some form of exclusive access implemented in hardware
    Lock lock; //get exclusive access  
    T temp = value; //value is the value of atomic this->value
    if (temp != expected) {
        expected = temp;
        return false; 
    }
    value = desired;
    return true;
}
