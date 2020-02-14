#ifndef DEBUG_PAGE_H
#define DEBUG_PAGE_H

#include <QObject>

class DebugPage : public QObject {
	Q_OBJECT
public:
	explicit DebugPage( QObject *parent = nullptr );
	void Print( QString _text );

signals:
	void qmlPrintDebug( QString text );
public slots:
	void debugUpdate();

private:
	QString loc_buf;
};

extern DebugPage pDebug;

#endif /* DEBUG_PAGE_H */
