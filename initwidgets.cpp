#include "uitestmaker.h"

void ucUiTestMaker::InitMainMenu() {
	QLabel       *  labelVersion;
	QPushButton  *  buttonQueAns;
	QPushButton  *  buttonAnsQue;
	QPushButton  *  buttonMix;
	QPushButton  *  buttonTypeQueAns;
	QPushButton  *  buttonTypeAnsQue;
	QPushButton  *  buttonTypeMix;
	QPushButton  *  buttonNewFile;
	QPushButton  *  buttonExit;
	QPushButton  *  buttonManageDict;
	QLabel       *  labelFreeLine;

	labelVersion       = new QLabel( VERSION );
	buttonQueAns       = new QPushButton( "Question -> Answer" );
	buttonAnsQue       = new QPushButton( "Answer -> Question" );
	buttonMix          = new QPushButton( "Mix" );
	buttonTypeQueAns   = new QPushButton( "Type Question -> Answer" );
	buttonTypeAnsQue   = new QPushButton( "Type Answer -> Question" );
	buttonTypeMix      = new QPushButton( "Type mix" );
	buttonManageDict   = new QPushButton( "Manage dictionary" );
	buttonNewFile      = new QPushButton( "Open new file" );
	buttonExit         = new QPushButton( "Exit" );
	labelFreeLine      = new QLabel( "" );

	labelVersion->setAlignment( Qt::AlignHCenter );
	
	QWidget* widgetMainMenu = new QWidget;
	QVBoxLayout* layoutMainMenu = new QVBoxLayout;
	layoutMainMenu->addWidget( labelVersion );
	layoutMainMenu->addWidget( buttonQueAns );
	layoutMainMenu->addWidget( buttonAnsQue );
	layoutMainMenu->addWidget( buttonMix );
		layoutMainMenu->addWidget( labelFreeLine );
	layoutMainMenu->addWidget( buttonTypeQueAns );
	layoutMainMenu->addWidget( buttonTypeAnsQue );
	layoutMainMenu->addWidget( buttonTypeMix );
		layoutMainMenu->addWidget( labelFreeLine );
	layoutMainMenu->addWidget( buttonManageDict );
	layoutMainMenu->addWidget( buttonNewFile );
	layoutMainMenu->addWidget( buttonExit );
		layoutMainMenu->addWidget( labelFreeLine );
	widgetMainMenu->setLayout( layoutMainMenu );

	connect( buttonQueAns,     SIGNAL( clicked( bool ) ), this, SLOT( SlotQueAns() ) );
	connect( buttonAnsQue,     SIGNAL( clicked( bool ) ), this, SLOT( SlotAnsQue() ) );
	connect( buttonMix,        SIGNAL( clicked( bool ) ), this, SLOT( SlotMix() ) );
	connect( buttonTypeQueAns, SIGNAL( clicked( bool ) ), this, SLOT( SlotTypeQueAns() ) );
	connect( buttonTypeAnsQue, SIGNAL( clicked( bool ) ), this, SLOT( SlotTypeAnsQue() ) );
	connect( buttonTypeMix,    SIGNAL( clicked( bool ) ), this, SLOT( SlotTypeMix() ) );
	connect( buttonManageDict, SIGNAL( clicked( bool ) ), this, SLOT( SlotManageDict() ) );
	connect( buttonNewFile,    SIGNAL( clicked( bool ) ), this, SLOT( SlotNewFile() ) );
	connect( buttonExit,       SIGNAL( clicked( bool ) ), this, SLOT( close() ) );

	stackedWidget->addWidget( widgetMainMenu );
}

void ucUiTestMaker::InitNextWord() {
	QPushButton  *  buttonNext;
	QPushButton  *  buttonMainMenu;
	QPushButton  *  buttonFontIncrease;
	QPushButton  *  buttonFontDecrease;
	QLabel       *  labelFreeLine;

	buttonNext         = new QPushButton( "Next" );
	buttonMainMenu     = new QPushButton( "Main menu" );
	buttonFontDecrease = new QPushButton( "-" );
	buttonFontIncrease = new QPushButton( "+" );
	labelFreeLine      = new QLabel( "" );
	
	QWidget* widgetNextWord = new QWidget;
	QVBoxLayout* layoutNextWord = new QVBoxLayout;
	layoutNextWord->addWidget( outCounter[0] );
		layoutNextWord->addWidget( labelFreeLine );
	layoutNextWord->addWidget( outTextQueAns );
		layoutNextWord->addWidget( labelFreeLine );
	layoutNextWord->addWidget( buttonNext );
	layoutNextWord->addWidget( buttonMainMenu );
	QHBoxLayout* layoutFontSize;
	layoutFontSize = new QHBoxLayout;
	layoutFontSize->addWidget( buttonFontDecrease );
	layoutFontSize->addWidget( buttonFontIncrease );
	layoutNextWord->addLayout( layoutFontSize );
		layoutNextWord->addWidget( labelFreeLine );
	widgetNextWord->setLayout( layoutNextWord );

	connect( buttonNext,         SIGNAL( clicked( bool ) ), this, SLOT( SlotNext() ) );
	connect( buttonMainMenu,     SIGNAL( clicked( bool ) ), this, SLOT( SlotMenu() ) );
	connect( buttonFontIncrease, SIGNAL( clicked( bool ) ), this, SLOT( SlotIncreaseFont() ) );
	connect( buttonFontDecrease, SIGNAL( clicked( bool ) ), this, SLOT( SlotDecreaseFont() ) );

	stackedWidget->addWidget( widgetNextWord );
}

