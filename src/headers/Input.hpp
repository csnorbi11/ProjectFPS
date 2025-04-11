#ifndef INPUT_HPP
#define INPUT_HPP

#include <GLFW/glfw3.h>

namespace Input {
  enum class Action {
    PRESSED,
    RELEASED,
    HELD
  };

  enum class Key {
    UNKNOWN,
    NUM1,NUM2,NUM3,NUM4,NUM5,NUM6,NUM7,NUM8,NUM9,NUM0,
    Q,W,E,R,T,Z,U,I,O,P,A,S,D,F,G,H,J,K,L,Y,X,C,V,B,N,M,
    COMMA,DOT,MINUS,
    ESCAPE,ENTER,
    RIGHT,LEFT,UP,DOWN,
    SPACE, LSHIFT, LCTRL
  };

  enum class Modifier : uint8_t {
    SHIFT=1<<1,
    CTRL=1<<2,
    ALT=1<<3,
    NONE=0
  };

  inline Key getKeyGLFW(const int glfwKey) {
    switch (glfwKey) {
      case GLFW_KEY_0: return Key::NUM0;
      case GLFW_KEY_1: return Key::NUM1;
      case GLFW_KEY_2: return Key::NUM2;
      case GLFW_KEY_3: return Key::NUM3;
      case GLFW_KEY_4: return Key::NUM4;
      case GLFW_KEY_5: return Key::NUM5;
      case GLFW_KEY_6: return Key::NUM6;
      case GLFW_KEY_7: return Key::NUM7;
      case GLFW_KEY_8: return Key::NUM8;
      case GLFW_KEY_9: return Key::NUM9;
      case GLFW_KEY_Q: return Key::Q;
      case GLFW_KEY_W: return Key::W;
      case GLFW_KEY_E: return Key::E;
      case GLFW_KEY_R: return Key::R;
      case GLFW_KEY_T: return Key::T;
      case GLFW_KEY_Z: return Key::Z;
      case GLFW_KEY_U: return Key::U;
      case GLFW_KEY_I: return Key::I;
      case GLFW_KEY_O: return Key::O;
      case GLFW_KEY_P: return Key::P;
      case GLFW_KEY_A: return Key::A;
      case GLFW_KEY_S: return Key::S;
      case GLFW_KEY_D: return Key::D;
      case GLFW_KEY_F: return Key::F;
      case GLFW_KEY_G: return Key::G;
      case GLFW_KEY_H: return Key::H;
      case GLFW_KEY_J: return Key::J;
      case GLFW_KEY_K: return Key::K;
      case GLFW_KEY_L: return Key::L;
      case GLFW_KEY_Y: return Key::Y;
      case GLFW_KEY_X: return Key::X;
      case GLFW_KEY_C: return Key::C;
      case GLFW_KEY_V: return Key::V;
      case GLFW_KEY_B: return Key::B;
      case GLFW_KEY_N: return Key::N;
      case GLFW_KEY_M: return Key::M;
      case GLFW_KEY_COMMA: return Key::COMMA;
      case GLFW_KEY_PERIOD: return Key::DOT;
      case GLFW_KEY_MINUS: return Key::MINUS;
      case GLFW_KEY_ESCAPE: return Key::ESCAPE;
      case GLFW_KEY_UP: return Key::UP;
      case GLFW_KEY_DOWN: return Key::DOWN;
      case GLFW_KEY_LEFT: return Key::LEFT;
      case GLFW_KEY_RIGHT: return Key::RIGHT;
      case GLFW_KEY_LEFT_CONTROL: return Key::LCTRL;
      case GLFW_KEY_LEFT_SHIFT: return Key::LSHIFT;
      case GLFW_KEY_SPACE: return Key::SPACE;
      default: return Key::UNKNOWN;
    }
  }



}

#endif //INPUT_HPP
