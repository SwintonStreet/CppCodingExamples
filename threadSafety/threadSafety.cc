#include<iostream>
#include<thread>

struct s
{
    std::thread th;

    // threads are considered joinable when they have
    // a function to be joined
    s() : th([](){return 0;})
    {}

    auto join ()
    {
        return th.join();
    }

    ~s()
    {
        // if the thread destructor is called while the thread
        // is joinable it will call a terminate
        //
        // other options are to detach the thread or for the struct/class
        // not to own the thread
        if (th.joinable())
        {
            std::cout << "joining the thread\n";
            th.join();
        }
    }
};

int main () {

    std::cout << "Hello World!\n";

    {
        s myThreadObject;
    }

    std::cout << "Hello World!\n";

    return 0;
}
