/***************************************************************************
                          kdevdoc.h  -  description
                             -------------------
    begin                : �� 09 21 05:30:27 CST 2000
    copyright            : (C) 2000 by 
    email                : 
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef KDEVDOC_H
#define KDEVDOC_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif 

// include files for QT
#include <qobject.h>
#include <qstring.h>
#include <qlist.h>

// forward declaration of the Kdev classes
class KdevView;

/**	KdevDoc provides a document object for a document-view model.
  *
  * The KdevDoc class provides a document object that can be used in conjunction with the classes
  * KdevApp and KdevView to create a document-view model for MDI (Multiple Document Interface)
  * Qt 2.1 applications based on QApplication and QMainWindow as main classes and QWorkspace as MDI manager widget.
  * Thereby, the document object is created by the KdevApp instance (and kept in a document list) and contains
  * the document structure with the according methods for manipulating the document
  * data by KdevView objects. Also, KdevDoc contains the methods for serialization of the document data
  * from and to files.
  * @author Source Framework Automatically Generated by KDevelop, (c) The KDevelop Team. 	
  * @version KDevelop version 1.1 code generation
  */
class KdevDoc : public QObject
{
  Q_OBJECT

  friend KdevView;

  public:
    /** Constructor for the fileclass of the application */
    KdevDoc();
    /** Destructor for the fileclass of the application */
    ~KdevDoc();

    /** adds a view to the document which represents the document contents. Usually this is your main view. */
    void addView(KdevView *view);
    /** removes a view from the list of currently connected views */
    void removeView(KdevView *view);
		/** gets called if a view is removed or added */
		void changedViewList();
    /** returns the first view instance */
		KdevView* firstView(){ return pViewList->first(); };
		/** returns true, if the requested view is the last view of the document */
    bool isLastView();
    /** This method gets called when the user is about to close a frame window. It checks, if more than one view
    	* is connected to the document (then the frame can be closed), if pFrame is the last view and the document is
    	* modified, the user gets asked if he wants to save the document.
    	*/
		bool canCloseFrame(KdevView* pFrame);
    /** sets the modified flag for the document after a modifying action on the view connected to the document.*/
    void setModified(bool _m=true){ modified=_m; };
    /** returns if the document is modified or not. Use this to determine if your document needs saving by the user on closing.*/
    bool isModified(){ return modified; };
    /** deletes the document's contents */
    void deleteContents();
    /** initializes the document generally */
    bool newDocument();
    /** closes the acutal document */
    void closeDocument();
    /** loads the document by filename and format and emits the updateViews() signal */
    bool openDocument(const QString &filename, const char *format=0);
    /** saves the document under filename and format.*/	
    bool saveDocument(const QString &filename, const char *format=0);
    /** sets the path to the file connected with the document */
    void setPathName(const QString &name);
    /** returns the pathname of the current document file*/
    const QString& pathName() const;

    /** sets the filename of the document */
    void setTitle(const QString &title);
    /** returns the title of the document */
    const QString& title() const;
	
  public slots:
    /** calls repaint() on all views connected to the document object and is called by the view by which the document has been changed.
     * As this view normally repaints itself, it is excluded from the paintEvent.
     */
    void updateAllViews(KdevView *sender);
 	
  private:
    /** the modified flag of the current document */
    bool modified;
    QString m_title;
    QString m_filename;
    /** the list of the views currently connected to the document */
    QList<KdevView> *pViewList;	

};

#endif // KDEVDOC_H
