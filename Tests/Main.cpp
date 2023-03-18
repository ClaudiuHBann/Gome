#include "Tests/pch.h"
//

#include "Shared/Networking/Message/MessageTests.h"
#include "Tests/Shared/Networking/TCP/TCPTests.h"

using namespace Shared;
using namespace Networking;
using namespace Message;
using namespace TCP;

int main()
{
    TEST_CLASS(MessageTests);
    TEST_CLASS(TCPTests);

    return 0;
}

/*
    TODO:
         - move the callbacks to the end, DON'T COPY THEM
         - make a class from that message response tuple, or at least an using
         - a better sending/receiving logic (a sent packet waits a ACK and bis)
         - should we work just with shared_ptr (like all callbacks and all) because we need something to work with
   everywhere
         -
*/