void ucUiTestMaker::InitTypeAns() {
	QPushButton  *  buttonMainMenu;
	QPushButton  *  buttonFontIncrease;
	QPushButton  *  buttonFontDecrease;
	QPushButton  *  buttonSkip;
	QLabel       *  labelFreeLine;

	buttonCheck        = new QPushButton( "Check" );
	buttonSkip         = new QPushButton( "Skip" );
	buttonMainMenu     = new QPushButton( "Main menu" );
	buttonFontDecrease = new QPushButton( "-" );
	buttonFontIncrease = new QPushButton( "+" );
	labelFreeLine      = new QLabel( "" );
	
	QWidget* widgetTypeAnswer = new QWidget;
	QVBoxLayout* layoutTypeAnswer = new QVBoxLayout;
	layoutTypeAnswer->addWidget( outCounter[1] );
		layoutTypeAnswer->addWidget( labelFreeLine );
	layoutTypeAnswer->addWidget( outTextType );
		layoutTypeAnswer->addWidget( labelFreeLine );
	layoutTypeAnswer->addWidget( inTextType );
		layoutTypeAnswer->addWidget( labelFreeLine );
	layoutTypeAnswer->addWidget( buttonCheck );
	layoutTypeAnswer->addWidget( buttonSkip );
	layoutTypeAnswer->addWidget( buttonMainMenu );
	QHBoxLayout* layoutFontSize;
	layoutFontSize = new QHBoxLayout;
	layoutFontSize->addWidget( buttonFontDecrease );
	layoutFontSize->addWidget( buttonFontIncrease );
	layoutTypeAnswer->addLayout( layoutFontSize );
		layoutTypeAnswer->addWidget( labelFreeLine );
	widgetTypeAnswer->setLayout( layoutTypeAnswer );

	connect( buttonCheck,        SIGNAL( clicked( bool ) ), this, SLOT( SlotNext() ) );
	connect( buttonSkip,         SIGNAL( clicked( bool ) ), this, SLOT( SlotSkipWord() ) );
	connect( buttonMainMenu,     SIGNAL( clicked( bool ) ), this, SLOT( SlotMenu() ) );
	connect( buttonFontIncrease, SIGNAL( clicked( bool ) ), this, SLOT( SlotIncreaseFont() ) );
	connect( buttonFontDecrease, SIGNAL( clicked( bool ) ), this, SLOT( SlotDecreaseFont() ) );

	stackedWidget->addWidget( widgetTypeAnswer );
}

void ucUiTestMaker::InitSetupDict() {
	QPushButton  *  buttonAddNewQue;
	QPushButton  *  buttonEditQue;
	QPushButton  *  buttonDeleteQue;
	QPushButton  *  buttonSave;
	QPushButton  *  buttonMainMenu;
	QLabel       *  labelFreeLine;

	buttonAddNewQue    = new QPushButton( "Add" );
	buttonEditQue      = new QPushButton( "Edit" );
	buttonDeleteQue    = new QPushButton( "Delete" );
	buttonSave         = new QPushButton( "Save to file" );
	buttonMainMenu     = new QPushButton( "Main menu" );
	labelFreeLine      = new QLabel( "" );

	QWidget* widgetManageDict = new QWidget;
	QVBoxLayout* layoutManageDict = new QVBoxLayout;
	layoutManageDict->addWidget( outTextDict );
		layoutManageDict->addWidget( labelFreeLine );
	QLabel* lableAns = new QLabel( " - " );
	QHBoxLayout* layoutQue = new QHBoxLayout;
	layoutQue->addWidget( inTextDict[0] );
	layoutQue->addWidget( lableAns );
	layoutQue->addWidget( inTextDict[1] );
	layoutManageDict->addLayout( layoutQue );
		layoutManageDict->addWidget( labelFreeLine );
	layoutManageDict->addWidget( buttonAddNewQue );
	QHBoxLayout* layoutDeleteEdit;
	layoutDeleteEdit = new QHBoxLayout;
	layoutDeleteEdit->addWidget( buttonEditQue );
	layoutDeleteEdit->addWidget( buttonDeleteQue );
	layoutManageDict->addLayout( layoutDeleteEdit );
	layoutManageDict->addWidget( buttonSave );
	layoutManageDict->addWidget( buttonMainMenu );
	widgetManageDict->setLayout( layoutManageDict );

	connect( buttonAddNewQue, SIGNAL( clicked( bool ) ), this, SLOT( SlotAddNewQue() ) );
	connect( buttonEditQue,   SIGNAL( clicked( bool ) ), this, SLOT( SlotEditQue() ) );
	connect( buttonDeleteQue, SIGNAL( clicked( bool ) ), this, SLOT( SlotDeleteQue() ) );
	connect( buttonSave,      SIGNAL( clicked( bool ) ), this, SLOT( SlotSave() ) );
	connect( buttonMainMenu,  SIGNAL( clicked( bool ) ), this, SLOT( SlotMenu() ) );

	stackedWidget->addWidget( widgetManageDict );
}
