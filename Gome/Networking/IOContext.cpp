#include "Gome/pch.h"
//
#include "IOContext.h"
//

namespace Networking
{
IOContext::IOContext() : mIOContext(make_unique<io_context>())
{
}

tcp::socket IOContext::CreateSocket()
{
    return tcp::socket(*mIOContext);
}

tcp::resolver IOContext::CreateResolver()
{
    return tcp::resolver(*mIOContext);
}

tcp::acceptor IOContext::CreateAcceptor()
{
    return tcp::acceptor(*mIOContext);
}

io_context &IOContext::operator*()
{
    return *mIOContext;
}

void IOContext::Run()
{
    mIOContext->run();
}

void IOContext::Stop()
{
    mIOContext->stop();
}
} // namespace Networking
