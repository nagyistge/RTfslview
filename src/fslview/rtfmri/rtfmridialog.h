#ifndef RTFMRIDIALOG_H
#define RTFMRIDIALOG_H

#include "rtfmridialogbase.h"

class rtfMRIDialog : public rtfMRIDialogBase
{
Q_OBJECT

public:
  rtfMRIDialog(QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = WStyle_Customize | WStyle_NormalBorder|WStyle_Title);
  QString inputdir;
  QString mask;
  QString TimingFile;
  int NTR;
  int BS;

private slots:
  void setInputDir();
  void setMaskFile();
  void setNTR();
  void setBuffer();
  void setTimingFile();
private:
	
	
};
#endif //RTFMRIDIALOG_H
