/****************************************************************************
** Form interface generated from reading ui file '/home/rtmri/fsl/src/fslview/src/fslview/rtfmridialogbase.ui'
**
** Created: Tue Mar 12 15:55:25 2013
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
class QLabel;
class QLineEdit;

class rtfMRIDialogBase : public QDialog
{
    Q_OBJECT

public:
    rtfMRIDialogBase( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~rtfMRIDialogBase();

    QPushButton* pushButtonInputDir;
    QLabel* textLabel2;
    QLabel* textLabel2_2;
    QPushButton* buttonOk;
    QPushButton* buttonCancel;
    QPushButton* pushButtonMask;
    QLineEdit* lineEditTR;
    QLineEdit* lineEditBuffer;
    QLineEdit* dirEdit;
    QLineEdit* maskEdit;

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

};

#endif // RTFMRIDIALOGBASE_H
