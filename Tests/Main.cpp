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
         - a better sending/receiving logic (a sent packet waits a ACK and bis)
         -
*/
