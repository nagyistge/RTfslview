#include <dirent.h>
#include <errno.h>
#include "rtproc.h"
#include <iostream>
#include <fstream>


using namespace std;

QString RTThread::get_outputdir()
{
	return outputdir;
}

int RTThread::findFiles (QString mask, QStringList &files)
{
	
	QString dcm= QString("dcm");
	QString dcm2nii = "dcm2nii -e n -d n -f y -g y -i n -m n -n y -p n -r n -v n ";
	QString apply_mask = "fslmaths ";
   	bool looking;
	int sts;
	QString file;
	
	looking = TRUE;
        InfoList =  IDir.entryInfoList();
	QFileInfoListIterator it( *InfoList );
	QFileInfo *fi;  
        
	while (looking)
	{	
		IDir.refresh();
		QFileInfoListIterator it( *InfoList );
		QFileInfo *fi;
	while ( (fi = it.current()) !=0)
	 {
		
		if ((fi->isDir()) && (!(fi->isHidden())) )
		{				
			outputdir = outputdir+fi->fileName()+"_read/";			
			IDir.mkdir(outputdir,TRUE);			
			inputdir = inputdir + fi->fileName()+"/";			
			IDir.cd ( inputdir, TRUE );
			IDir.setCurrent(inputdir);
			InfoList =  IDir.entryInfoList();
			QFileInfoListIterator it( *InfoList );
			QFileInfo *fi;
		}else if (fi->isFile())
		{
			QString bn = fi->baseName();			
			if ((fi->extension() == dcm) && (bn != lastdcm))
			{

				QString fp = fi->filePath();
				sts = system((dcm2nii+fp).data());
				if (sts == 0)		
				{
					if (mask != "")
					{	
						system((apply_mask + bn + " -mul " + mask + " " + bn +"_mask.nii.gz").data());
						file =  bn + "+_mask.nii.gz"; 
						system(("rm " + inputdir + bn + ".nii.gz").data());	
					}else file =  bn +".nii.gz";	
					files.append(file);
					lastdcm = bn;
					
				}
			}
			++it;		
		}
		else if ((fi->isDir()) && (fi->isHidden()) ) ++it;
			
	}
	looking = FALSE;
	}
	return 0;
	//Files = IDir->entryList(QDir::Dirs || QDir::Files, QDir::Time)
}
	
RTThread::RTThread()
{
	
	
}

void RTThread::set_properties(QMainWindow *mw, QString id, QString maskf, int nrt, int bufferl)
{
	
	/*time_t now = time(0);
        struct tm tstruct;
        char buf[80];
        tstruct = *localtime(&now);
        strftime(buf, sizeof(buf),"%Y%m%d/",&tstruct);
  	date =QString(buf);
  	*/
	receiver =  mw;
        inputdir = id;
	lastdcm = "";
	outputdir = inputdir;
	QDir IDir = QDir(inputdir);
	IDir.cd ( id.data(), TRUE );
        IDir.setSorting(QDir::Time);
	IDir.setFilter(QDir::Dirs || QDir::Files);
	IDir.setCurrent(inputdir);

 	InfoList = IDir.entryInfoList();


	mask = maskf;
	NRT = nrt;
	buffer = bufferl;
	file_read = TRUE;
	exp_running = TRUE;
	nrt_elapsed=0;
}

RTThread::~RTThread(){}
	
void RTThread::stop()
{
	mutex.lock();
	exp_running = FALSE;
	nrt_elapsed=0;
	QCustomEvent *event = new QCustomEvent(12346);
	event->setData(new QString("done"));
	QApplication::postEvent(receiver,event);
	mutex.unlock();
		
}
  
void RTThread::set_fileread()
{
		// function called when finish one file
		mutex.lock();
		file_read = TRUE;
	    nrt_elapsed++;
		mutex.unlock();
}
/*  
void RTThread::run()
{
	vector<string> files = vector<string>();
	string lastfile;
	
	mutex.lock();
	while (exp_running && (nrt_elapsed < NRT))
	{
		if (file_read)
		{
			mutex.unlock();
			if (findfiles(inputdir,files) == 0 )
			{					
				qsort(&files[0],files.size(),sizeof(string),cmpr);
				for (unsigned int i=0;i<files.size();i++)
				{	
					if (files[i].find(".nii.gz") != string::npos)
					{
						QString fn = QString(files[i]);
						if (!(files[i] == lastfile))
						{
							mutex.lock();
							file_read = FALSE;
							mutex.unlock();
							QCustomEvent *event = new QCustomEvent(12345);
							event->setData(new QString(fn.data()));
							QApplication::postEvent(receiver,event);
							lastfile = files[i];
							files.erase(files.begin()); 
						}
					}
					usleep(500);
					break;
					
				}
			}		
		}	
		usleep(500);
	}
	
	stop();
	
}

*/
		

void RTThread::run()
{
	QStringList files = QStringList();
	QString lastfile;
	inputdir = inputdir;
	int sts;	
	
	mutex.lock();
	while (exp_running && (nrt_elapsed < NRT))
	{
		if (file_read)
		{
			mutex.unlock();
			sts = findFiles(mask,files);
			//if (sts == 0 )
			//{					
				//qsort(&files[0],files.size(),sizeof(string),cmpr);
				for (unsigned int i=0;i<files.size();i++)
				{	
					if (files[i].contains(".nii.gz",TRUE))
					{						
						QString fn = files[i];
						if (!(fn == lastfile))
						{
							mutex.lock();
							file_read = FALSE;
							mutex.unlock();
							QCustomEvent *event = new QCustomEvent(12345);
							//event->setData(new QString(fn.data()));
							event->setData(new QString(inputdir + fn.data()));
							QApplication::postEvent(receiver,event);
							lastfile = fn;
							files.erase(files.begin()); 
						}
					}
					usleep(500);
					break;
					
				}
			//}
			/*else if (sts == 5)
			{
				inputdir = QString(files[0]);		
				break;				
			}
			*/		
		}	
		usleep(500);
	}
	
	stop();
	
}


		
