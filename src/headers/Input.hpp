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
    RIGHT,LEFT,UP,DOWN
  };

  enum class Modifier : uint8_t {
    SHIFT=1<<1,
    CTRL=1<<2,
    ALT=1<<3,
    NONE=0
  };

  inline Key getKeyGLFW(const int glfwKey) {
    switch (glfwKey) {
      case GLFW_KEY_0: return Input::Key::NUM0;
      case GLFW_KEY_1: return Input::Key::NUM1;
      case GLFW_KEY_2: return Input::Key::NUM2;
      case GLFW_KEY_3: return Input::Key::NUM3;
      case GLFW_KEY_4: return Input::Key::NUM4;
      case GLFW_KEY_5: return Input::Key::NUM5;
      case GLFW_KEY_6: return Input::Key::NUM6;
      case GLFW_KEY_7: return Input::Key::NUM7;
      case GLFW_KEY_8: return Input::Key::NUM8;
      case GLFW_KEY_9: return Input::Key::NUM9;
      case GLFW_KEY_Q: return Input::Key::Q;
      case GLFW_KEY_W: return Input::Key::W;
      case GLFW_KEY_E: return Input::Key::E;
      case GLFW_KEY_R: return Input::Key::R;
      case GLFW_KEY_T: return Input::Key::T;
      case GLFW_KEY_Z: return Input::Key::Z;
      case GLFW_KEY_U: return Input::Key::U;
      case GLFW_KEY_I: return Input::Key::I;
      case GLFW_KEY_O: return Input::Key::O;
      case GLFW_KEY_P: return Input::Key::P;
      case GLFW_KEY_A: return Input::Key::A;
      case GLFW_KEY_S: return Input::Key::S;
      case GLFW_KEY_D: return Input::Key::D;
      case GLFW_KEY_F: return Input::Key::F;
      case GLFW_KEY_G: return Input::Key::G;
      case GLFW_KEY_H: return Input::Key::H;
      case GLFW_KEY_J: return Input::Key::J;
      case GLFW_KEY_K: return Input::Key::K;
      case GLFW_KEY_L: return Input::Key::L;
      case GLFW_KEY_Y: return Input::Key::Y;
      case GLFW_KEY_X: return Input::Key::X;
      case GLFW_KEY_C: return Input::Key::C;
      case GLFW_KEY_V: return Input::Key::V;
      case GLFW_KEY_B: return Input::Key::B;
      case GLFW_KEY_N: return Input::Key::N;
      case GLFW_KEY_M: return Input::Key::M;
      case GLFW_KEY_COMMA: return Input::Key::COMMA;
      case GLFW_KEY_PERIOD: return Input::Key::DOT;
      case GLFW_KEY_MINUS: return Key::MINUS;
      case GLFW_KEY_ESCAPE: return Key::ESCAPE;
      case GLFW_KEY_UP: return Key::UP;
      case GLFW_KEY_DOWN: return Key::DOWN;
      case GLFW_KEY_LEFT: return Key::LEFT;
      case GLFW_KEY_RIGHT: return Key::RIGHT;
      default: return Input::Key::UNKNOWN;
    }
  }



}

#endif //INPUT_HPP
