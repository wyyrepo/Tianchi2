#include "tcGuiCommon.h"

void onTextChanged_limitMaxLength(QTextEdit* editor, int maxLength)
{
    QString textContent = editor->toPlainText();
    int length = textContent.count();
    if ( length > maxLength )
    {
        int position = editor->textCursor().position();
        QTextCursor textCursor = editor->textCursor();
        textContent.remove(position - (length - maxLength), length - maxLength);
        editor->setText(textContent);
        textCursor.setPosition(position - (length - maxLength));
        editor->setTextCursor(textCursor);
    }
}