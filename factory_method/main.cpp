//
// Created by Kris Cui on 2/23/22.
//

#include <iostream>
#include <memory>

// object interface
class Button {
 public:
  virtual ~Button() = default;
  virtual void render() = 0;
};

// concrete object #1
class WindowsButton : public Button {
 public:
  void render() override {
    std::cout << "Windows button rendered." << std::endl;
  }
};

// concrete object #2
class UbuntuButton : public Button {
 public:
  void render() override {
    std::cout << "Ubuntu button rendered." << std::endl;
  }
};

// factory class
class Dialog {
 public:
  virtual ~Dialog() = default;
  [[nodiscard]] virtual std::unique_ptr<Button> create_button() const = 0;
};

// concrete factory class #1
class WindowsDialog : public Dialog {
 public:
  // return std::unique_ptr here to transfer object ownership to caller
  [[nodiscard]] std::unique_ptr<Button> create_button() const override {
    return std::make_unique<WindowsButton>();
  }
};

// concrete factory class #2
class UbuntuDialog : public Dialog {
 public:
  [[nodiscard]] std::unique_ptr<Button> create_button() const override {
    return std::make_unique<UbuntuButton>();
  }
};

void client_logic(const Dialog &dialog) {
  // logic specific to different button type is decoupled from client logic
  auto button = dialog.create_button();
  button->render();
}

int main() {
  auto windows_dialog = std::make_unique<WindowsDialog>();
  client_logic(*windows_dialog);

  auto ubuntu_dialog = std::make_unique<UbuntuDialog>();
  client_logic(*ubuntu_dialog);

  return 0;
}