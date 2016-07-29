/********************************************************************************
** Form generated from reading UI file 'instancedrender.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INSTANCEDRENDER_H
#define UI_INSTANCEDRENDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InstancedRenderClass
{
public:

    void setupUi(QWidget *InstancedRenderClass)
    {
        if (InstancedRenderClass->objectName().isEmpty())
            InstancedRenderClass->setObjectName(QStringLiteral("InstancedRenderClass"));
        InstancedRenderClass->resize(600, 400);

        retranslateUi(InstancedRenderClass);

        QMetaObject::connectSlotsByName(InstancedRenderClass);
    } // setupUi

    void retranslateUi(QWidget *InstancedRenderClass)
    {
        InstancedRenderClass->setWindowTitle(QApplication::translate("InstancedRenderClass", "InstancedRender", 0));
    } // retranslateUi

};

namespace Ui {
    class InstancedRenderClass: public Ui_InstancedRenderClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INSTANCEDRENDER_H
