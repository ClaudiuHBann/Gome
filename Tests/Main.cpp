#include "Tests/pch.h"
//

#include "Networking/Message/MessageTests.h"
#include "Tests/Networking/TCP/TCPTests.h"

using namespace Networking;
using namespace Message;
using namespace TCP;

int main()
{
    TEST_CLASS(MessageTests);
    TEST_CLASS(TCPTests);

    return 0;
}
