/***************************************************************************
                      kraftview.h  - view of kraft documents
                             -------------------
    begin                : Mit Dez 31 19:24:05 CET 2003
    copyright            : (C) 2003 by Klaas Freitag
    email                : freitag@kde.org
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef KRAFTVIEW_H
#define KRAFTVIEW_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

// include files for Qt
#include <qwidget.h>
#include <qmap.h>
#include <qtabwidget.h>

#include <kdialogbase.h>
#include <kabc/addressee.h>

#include "kraftdoc.h"

/** The KraftView class provides the view widget for the KraftApp instance.
 * The View instance inherits QWidget as a base class and represents
 * the view object of a KTMainWindow. As KraftView is part of the
 * docuement-view model, it needs a reference to the document object
 * connected with it by the KraftApp class to manipulate and display
 * the document structure provided by the KraftDoc class.
 *
 * @author Source Framework Automatically Generated by KDevelop, (c) The KDevelop Team.
 * @version KDevelop version 0.4 code generation
 */
#include <qptrlist.h>

#include "positionviewwidget.h"

class QScrollView;
class DocHeaderEdit;
class DocFooterEdit;
class PositionViewWidget;
class DocPosition;
class QLabel;
class QResizeEvent;
class QSignalMapper;
class QWidgetStack;
class QVBox;
class QSplitter;
class DocOverviewWidget;
class DocPostCard;
class QTimer;
class CatalogSelection;
class AddressSelection;
class KPushButton;

class DocAssistant : public QSplitter
{
  Q_OBJECT

public:
  DocAssistant( QWidget* );

  DocPostCard *postCard();

  bool isFullPreview() {
    return mFullPreview;
  }
public slots:
  void slotShowCatalog();
  void slotShowAddresses();
  void setFullPreview( bool );
  void slotRenderCompleted();

signals:
  void selectPage( int );
  void selectedPosition( DocPosition* );
private:
  DocPostCard *mPostCard;
  CatalogSelection *mCatalogSelection;
  QWidgetStack *mWidgetStack;
  AddressSelection *mAddressSelection;
  QValueList<int> mSplitterSizes;
  bool mFullPreview;
};

class KraftViewScroll : public QScrollView
{
  Q_OBJECT

public:
  KraftViewScroll( QWidget* );
  ~KraftViewScroll() { }

  void viewportResizeEvent( QResizeEvent* );
  void addChild( QWidget *child, int x=0, int y=0 );
  // the removeChild method is not virtual for scrollview, so
  // our own needs to be implemented.
  void kraftRemoveChild( PositionViewWidget *child );

public slots:
  void resizeContents( int, int );

private:
  QPtrList<PositionViewWidget> mWidgetList;
};



class KraftView : public KDialogBase
{
  Q_OBJECT
  public:
    /** Constructor for the main view */
    KraftView(QWidget *parent, const char *name=0);
    /** Destructor for the main view */
    ~KraftView();

    /** returns a pointer to the document connected to the view
    instance. Mind that this method requires a KraftApp instance as a
    parent * widget to get to the window document pointer by calling
    the KraftApp::getDocument() method.
     *
     * @see KraftApp#getDocument
     */
    KraftDoc *getDocument() const;

    /** contains the implementation for printing functionality */
    void print(QPrinter *pPrinter);

    void setup( DocGuardedPtr );


    typedef QMap<DocPositionBase*, PositionViewWidget*> PositionMap;

  public slots:
    void slotSelectAddress( KABC::Addressee contact = KABC::Addressee() );
    void redrawDocument( );
    void slotModifiedPositions();
    void slotModifiedHeader();
    void slotModifiedFooter();
    void slotAddPosition( DocPosition *selectedDP = 0 );
    void slotFocusPosition( PositionViewWidget*,  int );

  protected slots:
    void slotOk();
    void slotCancel();
    void savePositions();
    void redrawDocPositions( );
    void redrawSumBox();
    void done( int );
    void slotMovePositionUp( int );
    void slotMovePositionDown( int );
    void slotDeletePosition( int );
    void slotUnlockPosition( int );
    void slotLockPosition( int );
    void slotPositionModified( int );
    void slotAboutToShow( QWidget* );
  void slotSwitchToPage( int );
  void refreshPostCard( );
  void slotShowCatalog( bool );

  signals:
    void selectPage( int );
    void viewClosed( bool );
    void selectedPosition( DocPosition* );
  private:
    void setupDocumentOverview( QWidget* );
    void setupDocHeaderView();
    void setupPositions();
    void setupFooter();
    void setupTextsView();
    PositionViewWidget *createPositionViewWidget( DocPositionBase*, int );

    QStringList generateLetterHead( KABC::Addressee adr );

    KraftViewScroll *m_positionScroll;
    DocHeaderEdit *m_headerEdit;
    DocFooterEdit *m_footerEdit;

    PositionViewWidgetList mPositionWidgetList;

    QString mContactUid;
    DocGuardedPtr m_doc;
    QSignalMapper *mDeleteMapper;
    QSignalMapper *mMoveUpMapper;
    QSignalMapper *mMoveDownMapper;
    QSignalMapper *mUnlockPositionMapper;
    QSignalMapper *mLockPositionMapper;
    QSignalMapper *mModifiedMapper;

  QLabel *mDetailHeader;
  QString mDetailHeaderTexts[3];
  QSplitter *mCSplit;
  KPushButton *mCatalogToggle;

  QWidget *mSumSpacer;
  QWidgetStack *mViewStack;
  QVBox *mGlobalVBox;
  int mHeaderId;
  DocOverviewWidget *mDocOverview;
  DocAssistant *mAssistant;
  bool mShowAssistantDetail;
};

#endif // KRAFTVIEW_H
