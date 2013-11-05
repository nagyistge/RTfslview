
#ifndef RFMRIDIALOG_H
#define RTFMRIDIALOG_H

#include "rtfmridialogbase.h"


class rtfMRI;

class rtfMRIDialog : public rtfMRIDialogBase
{
Q_OBJECT

public:

private slots:
   void setInputDir();
   void setNTR();
   void setMaskFile();
   void setBuffer();

private:
  
  void show() {}

 
};

#endif // ATLASOPTIONSDIALOG_H
