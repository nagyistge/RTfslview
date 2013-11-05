#if !defined (RTPROC_H)
#define RTPROC_H
#define QT_THREAD_SUPPORT

#include <stdio.h>
#include <stdlib.h>
#include <qmessagebox.h>
#include <vector>
#include <string>
#include <qthread.h>
#include <qdir.h>
#include <qfileinfo.h>
#include <qmutex.h>
#include <qevent.h>
#include <qmainwindow.h>
#include <qapplication.h>
#include <qiodevice.h>
#include <qstringlist.h>

class QString;
class QDir;

typedef enum
	{
		newFileFound, endRT
	} RTevt;
		

class RTThread : public QThread
{
	public:
		RTThread();
		virtual ~RTThread();
		void run();
		void stop();
		void set_fileread();
	        void set_properties(QMainWindow *,QString, QString, int,int);
		QString get_outputdir();
		QString get_inputdir();
		int NRT;
		
	private:
		QMutex mutex;
		QMainWindow *receiver;
		QString mask;
		QString inputdir;
		QString outputdir;
		QString date;
		QString lastdcm;
		QDir IDir;
                QStringList Design;
		const QFileInfoList *InfoList;		
		bool exp_running;
		bool file_read;
		int nrt_elapsed;
		int buffer;
		int findFiles(QString, QStringList &);//, vector<string> & )QString test;QStringList list;string.append(test); 
		int createDesignFile();
		int writeDesignFile();
		int updateDesignFile();

		//Design file Parameters
		int npts;
		int TR;
		int ndelete;
		float dwell;
		int TE;
		int evs_orig; // must collect or generate EVnames and and generate EV section of design file
		int evs_real; //gotta figure out how you know how many of these there are
		QString featdir;
		QString highres_image;
		// Must figure out how to set up the contrasts here
	
		QStringList EVinfo; // gotta take out the numbers in here
		
		
/*
# EV 1 title
set fmri(evtitle1) "fixation"

# Basic waveform shape (EV 1)
# 0 : Square
# 1 : Sinusoid
# 2 : Custom (1 entry per volume)
# 3 : Custom (3 column format)
# 4 : Interaction
# 10 : Empty (all zeros)
set fmri(shape1) 3

# Convolution (EV 1)
# 0 : None
# 1 : Gaussian
# 2 : Gamma
# 3 : Double-Gamma HRF
# 4 : Gamma basis functions
# 5 : Sine basis functions
# 6 : FIR basis functions
set fmri(convolve1) 2

# Convolve phase (EV 1)
set fmri(convolve_phase1) 0

# Apply temporal filtering (EV 1)
set fmri(tempfilt_yn1) 1

# Add temporal derivative (EV 1)
set fmri(deriv_yn1) 1

# Custom EV file (EV 1)
set fmri(custom1) "/home/dmastrov/Courses/Cognitive_Neuroscience/facial_recognistion_study/data/ana/fixation.txt"

# Gamma sigma (EV 1)
set fmri(gammasigma1) 3

# Gamma delay (EV 1)
set fmri(gammadelay1) 6

# Orthogonalise EV 1 wrt EV 0
set fmri(ortho1.0) 0

# Orthogonalise EV 1 wrt EV 1
set fmri(ortho1.1) 0

# Orthogonalise EV 1 wrt EV 2
set fmri(ortho1.2) 0

# Orthogonalise EV 1 wrt EV 3
set fmri(ortho1.3) 0

# Orthogonalise EV 1 wrt EV 4
set fmri(ortho1.4) 0

# Orthogonalise EV 1 wrt EV 5
set fmri(ortho1.5) 0

# Orthogonalise EV 1 wrt EV 6
set fmri(ortho1.6) 0
*/

		
};



#endif
