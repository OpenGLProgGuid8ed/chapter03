/********************************************************************************
** Form generated from reading UI file 'bsd.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BSD_H
#define UI_BSD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BsdClass
{
public:

    void setupUi(QWidget *BsdClass)
    {
        if (BsdClass->objectName().isEmpty())
            BsdClass->setObjectName(QStringLiteral("BsdClass"));
        BsdClass->resize(600, 400);

        retranslateUi(BsdClass);

        QMetaObject::connectSlotsByName(BsdClass);
    } // setupUi

    void retranslateUi(QWidget *BsdClass)
    {
        BsdClass->setWindowTitle(QApplication::translate("BsdClass", "Bsd", 0));
    } // retranslateUi

};

namespace Ui {
    class BsdClass: public Ui_BsdClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BSD_H
