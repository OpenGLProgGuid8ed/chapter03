/********************************************************************************
** Form generated from reading UI file 'uniform.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UNIFORM_H
#define UI_UNIFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_uniformClass
{
public:

    void setupUi(QWidget *uniformClass)
    {
        if (uniformClass->objectName().isEmpty())
            uniformClass->setObjectName(QStringLiteral("uniformClass"));
        uniformClass->resize(600, 400);

        retranslateUi(uniformClass);

        QMetaObject::connectSlotsByName(uniformClass);
    } // setupUi

    void retranslateUi(QWidget *uniformClass)
    {
        uniformClass->setWindowTitle(QApplication::translate("uniformClass", "uniform", 0));
    } // retranslateUi

};

namespace Ui {
    class uniformClass: public Ui_uniformClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UNIFORM_H
