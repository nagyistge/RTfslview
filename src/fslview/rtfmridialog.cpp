#include "rtfmridialog.h"
#include "applicationwindowbase.h"
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qwidget.h>
#include <vector>

using namespace std;



rtfMRIDialog::rtfMRIDialog(QWidget* p, const char* name , bool modal , WFlags fl ) : rtfMRIDialogBase( p, "RT fMRI Settings", false, fl )
{
}

void rtfMRIDialog::setMaskFile()
{
	QString maskf = QFileDialog::getExistingDirectory( "ROI Mask",this, QDir::currentDirPath() );
	if(!maskf.isEmpty()) {
		mask = maskf;
		maskEdit->setText(mask);		
	}
}

void rtfMRIDialog::setInputDir()
{

	//set Menu Items Stat;
	QString dir = QFileDialog::getExistingDirectory( "Real Time File Directory",this, QDir::currentDirPath() );
	if(!dir.isEmpty()) {
		inputdir = dir;
		dirEdit->setText(dir);		
	}		
	
}

void rtfMRIDialog::setNTR()
{
	NTR= lineEditTR->text().toInt();
}

void rtfMRIDialog::setBuffer()
{
	BS= lineEditBuffer->text().toInt();
}

