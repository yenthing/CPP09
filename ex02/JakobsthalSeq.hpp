#pragma once

template <typename T>
class JakobsthalSeq
{
    public:
        JakobsthalSeq();
        ~JakobsthalSeq();
        JakobsthalSeq(const JakobsthalSeq& other);
        JakobsthalSeq& operator=(const JakobsthalSeq& other);

    private:
        T* _data;
        static const size_t _size = 33;
        static const sizeSeq[_size] = {
            0, 1, 1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461, 
            10923, 21845, 43691, 87381, 174763, 349525, 699051, 1398101, 
            2796203, 5592405, 11184811, 22369621, 44739243, 89478485, 
            178956971, 357913941, 715827883, 1431655765};

        std::size_t generateSequence(std::size_t n);
};