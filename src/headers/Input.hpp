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

  inline Key mapGLFW(const int glfwKey) {
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
  inline int mapKey(const Key key) {
      switch (key) {
      case Key::NUM0: return GLFW_KEY_0;
      case Key::NUM1: return GLFW_KEY_1;
      case Key::NUM2: return GLFW_KEY_2;
      case Key::NUM3: return GLFW_KEY_3;
      case Key::NUM4: return GLFW_KEY_4;
      case Key::NUM5: return GLFW_KEY_5;
      case Key::NUM6: return GLFW_KEY_6;
      case Key::NUM7: return GLFW_KEY_7;
      case Key::NUM8: return GLFW_KEY_8;
      case Key::NUM9: return GLFW_KEY_9;
      case Key::Q: return GLFW_KEY_Q;
      case Key::W: return GLFW_KEY_W;
      case Key::E: return GLFW_KEY_E;
      case Key::R: return GLFW_KEY_R;
      case Key::T: return GLFW_KEY_T;
      case Key::Z: return GLFW_KEY_Z;
      case Key::U: return GLFW_KEY_U;
      case Key::I: return GLFW_KEY_I;
      case Key::O: return GLFW_KEY_O;
      case Key::P: return GLFW_KEY_P;
      case Key::A: return GLFW_KEY_A;
      case Key::S: return GLFW_KEY_S;
      case Key::D: return GLFW_KEY_D;
      case Key::F: return GLFW_KEY_F;
      case Key::G: return GLFW_KEY_G;
      case Key::H: return GLFW_KEY_H;
      case Key::J: return GLFW_KEY_J;
      case Key::K: return GLFW_KEY_K;
      case Key::L: return GLFW_KEY_L;
      case Key::Y: return GLFW_KEY_Y;
      case Key::X: return GLFW_KEY_X;
      case Key::C: return GLFW_KEY_C;
      case Key::V: return GLFW_KEY_V;
      case Key::B: return GLFW_KEY_B;
      case Key::N: return GLFW_KEY_N;
      case Key::M: return GLFW_KEY_M;
      case Key::COMMA: return GLFW_KEY_COMMA;
      case Key::DOT: return GLFW_KEY_PERIOD;
      case Key::MINUS: return GLFW_KEY_MINUS;
      case Key::ESCAPE: return GLFW_KEY_ESCAPE;
      case Key::UP: return GLFW_KEY_UP;
      case Key::DOWN: return GLFW_KEY_DOWN;
      case Key::LEFT: return GLFW_KEY_LEFT;
      case Key::RIGHT: return GLFW_KEY_RIGHT;
      case Key::LCTRL: return GLFW_KEY_LEFT_CONTROL;
      case Key::LSHIFT: return GLFW_KEY_LEFT_SHIFT;
      case Key::SPACE: return GLFW_KEY_SPACE;
      default: return GLFW_KEY_UNKNOWN;
      }
  }

  class IInput {
  public:
	  ~IInput() = default;

      virtual void update() = 0;

      virtual bool toggleKey(Input::Key key) = 0;
      virtual Input::Action getKeyState(Input::Key key) = 0;
      virtual Input::Action getMouseButtonState(uint8_t button) = 0;
      virtual double getMouseScrollY() = 0;
      virtual double getMouseX() = 0;
      virtual double getMouseY() = 0;
  };


}

#endif //INPUT_HPP
