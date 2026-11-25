// SPDX-FileCopyrightText: 2026 Reion Wong <reionwong@gmail.com>
// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include "ui/view.h"

#include <string>

namespace properdesktop::ui {
class Label;
}

// The expression being typed, in large text against the right margin; its
// start slides out at the left margin once it is wider than the space
// between them. Not editable: the keypad and the keyboard change it.
class ExpressionField : public properdesktop::ui::View
{
public:
    static constexpr double FontSize = 20;

    ExpressionField();

    const std::string& text() const;
    void setText(const std::string& text);

    properdesktop::ui::Label* label() const { return m_label; }

protected:
    void layout() override;

private:
    // The space between the margins, which clips the label.
    properdesktop::ui::View* m_clip;
    properdesktop::ui::Label* m_label;
};
