/********************************************************************************
** Form generated from reading UI file 'xtb.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XTB_H
#define UI_XTB_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_xtbClass
{
public:

    void setupUi(QWidget *xtbClass)
    {
        if (xtbClass->objectName().isEmpty())
            xtbClass->setObjectName(QStringLiteral("xtbClass"));
        xtbClass->resize(600, 400);

        retranslateUi(xtbClass);

        QMetaObject::connectSlotsByName(xtbClass);
    } // setupUi

    void retranslateUi(QWidget *xtbClass)
    {
        xtbClass->setWindowTitle(QApplication::translate("xtbClass", "xtb", 0));
    } // retranslateUi

};

namespace Ui {
    class xtbClass: public Ui_xtbClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XTB_H
