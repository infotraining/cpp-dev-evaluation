#include "starter.hpp"
#include <utility>

PacketBuffer::PacketBuffer(size_t size) : size_(size) {
    // TODO: Zaalokuj bufor
}

size_t PacketBuffer::size() const {
    return size_;
}

std::unique_ptr<uint8_t[]> PacketBuffer::releaseBuffer() {
    // TODO: Przekaż własność bufora i zaktualizuj size_
    return nullptr;
}

bool NodeB::hasValidPrev() const {
    // TODO: Sprawdź czy wskaźnik prev wskazuje na istniejący obiekt
    return false;
}
