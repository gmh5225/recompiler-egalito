#include <ostream>
#include <cstring>  // for strlen
#include "deferred.h"

std::ostream &operator << (std::ostream &stream, DeferredValue &dv) {
    dv.writeTo(stream);
    return stream;
}

void DeferredValueCString::writeTo(std::ostream &stream) {
    stream.write(getPtr(), getSize());
}

size_t DeferredStringList::add(const std::string &data, bool withNull) {
    size_t oldIndex = output.length();
    size_t len = data.length();
    if(withNull) len ++;
    output.append(data.c_str(), len);
    return oldIndex;
}

size_t DeferredStringList::add(const char *str, bool withNull) {
    size_t oldIndex = output.length();
    size_t len = std::strlen(str);
    if(withNull) len ++;
    output.append(str, len);
    return oldIndex;
}
