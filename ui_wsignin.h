/********************************************************************************
** Form generated from reading UI file 'wsignin.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WSIGNIN_H
#define UI_WSIGNIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WSignin
{
public:

    void setupUi(QWidget *WSignin)
    {
        if (WSignin->objectName().isEmpty())
            WSignin->setObjectName(QStringLiteral("WSignin"));
        WSignin->resize(400, 300);
        QIcon icon;
        icon.addFile(QStringLiteral("../ShElTeR/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        WSignin->setWindowIcon(icon);

        retranslateUi(WSignin);

        QMetaObject::connectSlotsByName(WSignin);
    } // setupUi

    void retranslateUi(QWidget *WSignin)
    {
        WSignin->setWindowTitle(QApplication::translate("WSignin", "\346\263\250\345\206\214", 0));
    } // retranslateUi

};

namespace Ui {
    class WSignin: public Ui_WSignin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WSIGNIN_H
