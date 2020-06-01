 
#include <common/inputstream.h>

namespace kayos
{
    namespace common
    {
        
        InputStream::InputStream(InputStreamEventHandler<string>* handler)
            : BasicInputStream<string>::BasicInputStream(handler)
        {
        }
        
    }
}
