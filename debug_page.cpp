#include "debug_page.h"

DebugPage pDebug;

DebugPage::DebugPage( QObject *parent ) : QObject( parent ) {
}

void DebugPage::debugUpdate() {
	emit qmlPrintDebug(loc_buf);
}

void DebugPage::Print( QString _text ) {
	loc_buf += _text + "\n";
}
