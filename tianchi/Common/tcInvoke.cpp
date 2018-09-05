#include "tcInvoke.h"

bool TcInvoke::invoke(QGenericArgument val0,
                      QGenericArgument val1,
                      QGenericArgument val2,
                      QGenericArgument val3,
                      QGenericArgument val4,
                      QGenericArgument val5,
                      QGenericArgument val6,
                      QGenericArgument val7,
                      QGenericArgument val8,
                      QGenericArgument val9)
{
    try {
        return m_object != nullptr
                ? m_object->metaObject()->invokeMethod(m_object, m_method,
                                                       val0, val1, val2, val3, val4,
                                                       val5, val6, val7, val8, val9)
                : false;
    }catch(...)
    {
        return false;
    }
}
