#include <dirent.h>
#include <errno.h>
#include "rtproc.h"
#include <iostream>
#include <fstream>

using namespace std;

static int cmpr(const void *a, const void *b) { 
 return strcmp(*(char **)a, *(char **)b);
}

/*
int findfiles (string dir, vector<string> &files)
{
   DIR *dp;
   string file;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
	file = string(dirp->d_name);
	if ((file.find(".nii.gz") != string::npos))        
	files.push_back(file);
    }
    closedir(dp);
    return 0;
}
*/

/*
int findfiles (string dir, string mask, vector<string> &files)
{
   DIR *dp;
   string file;
   string dcm2nii = "dcm2nii -e n -d n -f y -g y -i n -m n -n y -p n -r n -v n ";
   string apply_mask = "fslmaths ";
   int sts;
  
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
	file = string(dirp->d_name);	
	/*if ( (dirp->d_type == DT_DIR) && (file != string("..")))
	{
		files.push_back(file);
		sts = 5;
	}else
	*/
/*
	if ( (file.find(".dcm") != string::npos))
	{	
		sts = system((dcm2nii+dir+file).c_str());
		if (sts == 0)		
		{
			file = 	file.substr(0, file.rfind("."));
			if (mask != "")
			{	
			system((apply_mask + dir + file + " -mul " + mask + " " + dir + file +"_mask.nii.gz").c_str());
			file = file + "+_mask.nii.gz"; 
			system(("rm " + dir + file + ".nii.gz").c_str());	
			}else file = file +".nii.gz";	
			files.push_back(file);
		}
	   
	}
	}
    closedir(dp);
    return 0;
}
*/
	
RTThread::RTThread()
{
	
	
}

QString RTThread::get_outputdir()
{
	return outputdir;
}
/*
QString RTThread::get_inputdir()
{
	return inputdir;
}
*/
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
			outputdir = outputdir+fi->fileName()+"/";			
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

void RTThread::set_properties(QMainWindow *mw, QString id, QString maskf, int nrt, int bufferl)
{
	
	/*time_t now = time(0);
        struct tm tstruct;
        char buf[80];
        tstruct = *localtime(&now);
        strftime(buf, sizeof(buf),"%Y%m%d/",&tstruct);
  	date =QString(buf);
  	*/
	inputdir = id;
	lastdcm = "";
	outputdir = inputdir.left(inputdir.length()-1)+"_read/";
	QDir IDir = QDir(inputdir);
	IDir.cd ( id.data(), TRUE );
        IDir.setSorting(QDir::Time);
	IDir.setFilter(QDir::Dirs || QDir::Files);
	IDir.setCurrent(inputdir);

 	InfoList = IDir.entryInfoList();
	receiver =  mw;
        
	mask = maskf;
	NRT = nrt;
	buffer = bufferl;
	file_read = TRUE;
	exp_running = TRUE;
	nrt_elapsed=0;
	npts = 1;
	int sts = createDesignFile();
	
	TR = 2;
	ndelete = 0;
	dwell = 0.7;
	evs_orig = 2;
	evs_real = 4; //??
	featdir = inputdir;
	createDesignFile();
}

int RTThread::updateDesignFile()
{
	npts++;
	int l_npts = 42;  //gonna have to figure out what line this should be or how to automate
	Design[l_npts] = npts;
	int sts = writeDesignFile();
	

}

int RTThread::createDesignFile()
{
     

	     
	//Read template file
     const QString empty = "/home/rtmri/fsl_feat_timing/empty.fsf";


     EVinfo << "# EV 1 title" << "set fmri(evtitle1) " << "# Basic waveform shape (EV 1)" <<
		"# 0 : Square" << "# 1 : Sinusoid" << "# 2 : Custom (1 entry per volume)" << 
		"# 3 : Custom (3 column format)" << "# 4 : Interaction" << "# 10 : Empty (all zeros)" <<
		"set fmri(shape1) 3" << "";


     QFile file(empty);
     if (!file.open(IO_ReadOnly)){
	QMessageBox::information(0,"Error",file.errorString());
	return -1;	
	}

     QTextStream in(&file);
     
     while(!in.atEnd()){
	QString line = in.readLine();
	
	if (line.contains("outputdir", TRUE))
		line.append(outputdir);
	else if (line.contains("tr",TRUE))
		line.append(QString::number(TR));
	else if (line.contains("npts",TRUE))
		line.append(QString::number(npts));
	else if (line.contains("ndelete",TRUE))
		line.append(QString::number(ndelete));
	else if (line.contains("dwell",TRUE))
		line.append(QString::number(dwell));
	else if (line.contains("te", TRUE))
		line.append(QString::number(TE));
	else if (line.contains("evs_orig",TRUE))
		line.append(QString::number(evs_orig));
	else if (line.contains("evs_real",TRUE))
		line.append(QString::number(evs_real)); //see if this should be calculated from evs_orig
	else if (line.contains("feat_files", TRUE))
		line.append(featdir);
	else if (line.contains("highres_files",TRUE))
		line.append(inputdir); //we are going to need a way to identify the high res file so it is not confused with the functional ones
/*	

Well we need to build this part smart based on how many evs there are

	else if(line.contains("evtitle1",TRUE))
		line.append("ev1");  //do you want to add a gui for defining evs
	else if (line.contains("custom1",TRUE))
		line.append(featdir);

And put the contrasts part
*/

	




	Design.append(line);
	}
	
     file.close();

    //Modify Design with input parameters

    int sts = writeDesignFile();
    

}


int RTThread::writeDesignFile()
{

	//Write Design file
    QString filename = inputdir + "Design.fsf";
    QFile file(filename);
    if (file.open(IO_ReadWrite)) {
        QTextStream stream(&file);
	for (unsigned int l=0; l < Design.size(); l++)
	{        
		stream << Design[l] << endl;
	}
    }

   file.close();


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
			sts = findFiles(mask, files);
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
			}*/		
		}	
		usleep(500);
	}
	
	stop();
	
}


		
