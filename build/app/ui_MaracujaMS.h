/********************************************************************************
** Form generated from reading UI file 'MaracujaMS.ui'
**
** Created: Wed Apr 3 14:03:03 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MARACUJAMS_H
#define UI_MARACUJAMS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QFormLayout>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_MaracujaMS
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *load_ms;
    QPushButton *save_ms;
    QCustomPlot *view;
    QFrame *line;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *filter_name;
    QLabel *label_2;
    QSpinBox *filter_id;
    QLabel *label_3;
    QLineEdit *filter_values;
    QLabel *label_4;
    QDoubleSpinBox *filter_begin;
    QLabel *label_5;
    QDoubleSpinBox *filter_end;
    QLabel *label_6;
    QLineEdit *filter_sensit;
    QSpacerItem *verticalSpacer;
    QPushButton *add_channel;
    QPushButton *default_channels;
    QSpacerItem *verticalSpacer_4;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_4;
    QComboBox *channel_choice;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QPushButton *filter_load_image;
    QPushButton *filter_show_image;
    QSpacerItem *verticalSpacer_2;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_8;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_7;
    QCheckBox *whitebalance;
    QPushButton *calculation_button;
    QPushButton *saveRGB;
    QSpacerItem *verticalSpacer_3;
    QWidget *tab_4;
    QVBoxLayout *verticalLayout_10;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout_9;
    QPushButton *load_spectrum1_button;
    QPushButton *show_spectrum1_button;
    QGroupBox *groupBox_6;
    QVBoxLayout *verticalLayout_11;
    QPushButton *load_spectrum2_button;
    QPushButton *show_spectrum2_button;
    QPushButton *multiply_spectra_button;
    QPushButton *apply_spectrum2_to_image_button;
    QSpacerItem *verticalSpacer_31;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MaracujaMS)
    {
        if (MaracujaMS->objectName().isEmpty())
            MaracujaMS->setObjectName(QString::fromUtf8("MaracujaMS"));
        MaracujaMS->resize(830, 617);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MaracujaMS->sizePolicy().hasHeightForWidth());
        MaracujaMS->setSizePolicy(sizePolicy);
        MaracujaMS->setMinimumSize(QSize(0, 0));
        MaracujaMS->setMaximumSize(QSize(9999999, 999999));
        MaracujaMS->setFocusPolicy(Qt::ClickFocus);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/maracujams.svg"), QSize(), QIcon::Normal, QIcon::Off);
        MaracujaMS->setWindowIcon(icon);
        centralwidget = new QWidget(MaracujaMS);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(7, -1, -1, -1);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        load_ms = new QPushButton(centralwidget);
        load_ms->setObjectName(QString::fromUtf8("load_ms"));

        horizontalLayout->addWidget(load_ms);

        save_ms = new QPushButton(centralwidget);
        save_ms->setObjectName(QString::fromUtf8("save_ms"));

        horizontalLayout->addWidget(save_ms);


        gridLayout->addLayout(horizontalLayout, 1, 1, 1, 1);

        view = new QCustomPlot(centralwidget);
        view->setObjectName(QString::fromUtf8("view"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(view->sizePolicy().hasHeightForWidth());
        view->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(view, 0, 0, 1, 1);

        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 1, 0, 1, 1);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy2);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout = new QVBoxLayout(tab);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        formLayout = new QFormLayout(groupBox);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label);

        filter_name = new QLineEdit(groupBox);
        filter_name->setObjectName(QString::fromUtf8("filter_name"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(filter_name->sizePolicy().hasHeightForWidth());
        filter_name->setSizePolicy(sizePolicy3);

        formLayout->setWidget(1, QFormLayout::FieldRole, filter_name);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_2);

        filter_id = new QSpinBox(groupBox);
        filter_id->setObjectName(QString::fromUtf8("filter_id"));
        filter_id->setMaximum(99);

        formLayout->setWidget(2, QFormLayout::FieldRole, filter_id);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(5, QFormLayout::LabelRole, label_3);

        filter_values = new QLineEdit(groupBox);
        filter_values->setObjectName(QString::fromUtf8("filter_values"));
        sizePolicy3.setHeightForWidth(filter_values->sizePolicy().hasHeightForWidth());
        filter_values->setSizePolicy(sizePolicy3);

        formLayout->setWidget(5, QFormLayout::FieldRole, filter_values);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        filter_begin = new QDoubleSpinBox(groupBox);
        filter_begin->setObjectName(QString::fromUtf8("filter_begin"));

        formLayout->setWidget(3, QFormLayout::FieldRole, filter_begin);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_5);

        filter_end = new QDoubleSpinBox(groupBox);
        filter_end->setObjectName(QString::fromUtf8("filter_end"));

        formLayout->setWidget(4, QFormLayout::FieldRole, filter_end);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout->setWidget(6, QFormLayout::LabelRole, label_6);

        filter_sensit = new QLineEdit(groupBox);
        filter_sensit->setObjectName(QString::fromUtf8("filter_sensit"));
        sizePolicy3.setHeightForWidth(filter_sensit->sizePolicy().hasHeightForWidth());
        filter_sensit->setSizePolicy(sizePolicy3);

        formLayout->setWidget(6, QFormLayout::FieldRole, filter_sensit);


        verticalLayout->addWidget(groupBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        add_channel = new QPushButton(tab);
        add_channel->setObjectName(QString::fromUtf8("add_channel"));

        verticalLayout->addWidget(add_channel);

        default_channels = new QPushButton(tab);
        default_channels->setObjectName(QString::fromUtf8("default_channels"));

        verticalLayout->addWidget(default_channels);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_3 = new QVBoxLayout(tab_2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        groupBox_3 = new QGroupBox(tab_2);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        verticalLayout_4 = new QVBoxLayout(groupBox_3);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        channel_choice = new QComboBox(groupBox_3);
        channel_choice->setObjectName(QString::fromUtf8("channel_choice"));

        verticalLayout_4->addWidget(channel_choice);


        verticalLayout_3->addWidget(groupBox_3);

        groupBox_2 = new QGroupBox(tab_2);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        filter_load_image = new QPushButton(groupBox_2);
        filter_load_image->setObjectName(QString::fromUtf8("filter_load_image"));

        verticalLayout_2->addWidget(filter_load_image);

        filter_show_image = new QPushButton(groupBox_2);
        filter_show_image->setObjectName(QString::fromUtf8("filter_show_image"));

        verticalLayout_2->addWidget(filter_show_image);


        verticalLayout_3->addWidget(groupBox_2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        verticalLayout_8 = new QVBoxLayout(tab_3);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        groupBox_4 = new QGroupBox(tab_3);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        verticalLayout_7 = new QVBoxLayout(groupBox_4);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        whitebalance = new QCheckBox(groupBox_4);
        whitebalance->setObjectName(QString::fromUtf8("whitebalance"));
        whitebalance->setChecked(true);

        verticalLayout_7->addWidget(whitebalance);

        calculation_button = new QPushButton(groupBox_4);
        calculation_button->setObjectName(QString::fromUtf8("calculation_button"));

        verticalLayout_7->addWidget(calculation_button);

        saveRGB = new QPushButton(groupBox_4);
        saveRGB->setObjectName(QString::fromUtf8("saveRGB"));

        verticalLayout_7->addWidget(saveRGB);


        verticalLayout_8->addWidget(groupBox_4);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_8->addItem(verticalSpacer_3);

        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        verticalLayout_10 = new QVBoxLayout(tab_4);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        groupBox_5 = new QGroupBox(tab_4);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        verticalLayout_9 = new QVBoxLayout(groupBox_5);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        load_spectrum1_button = new QPushButton(groupBox_5);
        load_spectrum1_button->setObjectName(QString::fromUtf8("load_spectrum1_button"));

        verticalLayout_9->addWidget(load_spectrum1_button);

        show_spectrum1_button = new QPushButton(groupBox_5);
        show_spectrum1_button->setObjectName(QString::fromUtf8("show_spectrum1_button"));

        verticalLayout_9->addWidget(show_spectrum1_button);


        verticalLayout_10->addWidget(groupBox_5);

        groupBox_6 = new QGroupBox(tab_4);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        verticalLayout_11 = new QVBoxLayout(groupBox_6);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        load_spectrum2_button = new QPushButton(groupBox_6);
        load_spectrum2_button->setObjectName(QString::fromUtf8("load_spectrum2_button"));

        verticalLayout_11->addWidget(load_spectrum2_button);

        show_spectrum2_button = new QPushButton(groupBox_6);
        show_spectrum2_button->setObjectName(QString::fromUtf8("show_spectrum2_button"));

        verticalLayout_11->addWidget(show_spectrum2_button);


        verticalLayout_10->addWidget(groupBox_6);

        multiply_spectra_button = new QPushButton(tab_4);
        multiply_spectra_button->setObjectName(QString::fromUtf8("multiply_spectra_button"));

        verticalLayout_10->addWidget(multiply_spectra_button);

        apply_spectrum2_to_image_button = new QPushButton(tab_4);
        apply_spectrum2_to_image_button->setObjectName(QString::fromUtf8("apply_spectrum2_to_image_button"));

        verticalLayout_10->addWidget(apply_spectrum2_to_image_button);

        verticalSpacer_31 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_10->addItem(verticalSpacer_31);

        tabWidget->addTab(tab_4, QString());

        gridLayout->addWidget(tabWidget, 0, 1, 1, 1);

        MaracujaMS->setCentralWidget(centralwidget);
        statusBar = new QStatusBar(MaracujaMS);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MaracujaMS->setStatusBar(statusBar);

        retranslateUi(MaracujaMS);

        tabWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MaracujaMS);
    } // setupUi

    void retranslateUi(QMainWindow *MaracujaMS)
    {
        MaracujaMS->setWindowTitle(QApplication::translate("MaracujaMS", "Maracuja Multispectral", 0, QApplication::UnicodeUTF8));
        load_ms->setText(QApplication::translate("MaracujaMS", "Load MS", 0, QApplication::UnicodeUTF8));
        save_ms->setText(QApplication::translate("MaracujaMS", "Save MS", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MaracujaMS", "Filter", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MaracujaMS", "name:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MaracujaMS", "id:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MaracujaMS", "values:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MaracujaMS", "begin:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MaracujaMS", "end:", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MaracujaMS", "sensitivity:", 0, QApplication::UnicodeUTF8));
        add_channel->setText(QApplication::translate("MaracujaMS", "Add Channel", 0, QApplication::UnicodeUTF8));
        default_channels->setText(QApplication::translate("MaracujaMS", "Set the default filters", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MaracujaMS", "Channel", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("MaracujaMS", "Channel", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("MaracujaMS", "Image", 0, QApplication::UnicodeUTF8));
        filter_load_image->setText(QApplication::translate("MaracujaMS", "Load Image", 0, QApplication::UnicodeUTF8));
        filter_show_image->setText(QApplication::translate("MaracujaMS", "Show Image", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MaracujaMS", "Image", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("MaracujaMS", "RGB reconstruction", 0, QApplication::UnicodeUTF8));
        whitebalance->setText(QApplication::translate("MaracujaMS", "white balance", 0, QApplication::UnicodeUTF8));
        calculation_button->setText(QApplication::translate("MaracujaMS", "Calculation", 0, QApplication::UnicodeUTF8));
        saveRGB->setText(QApplication::translate("MaracujaMS", "Save RGB picture", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MaracujaMS", "Calculation", 0, QApplication::UnicodeUTF8));
        groupBox_5->setTitle(QApplication::translate("MaracujaMS", "Spectrum 1", 0, QApplication::UnicodeUTF8));
        load_spectrum1_button->setText(QApplication::translate("MaracujaMS", "Load Spectrum 1", 0, QApplication::UnicodeUTF8));
        show_spectrum1_button->setText(QApplication::translate("MaracujaMS", "Display Spectrum 1", 0, QApplication::UnicodeUTF8));
        groupBox_6->setTitle(QApplication::translate("MaracujaMS", "Spectrum 2", 0, QApplication::UnicodeUTF8));
        load_spectrum2_button->setText(QApplication::translate("MaracujaMS", "Load Spectrum 2", 0, QApplication::UnicodeUTF8));
        show_spectrum2_button->setText(QApplication::translate("MaracujaMS", "Display Spectrum 2", 0, QApplication::UnicodeUTF8));
        multiply_spectra_button->setText(QApplication::translate("MaracujaMS", "Multiply Spectra", 0, QApplication::UnicodeUTF8));
        apply_spectrum2_to_image_button->setText(QApplication::translate("MaracujaMS", "Apply Spectrum 2 to Image", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("MaracujaMS", "Spectrum", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MaracujaMS: public Ui_MaracujaMS {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MARACUJAMS_H
