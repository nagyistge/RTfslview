/****************************************************************************
** Form interface generated from reading ui file '/home/rtmri/fsl/src/fslview/src/fslview/rtfmridialogbase.ui'
**
** Created: Wed May 29 15:51:49 2013
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef RTFMRIDIALOGBASE_H
#define RTFMRIDIALOGBASE_H

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QPushButton;
class QLineEdit;
class QLabel;

class rtfMRIDialogBase : public QDialog
{
    Q_OBJECT

public:
    rtfMRIDialogBase( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~rtfMRIDialogBase();

    QPushButton* pushButtonInputDir;
    QLineEdit* dirEdit;
    QLineEdit* lineEditBuffer;
    QLabel* textLabel2_2;
    QPushButton* buttonOk;
    QPushButton* buttonCancel;
    QLabel* textLabel2;
    QPushButton* pushButtonMask;
    QPushButton* pushButtonTF;
    QLineEdit* maskEdit;
    QLineEdit* lineEditTR;
    QLineEdit* tfEdit;

protected:
    QHBoxLayout* Layout1;

protected slots:
    virtual void languageChange();

private slots:
    virtual void setInputDir();
    virtual void runExp();
    virtual void setNTR();
    virtual void setMaskFile();
    virtual void setBuffer();
    virtual void setTimingFile();

};

#endif // RTFMRIDIALOGBASE_H
