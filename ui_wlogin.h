/********************************************************************************
** Form generated from reading UI file 'wlogin.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WLOGIN_H
#define UI_WLOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WLogin
{
public:

    void setupUi(QWidget *WLogin)
    {
        if (WLogin->objectName().isEmpty())
            WLogin->setObjectName(QStringLiteral("WLogin"));
        WLogin->resize(400, 300);
        QIcon icon;
        icon.addFile(QStringLiteral("../ShElTeR/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        WLogin->setWindowIcon(icon);

        retranslateUi(WLogin);

        QMetaObject::connectSlotsByName(WLogin);
    } // setupUi

    void retranslateUi(QWidget *WLogin)
    {
        WLogin->setWindowTitle(QApplication::translate("WLogin", "\347\231\273\345\275\225", 0));
    } // retranslateUi

};

namespace Ui {
    class WLogin: public Ui_WLogin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WLOGIN_H
