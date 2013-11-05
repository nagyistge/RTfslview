/*  FSLView - 2D/3D Interactive Image Viewer
 
    V Rama Aravind, James Saunders, David Flitney, Mark Jenkinson,

    Christian Beckmann and Stephen Smith, FMRIB Image Analysis Group

    Copyright (C) 2002-2003 University of Oxford  */

/*  CCOPYRIGHT */

/****************************************************************************
** $Id: application.cpp,v 1.146.2.3 2010/04/19 15:46:29 flitney Exp $
**
** Copyright (C) 2002 University of Oxford.  All rights reserved.
**
** FSLView
**
*****************************************************************************/

#if defined(WIN32)
#include <strstream>
//using namespace std;
#endif

#include "viewwidget.h"
#include "orthowidget.h"
#include "lightboxwidget.h"
#include "singlewidget.h"
#include "vtkwidget.h"
#include "timeserieswidget.h"
#include "clusterbrowser.h"
#include "histogramwidget.h"
#include "propertiesdialogimpl.h"
#include "createmaskdialog.h"
#include "application.h"
#include "assistantclient.h"

#include <qaction.h>
#include <qworkspace.h>
#include <qpixmap.h>
#include <qlabel.h>
#include <qpopupmenu.h>
#include <qmenubar.h>
#include <qkeycode.h>
#include <qfiledialog.h>
#include <qstatusbar.h>
#include <qmessagebox.h>
#include <qapplication.h>
#include <qaccel.h>
#include <qwhatsthis.h>
#include <qcheckbox.h>
#include <qtoolbutton.h>
#include <qtooltip.h>

#include "version.h"
#include "tracker.h"
#include "preferences.h"
#include "storage/error.h"
#include "storage/image.h"
#include "fslio/fslio.h"

#include "modelfit.h"

#include <algorithm>
#include <functional>
#include <boost/bind.hpp>


rtfMRIWindow::rtfMRIWindow():
{



}

rtfMRIWindow::~rtfMRIWindow()
{

}
