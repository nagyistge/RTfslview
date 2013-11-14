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
		int NRT;
		
		
	private:
		QMutex mutex;
		QMainWindow *receiver;
		QString inputdir;
		QString outputdir;
		QString date;
		QString mask;
		bool exp_running;
		bool file_read;
		int nrt_elapsed;
		int buffer;
		int findFiles(QString, QStringList &);
		QString lastdcm;
		QDir IDir;
        QStringList Design;
		const QFileInfoList *InfoList;		
		
		
};



#endif
