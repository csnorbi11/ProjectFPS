#ifndef DEBUGMODE_HPP
#define DEBUGMODE_HPP

enum class InputDebugMode : uint8_t {
    Key=0x01,
    MouseCursor=0x02,
    MouseButton=0x03,
    MouseScroll=0x04,
    None=0x00
};

inline bool operator&(InputDebugMode lhs, InputDebugMode rhs) {
    if (static_cast<uint8_t>(lhs)&static_cast<uint8_t>(rhs))
        return true;
    return false;
}

inline InputDebugMode inputDebugMode=InputDebugMode::None;


#endif //DEBUGMODE_HPP
