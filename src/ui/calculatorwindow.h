// SPDX-FileCopyrightText: 2026 Reion Wong <reionwong@gmail.com>
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include "calculator.h"

#include "base/signal.h"
#include "ui/window.h"

#include <cstdint>
#include <map>
#include <memory>
#include <string>

class ExpressionField;
class HistoryView;
class Keypad;

namespace properdesktop::ui {
class AboutDialog;
class Menu;
struct KeyEvent;
}

// The calculator's window: the history and the expression above the keypad.
class CalculatorWindow
{
public:
    static constexpr double HeaderHeight = 40;
    static constexpr double Width = 280;
    static constexpr double ExpressionHeight = 40;

    // Fixed: the history's visible rows, the expression and the keypad at the width.
    static properdesktop::ui::SizeF size();

    CalculatorWindow();
    ~CalculatorWindow();

    properdesktop::ui::Window& window() { return m_window; }
    Calculator& calculator() { return m_calculator; }

    // What a keypad key does to the expression; Keypad::Backspace for the glyph key.
    void press(const std::string& key);
    // The expression as shown, to the clipboard.
    void copy();
    // Text as if typed: the characters the keypad has, by the same rules; the
    // rest, commas among them, as thousands separators usually are, skipped.
    void paste(const std::string& text);
    void pasteClipboard();
    void clearHistory();

    const std::string& expression() const;
    ExpressionField* expressionField() const;
    HistoryView* history() const;
    Keypad* keypad() const;

private:
    class Root;

    // A keyboard key holds its keypad key down until it is let go.
    bool keyPress(const properdesktop::ui::KeyEvent& event);
    bool keyRelease(const properdesktop::ui::KeyEvent& event);
    void releaseKeys();
    // After the expression or the history changed.
    void update();
    void buildMainMenu();
    void openAbout();
    void retranslate();

    Calculator m_calculator;
    properdesktop::ui::Window m_window;
    Root* m_root;
    std::unique_ptr<properdesktop::ui::Menu> m_mainMenu;
    std::unique_ptr<properdesktop::ui::AboutDialog> m_about;
    // The keypad keys held down from the keyboard, by the keyboard key.
    std::map<uint64_t, std::string> m_heldKeys;
    properdesktop::base::Subscription m_languageChanged;
};
